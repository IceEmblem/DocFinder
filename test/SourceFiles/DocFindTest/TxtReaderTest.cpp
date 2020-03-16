#include <gtest/gtest.h>
#include <fstream>
#include <sstream>
#include "../../../src/DocFind/HeaderFiles/DocumentReaders/TxtReader.hpp"
#include "../../../src/DocFind/HeaderFiles/DirectoriesOperate.hpp"
#include "../../../src/DocFind/HeaderFiles/FileOperate.hpp"

using namespace DocFind;

std::string programPath = "./test/bin/TxtReaderTestDir";

class TxtReaderTest : public testing::Test {
public:
        // 第一个测试用例开始时调用
    static void SetUpTestCase()
    {
        DirectoriesOperate::createDir(programPath);
    }
    
    // 最后一个测试用例结束后调用
    static void TearDownTestCase()
    {
        system(("rm -r " + programPath).c_str());
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

TEST_F(TxtReaderTest, getDocTextTest){
    std::string testFile = programPath + "/testFile";
    std::ofstream file;
    file.open(testFile);
    file << "ABCDEF";
    file.close();

    TxtReader txtReader;
    std::string text = txtReader.getDocText(testFile);
    EXPECT_EQ(text, "ABCDEF");
}

TEST_F(TxtReaderTest, getDocTitleForText){
    std::stringstream ss;
    ss << "title1" << std::endl;
    ss << "content text ....... lllll dddes" << std::endl << "dksldhfklashjxifdknzxklhvcishadf" << std::endl << std::endl;
    ss << "title2" << std::endl;
    ss << "content text llllllllllksdsdlkhfkaljhdslkjnzlkjfdhdsf" << std::endl << std::endl;
    ss << "title3" << std::endl << std::endl;
    ss << "这不是一个标题 。。。。。。。。" << std::endl;

    TxtReader txtReader;
    auto titles = txtReader.getDocTitleForText(ss.str());
    EXPECT_EQ(titles.size(), 3);
    EXPECT_EQ(titles[0], "title1");
    EXPECT_EQ(titles[1], "title2");
    EXPECT_EQ(titles[2], "title3");
}