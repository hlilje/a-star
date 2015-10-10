#pragma once

#include "path.hpp"
#include <cassert>


/*
 * Test various small edge cases.
 */
void TestEdgeCases();

/*
 * Test a small instance of an invalid path.
 */
void TestInvalidPath();

/*
 * Test a larger instance of an invalid path.
 */
void TestInvalidLongPath();

/*
 * Test a small instance of a valid path.
 */
void TestValidPath();

/*
 * Test a larger instance of a valid path.
 */
void TestValidLongPath();
