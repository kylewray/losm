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


#ifndef LOSM_H
#define LOSM_H


#include <string>
#include <vector>
#include <unordered_map>

#include "losm_node.h"
#include "losm_edge.h"
#include "losm_landmark.h"

/**
 * A class which loads and stores Light-OSM objects.
 */
class LOSM {
public:
	/**
	 * The default constructor for the LOSM class.
	 */
	LOSM();

	/**
	 * The constructor for the LOSM class which allows the user to load the files
	 * specified containing nodes, edges, and landmarks.
	 * @param nodesFilename		The nodes' filename.
	 * @param edgesFilename		The edges' filename.
	 * @param landmarksFilename	The landmarks' filename.
	 * @throws LOSMException	One of the files did not exist, or was invalid.
	 */
	LOSM(std::string nodesFilename, std::string edgesFilename, std::string landmarksFilename);

	/**
	 * The default deconstructor for the LOSM class.
	 */
	virtual ~LOSM();

	/**
	 * Load the files specified which contain nodes, edges, and landmarks.
	 * @param nodesFilename		The nodes' filename.
	 * @param edgesFilename		The edges' filename.
	 * @param landmarksFilename	The landmarks' filename.
	 * @throws LOSMException	One of the files did not exist, or was invalid.
	 */
	void load(std::string nodesFilename, std::string edgesFilename, std::string landmarksFilename);

	/**
	 * Get the list of LOSMNodes.
	 * @return The list of LOSMNodes.
	 */
	const std::vector<const LOSMNode *> &get_nodes() const;

	/**
	 * Get the list of LOSMEdges.
	 * @return The list of LOSMEdges.
	 */
	const std::vector<const LOSMEdge *> &get_edges() const;

	/**
	 * Get the list of LOSMLandmarks.
	 * @return The list of LOSMLandmarks.
	 */
	const std::vector<const LOSMLandmark *> &get_landmarks() const;

	/**
	 * Get the neighbors of a node.
	 * @param The node in question.
	 * @param The list of neighbors of the node provided. This will be modified.
	 */
	void get_neighbors(const LOSMNode *node, std::vector<const LOSMNode *> &neighbors) const;

private:
	/**
	 * The list of nodes.
	 */
	std::vector<const LOSMNode *> nodes;

	/**
	 * The list of edges.
	 */
	std::vector<const LOSMEdge *> edges;

	/**
	 * The list of landmarks.
	 */
	std::vector<const LOSMLandmark *> landmarks;

	/**
	 * A mapping of each node to a list of neighboring vertices.
	 */
	std::unordered_map<const LOSMNode *, std::vector<const LOSMNode *> > neighbors;

};


#endif // LOSM_H
