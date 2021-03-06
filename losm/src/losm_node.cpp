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
#include "../include/losm_utilities.h"
#include "../include/losm_exception.h"

#include <iostream>
#include <fstream>

LOSMNode::LOSMNode(unsigned long uid, float x, float y, unsigned int degree)
{
	this->uid = uid;
	this->x = x;
	this->y = y;
	this->degree = degree;
}

LOSMNode::~LOSMNode()
{ }

unsigned long LOSMNode::get_uid() const
{
	return uid;
}

float LOSMNode::get_x() const
{
	return x;
}

float LOSMNode::get_y() const
{
	return y;
}

unsigned int LOSMNode::get_degree() const
{
	return degree;
}

void LOSMNode::load(std::string filename, std::vector<const LOSMNode *> &result)
{
	result.clear();

	// Attempt to open the file.
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Error[LOSMNode::load]: Failed to open the file '" << filename << "'." << std::endl;
		throw LOSMException();
	}

	std::string line;
	int row = 1;
	bool error = false;

	// Iterate over all lines of the file separately.
	while (std::getline(file, line)) {
		std::vector<std::string> items = split_string_by_comma(line);

		// Ensure that the proper number of items exist.
		if (items.size() != 4) {
			std::cerr << "Error[LOSMNode::load]: Incorrect number of comma-delimited items on line " <<
					row << " in file '" << filename << "'." << std::endl;
			error = true;
			break;
		}

		// Attempt to parse the unique identifier.
		unsigned long nodeUID = 0;
		try {
			nodeUID = std::stol(items[0]);
        } catch (const std::exception &err) {
			std::cerr << "Error[LOSMNode::load]: Failed to convert " << items[0] << " to an integer on line " <<
					row << " in file '" << filename << "'." << std::endl;
			error = true;
			break;
        }

		// Attempt to parse the x coordinate.
        float nodeX = 0.0f;
		try {
			nodeX = std::stod(items[1]);
        } catch (const std::exception &err) {
			std::cerr << "Error[LOSMNode::load]: Failed to convert " << items[1] << " to a float on line " <<
					row << " in file '" << filename << "'." << std::endl;
			error = true;
			break;
        }

		// Attempt to parse the y coordinate.
        float nodeY = 0.0f;
		try {
			nodeY = std::stod(items[2]);
        } catch (const std::exception &err) {
			std::cerr << "Error[LOSMNode::load]: Failed to convert " << items[2] << " to a float on line " <<
					row << " in file '" << filename << "'." << std::endl;
			error = true;
			break;
        }

		// Attempt to parse the node's degree.
        unsigned int nodeDegree = 0;
		try {
			nodeDegree = std::stoi(items[3]);
        } catch (const std::exception &err) {
			std::cerr << "Error[LOSMNode::load]: Failed to convert " << items[3] << " to an integer on line " <<
					row << " in file '" << filename << "'." << std::endl;
			error = true;
			break;
        }

        // Now, with the variables loaded, we may create the node and add it.
        result.push_back(new LOSMNode(nodeUID, nodeX, nodeY, nodeDegree));

		row++;
	}

	// Clear all the memory of the nodes created half way through the loading process before the error arose.
	// Then, throw the exception.
	if (error) {
		for (const LOSMNode *node : result) {
			delete node;
		}
		result.clear();
		throw LOSMException();
	}

	file.close();
}
