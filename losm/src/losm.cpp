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


#include "../include/losm.h"
#include "../include/losm_exception.h"

#include <unordered_map>
#include <algorithm>

LOSM::LOSM()
{ }

LOSM::LOSM(std::string nodesFilename, std::string edgesFilename, std::string landmarksFilename)
{
	load(nodesFilename, edgesFilename, landmarksFilename);
}

LOSM::~LOSM()
{
	for (const LOSMNode *node : nodes) {
		delete node;
	}
	nodes.clear();

	for (const LOSMEdge *edge : edges) {
		delete edge;
	}
	edges.clear();

	for (const LOSMLandmark *landmark : landmarks) {
		delete landmark;
	}
	landmarks.clear();
}

void LOSM::load(std::string nodesFilename, std::string edgesFilename, std::string landmarksFilename)
{
	LOSMNode::load(nodesFilename, nodes);

	LOSMEdge::load(edgesFilename, nodes, edges, neighbors);

	LOSMLandmark::load(landmarksFilename, landmarks);
}

const std::vector<const LOSMNode *> &LOSM::get_nodes() const {
	return nodes;
}

const std::vector<const LOSMEdge *> &LOSM::get_edges() const {
	return edges;
}

const std::vector<const LOSMLandmark *> &LOSM::get_landmarks() const {
	return landmarks;
}

void LOSM::get_neighbors(const LOSMNode *node, std::vector<const LOSMNode *> &result) const {
	std::unordered_map<const LOSMNode *, std::vector<const LOSMNode *> >::const_iterator alpha = neighbors.find(node);
	if (alpha == neighbors.end()) {
		throw LOSMException();
	}

	result = alpha->second;
}
