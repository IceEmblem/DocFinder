#include <gtest/gtest.h>
#include "../../../src/Program/HeaderFiles/CommandContext.hpp"

using namespace  DocFind;

static std::string programDirPath = "./test/bin/CommandContextTestDir";

class CommandContextTest : public testing::Test {
public:
    static void SetUpTestCase()
    {
        CommandContext::init(programDirPath);
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

TEST_F(CommandContextTest, setDataTest){
    CommandContext::Instances()->setData("key1", std::make_shared<std::string>("value1"));
    auto value = std::static_pointer_cast<std::string>(CommandContext::Instances()->getData("key1"));

    EXPECT_EQ(*value, "value1");
}