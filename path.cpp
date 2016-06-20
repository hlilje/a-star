#include "path.hpp"
#include <cmath>
#include <queue>
#include <vector>

using PQElement = std::pair<int, int>; // <prio, value>


int CoordToNode( const int nX, const int nY, const int nMapWidth )
{
    return nY * nMapWidth + nX;
}

void NodeToCoord( const int nNode, int* const pCoord, const int nMapWidth )
{
    pCoord[0] = nNode % nMapWidth;
    pCoord[1] = nNode / nMapWidth;
}

int Heuristic( const int nFromX, const int nFromY, const int nToX, const int nToY )
{
    return std::abs( nFromX - nToX ) + std::abs( nFromY - nToY );
}

int ReconstructPath( const int nStart, const int nTarget, const int nOutBufferSize,
                     int* const pOutBuffer, std::unordered_map<int, int>& CameFrom )
{
    std::vector<int> Path;
    int nCurrent = nTarget;
    Path.push_back( nCurrent );

    while ( nCurrent != nStart )
    {
        nCurrent = CameFrom[nCurrent];
        Path.push_back( nCurrent );
    }

    const int nPathLength = Path.size() - 1; // Excluding start node

    for ( int i = nPathLength - 1, j = 0; ( i >= 0 ) && ( j < nOutBufferSize );
          --i, ++j )
    {
        pOutBuffer[j] = Path[i];
    }

    return nPathLength;
}

int FindPath( const int nStartX, const int nStartY,
              const int nTargetX, const int nTargetY,
              const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
              int* pOutBuffer, const int nOutBufferSize )
{
    if ( ( nStartX == nTargetX ) && ( nStartY == nTargetY ) )
    {
        return 0;
    }

    std::priority_queue< PQElement, std::vector<PQElement>,
                         std::greater<PQElement> > Fringe;
    std::unordered_map<int, int> CameFrom;
    std::unordered_map<int, int> Cost;

    const int nStart  = CoordToNode( nStartX, nStartY, nMapWidth );
    const int nTarget = CoordToNode( nTargetX, nTargetY, nMapWidth );

    Fringe.emplace( 0, nStart );
    Cost[nStart] = 0;

    const int pMod[8] = { -1, 0, 1, 0, 0, -1, 0, 1 }; // (x, y) pairs
    int pCoord[2]     = { 0, 0 };
    bool bFound       = false;
    while ( !Fringe.empty() )
    {
        const int nCurrent = Fringe.top().second; Fringe.pop();
        NodeToCoord( nCurrent, pCoord, nMapWidth );

        if ( nCurrent == nTarget )
        {
            bFound = true;
            break;
        }

        for ( int i = 0; i < 8; i += 2 )
        {
            const int nNewX      = pCoord[0] + pMod[i];
            const int nNewY      = pCoord[1] + pMod[i + 1];
            const int nNeighbour = CoordToNode( nNewX, nNewY, nMapWidth );

            if ( ( nNewX >= 0 ) && ( nNewX < nMapWidth ) &&
                 ( nNewY >= 0 ) && ( nNewY < nMapHeight ) && pMap[nNeighbour] )
            {
                const int nNewCost = Cost[nCurrent] + 1;
                if ( Cost.find( nNeighbour ) == Cost.end() || nNewCost < Cost[nNeighbour] )
                {
                    const int nPriority = nNewCost + Heuristic( nNewX, nNewY,
                                                                nTargetX, nTargetY );
                    CameFrom[nNeighbour] = nCurrent;
                    Cost[nNeighbour] = nNewCost;
                    Fringe.emplace( nPriority, nNeighbour );
                }
            }
        }
    }

    if ( !bFound )
    {
        return -1;
    }

    return ReconstructPath( nStart, nTarget, nOutBufferSize, pOutBuffer, CameFrom );
}
