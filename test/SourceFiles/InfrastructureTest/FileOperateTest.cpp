#include <gtest/gtest.h>
#include "../../../src/Infrastructure/HeaderFiles/DirectoriesOperate.hpp"
#include "../../../src/Infrastructure/HeaderFiles/FileOperate.hpp"

using namespace Infrastructure;

static std::string programPath = "./test/bin/FileOperateTestDir";

class FileOperateTest : public testing::Test {
public:
    // 每个测试用例开始时调用
    void SetUp()
    {
        DirectoriesOperate::createDir(programPath);
    }

    // 每个测试用例结束后调用
    void TearDown()
    {
        std::string cmd = "rm -r " + programPath;
        system(cmd.c_str());
    } 
};

// 创建文件和是否存在文件测试
TEST_F(FileOperateTest, createFile_and_isExistFile_Test)
{
    std::string filePath = programPath + "/testFile.text";
    FileOperate::createFile(filePath);

    EXPECT_EQ(FileOperate::isExistFile(filePath), true);

}

// 写入文本和获取文件文本测试
TEST_F(FileOperateTest, writeFileText_and_getFileText_Test)
{
    std::string filePath = programPath + "/testFile.text";
    FileOperate::createFile(filePath);

    std::string text = "ABCed";
    FileOperate::writeFileText(filePath, text);

    std::string a = FileOperate::getFileText(filePath);
    EXPECT_EQ(FileOperate::getFileText(filePath), text);
}

// 获取文件名，获取文件路径，获取文件后缀测试
TEST_F(FileOperateTest, getFileName_getFileDirPath_getPostfix_Test)
{
    std::string filePath = programPath + "/path/testFile.text";
    EXPECT_EQ(FileOperate::getFileName(filePath), "testFile.text");
    EXPECT_EQ(FileOperate::getFileDirPath(filePath), programPath + "/path");
    EXPECT_EQ(FileOperate::getPostfix(filePath), "text");
}