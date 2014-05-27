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


#ifndef LOSM_NODE_H
#define LOSM_NODE_H


#include <string>

/**
 * A class which stores a Light-OSM node.
 */
class LOSMNode {
public:
	/**
	 * The default constructor for the LOSMNode class, which requires the specification of
	 * each element in the node.
	 * @param uid		The unique identifier for the node.
	 * @param x 		The x coordinate (latitude).
	 * @param y			The y coordinate (longitude).
	 * @param degree	The degree of the node, meaning how many edges involve it.
	 */
	LOSMNode(unsigned int uid, float x, float y, unsigned int degree);

	/**
	 * The default deconstructor for the LOSMNode class.
	 */
	virtual ~LOSMNode();

	/**
	 * Get the unique identifier for the node.
	 * @return The unique identifier for the node.
	 */
	unsigned int get_uid() const;

	/**
	 * Get the x coordinate (latitude).
	 * @return The x-coordinate (latitude).
	 */
	float get_x() const;

	/**
	 * Get the y coordinate (longitude).
	 * @return The y-coordinate (longitude).
	 */
	float get_y() const;

	/**
	 * Get the degree of the node.
	 * @param The degree of the node.
	 */
	unsigned int get_degree() const;

private:
	/**
	 * The unique identifier for the node.
	 */
	unsigned int uid;

	/**
	 * The x coordinate (latitude).
	 */
	float x;

	/**
	 * The y coordinate (longitude).
	 */
	float y;

	/**
	 * The degree of the node, meaning how many edges involve it.
	 */
	unsigned int degree;

};


#endif // LOSM_NODE_H
