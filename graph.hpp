#pragma once

#include <vector>


struct Node {
    const int nX, nY;
    const bool bBlocked;
    std::vector<Node*> vEdges;

    Node(const int nX, const int nY, const bool bBlocked);
};
