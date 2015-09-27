#include "path.hpp"
#include <iostream> // TODO: Remove


void CreateNodes(const unsigned char* pMap, const int nMapWidth,
                 const int nMapHeight, const int nStartX, const int nStartY,
                 const int nTargetX, const int nTargetY, Node** pNodes) {
    int size = nMapWidth * nMapHeight;
    Node* nStart = new Node(nStartX, nStartY);
    Node* nTarget = new Node(nTargetX, nTargetY);

    for (int i = 0; i < nMapHeight; ++i) {
        int nStart = i * nMapWidth;
        for (int j = nStart; j < nStart + nMapWidth; ++j) {
            int nX = j % nMapWidth;
            int nY = i;
            Node* nNode = new Node(nX, nY);
            pNodes[j] = nNode;
        }
    }
}

void DeleteNodes(const int nNumNodes, Node** pNodes) {
    for (int i = 0; i < nNumNodes; ++i)
        delete pNodes[i];
    delete[] pNodes;
}

int FindPath(const int nStartX, const int nStartY,
             const int nTargetX, const int nTargetY,
             const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
             int* pOutBuffer, const int nOutBufferSize) {
    int size = nMapWidth * nMapHeight;
    Node** pNodes = new Node*[size];

    CreateNodes(pMap, nMapWidth, nMapHeight, nStartX, nStartY, nTargetX,
                nTargetY, pNodes);

    std::set<Node*> sClosed; // Already evaluated nodes
    std::set<Node*> sOpen;   // Tentative nodes

    DeleteNodes(size, pNodes);

    return -1;
}
