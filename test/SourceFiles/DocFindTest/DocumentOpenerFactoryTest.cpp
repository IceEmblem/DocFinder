#include <gtest/gtest.h>
#include "../../../src/DocFind/HeaderFiles/DocumentOpenerFactory.hpp"
#include "../../../src/DocFind/HeaderFiles/DirectoriesOperate.hpp"

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

static std::string programDirPath = "./test/bin/DocumentOpenerFactoryTestDir";

class DocumentOpenerFactoryTest : public testing::Test{
public:
    // 第一个测试用例开始时调用
    static void SetUpTestCase()
    {
        DirectoriesOperate::createDir(programDirPath);
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
    // 不能注册两个相同名称的打开器
    try{
        DocumentOpenerFactory::Register(std::make_shared<DocumentOpenerTestClass>());
        EXPECT_EQ(true, false);
    }
    catch(std::logic_error){
        EXPECT_EQ(true, true);
    }

    // 测试 getDocumentOpener 方法
    DocumentOpenerFactory documentOpenerFactory(programDirPath);
    auto opener = documentOpenerFactory.getDocumentOpener("testDocPostfix");
    EXPECT_EQ(opener->getExecName(), "testExecName");

    // 测试 registerExecPath 方法
    documentOpenerFactory.registerExecPath("testExecName", "testExecPath1");
    // 重复注册使用后者
    documentOpenerFactory.registerExecPath("testExecName", "testExecPath");
    // 对于注册执行路径，新建类一样有效
    DocumentOpenerFactory newDocumentOpenerFactory(programDirPath);

    // 测试 open 方法
    newDocumentOpenerFactory.open("./file.testDocPostfix");
    EXPECT_EQ(testDocPath, "./file.testDocPostfix");
    EXPECT_EQ(testExecPath, "testExecPath");
}