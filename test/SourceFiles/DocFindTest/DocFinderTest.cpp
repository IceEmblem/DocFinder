#include <gtest/gtest.h>
#include <fstream>
#include "../../../src/Infrastructure/HeaderFiles/DirectoriesOperate.hpp"
#include "../../../src/DocFind/HeaderFiles/DocFinder.hpp"
#include "../../../src/Infrastructure/HeaderFiles/FileOperate.hpp"

using namespace DocFind;
using namespace Infrastructure;
using namespace std;

static std::string programDirPath = "./test/bin/DocFinderTestDir";

DocFind::DocFinder * docFinder;

// 测试类
class DocFinderTest:public testing::Test
{
public:
    // 第一个测试用例开始时调用
    static void SetUpTestCase()
    {
        DirectoriesOperate::createDir(programDirPath);

        // 创建测试文件
        FileOperate::createFile(programDirPath + "/Pre_DocFinderTestFile1.txt");
        FileOperate::createFile(programDirPath + "/Pre_DocFinderTestFile2.txt");
        FileOperate::createFile(programDirPath + "/测试文件3.txt");
    }
    
    // 最后一个测试用例结束后调用
    static void TearDownTestCase()
    {
        system(("rm -r " + programDirPath).c_str());
    }

    // 每个测试用例开始时调用
    void SetUp()
    {
        docFinder = new DocFind::DocFinder(programDirPath + "");
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
    auto results = docFinder->find({ "DocFinderTestFile1" });

    EXPECT_EQ(results.size(), 1);
    EXPECT_EQ(results[0].document->name, "Pre_DocFinderTestFile1.txt");

    // 不区分大小写测试
    results = docFinder->find({ "file1" });
    EXPECT_EQ(results[0].document->name, "Pre_DocFinderTestFile1.txt");

    // 中文测试
    results = docFinder->find({ "文件3" });
    EXPECT_EQ(results[0].document->name, "测试文件3.txt");
}