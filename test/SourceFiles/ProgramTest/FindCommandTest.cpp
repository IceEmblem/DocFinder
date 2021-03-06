#include <gtest/gtest.h>
#include "../../../src/Program/HeaderFiles/CommandContext.hpp"
#include "../../../src/Program/HeaderFiles/FindCommand.hpp"
#include "../../../src/Infrastructure/HeaderFiles/DirectoriesOperate.hpp"
#include "../../../src/Infrastructure/HeaderFiles/FileOperate.hpp"

using namespace std;
using namespace DocFind;
using namespace Infrastructure;


static std::string programDirPath = "./test/bin/FindCommandTestDir";

static FindCommand * findCommand;

class FindCommandTest : public testing::Test {
public:
    static void SetUpTestCase()
    {
        // 创建测试目录
        DirectoriesOperate::createDir(programDirPath);

        // 创建测试文件
        FileOperate::createFile(programDirPath+"/FindCommandTestFile1.txt");
        FileOperate::createFile(programDirPath+"/FindCommandTestFile2.txt");

        // 初始化命令上下文
        CommandContext::init(programDirPath);
        findCommand = new FindCommand();
    }
    
    // 最后一个测试用例结束后调用
    static void TearDownTestCase()
    {
        delete findCommand;
        system(("rm -r " + programDirPath).c_str());
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

// 测试查找功能
TEST_F(FindCommandTest, exec_findTest) {
    string nextCmd;
    string result = findCommand->exec("find", "Find File1", nextCmd);

    int index = result.find("FindCommandTestFile1");

    // 结果中应该包含文件1的文件名
    EXPECT_EQ(index != result.npos, true);

    // 不接受空关键字
    result = findCommand->exec("find", "", nextCmd);
    index = result.find("FindCommandTestFile1");

    // 结果中应该包含文件1的文件名
    EXPECT_EQ(index == result.npos, true);
}

// 测试输出下一个命令功能
TEST_F(FindCommandTest, exec_openOrReadDocTest) {
    string nextCmd;
    string result = findCommand->exec("find", "File1", nextCmd);
    EXPECT_EQ(nextCmd, "");

    result = findCommand->exec("fo", "1", nextCmd);
    int index = nextCmd.find("open ");
    // nextCmd 应该为 "open ...."
    EXPECT_EQ(index, 0);
}