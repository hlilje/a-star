#pragma once

#include "priority_queue.hpp"
#include <unordered_map>
#include <vector>


/*
 * Build the output buffer from the given `vPath` as per specifications.
 */
void BuildOutputBuffer(int* pOutBuffer, const std::vector<int>& vPath);

/*
 * Convert (0-based) map coordinates to the corresponing array node index.
 *
 * @return The corresponding index in `pMap`.
 */
int CoordToNode(const int nX, const int nY, const int nMapWidth);

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
 * Heuristic estimate for cost of distance between nodes `nFrom` and `nTo`.
 *
 * @return: The Manhattan distance between the nodes.
 */
int Heuristic(const int nFrom, const int nTo, const int nMapWidth);

/*
 * Convert the given node index to coordinates on the map.
 *
 * @return A pair of 0-based coordinates corresponding to the map position.
 */
std::pair<int, int> NodeToCoord(const int nNode, const int nMapWidth);

/*
 * Reconstruct the taken path by backtracking.
 *
 * @return: The reconstructed path in reverse.
 */
std::vector<int> ReconstructPath(std::unordered_map<int, int>& mCameFrom,
                                 const int nStart, const int nTarget);
