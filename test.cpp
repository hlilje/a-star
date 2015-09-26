#include "test.hpp"


void test_valid_path() {
    unsigned char pMap[] = {1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1};
    int pOutBuffer[12];

    int res = FindPath(0, 0, 1, 2, pMap, 4, 3, pOutBuffer, 12);
    assert(res == 3);

    assert(pOutBuffer[0] == 1);
    assert(pOutBuffer[0] == 5);
    assert(pOutBuffer[0] == 9);
}

void test_invalid_path() {
    unsigned char pMap[] = {0, 0, 1, 0, 1, 1, 1, 0, 1};
    int pOutBuffer[7];

    int res = FindPath(2, 0, 0, 2, pMap, 3, 3, pOutBuffer, 7);
    assert(res == -1);
}
