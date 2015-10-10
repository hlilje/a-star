#include "test.hpp"


int main() {
    TestEdgeCases();
    TestInvalidPath();
    TestInvalidLongPath();
    TestValidPath();
    TestValidLongPath();

    return 0;
}
