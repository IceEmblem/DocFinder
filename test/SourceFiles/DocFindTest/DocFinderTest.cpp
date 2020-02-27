#include <gtest/gtest.h>
#include <fstream>
#include "../../../src/DocFind/HeaderFiles/DocFinder.hpp"

using namespace std;

DocFind::DocFinder * docFinder;

// 测试类
class DocFinderTest:public testing::Test
{
public:
    // 第一个测试用例开始时调用
    static void SetUpTestCase()
    {
        // 创建测试文件
        ofstream file1("./test/bin/TestFile1.txt", fstream::out);
        file1.close();

        ofstream file2("./test/bin/TestFile2.txt", fstream::out);
        file2.close();
    }
    
    // 最后一个测试用例结束后调用
    static void TearDownTestCase()
    {
    }

    // 每个测试用例开始时调用
    void SetUp()
    {
        docFinder = new DocFind::DocFinder("./test/bin");
    }

    // 每个测试用例结束后调用
    void TearDown()
    {
        delete docFinder;
    } 
};

// 测试用例，用例名为 FindTest
TEST_F(DocFinderTest, FindTest)
{
    auto results = docFinder->find({ "File1" });

    EXPECT_EQ(results.size(), 1);
    EXPECT_EQ(results[0].document.name, "TestFile1.txt");
}