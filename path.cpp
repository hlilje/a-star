#include "path.hpp"
#include <iostream> // TODO: Remove


void CreateNodes(const unsigned char* pMap, const int nMapWidth,
                 const int nMapHeight, const int nStartX, const int nStartY,
                 const int nTargetX, const int nTargetY, Node*** pNodes) {
    int size = nMapWidth * nMapHeight;
    Node* pStart = new Node(nStartX, nStartY);
    Node* pTarget = new Node(nTargetX, nTargetY);

    for (int i = 0; i < nMapHeight; ++i) {
        int nStart = i * nMapWidth;
        for (int j = nStart; j < nStart + nMapWidth; ++j) {
            int nX = j % nMapWidth;
            int nY = i;
            Node* nNode;
            if ((nX == pStart->nX) && (nY == pStart->nY))
                nNode = pStart;
            else if ((nX == pTarget->nX) && (nY  == pTarget->nY))
                nNode = pTarget;
            else
                nNode = new Node(nX, nY);
            pNodes[i][j] = nNode;
        }
    }
}

void DeleteNodes(const int nMapWidth, const int nMapHeight, Node*** pNodes) {
    for (int i = 0; i < nMapHeight; ++i) {
        for (int j = 0; j < nMapHeight; ++j)
            delete pNodes[i][j];
        delete[] pNodes[i];
    }
    delete[] pNodes;
}

int FindPath(const int nStartX, const int nStartY,
             const int nTargetX, const int nTargetY,
             const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
             int* pOutBuffer, const int nOutBufferSize) {
    int size = nMapWidth * nMapHeight;
    Node*** pNodes = new Node**[nMapHeight];
    for (int i = 0; i < nMapHeight; ++i)
        pNodes[i] = new Node*[nMapWidth];

    CreateNodes(pMap, nMapWidth, nMapHeight, nStartX, nStartY, nTargetX,
                nTargetY, pNodes);

    std::set<Node*> sClosed; // Already evaluated nodes
    std::set<Node*> sOpen;   // Tentative nodes

    DeleteNodes(nMapWidth, nMapHeight, pNodes);

    return -1;
}
