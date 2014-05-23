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

from lxml import etree


class Node:
    """ A node object, which simply stores an (x, y) location and a unique identifier. It
        also holds the degree of the node.
    """

    def __init__(self, uid, x, y, degree):
        """ The constructor for the node object.

            Parameters:
                uid    -- The unique id of the node.
                x      -- The x position of the node.
                y      -- The y position of the node.
                degree -- The degree of this node in the graph.
        """

        self.uid = uid
        self.x = x
        self.y = y
        self.degree = degree


    def __str__(self):
        """ Represent the node as a string. """

        return "Node %s is located at (%s, %s) with degree %s" % (self.uid, self.x, self.y, self.degree)


class Edge:
    """ An edge object, which stores two node ids and the distance between them. """

    def __init__(self, uid1, uid2, distance):
        """ The constructor of the landmark object.

            Parameters:
                uid1     -- The first node's unique identifier.
                uid2     -- The second node's unique identifier.
                distance -- The distance from the first node to the second node.
        """

        self.uid1 = uid1
        self.uid2 = uid2
        self.distance = distance


    def __str__(self):
        """ Represent the edge as a string. """

        return "Node %s is linked to Node %s with distance %s" % (self.uid1, self.uid2, self.distance)


class Landmark:
    """ A landmark object, which stores the (x, y) location and unique identifier of a landmark,
        as well as its name.
    """

    def __init__(self, uid, x, y, name):
        """ The constructor for the landmark object.

            Parameters:
                uid    -- The unique id of the landmark.
                x      -- The x position of the landmark.
                y      -- The y position of the landmark.
                name -- 
        """
        
        self.uid = uid
        self.x = x
        self.y = y
        self.name = name


    def __str__(self):
        """ Represent the landmark as a string. """

        return "Landmark %s is located at (%s, %s) with name %s" % (self.uid, self.x, self.y, self.name)


def convert(tree, interests=list()):
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

    nodes = list()
    edges = list()
    landmarks = list()

    allNodes = list(tree.iter("node"))
    allWays = list(tree.iter("way"))
    
    # Find the list of all highways.
    highways = list()
    for way in allWays:
        for tag in way.iter("tag"):
            if tag.attrib['k'] == "highway":
                highways += way
                break

    # Look at every pair of ways and determine if nodes exist in more than one way. If they
    # do, then these are intersections, which we define as nodes in our graph.
    for i, way1 in enumerate(highways):
        for way2 in highways[(i + 1):]:
            for nd1 in way1.iter("nd"):
                for nd2 in way2.iter("nd"):
                    if nd1.attrib['ref'] == nd2.attrib['ref']:
                        nodes += [nd1.attrib['ref']]

    print("\n".join(nodes))

    # Find the list of all amenities of interest and create landmarks out of them.
    for node in allNodes:
        interest = False
        name = "Unknown"

        for tag in node.iter("tag"):
            if tag.attrib['k'] == "name":
                name = tag.attrib['v']
            if tag.attrib['k'] == "amenity" and tag.attrib['v'] in interests:
                interest = True

        if interest:
            landmarks += [name]

    print("------")
    print("\n".join(landmarks))

    return nodes, edges, landmarks


def save(filePrefix, nodes, edges, landmarks):
    """ Save the nodes, edges, and landmarks as three separate files, given a file prefix.

        Parameters:
            filePrefix -- The prefix to append to the three output files.
            nodes      -- The list of Node objects.
            edges      -- The list of Edge objects.
            landmarks  -- The list of Landmark objects.
    """

    pass


# Only try to run this code if the proper number of arguments were specified.
if __name__ == "__main__":
    if len(sys.argv) >= 3:
        inputFile = sys.argv[1]
        outputFilePrefix = sys.argv[2]

        try:
            with open(inputFile, 'r') as f:
                if len(sys.argv) > 3:
                    nodes, edges, landmarks = convert(etree.parse(f), sys.argv[3:])
                else:
                    nodes, edges, landmarks = convert(etree.parse(f))

                save(outputFilePrefix, nodes, edges, landmarks)
        except IOError:
            print("Failed to open file '%s'." % (inputFile))
