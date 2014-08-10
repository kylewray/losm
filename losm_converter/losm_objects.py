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

        self.uid = int(uid)
        self.x = float(x)
        self.y = float(y)
        self.degree = int(degree)


    def __str__(self):
        """ Represent the node as a string. """

        return "Node %i is located at (%f, %f) with degree %i" % \
            (self.uid, self.x, self.y, self.degree)


    def data(self):
        """ Convert this information into a simple comma-delimited list.

            Returns:
                The string with each element delimited by a comma.
        """

        return ",".join(map(str, [self.uid, self.x, self.y, self.degree]))


class Edge:
    """ An edge object, which stores two node ids, as well as the distance between them, and the
        road's speed limit.
    """

    def __init__(self, uid1, uid2, name, distance, speedLimit, lanes):
        """ The constructor of the landmark object.

            Parameters:
                uid1       -- The first node's unique identifier.
                uid2       -- The second node's unique identifier.
                name       -- The name of the road.
                distance   -- The distance from the first node to the second node.
                speedLimit -- The speed limit for this road.
                lanes      -- The number of lanes on this road.
        """

        self.uid1 = int(uid1)
        self.uid2 = int(uid2)
        self.name = name
        self.distance = float(distance)
        self.speedLimit = int(speedLimit)
        self.lanes = int(lanes)


    def __str__(self):
        """ Represent the edge as a string. """

        return "Edge between Node %i and Node %i has name %s with distance %f and %i lanes" % \
                (self.uid1, self.uid2, self.name, self.distance, self.lanes)


    def data(self):
        """ Convert this information into a simple comma-delimited list.

            Returns:
                The string with each element delimited by a comma.
        """

        return ",".join(map(str, [self.uid1, self.uid2, self.name, self.distance, \
                self.speedLimit, self.lanes]))


class Landmark:
    """ A landmark object, which stores the (x, y) location and unique identifier of a landmark,
        as well as its name.
    """

    def __init__(self, uid, x, y, name):
        """ The constructor for the landmark object.

            Parameters:
                uid  -- The unique id of the landmark.
                x    -- The x position of the landmark.
                y    -- The y position of the landmark.
                name -- The name of the landmark.
        """

        self.uid = int(uid)
        self.x = float(x)
        self.y = float(y)
        self.name = name


    def __str__(self):
        """ Represent the landmark as a string. """

        return "Landmark %i is located at (%f, %f) with name %s" % \
                (self.uid, self.x, self.y, self.name)


    def data(self):
        """ Convert this information into a simple comma-delimited list.

            Returns:
                The string with each element delimited by a comma.
        """

        return ",".join(map(str, [self.uid, self.x, self.y, self.name]))

