#ifndef PATH_HPP
#define PATH_HPP

#include <unordered_map>


int CoordToNode( const int nX, const int nY, const int nMapWidth );

std::pair<int, int> NodeToCoord( const int nNode, const int nMapWidth );

int Heuristic( const int nFromX, const int nFromY, const int nToX, const int nToY );

int ReconstructPath( const int nStart, const int nTarget, const int nOutBufferSize,
                     int* pOutBuffer, std::unordered_map<int, int>& CameFrom );

/*
 * Finds a path from the given start position to the given target using A*
 * search. If the resulting path is longer than the output buffer, as many
 * nodes as possible will be stored.
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
int FindPath( const int nStartX, const int nStartY,
              const int nTargetX, const int nTargetY,
              const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
              int* pOutBuffer, const int nOutBufferSize );

#endif // PATH_HPP
