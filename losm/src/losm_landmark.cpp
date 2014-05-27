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


#include "../include/losm_landmark.h"
#include "../include/losm_exception.h"

#include <fstream>

/**
 * The default constructor for the LOSMLandmark class, which requires the specification of
 * each element in the landmark.
 * @param uid	The unique identifier for the node.
 * @param x 	The x coordinate (latitude).
 * @param y		The y coordinate (longitude).
 * @param name	The name of the landmark.
 */
LOSMLandmark::LOSMLandmark(unsigned int uid, float x, float y, std::string name)
{
	this->uid = uid;
	this->x = x;
	this->y = y;
	this->name = name;
}

/**
 * The default deconstructor for the LOSMLandmark class.
 */
LOSMLandmark::~LOSMLandmark()
{ }

/**
 * Get the unique identifier for the landmark.
 * @return The unique identifier for the landmark.
 */
unsigned int LOSMLandmark::get_uid() const
{
	return uid;
}

/**
 * Get the x coordinate (latitude).
 * @return The x-coordinate (latitude).
 */
float LOSMLandmark::get_x() const
{
	return x;
}

/**
 * Get the y coordinate (longitude).
 * @return The y-coordinate (longitude).
 */
float LOSMLandmark::get_y() const
{
	return y;
}

/**
 * Get the name of the node.
 * @return The name of the node.
 */
std::string LOSMLandmark::get_name() const
{
	return name;
}

/**
 * Load a list of LOSMLandmark objects from a comma-delimited file.
 * @param filename			The name of the file to load.
 * @param result			The resultant list of LOSMLandmarks. This will be modified.
 * @throws LOSMException	The file failed to load.
 */
void LOSMLandmark::load(std::string filename, std::vector<const LOSMLandmark *> &result)
{
	throw LOSMException();
}
