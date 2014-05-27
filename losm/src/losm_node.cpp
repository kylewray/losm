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


#include "../include/losm_node.h"
#include "../include/losm_exception.h"

#include <fstream>

/**
 * The default constructor for the LOSMNode class, which requires the specification of
 * each element in the node.
 * @param uid		The unique identifier for the node.
 * @param x 		The x coordinate (latitude).
 * @param y			The y coordinate (longitude).
 * @param degree	The degree of the node, meaning how many edges involve it.
 */
LOSMNode::LOSMNode(unsigned int uid, float x, float y, unsigned int degree)
{
	this->uid = uid;
	this->x = x;
	this->y = y;
	this->degree = degree;
}

/**
 * The default deconstructor for the LOSMNode class.
 */
LOSMNode::~LOSMNode()
{ }

/**
 * Get the unique identifier for the node.
 * @return The unique identifier for the node.
 */
unsigned int LOSMNode::get_uid() const
{
	return uid;
}

/**
 * Get the x coordinate (latitude).
 * @return The x-coordinate (latitude).
 */
float LOSMNode::get_x() const
{
	return x;
}

/**
 * Get the y coordinate (longitude).
 * @return The y-coordinate (longitude).
 */
float LOSMNode::get_y() const
{
	return y;
}

/**
 * Get the degree of the node.
 * @return The degree of the node.
 */
unsigned int LOSMNode::get_degree() const
{
	return degree;
}

/**
 * Load a list of LOSMNode objects from a comma-delimited file.
 * @param filename			The name of the file to load.
 * @param result			The resultant list of LOSMNodes. This will be modified.
 * @throws LOSMException	The file failed to load.
 */
void LOSMNode::load(std::string filename, std::vector<const LOSMNode *> &result)
{
	throw LOSMException();
}
