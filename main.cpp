#include "test.hpp"
#include <iostream>


int main() {
    std::ios_base::sync_with_stdio(false);

    test_valid_path();
    test_invalid_path();

    return 0;
}
