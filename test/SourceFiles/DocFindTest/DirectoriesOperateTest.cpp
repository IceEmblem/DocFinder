#include <gtest/gtest.h>
#include <string>
#include "../../../src/Infrastructure/HeaderFiles/DirectoriesOperate.hpp"
#include "../../../src/Infrastructure/HeaderFiles/FileOperate.hpp"

using namespace Infrastructure;

static std::string programDirPath = "./test/bin/DirectoriesOperateTestDir";

class DirectoriesOperateTest : public testing::Test {
public:
    static void SetUpTestCase()
    {
        DirectoriesOperate::createDir(programDirPath);
        DirectoriesOperate::createDir(programDirPath + "/TestChildDir");

        // 创建测试文件
        FileOperate::createFile(programDirPath + "/TestFile1.txt");

        // 创建测试文件
        FileOperate::createFile(programDirPath + "/TestFile2.txt");
    }
    
    // 最后一个测试用例结束后调用
    static void TearDownTestCase()
    {
        std::string cmd = "rm -r " + programDirPath;
        system(cmd.c_str());
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
    auto results = DirectoriesOperate::getFiles(programDirPath);

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