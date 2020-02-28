#include <gtest/gtest.h>
#include <fstream>
#include "../../../src/DocFind/HeaderFiles/DocumentManager.hpp"

using namespace  DocFind;
using namespace std;

static std::string currentDirPath = "./test/bin/DocumentManagerTestDir";

static DocumentManager * documentManager = nullptr;

// 测试类
class DocumentManagerTest:public testing::Test
{
public:
    // 第一个测试用例开始时调用
    static void SetUpTestCase()
    {
        DirectoriesOperate::createDir(currentDirPath);

        DirectoriesOperate::createDir(currentDirPath + "/ChildDir");

        // 创建测试文件
        ofstream file1(currentDirPath+"/File1.txt", fstream::out);
        file1.close();

        ofstream file2(currentDirPath+"/File2.txt", fstream::out);
        file2.close();

        ofstream file3(currentDirPath+"/ChildDir/File3.txt", fstream::out);
        file3.close();
    }
    
    // 最后一个测试用例结束后调用
    static void TearDownTestCase()
    {
    }

    // 每个测试用例开始时调用
    void SetUp()
    {
        // 清理文档
        ofstream file1(currentDirPath+"/DocFinder/KeyWordToDocs.txt", fstream::out);
        file1.close();
        documentManager = new DocumentManager(currentDirPath);
    }

    // 每个测试用例结束后调用
    void TearDown()
    {
        delete documentManager;
    } 
};

TEST_F(DocumentManagerTest, getDocuments)
{
    auto results = documentManager->getDocuments();

    EXPECT_EQ(results.size(), 4);

    bool isHaveFile3 = false;
    for(auto result : results){
        if(result->name == "File3.txt"){
            isHaveFile3 = true;
            EXPECT_EQ(result->relativePath, "/ChildDir/File3.txt");
            EXPECT_EQ(result->keys[0], "ChildDir");
            EXPECT_EQ(result->keys[1], "File3.txt");
        }
    }

    EXPECT_EQ(isHaveFile3, true);
}

TEST_F(DocumentManagerTest, addKeyWordToDoc)
{
    auto results = documentManager->getDocuments();
    std::shared_ptr<Document> file3Doc;

    for(auto result : results){
        if(result->name == "File3.txt"){
            file3Doc = result;
            break;
        }
    }

    documentManager->addKeyWordToDoc("File3TestKey", file3Doc);

    DocumentManager newDocumentManager(currentDirPath);
    auto newResults = newDocumentManager.getDocuments();
    std::shared_ptr<Document> newFile3Doc;

    for(auto result : newResults){
        if(result->name == "File3.txt"){
            newFile3Doc = result;
            break;
        }
    }

    bool isHadKey = false;
    for(auto key : newFile3Doc->keys){
        if(key == "File3TestKey"){
            isHadKey = true;
            break;
        }
    }
    
    EXPECT_EQ(isHadKey, true);
}