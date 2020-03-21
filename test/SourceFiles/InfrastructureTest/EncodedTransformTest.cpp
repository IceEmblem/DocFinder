#include <gtest/gtest.h>
#include "../../../src/Infrastructure/HeaderFiles/EncodedTransform.hpp"

using namespace Infrastructure;

class EncodedTransformTest : public testing::Test {
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

TEST_F(EncodedTransformTest, UTF8ToGBK)
{
    // 我的 gbk 编码
    const char gbkme[] = { static_cast<char>(0xce), static_cast<char>(0xd2) };
    const char *utfme = "我";

    std::string output = EncodedTransform::UTF8ToGBK(utfme);
    EXPECT_EQ(output, gbkme);
}

TEST_F(EncodedTransformTest, GBKToUTF8)
{
    // 我的 gbk 编码
    const char gbkme[] = { static_cast<char>(0xce), static_cast<char>(0xd2) };
    const char *utfme = "我";

    std::string output = EncodedTransform::GBKToUTF8(gbkme);
    EXPECT_EQ(output, utfme);
}