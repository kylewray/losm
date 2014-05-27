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


#include "../include/losm_edge.h"
#include "../include/losm_exception.h"

#include <fstream>

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
LOSMEdge::LOSMEdge(const LOSMNode *n1, const LOSMNode *n2, std::string name, float distance,
		unsigned int speedLimit, unsigned int lanes)
{
	this->n1 = n1;
	this->n2 = n2;
	this->name = name;
	this->distance = distance;
	this->speedLimit = speedLimit;
	this->lanes = lanes;
}

/**
 * The default deconstructor for the LOSMEdge class.
 */
LOSMEdge::~LOSMEdge()
{ }

/**
 * Get the first node.
 * @return The first node.
 */
const LOSMNode *LOSMEdge::get_node_1() const
{
	return n1;
}

/**
 * Get the second node.
 * @return The second node.
 */
const LOSMNode *LOSMEdge::get_node_2() const
{
	return n2;
}

/**
 * Get the name of the edge.
 * @return The name of the edge.
 */
std::string LOSMEdge::get_name() const
{
	return name;
}

/**
 * Get the distance (in miles) of the edge.
 * @return The distance (in miles) of the edge.
 */
float LOSMEdge::get_distance() const
{
	return distance;
}

/**
 * Get the speed limit of the edge.
 * @return The speed limit of the edge.
 */
unsigned int LOSMEdge::get_speed_limit() const
{
	return speedLimit;
}

/**
 * Get the number of lanes in total on the edge.
 * @return The number of lanes in total on the edge.
 */
unsigned int LOSMEdge::get_lanes() const
{
	return lanes;
}

/**
 * Load a list of LOSMEdge objects from a comma-delimited file.
 * @param filename			The name of the file to load.
 * @param nodes				The list of LOSMNode objects to use in order to
 * @param edgesResult		The resultant list of LOSMEdges. This will be modified.
 * @param neighborsResult	The mapping from each LOSMNode to the list of neighboring LOSMNodes.
 * 							This will be modified.
 * @throws LOSMException	The file failed to load, or a uid could not be found.
 */
void LOSMEdge::load(std::string filename, const std::vector<const LOSMNode *> nodes,
		std::vector<const LOSMEdge *> &edgesResult,
		std::unordered_map<const LOSMNode *, std::vector<const LOSMNode *> > &neighborsResult)
{
	throw LOSMException();
}

