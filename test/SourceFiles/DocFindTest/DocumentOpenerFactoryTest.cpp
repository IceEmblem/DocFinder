#include <gtest/gtest.h>
#include "../../../src/DocFind/HeaderFiles/DocumentOpenerFactory.hpp"

using namespace DocFind;

static std::string testDocPath;
static std::string testExecPath;
class DocumentOpenerTestClass : public DocumentOpener{
public:
    std::string getExecName() const{
        return "testExecName";
    };

    bool isCanOpen(std::string docPostfix) const{
        if(docPostfix == "testDocPostfix"){
            return true;
        }

        return false;
    }

    // 将 docPath 和 execPath 写入全局变量中
    void open(std::string docPath, std::string execPath) const{
        testDocPath = docPath;
        testExecPath = execPath;
    }
};

static std::string programDirPath = "./test/bin";

class DocumentOpenerFactoryTest : public testing::Test{
public:
    // 第一个测试用例开始时调用
    static void SetUpTestCase()
    {
        DocumentOpenerFactory::RegisterBuiltInOpener();
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

TEST_F(DocumentOpenerFactoryTest, baseTest)
{
    // 测试 Register 方法；
    DocumentOpenerFactory::Register(std::make_shared<DocumentOpenerTestClass>());

    // 测试 getDocumentOpener 方法
    DocumentOpenerFactory documentOpenerFactory(programDirPath);
    auto opener = documentOpenerFactory.getDocumentOpener("testDocPostfix");
    EXPECT_EQ(opener->getExecName(), "testExecName");

    // 测试 registerExecPath 方法
    documentOpenerFactory.registerExecPath("testExecName", "testExecPath");

    // 测试 open 方法
    documentOpenerFactory.open("./file.testDocPostfix");
    EXPECT_EQ(testDocPath, "./file.testDocPostfix");
    EXPECT_EQ(testExecPath, "testExecPath");
}