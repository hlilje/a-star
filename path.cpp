#include "path.hpp"

using Node = std::pair<int, int>;


int CoordToNode(const int nX, const int nY, const int nMapWidth) {
    return nY * nMapWidth + nX;
}

int FindPath(const int nStartX, const int nStartY,
             const int nTargetX, const int nTargetY,
             const unsigned char* pMap, const int nMapWidth,
             const int nMapHeight, int* pOutBuffer, const int nOutBufferSize) {
    if ((nStartX == nTargetX) && (nStartY == nTargetY))
        return -1;

    PriorityQueue<int> sFringe;             // Tentative nodes
    std::unordered_map<int, int> mCameFrom; // Navigated nodes
    std::unordered_map<int, int> mCost;     // Cost so far

    int nStart = CoordToNode(nStartX, nStartY, nMapWidth);
    int nTarget = CoordToNode(nTargetX, nTargetY, nMapWidth);

    sFringe.put(nStart, 0);
    mCost[nStart] = 0;

    bool found = false;
    int mod[8] = {-1, 0, 1, 0, 0, -1, 0, 1}; // (x, y) pairs
    while (!sFringe.empty()) {
        int nCurrent = sFringe.get(); // Node with lowest cost
        Node nCurrentNode = NodeToCoord(nCurrent, nMapWidth);

        if (nCurrent == nTarget) {
            found = true;
            break;
        }

        // Add neighbours to the queue
        for (int i = 0; i < 8; i += 2) {
            int nNewX = nCurrentNode.first + mod[i];
            int nNewY = nCurrentNode.second + mod[i + 1];
            int nNeighbour = CoordToNode(nNewX, nNewY, nMapWidth);
            // Check if valid index and not blocked
            if ((nNewX >= 0) && (nNewX < nMapWidth) && (nNewY >= 0) &&
                (nNewY < nMapHeight) && pMap[nNeighbour]) {
                // Distance to neighbours always 1
                int nNewScore = mCost[nCurrent] + 1;
                if (!mCost.count(nNeighbour) ||
                    nNewScore < mCost[nNeighbour]) {
                    int nPriority = nNewScore +
                                    Heuristic(nNewX, nNewY, nTargetX, nTargetY);
                    mCost[nNeighbour] = nNewScore;
                    sFringe.put(nNeighbour, nPriority);
                    mCameFrom[nNeighbour] = nCurrent;
                }
            }
        }
    }

    if (!found) return -1;

    return ReconstructPath(nStart, nTarget, nOutBufferSize, pOutBuffer,
                           mCameFrom);
}

int Heuristic(const int nFromX, const int nFromY, const int nToX,
              const int nToY) {
    return std::abs(nFromX - nToX) + std::abs(nFromY - nToY);
}

Node NodeToCoord(const int nNode, const int nMapWidth) {
    return Node(nNode % nMapWidth, nNode / nMapWidth);
}

int ReconstructPath(const int nStart, const int nTarget,
                    const int nOutBufferSize, int* pOutBuffer,
                    std::unordered_map<int, int>& mCameFrom) {
    std::vector<int> vPath;
    int nCurrent = nTarget;
    vPath.push_back(nCurrent);

    while (nCurrent != nStart) {
        nCurrent = mCameFrom[nCurrent];
        vPath.push_back(nCurrent);
    }

    int nPathLength = vPath.size() - 1; // Excluding start node

    // Store as much of the path as possible
    for (int i = nPathLength - 1, j = 0; (i >= 0) && (j < nOutBufferSize);
         --i, ++j)
        pOutBuffer[j] = vPath[i];

    return nPathLength;
}
