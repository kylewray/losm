/**
 *  The MIT License (MIT)
 *
 *  Copyright (c) 2014 Kyle Wray
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of
 *  this software and associated documentation files (the "Software"), to deal in
 *  the Software without restriction, including without limitation the rights to
 *  use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 *  the Software, and to permit persons to whom the Software is furnished to do so,
 *  subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 *  FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 *  COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 *  IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 *  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */


#ifndef LOSM_EDGE_H
#define LOSM_EDGE_H


#include <string>

#include "losm_node.h"

/**
 * A class which stores a Light-OSM edge.
 */
class LOSMEdge {
public:
	/**
	 * The default constructor for the LOSMEdge class, which requires the specification of
	 * each element in the edge.
	 * @param n1			The edge's first node.
	 * @param n2			The edge's second node.
	 * @param name			The name of the edge, meaning the stree name.
	 * @param distance		The distance of this edge (in miles).
	 * @param speedLimit	The speed limit of this edge.
	 * @param lanes			The total number of lanes (all directions).
	 */
	LOSMEdge(const LOSMNode *n1, const LOSMNode *n2, std::string name, float distance,
			unsigned int speedLimit, unsigned int lanes);

	/**
	 * The default deconstructor for the LOSMEdge class.
	 */
	virtual ~LOSMEdge();

	/**
	 * Get the first node.
	 * @return The first node.
	 */
	const LOSMNode *get_node_1() const;

	/**
	 * Get the second node.
	 * @return The second node.
	 */
	const LOSMNode *get_node_2() const;

	/**
	 * Get the name of the edge.
	 * @return The name of the edge.
	 */
	std::string get_name() const;

	/**
	 * Get the distance (in miles) of the edge.
	 * @return The distance (in miles) of the edge.
	 */
	float get_distance() const;

	/**
	 * Get the speed limit of the edge.
	 * @return The speed limit of the edge.
	 */
	unsigned int get_speed_limit() const;

	/**
	 * Get the number of lanes in total on the edge.
	 * @return The number of lanes in total on the edge.
	 */
	unsigned int get_lanes() const;

private:
	/**
	 * The first node.
	 */
	const LOSMNode *n1;

	/**
	 * The second node.
	 */
	const LOSMNode *n2;

	/**
	 * The name of the edge (i.e., street name).
	 */
	std::string name;

	/**
	 * The distance (in miles) of the edge.
	 */
	float distance;

	/**
	 * The speed limit of the edge.
	 */
	unsigned int speedLimit;

	/**
	 * The number of lanes in total on the edge.
	 */
	unsigned int lanes;

};


#endif // LOSM_EDGE_H
