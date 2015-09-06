""" The MIT License (MIT)

    Copyright (c) 2015 Kyle Hollins Wray, University of Massachusetts

    Permission is hereby granted, free of charge, to any person obtaining a copy of
    this software and associated documentation files (the "Software"), to deal in
    the Software without restriction, including without limitation the rights to
    use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
    the Software, and to permit persons to whom the Software is furnished to do so,
    subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
    FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
    COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
    IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
    CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
"""

from __future__ import print_function

import os
import sys

thisFilePath = os.path.dirname(os.path.realpath(__file__))
sys.path.append(thisFilePath)

import math
import csv

from lxml import etree

from losm_objects import Node, Edge, Landmark


class LOSMConverter(object):
    """ A class which converts a OSM object to a set of three Light-OSM files. """

    def __init__(self, filePrefix=None):
        """ The constructor for the LOSMConverter class. Optionally, load the
            LOSM files with the corresponding file prefix provided.
            
            Parameters:
                filePrefix -- The prefix for the three LOSM files.
        """

        self.nodes = list()
        self.edges = list()
        self.landmarks = list()

        if filePrefix != None:
            self.load(filePrefix)


    def open(self, inputFile, interests=list()):
        """ Just open an input file and store the data in nodes, edges, and landmarks.

            Parameters:
                inputFile -- The input OSM file.
                interests -- The list of interests (landmark types).
        """

        try:
            with open(inputFile, 'r') as f:
                self.convert(etree.parse(f), interests)
        except IOError:
            print("Failed to open file '%s'." % (inputFile))
            raise Exception()


    def execute(self, inputFile, outputFilePrefix, interests):
        """ Execute the entire process with the parameters specified.

            Parameters:
                inputFile        -- The input OSM file.
                outputFilePrefix -- The desired output files' prefix.
                interests        -- The list of interests (landmark types).
        """

        try:
            with open(inputFile, 'r') as f:
                self.convert(etree.parse(f), interests)
                self.save(outputFilePrefix)
        except IOError:
            print("Failed to open file '%s'." % (inputFile))
            raise Exception()


    def haversine(self, lat1, lon1, lat2, lon2, miles=True):
        """ Compute the Haversine distance (in miles, or km) given two lat/lon coordinates.

            Parameters:
                lat1  -- The first latitude in degrees.
                lon1  -- The first longitude in degrees.
                lat2  -- The second latitude in degress.
                lon2  -- The second longitude in degrees.
                miles -- Do the computation in terms of miles, or kilometers.
        """

        radiusOfEarthInMiles = 3959.0

        # Convert everything from degrees to radians.
        lat1, lon1, lat2, lon2 = map(math.radians, [lat1, lon1, lat2, lon2])

        # Haversine formula.
        dlat = lat2 - lat1
        dlon = lon2 - lon1

        alpha = math.sin(dlat / 2.0) ** 2 + math.cos(lat1) * math.cos(lat2) * math.sin(dlon / 2.0) ** 2
        beta = 2.0 * math.asin(math.sqrt(alpha))

        distanceInMiles = radiusOfEarthInMiles * beta

        return distanceInMiles


    def convert(self, tree, interests=list()):
        """ Convert the XML tree provided into the individual nodes, edges, and landmarks.

            Parameters:
                tree      -- The XML tree of the OSM file.
                interests -- Optionally, specify the list of interests (amenity values) to keep
                             as landmarks.
        """

        nodes = dict()
        edges = list()
        landmarks = list()

        allNodes = {node.attrib['id']: node for node in list(tree.iter("node"))}
        allWays = list(tree.iter("way"))

        # Both a list of valid highway types and a mapping from them to
        # their default speed limits.
        highwayTypes = {"motorway": 65, "motorway_link": 50,
                        "trunk": 65, "trunk_link": 50,
                        "primary": 65, "primary_link": 50,
                        "secondary": 50,
                        "tertiary": 40,
                        "unclassified": 25,
                        "residential": 25}

        # Find the list of all highways.
        highways = list()
        for way in allWays:
            for tag in way.iter("tag"):
                if tag.attrib['k'] == "highway" and \
                        tag.attrib['v'] in set(highwayTypes.keys()):
                    highways += [way]
                    break

        # Look at every pair of ways and determine if nodes exist in more than one way.
        # If they do, then these are intersections, which we define as nodes in our graph.
        for way in highways:
            # First, collect the important tag information from this way. These
            # have default values.
            name = "Unknown"
            speedLimit = None
            lanes = 2
            highwayType = None

            for tag in way.iter("tag"):
                if tag.attrib['k'] == "name":
                    name = tag.attrib['v']
                elif tag.attrib['k'] == "maxspeed":
                    # Note: 'maxspeed' value is of the form '<speed> mph'.
                    speedLimit = tag.attrib['v'].split(" ")[0]
                elif tag.attrib['k'] == "lanes":
                    lanes = tag.attrib['v']
                elif tag.attrib['k'] == "highway":
                    highwayType = tag.attrib['v']

            if speedLimit == None:
                #try:
                speedLimit = highwayTypes[highwayType]
                #except KeyError:
                #    speedLimit = 25

                #if highwayType == "motorway":
                #    speedLimit = 65
                #elif highwayType == "trunk":
                #    speedLimit = 65
                #elif highwayType == "primary":
                #    speedLimit = 65
                #elif highwayType == "secondary":
                #    speedLimit = 50
                #elif highwayType == "tertiary":
                #    speedLimit = 40
                #else:
                #    speedLimit = 25

            nds = list(way.iter("nd"))
            for i, nd in enumerate(nds):
                uid = nd.attrib['ref']
                node = allNodes[uid]

                try:
                    nodes[uid]
                except KeyError:
                    nodes[uid] = Node(uid, node.attrib['lat'], node.attrib['lon'], 0)

                if i > 0:
                    uidPrev = nds[i - 1].attrib['ref']

                    distance = self.haversine(float(nodes[uid].x), float(nodes[uid].y),
                                        float(nodes[uidPrev].x), float(nodes[uidPrev].y))
                    edges += [Edge(uid, nds[i - 1].attrib['ref'], name,
                                        distance, speedLimit, lanes)]

        # Find the list of all amenities of interest and create landmarks out of them.
        for node in allNodes.values():
            interest = False
            name = "Unknown"

            for tag in node.iter("tag"):
                if tag.attrib['k'] == "name":
                    name = tag.attrib['v']
                if tag.attrib['k'] == "amenity" and tag.attrib['v'] in interests:
                    interest = True

            if interest:
                newLandmark = Landmark(node.attrib['id'], node.attrib['lat'],
                                node.attrib['lon'], name)
                landmarks += [newLandmark]

        # Compute the degree of all the nodes.
        for edge in edges:
            nodes[str(edge.uid1)].degree += 1
            nodes[str(edge.uid2)].degree += 1

        # Finally, store all this in the attributes of the class.
        self.nodes = list(nodes.values())
        self.edges = edges
        self.landmarks = landmarks


    def simplified_graph(self):
        """ Return the simplified graph by removing all but the intersection nodes and the corresponding edges.

            Returns:
                nodes   --  A list of nodes in the new graph (Node objects).
                edges   --  A list of edges in the new graph (Edge objects).
        """

        nodes = set()
        edges = list()

        getNode = {node.uid: node for node in self.nodes}
        getEdge1 = {edge.uid1: edge for edge in self.edges}
        getEdge2 = {edge.uid2: edge for edge in self.edges}

        simpleEdgesVisited = list()

        # From this starting node, expand outwards following each outgoing edge until it reaches
        # another intersection node.
        for node in self.nodes:
            if node.degree == 2:
                continue

            nodes |= {node}

            # Check all outgoing edges and find the next intersection node.
            outgoingEdges = [edge for edge in self.edges if edge.uid1 == node.uid or edge.uid2 == node.uid]

            for edge in outgoingEdges:
                nodePrime = None
                if edge.uid1 == node.uid:
                    nodePrime = getNode[edge.uid2]
                elif edge.uid2 == node.uid:
                    nodePrime = getNode[edge.uid1]

                visitedNodes = [node.uid, nodePrime.uid]

                distance = edge.distance

                while nodePrime.degree == 2:
                    edgePrime = None
                    edgePrimeCandidates = [e for e in self.edges \
                                            if e.uid1 == nodePrime.uid or \
                                               e.uid2 == nodePrime.uid]

                    for edgePrimeCandidate in edgePrimeCandidates:
                        if edgePrimeCandidate.uid1 != nodePrime.uid and \
                                edgePrimeCandidate.uid1 not in visitedNodes:
                            edgePrime = edgePrimeCandidate
                            nodePrime = getNode[edgePrime.uid1]
                            break
                        elif edgePrimeCandidate.uid2 != nodePrime.uid and \
                                edgePrimeCandidate.uid2 not in visitedNodes:
                            edgePrime = edgePrimeCandidate
                            nodePrime = getNode[edgePrime.uid2]
                            break

                    if edgePrime is None:
                        print("Warning: Strange roads in the map detected; removing them.")
                        break

                    distance += edgePrime.distance
                    visitedNodes += [nodePrime.uid]

                # Add a new edge which is the link between these new nodes, summing the distance traversed.
                # Also, make sure this edge has not already been added by following the path from
                # the other direction.
                if (node.uid, nodePrime.uid) not in simpleEdgesVisited:
                    edges += [Edge(node.uid, nodePrime.uid, edge.name, distance, edge.speedLimit, edge.lanes)]
                    simpleEdgesVisited += [(node.uid, nodePrime.uid), (nodePrime.uid, node.uid)]

        return list(nodes), edges


    def save(self, filePrefix):
        """ Save the nodes, edges, and landmarks as three separate files, given a file prefix.

            Parameters:
                filePrefix -- The prefix to append to the three output files.
        """

        with open(filePrefix + "nodes.dat", "w") as f:
            for node in self.nodes:
                f.write(node.data() + "\n")

        with open(filePrefix + "edges.dat", "w") as f:
            for edge in self.edges:
                f.write(edge.data() + "\n")

        with open(filePrefix + "landmarks.dat", "w") as f:
            for landmark in self.landmarks:
                f.write(landmark.data() + "\n")


    def load(self, filePrefix):
        """ Load the nodes, edges, and landmarks from three separate files, given a file prefix.

            Parameters:
                filePrefix -- The prefix to append to the three input files.
        """

        self.nodes = list()
        self.edges = list()
        self.landmarks = list()

        with open(filePrefix + "nodes.dat", "r") as f:
            reader = csv.reader(f, delimiter=',')
            for row in reader:
                if len(row) != 4:
                    print("Failed to parse 4 arguments for node line: '" + ",".join(row) + "'.")
                    break

                node = Node(row[0], row[1], row[2], row[3])
                self.nodes.append(node)

        with open(filePrefix + "edges.dat", "r") as f:
            reader = csv.reader(f, delimiter=',')
            for row in reader:
                if len(row) != 6:
                    print("Failed to parse 6 arguments for edge line: '" + ",".join(row) + "'.")
                    break

                edge = Edge(row[0], row[1], row[2], row[3], row[4], row[5])
                self.edges.append(edge)

        with open(filePrefix + "landmarks.dat", "r") as f:
            reader = csv.reader(f, delimiter=',')
            for row in reader:
                if len(row) != 4:
                    print("Failed to parse 4 arguments for landmark line: '" + ",".join(row) + "'.")
                    break

                landmark = Landmark(row[0], row[1], row[2], row[3])
                self.landmarks.append(landmark)


    def __str__(self):
        """ Convert the data to a string.

            Returns:
                The string of the nodes, edges, and landmarks.
        """

        result = "------ NODES ------\n"
        result += "\n".join(map(str, self.nodes))
        result += "\n------ EDGES ------\n"
        result += "\n".join(map(str, self.edges))
        result += "\n------ LANDMARKS ------\n"
        result += "\n".join(map(str, self.landmarks))
        result += "\n------------\n"

        return result


# If parameters were given to the Python script, then the user wants to run
# this code with a particular input file.
if __name__ == "__main__":
    if len(sys.argv) >= 3:
        inputFile = sys.argv[1]
        outputFilePrefix = sys.argv[2]
        interests = sys.argv[3:]

        osmConverter = LOSMConverter()
        osmConverter.execute(inputFile, outputFilePrefix, interests)
        print(osmConverter)
    else:
        print("python losm_converter.py " + \
            "<input file> <output prefix for files> " + \
            "<optional list of landmarks>")

