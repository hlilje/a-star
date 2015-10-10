#include "test.hpp"


int main() {
    TestEdgeCases();
    TestInvalidLongPath();
    TestInvalidPath();
    TestValidLongPath();
    TestValidOnePath();
    TestValidPath();

    return 0;
}
