#include <gtest/gtest.h>
#include <string>
#include <fstream>
#include "../../../src/DocFind/HeaderFiles/DirectoriesOperate.hpp"
#include "../../../src/DocFind/HeaderFiles/FileOperate.hpp"

using namespace  DocFind;

static std::string programDirPath = "./test/bin";

class DirectoriesOperateTest : public testing::Test {
public:
    static void SetUpTestCase()
    {
        DirectoriesOperate::createDir(programDirPath + "/DirectoriesOperateTestDir");
        DirectoriesOperate::createDir(programDirPath + "/DirectoriesOperateTestDir/TestChildDir");

        // 创建测试文件
        FileOperate::createFile(programDirPath + "/DirectoriesOperateTestDir/TestFile1.txt");

        // 创建测试文件
        FileOperate::createFile(programDirPath + "/DirectoriesOperateTestDir/TestFile2.txt");
    }
    
    // 最后一个测试用例结束后调用
    static void TearDownTestCase()
    {
    }

    // 每个测试用例开始时调用
    void SetUp()
    {
    }

    // 每个测试用例结束后调用
    void TearDown()
    {
    } 
};

TEST_F(DirectoriesOperateTest, getFilesTest){
    auto results = DirectoriesOperate::getFiles(programDirPath + "/DirectoriesOperateTestDir");

    EXPECT_EQ(results.size(), 3);
    EXPECT_EQ(results["TestChildDir"], true);
    EXPECT_EQ(results["TestFile1.txt"], false);
    EXPECT_EQ(results["TestFile2.txt"], false);
}

TEST_F(DirectoriesOperateTest, getDirPathTest){
    std::string result;
    result = DirectoriesOperate::getDirPath("/abc/123");
    EXPECT_EQ(result, "/abc");

    result = DirectoriesOperate::getDirPath("E:/abc/lkj/123.lll");
    EXPECT_EQ(result, "E:/abc/lkj");
}