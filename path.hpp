#pragma once

#include "graph.hpp"
#include "priority_queue.hpp"
#include <algorithm>
#include <unordered_map>
#include <vector>


/*
 * Fill the output buffer with path indices as they appear in `pMap`,
 * excluding the start position.
 */
void BuildOutputBuffer(const int nMapWidth, int* pOutBuffer,
                       const std::vector<Node*>& vPath);

/*
 * Connect all traversable nodes with their traversable neighbours.
 */
void ConnectNeighbours(const int nMapWidth, const int nMapHeight,
                       Node*** pNodes);

/*
 * Create the initial nodes based on input originally given to `FindPath`.
 *
 * @return: Start and target node pair.
 */
std::pair<Node*, Node*> CreateNodes(const unsigned char* pMap,
                                    const int nMapWidth,
                                    const int nMapHeight, const int nStartX,
                                    const int nStartY,
                                    const int nTargetX, const int nTargetY,
                                    Node*** pNodes);

/*
 * Delete all the nodes.
 */
void DeleteNodes(const int nMapWidth, const int nMapHeight, Node*** pNodes);

/*
 * Find a path from the given start position to the given target using A*
 * search. If the resulting path is longer than the output buffer, it is
 * considered a failure.
 *
 * @param nStartX, nStartY:      0-based coordinates of the start position.
 * @param nTargetX, nTargetY:    0-based coordinates of the target position.
 * @param pMap:                  A grid of width `nMapWidth` and height
 *                               `nMapHeight`. The grid is given in row-major
 *                               order of increasing y-coordinate. Traversable
 *                               locations are indicated by 1, and impassible
 *                               locations are indicated by 0. Locations are
 *                               considered to be adjacent horizontally and
 *                               vertically but not diagonally.
 * @param nMapWidth, nMapHeight: Grid size of `pMap`.
 * @param pOutBuffer:            Positions visited in found path, as indices
 *                               for entries in `pMap`. Excludes start position
 *                               and includes the final position.
 * @param nOutBufferSize:        Maximum amount of number entries than can be
 *                               written to `pOutBuffer`.
 * @return:                      The length of the shortest path between Start
 *                               and Target, or −1 if no such path exists.
 */
int FindPath(const int nStartX, const int nStartY,
             const int nTargetX, const int nTargetY,
             const unsigned char* pMap, const int nMapWidth,
             const int nMapHeight, int* pOutBuffer, const int nOutBufferSize);

/*
 * Heuristic estimate for cost of distance between `pFrom` and `pTo`.
 *
 * @return: The Manhattan distance between the nodes.
 */
int Heuristic(const Node* pFrom, const Node* pTo);

/*
 * Reconstruct the taken path by backtracking.
 *
 * @return: The reconstructed path.
 */
std::vector<Node*> ReconstructPath(std::unordered_map<Node*, Node*>& mCameFrom,
                                   Node* pStart, Node* pTarget);
