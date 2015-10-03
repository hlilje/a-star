#include "path.hpp"
#include <iostream> // TODO: Remove


void ConnectNeighbours(const int nMapWidth, const int nMapHeight,
                       Node*** pNodes) {
    for (int i = 0; i < nMapHeight; ++i) {
        for (int j = 0; j < nMapWidth; ++j) {
            if (pNodes[i][j]->bBlocked) {
                continue;
            }

            if (i > 0) {
                if (!pNodes[i - 1][j]->bBlocked)
                    pNodes[i][j]->vEdges.push_back(pNodes[i - 1][j]);
            }
            if (i < nMapHeight - 1) {
                if (!pNodes[i + 1][j]->bBlocked)
                    pNodes[i][j]->vEdges.push_back(pNodes[i + 1][j]);
            }
            if (j > 0) {
                if (!pNodes[i][j - 1]->bBlocked)
                    pNodes[i][j]->vEdges.push_back(pNodes[i][j - 1]);
            }
            if (j < nMapWidth - 1) {
                if (!pNodes[i][j + 1]->bBlocked)
                    pNodes[i][j]->vEdges.push_back(pNodes[i][j + 1]);
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
    int size = nMapWidth * nMapHeight;
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
    int size = nMapWidth * nMapHeight;
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

    std::set<Node*> sClosed;                   // Already evaluated nodes
    std::set<Node*> sOpen;                     // Tentative nodes
    std::unordered_map<Node*, bool> mCameFrom; // Navigated nodes
    // Cost from start along best path
    std::unordered_map<Node*, int> mCostPath;
    // Estimated total cost from start to goal through y
    std::unordered_map<Node*, int> mCostTotal;

    sOpen.insert(pStart);
    mCostPath[pStart] = 0;
    mCostTotal[pStart] = mCostPath[pStart] + Heuristic(pStart, pTarget);

    DeleteNodes(nMapWidth, nMapHeight, pNodes);

    return -1;
}

int Heuristic(const Node* pFrom, const Node* pTo) {
    // Manhattan distance
    return std::abs(pFrom->nX - pTo->nX) + std::abs(pFrom->nY - pTo->nY);
}
