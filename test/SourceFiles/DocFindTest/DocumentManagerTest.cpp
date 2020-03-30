#include <gtest/gtest.h>
#include <sstream>
#include "../../../src/DocFind/HeaderFiles/DocumentManager.hpp"
#include "../../../src/Infrastructure/HeaderFiles/FileOperate.hpp"
#include "../../../src/Infrastructure/HeaderFiles/DirectoriesOperate.hpp"

using namespace  DocFind;
using namespace Infrastructure;
using namespace std;

static std::string currentDirPath = "./test/bin/DocumentManagerTestDir";

// 测试类
class DocumentManagerTest:public testing::Test
{
public:
    // 每个测试用例开始时调用
    void SetUp()
    {
        DirectoriesOperate::createDir(currentDirPath);
    }

    // 每个测试用例结束后调用
    void TearDown()
    {
        system(("rm -r " + currentDirPath).c_str());
    } 
};

TEST_F(DocumentManagerTest, getDocuments)
{
    FileOperate::createFile(currentDirPath+"/getDocuments_file.txt");
    
    DocumentManager documentManager(currentDirPath);
    auto results = documentManager.getDocuments();

    bool isHaveFile = false;
    for(auto result : results){
        if(result->name == "getDocuments_file.txt"){
            isHaveFile = true;
            EXPECT_EQ(result->relativePath, "/getDocuments_file.txt");
            EXPECT_EQ(result->keys[0], "getDocuments_file.txt");
        }
    }

    EXPECT_EQ(isHaveFile, true);
}

// 文档的关键字包含标题
TEST_F(DocumentManagerTest, getDocuments_docTitle)
{
    std::string filePath = currentDirPath + "/getDocuments_docTitle.txt";
    stringstream file;
    file << "title" << std::endl;
    file << "content" << std::endl;
    FileOperate::writeFileText(filePath, file.str());

    DocumentManager documentManager(currentDirPath);
    auto docs = documentManager.getDocuments();
    std::shared_ptr<Document> finddoc;
    for(auto doc : docs){
        if(doc->name == "getDocuments_docTitle.txt"){
            finddoc = doc;
            break;
        }
    }

    bool isExitTitle = false;
    for(auto key : finddoc->keys){
        if(key == "title"){
            isExitTitle = true;
            break;
        }
    }

    EXPECT_EQ(isExitTitle, true);
}

// 文档的关键字包含标题，文档路径包含空格
TEST_F(DocumentManagerTest, getDocuments_docTitle_pathHaveSpace)
{
    std::string filePath = currentDirPath + "/getDocuments docTitle.txt";
    stringstream file;
    file << "title" << std::endl;
    file << "content" << std::endl;
    FileOperate::writeFileText(filePath, file.str());

    DocumentManager documentManager(currentDirPath);
    auto docs = documentManager.getDocuments();
    std::shared_ptr<Document> finddoc;
    for(auto doc : docs){
        if(doc->name == "getDocuments docTitle.txt"){
            finddoc = doc;
            break;
        }
    }

    bool isExitTitle = false;
    for(auto key : finddoc->keys){
        if(key == "title"){
            isExitTitle = true;
            break;
        }
    }

    EXPECT_EQ(isExitTitle, true);
}

TEST_F(DocumentManagerTest, addKeyWordToDoc)
{
    FileOperate::createFile(currentDirPath+"/addKeyWordToDoc_file.txt");

    DocumentManager documentManager(currentDirPath);
    auto results = documentManager.getDocuments();
    std::shared_ptr<Document> file3Doc;

    for(auto result : results){
        if(result->name == "addKeyWordToDoc_file.txt"){
            file3Doc = result;
            break;
        }
    }

    documentManager.addKeyWordToDoc("addKeyWordToDocKey", file3Doc);

    DocumentManager newDocumentManager(currentDirPath);
    auto newResults = newDocumentManager.getDocuments();
    std::shared_ptr<Document> newFile3Doc;

    for(auto result : newResults){
        if(result->name == "addKeyWordToDoc_file.txt"){
            newFile3Doc = result;
            break;
        }
    }

    bool isHadKey = false;
    for(auto key : newFile3Doc->keys){
        if(key == "addKeyWordToDocKey"){
            isHadKey = true;
            break;
        }
    }
    
    EXPECT_EQ(isHadKey, true);
}

// 路径包含空格
TEST_F(DocumentManagerTest, addKeyWordToDoc_pathHaveSpace)
{
    FileOperate::createFile(currentDirPath+"/addKeyWordToDoc file.txt");

    DocumentManager documentManager(currentDirPath);
    auto results = documentManager.getDocuments();
    std::shared_ptr<Document> file3Doc;

    for(auto result : results){
        if(result->name == "addKeyWordToDoc file.txt"){
            file3Doc = result;
            break;
        }
    }

    documentManager.addKeyWordToDoc("addKeyWordToDocKey", file3Doc);

    DocumentManager newDocumentManager(currentDirPath);
    auto newResults = newDocumentManager.getDocuments();
    std::shared_ptr<Document> newFile3Doc;

    for(auto result : newResults){
        if(result->name == "addKeyWordToDoc file.txt"){
            newFile3Doc = result;
            break;
        }
    }

    bool isHadKey = false;
    for(auto key : newFile3Doc->keys){
        if(key == "addKeyWordToDocKey"){
            isHadKey = true;
            break;
        }
    }
    
    EXPECT_EQ(isHadKey, true);
}