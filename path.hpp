#pragma once

#include "graph.hpp"
#include <set>


void CreateNodes(const unsigned char* pMap, const int nMapWidth,
                 const int nMapHeight, const int nStartX, const int nStartY,
                 const int nTargetX, const int nTargetY, Node** pNodes);

void DeleteNodes(const int nNumNodes, Node** pNodes);

/**
 * Find a path from the given start position to the given target.
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
             const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
             int* pOutBuffer, const int nOutBufferSize);
