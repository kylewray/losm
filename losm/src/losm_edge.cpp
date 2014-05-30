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
#include "../include/losm_utilities.h"
#include "../include/losm_exception.h"

#include <iostream>
#include <fstream>

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

LOSMEdge::~LOSMEdge()
{ }

const LOSMNode *LOSMEdge::get_node_1() const
{
	return n1;
}

const LOSMNode *LOSMEdge::get_node_2() const
{
	return n2;
}

std::string LOSMEdge::get_name() const
{
	return name;
}

float LOSMEdge::get_distance() const
{
	return distance;
}

unsigned int LOSMEdge::get_speed_limit() const
{
	return speedLimit;
}

unsigned int LOSMEdge::get_lanes() const
{
	return lanes;
}

void LOSMEdge::load(std::string filename, const std::vector<const LOSMNode *> nodes,
		std::vector<const LOSMEdge *> &edgesResult,
		std::unordered_map<const LOSMNode *, std::vector<const LOSMNode *> > &neighborsResult)
{
	edgesResult.clear();

	// Attempt to open the file.
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Error[LOSMEdge::load]: Failed to open the file '" << filename << "'." << std::endl;
		throw LOSMException();
	}

	std::string line;
	int row = 1;
	bool error = false;

	// Iterate over all lines of the file separately.
	while (std::getline(file, line)) {
		std::vector<std::string> items = split_string_by_comma(line);

		// Ensure that the proper number of items exist.
		if (items.size() != 6) {
			std::cerr << "Error[LOSMEdge::load]: Incorrect number of comma-delimited items on line " <<
					row << "in file '" << filename << "'." << std::endl;
			error = true;
			break;
		}

		// Attempt to parse the first node's unique identifier.
		unsigned int edgeUID1 = 0;
		try {
			edgeUID1 = std::stoi(items[0]);
        } catch (const std::invalid_argument &err) {
			std::cerr << "Error[LOSMEdge::load]: Failed to convert " << items[0] << " to an integer on line " <<
					row << "in file '" << filename << "'." << std::endl;
			error = true;
			break;
        }

		// Find the node belonging to the first node's unique identifier.
        const LOSMNode *edgeN1 = nullptr;
        for (const LOSMNode *node : nodes) {
        	if (node->get_uid() == edgeUID1) {
        		edgeN1 = node;
        		break;
        	}
        }

		// Attempt to parse the second node's unique identifier.
		unsigned int edgeUID2 = 0;
		try {
			edgeUID2 = std::stoi(items[1]);
        } catch (const std::invalid_argument &err) {
			std::cerr << "Error[LOSMEdge::load]: Failed to convert " << items[1] << " to an integer on line " <<
					row << "in file '" << filename << "'." << std::endl;
			error = true;
			break;
        }

		// Find the node belonging to the second node's unique identifier.
        const LOSMNode *edgeN2 = nullptr;
        for (const LOSMNode *node : nodes) {
        	if (node->get_uid() == edgeUID2) {
        		edgeN2 = node;
        		break;
        	}
        }

        // The name is simply a string.
        std::string edgeName = items[2];

		// Attempt to parse the edge's distance.
        float edgeDistance = 0.0f;
		try {
			edgeDistance = std::stod(items[3]);
        } catch (const std::invalid_argument &err) {
			std::cerr << "Error[LOSMEdge::load]: Failed to convert " << items[3] << " to a float on line " <<
					row << "in file '" << filename << "'." << std::endl;
			error = true;
			break;
        }

		// Attempt to parse the edge's speed limit.
		unsigned int edgeSpeedLimit = 0;
		try {
			edgeSpeedLimit = std::stoi(items[4]);
        } catch (const std::invalid_argument &err) {
			std::cerr << "Error[LOSMEdge::load]: Failed to convert " << items[4] << " to an integer on line " <<
					row << "in file '" << filename << "'." << std::endl;
			error = true;
			break;
        }

		// Attempt to parse the edge's lanes.
		unsigned int edgeLanes = 0;
		try {
			edgeLanes = std::stoi(items[5]);
        } catch (const std::invalid_argument &err) {
			std::cerr << "Error[LOSMEdge::load]: Failed to convert " << items[5] << " to an integer on line " <<
					row << "in file '" << filename << "'." << std::endl;
			error = true;
			break;
        }

        // Now, with the variables loaded, we may create the node and add it.
        edgesResult.push_back(new LOSMEdge(edgeN1, edgeN2, edgeName, edgeDistance, edgeSpeedLimit, edgeLanes));

        // Add both nodes to each other's neighbors list.
        neighborsResult[edgeN1].push_back(edgeN2);
        neighborsResult[edgeN2].push_back(edgeN1);

		row++;
	}

	// Clear all the memory of the nodes created half way through the loading process before the error arose.
	// Then, throw the exception.
	if (error) {
		for (const LOSMEdge *edge : edgesResult) {
			delete edge;
		}
		edgesResult.clear();
		neighborsResult.clear();
		throw LOSMException();
	}

	file.close();
}

