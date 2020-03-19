#include <gtest/gtest.h>
#include "../../../src/Program/HeaderFiles/CommandContext.hpp"
#include "../../../src/Program/HeaderFiles/OpenCommand.hpp"

using namespace std;
using namespace DocFind;

OpenCommand * openCommand;

static std::string programDirPath = "./test/bin/OpenCommandTestDir";

class OpenCommandTest : public testing::Test {
public:
    static void SetUpTestCase()
    {
        // 初始化命令上下文
        CommandContext::init(programDirPath);
        openCommand = new OpenCommand();
    }
    
    // 最后一个测试用例结束后调用
    static void TearDownTestCase()
    {
        delete openCommand;
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