#include "path.hpp"

using Node = std::pair<int, int>;


void BuildOutputBuffer(int* pOutBuffer, const std::vector<int>& vPath) {
    // Start node not part of resulting path, path is reversed
    for (int i = vPath.size() - 2, j = 0; i >= 0; --i, ++j)
        pOutBuffer[j] = vPath[i];
}

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
        // TODO: Avoid unnecessary coordinates/index conversions
        int nCurrent = sFringe.get(); // Node with lowest cost
        Node nCurrentNode = NodeToCoord(nCurrent, nMapWidth);

        if (nCurrent == nTarget) {
            found = true;
            break;
        }

        // Add neighbours to the queue
        for (int k = 0; k < 8; k += 2) {
            int nNewX = nCurrentNode.first + mod[k];
            int nNewY = nCurrentNode.second + mod[k + 1];
            int nNeighbour = CoordToNode(nNewX, nNewY, nMapWidth);
            // Check if valid index and not blocked
            if ((nNewX >= 0) && (nNewX < nMapWidth) && (nNewY >= 0) &&
                (nNewY < nMapHeight) && pMap[nNeighbour]) {
                // Distance to neighbours always 1
                int nNewScore = mCost[nCurrent] + 1;
                if (!mCost.count(nNeighbour) ||
                    nNewScore < mCost[nNeighbour]) {
                    int nPriority = nNewScore + Heuristic(nNeighbour, nTarget,
                                                          nMapWidth);
                    mCost[nNeighbour] = nNewScore;
                    sFringe.put(nNeighbour, nPriority);
                    mCameFrom[nNeighbour] = nCurrent;
                }
            }
        }
    }

    if (!found) return -1;

    std::vector<int> vPath = ReconstructPath(mCameFrom, nStart, nTarget);
    if ((int) vPath.size() - 1 > nOutBufferSize) return -1;

    BuildOutputBuffer(pOutBuffer, vPath);

    return vPath.size() - 1; // Excluding start node
}

int Heuristic(const int nFrom, const int nTo, const int nMapWidth) {
    Node nFromNode = NodeToCoord(nFrom, nMapWidth);
    Node nToNode = NodeToCoord(nTo, nMapWidth);
    return std::abs(nFromNode.first - nToNode.first) +
                    std::abs(nFromNode.second - nToNode.second);
}

Node NodeToCoord(const int nNode, const int nMapWidth) {
    return Node(nNode % nMapWidth, nNode / nMapWidth);
}

std::vector<int> ReconstructPath(std::unordered_map<int, int>& mCameFrom,
                                 const int nStart, const int nTarget) {
    std::vector<int> vPath;
    int nCurrent = nTarget;
    vPath.push_back(nCurrent);

    while (nCurrent != nStart) {
        nCurrent = mCameFrom[nCurrent];
        vPath.push_back(nCurrent);
    }

    return vPath;
}
