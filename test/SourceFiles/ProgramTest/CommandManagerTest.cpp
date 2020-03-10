#include <gtest/gtest.h>
#include "../../../src/Program/HeaderFiles/Command.hpp"
#include "../../../src/Program/HeaderFiles/CommandManager.hpp"

using namespace std;

static std::string programDirPath = "./test/bin/CommandManagerTestDir";

CommandManager * commandManager;

// 用于测试命令管理器的类
class CommandTestClass : public Command {
public:
    CommandTestClass(){
        commandNames = { "test", "nexttest", "nextcmd" };
    }
    
    std::string exec(std::string command, std::string paramStr, std::string & nextCmd){
        if(command == "test"){
            return command + paramStr;
        }
        
        if(command == "nexttest"){
            nextCmd = "nextcmd";
            return "";
        }
        
        return command;
    }
};

// 测试类
class CommandManagerTest : public testing::Test {
public:
    static void SetUpTestCase()
    {
        CommandManager::RegisterBuiltInCommands();
        CommandManager::Register(std::make_shared<CommandTestClass>());
        commandManager = new CommandManager();
    }
    
    // 最后一个测试用例结束后调用
    static void TearDownTestCase()
    {
        delete commandManager;
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

TEST_F(CommandManagerTest, execTest) {
    string result = commandManager->Exec("test param");
    EXPECT_EQ(result, "testparam");
}

TEST_F(CommandManagerTest, nextTest) {
    string result = commandManager->Exec("nexttest");
    EXPECT_EQ(result, "nextcmd");
}