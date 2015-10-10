#include "test.hpp"


void TestEdgeCases() {
    unsigned char pMap[] = {1};
    int pOutBuffer[10];

    int nRes = FindPath(0, 0, 0, 0, pMap, 1, 1, pOutBuffer, 10);
    assert(nRes == -1);

    unsigned char pMap2[] = {1, 1, 1, 1, 1, 1};
    int pOutBuffer2[1];

    nRes = FindPath(0, 0, 2, 1, pMap2, 3, 2, pOutBuffer2, 0);
    assert(nRes == -1);
}

void TestInvalidPath() {
    unsigned char pMap[] = {
        0, 0, 1,
        0, 1, 1,
        1, 0, 1
    };
    int pOutBuffer[7];

    int nRes = FindPath(2, 0, 0, 2, pMap, 3, 3, pOutBuffer, 7);
    assert(nRes == -1);
}

void TestInvalidLongPath() {
    unsigned char pMap[] = {
        1, 0, 0, 1, 1, 1,
        1, 0, 1, 1, 1, 1,
        1, 0, 0, 1, 1, 0,
        1, 0, 1, 1, 0, 1,
        1, 1, 1, 0, 1, 1,
        0, 0, 0, 0, 0, 1
    };
    int pOutBuffer[100];

    int nRes = FindPath(0, 0, 5, 5, pMap, 6, 6, pOutBuffer, 100);
    assert(nRes == -1);
}

void TestValidPath() {
    unsigned char pMap[] = {
        1, 1, 1, 1,
        0, 1, 0, 1,
        0, 1, 1, 1
    };
    int pOutBuffer[12];

    int nRes = FindPath(0, 0, 1, 2, pMap, 4, 3, pOutBuffer, 12);
    assert(nRes == 3);

    assert(pOutBuffer[0] == 1);
    assert(pOutBuffer[1] == 5);
    assert(pOutBuffer[2] == 9);
}

void TestValidLongPath() {
    unsigned char pMap[] = {
        1, 1, 0, 1, 1, 1,
        1, 1, 1, 1, 0, 1,
        1, 1, 0, 1, 0, 1,
        1, 0, 1, 1, 1, 1,
        1, 1, 1, 0, 1, 1,
        0, 0, 0, 0, 1, 1
    };
    int pOutBuffer[100];

    int nRes = FindPath(0, 0, 5, 5, pMap, 6, 6, pOutBuffer, 100);
    assert(nRes == 10);
}
