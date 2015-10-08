#include "path.hpp"


void BuildOutputBuffer(const int nMapWidth, int* pOutBuffer,
                       const std::vector<Node*>& vPath) {
    // Start node not part of resulting path
    for (int i = 1; i < (int) vPath.size(); ++i) {
        Node* pNode = vPath[i];
        pOutBuffer[i - 1] = (pNode->nY * nMapWidth) + pNode->nX;
    }
}

void ConnectNeighbours(const int nMapWidth, const int nMapHeight,
                       Node*** pNodes) {
    for (int i = 0; i < nMapHeight; ++i) {
        for (int j = 0; j < nMapWidth; ++j) {
            if (pNodes[i][j]->bBlocked) {
                continue;
            }

            int mod[8] = {-1, 0, 1, 0, 0, -1, 0, 1}; // (x, y) pairs
            for (int k = 0; k < 8; k += 2) {
                int new_x = j + mod[k];
                int new_y = i + mod[k + 1];
                if ((new_x >= 0) && (new_x < nMapWidth) && (new_y >= 0) &&
                    (new_y < nMapHeight)) {
                    if (!pNodes[new_y][new_x]->bBlocked)
                        pNodes[i][j]->vEdges.push_back(pNodes[new_y][new_x]);
                }
            }
        }
    }
}

std::pair<Node*, Node*> CreateNodes(const unsigned char* pMap,
                                    const int nMapWidth,
                                    const int nMapHeight, const int nStartX,
                                    const int nStartY,
                                    const int nTargetX, const int nTargetY,
                                    Node*** pNodes) {
    Node* pStart = new Node(nStartX, nStartY, false);
    Node* pTarget = new Node(nTargetX, nTargetY, false);

    for (int i = 0; i < nMapHeight; ++i) {
        int nStart = i * nMapWidth;
        int nY = i;
        for (int j = nStart; j < nStart + nMapWidth; ++j) {
            int nX = j % nMapWidth;
            Node* nNode;
            if ((nX == pStart->nX) && (nY == pStart->nY))
                nNode = pStart;
            else if ((nX == pTarget->nX) && (nY  == pTarget->nY))
                nNode = pTarget;
            else
                nNode = new Node(nX, nY, !pMap[j]);
            pNodes[nY][nX] = nNode;
        }
    }

    return std::pair<Node*, Node*>(pStart, pTarget);
}

void DeleteNodes(const int nMapWidth, const int nMapHeight, Node*** pNodes) {
    for (int i = 0; i < nMapHeight; ++i) {
        for (int j = 0; j < nMapWidth; ++j) {
            delete pNodes[i][j];
        }
        delete[] pNodes[i];
    }
    delete[] pNodes;
}

int FindPath(const int nStartX, const int nStartY,
             const int nTargetX, const int nTargetY,
             const unsigned char* pMap, const int nMapWidth,
             const int nMapHeight, int* pOutBuffer, const int nOutBufferSize) {
    Node*** pNodes = new Node**[nMapHeight];
    for (int i = 0; i < nMapHeight; ++i)
        pNodes[i] = new Node*[nMapWidth];

    std::pair<Node*, Node*> pStartTarget = CreateNodes(pMap, nMapWidth,
                                                       nMapHeight, nStartX,
                                                       nStartY, nTargetX,
                                                       nTargetY, pNodes);
    ConnectNeighbours(nMapWidth, nMapHeight, pNodes);

    Node* pStart = pStartTarget.first;
    Node* pTarget = pStartTarget.second;

    PriorityQueue<Node*> sFringe;               // Tentative nodes
    std::unordered_map<Node*, Node*> mCameFrom; // Navigated nodes
    std::unordered_map<Node*, int> mCost;       // Cost so far

    sFringe.put(pStart, 0);
    mCost[pStart] = 0;

    bool found = false;
    while (!sFringe.empty()) {
        Node* pCurrent = sFringe.get(); // Node with lowest cost

        if (pCurrent == pTarget) {
            found = true;
            break;
        }

        for (Node* pNext : pCurrent->vEdges) {
            // Distance to neighbours always 1
            int nNewScore = mCost[pCurrent] + 1;
            if (!mCost.count(pNext) || nNewScore < mCost[pNext]) {
                int nPriority = nNewScore + Heuristic(pNext, pTarget);
                mCost[pNext] = nNewScore;
                sFringe.put(pNext, nPriority);
                mCameFrom[pNext] = pCurrent;
            }
        }
    }

    if (!found) {
        DeleteNodes(nMapWidth, nMapHeight, pNodes);
        return -1;
    }

    std::vector<Node*> vPath = ReconstructPath(mCameFrom, pStart, pTarget);
    if ((int) vPath.size() - 1 > nOutBufferSize) {
        DeleteNodes(nMapWidth, nMapHeight, pNodes);
        return -1;
    }

    BuildOutputBuffer(nMapWidth, pOutBuffer, vPath);
    DeleteNodes(nMapWidth, nMapHeight, pNodes);

    return vPath.size() - 1; // Excluding start node
}

int Heuristic(const Node* pFrom, const Node* pTo) {
    return std::abs(pFrom->nX - pTo->nX) + std::abs(pFrom->nY - pTo->nY);
}

std::vector<Node*> ReconstructPath(std::unordered_map<Node*, Node*>& mCameFrom,
                                   Node* pStart, Node* pTarget) {
    std::vector<Node*> vPath;
    Node* pCurrent = pTarget;
    vPath.push_back(pCurrent);

    while (pCurrent != pStart) {
        pCurrent = mCameFrom[pCurrent];
        vPath.push_back(pCurrent);
    }

    std::reverse(vPath.begin(), vPath.end());
    return vPath;
}
