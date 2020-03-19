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
    // 第一个测试用例开始时调用
    static void SetUpTestCase()
    {
        DirectoriesOperate::createDir(currentDirPath);
    }
    
    // 最后一个测试用例结束后调用
    static void TearDownTestCase()
    {
        system(("rm -r " + currentDirPath).c_str());
    }

    // 每个测试用例开始时调用
    void SetUp()
    {
        std::string path = currentDirPath+"/DocFinder/KeyWordToDocs.txt";
        if(FileOperate::isExistFile(path)){
            // 清理文档
            FileOperate::writeFileText(path, "");
        }
    }

    // 每个测试用例结束后调用
    void TearDown()
    {
    } 
};

TEST_F(DocumentManagerTest, getDocuments)
{
    DirectoriesOperate::createDir(currentDirPath + "/getDocumentsDir");
    FileOperate::createFile(currentDirPath+"/getDocumentsDir/getDocuments_file.txt");
    
    DocumentManager documentManager(currentDirPath);
    auto results = documentManager.getDocuments();

    bool isHaveFile = false;
    for(auto result : results){
        if(result->name == "getDocuments_file.txt"){
            isHaveFile = true;
            EXPECT_EQ(result->relativePath, "/getDocumentsDir/getDocuments_file.txt");
            EXPECT_EQ(result->keys[0], "getDocumentsDir");
            EXPECT_EQ(result->keys[1], "getDocuments_file.txt");
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
    DirectoriesOperate::createDir(currentDirPath + "/addKeyWordToDocDir");
    FileOperate::createFile(currentDirPath+"/addKeyWordToDocDir/addKeyWordToDoc_file.txt");

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
    DirectoriesOperate::createDir(currentDirPath + "/addKeyWordToDocDir");
    FileOperate::createFile(currentDirPath+"/addKeyWordToDocDir/addKeyWordToDoc file.txt");

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