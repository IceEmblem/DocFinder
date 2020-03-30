#include <gtest/gtest.h>
#include "../../../src/Infrastructure/HeaderFiles/StringOperate.hpp"

using namespace Infrastructure;

class StringOperateTest : public testing::Test{
public:
    // 每个测试用例开始时调用
    void SetUp()
    {
    }

    // 每个测试用例结束后调用
    void TearDown()
    {
    } 
};

TEST_F(StringOperateTest, replace){
    EXPECT_EQ(StringOperate::replace("ABCdeF", "de", "DE"), "ABCDEF");
}