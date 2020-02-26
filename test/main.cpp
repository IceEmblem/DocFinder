#include<gtest/gtest.h>
#include<map>
#include<iostream>

using namespace std;

static int add(int l, int r)
{
    return l + r;
}

// 测试类
class TestMap:public testing::Test
{
public:
    // 第一个测试用例开始时调用
    static void SetUpTestCase()
    {
        cout<<"SetUpTestCase()"<<endl;
    }
    
    // 最后一个测试用例结束后调用
    static void TearDownTestCase()
    {
        cout<<"TearDownTestCase()"<<endl;
    }

    // 每个测试用例开始时调用
    void SetUp()
    {
        cout<<"SetUp() is running"<<endl;
    }

    // 每个测试用例结束后调用
    void TearDown()
    {
        cout<<"TearDown() is running"<<endl;
    } 
};
 
// 测试用例，用例名为 Test1
TEST_F(TestMap, Test1)
{
    // 断言，3+2 等于 5
    EXPECT_EQ(add(3, 2), 5);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}