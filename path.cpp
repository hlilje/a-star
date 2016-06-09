#include "path.hpp"
#include <queue>
#include <vector>

using PQElement = std::pair<int, int>; // <prio, value>
using Node      = std::pair<int, int>;


int CoordToNode( const int nX, const int nY, const int nMapWidth )
{
    return nY * nMapWidth + nX;
}

int FindPath( const int nStartX, const int nStartY,
              const int nTargetX, const int nTargetY,
              const unsigned char* pMap, const int nMapWidth,
              const int nMapHeight, int* pOutBuffer, const int nOutBufferSize )
{
    if ( ( nStartX == nTargetX ) && ( nStartY == nTargetY ) )
    {
        return 0;
    }

    std::priority_queue<PQElement, std::vector<PQElement>, std::greater<PQElement>> Fringe;
    std::unordered_map<int, int> CameFrom;
    std::unordered_map<int, int> Cost;

    const int nStart  = CoordToNode( nStartX, nStartY, nMapWidth );
    const int nTarget = CoordToNode( nTargetX, nTargetY, nMapWidth );

    Fringe.emplace( 0, nStart );
    Cost[nStart] = 0;

    bool bFound = false;
    const int pMod[8] = { -1, 0, 1, 0, 0, -1, 0, 1 }; // (x, y) pairs
    while ( !Fringe.empty() )
    {
        const int nCurrent      = Fringe.top().second;
        const Node nCurrentNode = NodeToCoord( nCurrent, nMapWidth );
        Fringe.pop();

        if ( nCurrent == nTarget )
        {
            bFound = true;
            break;
        }

        for ( int i = 0; i < 8; i += 2 )
        {
            const int nNewX      = nCurrentNode.first + pMod[i];
            const int nNewY      = nCurrentNode.second + pMod[i + 1];
            const int nNeighbour = CoordToNode( nNewX, nNewY, nMapWidth );

            if ( ( nNewX >= 0 ) && ( nNewX < nMapWidth ) && ( nNewY >= 0 ) &&
                 ( nNewY < nMapHeight ) && pMap[nNeighbour] )
            {
                const int nNewScore = Cost[nCurrent] + 1;
                if ( !Cost.count( nNeighbour ) || nNewScore < Cost[nNeighbour] )
                {
                    const int nPriority = nNewScore + Heuristic( nNewX, nNewY, nTargetX, nTargetY );
                    Cost[nNeighbour] = nNewScore;
                    Fringe.emplace( nPriority, nNeighbour );
                    CameFrom[nNeighbour] = nCurrent;
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

int Heuristic( const int nFromX, const int nFromY, const int nToX, const int nToY )
{
    return std::abs( nFromX - nToX ) + std::abs( nFromY - nToY );
}

Node NodeToCoord( const int nNode, const int nMapWidth )
{
    return Node( nNode % nMapWidth, nNode / nMapWidth );
}

int ReconstructPath( const int nStart, const int nTarget, const int nOutBufferSize,
                     int* pOutBuffer, std::unordered_map<int, int>& CameFrom )
{
    std::vector<int> vPath;
    int nCurrent = nTarget;
    vPath.emplace_back( nCurrent );

    while ( nCurrent != nStart )
    {
        nCurrent = CameFrom[nCurrent];
        vPath.emplace_back( nCurrent );
    }

    const int nPathLength = vPath.size() - 1; // Excluding start node

    for ( int i = nPathLength - 1, j = 0; ( i >= 0 ) && ( j < nOutBufferSize ); --i, ++j )
    {
        pOutBuffer[j] = vPath[i];
    }

    return nPathLength;
}
