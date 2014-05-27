""" The MIT License (MIT)

    Copyright (c) 2014 Kyle Wray

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

import sys
import math

from lxml import etree

from losm_objects import Node, Edge, Landmark


class LOSMConverter:
    """ A class which converts a OSM object to a set of three Light-OSM files. """

    def __init__(self):
        """ The constructor for the LOSMConverter class. """

        self.nodes = list()
        self.edges = list()
        self.landmarks = list()


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


    def haversine(self, lat1, lon1, lat2, lon2, miles=True):
        """ Compute the Haversine distance (in miles, or km) given two lat/lon coordinates.

            Parameters:
                lat1  -- The first latitude.
                lon1  -- The first longitude.
                lat2  -- The second latitude.
                lon2  -- The second longitude.
                miles -- Do the computation in terms of miles, or kilometers.
        """

        dlat = lat2 - lat1
        dlon = lon2 - lon1

        alpha = pow(math.sin(dlat / 2.0), 2) \
            + math.cos(lat1) * math.cos(lat2) * pow(math.sin(dlon / 2.0), 2)
        beta = 2.0 * math.atan2(math.sqrt(alpha), math.sqrt(1.0 - alpha))

        radiusOfEarth = 3961.0
    #     radiusOfEarth = 6373.0

        return radiusOfEarth * beta


    def convert(self, tree, interests=list()):
        """ Convert the XML tree provided into the individual nodes, edges, and landmarks.

            Parameters:
                tree      -- The XML tree of the OSM file.
                interests -- Optionally, specify the list of interests (amenity values) to keep
                    as landmarks.

            Returns:
                nodes     -- The list of Node objects.
                edges     -- The list of Edge objects.
                landmarks -- The list of Landmark objects.
        """

        nodes = dict()
        edges = list()
        landmarks = list()

        allNodes = {node.attrib['id']: node for node in list(tree.iter("node"))}
        allWays = list(tree.iter("way"))

        # Find the list of all highways.
        highways = list()
        for way in allWays:
            for tag in way.iter("tag"):
                if tag.attrib['k'] == "highway":
                    highways += [way]
                    break

        # Look at every pair of ways and determine if nodes exist in more than one way. If they
        # do, then these are intersections, which we define as nodes in our graph.
        for way in highways:
            # First, collect the important tag information from this way. These have default values.
            name = "Unknown"
            speedLimit = 25
            lanes = 2

            for tag in way.iter("tag"):
                if tag.attrib['k'] == "name":
                    name = tag.attrib['v']
                elif tag.attrib['k'] == "maxspeed":
                    # Note: 'maxspeed' value is of the form '<speed> mph'.
                    speedLimit = tag.attrib['v'].split(" ")[0]
                elif tag.attrib['k'] == "lanes":
                    lanes = tag.attrib['v']

            nds = list(way.iter("nd"))
            for i, nd in enumerate(nds):
                uid = nd.attrib['ref']
                node = allNodes[uid]

                try:
                    nodes[uid].degree += 1
                except KeyError:
                    nodes[uid] = Node(uid, node.attrib['lat'], node.attrib['lon'], 2)

                if i > 0:
                    uidPrev = nds[i - 1].attrib['ref']
                    distance = self.haversine(float(nodes[uid].x), float(nodes[uid].y), \
                                         float(nodes[uidPrev].x), float(nodes[uidPrev].y))
                    edges += [Edge(nd.attrib['ref'], nds[i - 1].attrib['ref'], name, distance, speedLimit, lanes)]

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
                newLandmark = Landmark(node.attrib['id'], node.attrib['lon'], node.attrib['lat'], name)
                landmarks += [newLandmark]

        # Finally, store all this in the attributes of the class.
        self.nodes = nodes.values()
        self.edges = edges
        self.landmarks = landmarks


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
