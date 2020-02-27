#include <gtest/gtest.h>
#include <map>
#include <iostream>

using namespace std;

string ProgramPath;

int main(int argc, char** argv)
{
    ProgramPath = argv[0];

    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}