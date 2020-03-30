#include <string>
#include <memory>
#include <sstream>
#include "../../Infrastructure/HeaderFiles/FileOperate.hpp"
#include "../../Infrastructure/HeaderFiles/DirectoriesOperate.hpp"
#include "../HeaderFiles/DocumentManager.hpp"
#include "../HeaderFiles/Directories.hpp"
#include "../HeaderFiles/AppConfiguration.hpp"

using namespace Infrastructure;

namespace DocFind
{
    // 根据路径查找文档，使用折中算法
    static int getDocIndexForPath(std::vector<std::shared_ptr<Document>> &docs, std::string path)
    {
        int minIndex = 0;
        int maxIndex = docs.size() - 1;
        int middleIndex = (minIndex + maxIndex) / 2;
        if((minIndex + maxIndex) % 2 > 0){
            middleIndex++;
        }

        while (true)
        {
            int result = docs[middleIndex]->relativePath.compare(path);
            if(result == 0){
                return middleIndex;
            }

            // 如果最大路径和最小路径相等则没有匹配
           if(minIndex == maxIndex){
                return -1;
            }

            // 如果 中间路径 > 比较的路径
            if(result > 0){
                maxIndex = middleIndex;
                // 这里生成的中间索引取较小的（如：(1+2)/2 等于 1.5，我们取 1 而不是2，因为 2 是原先的中间索引，而中间索引我们刚比较过）
                middleIndex = (minIndex + maxIndex) / 2;
                continue;
            }

            // 如果 中间路径 < 比较路径
            if(result < 0){
                minIndex = middleIndex;
                // 这里生成的中间索引取较大的（如：(1+2)/2 等于 1.5，我们取 2 而不是 1，因为 1 是原先的中间索引，而中间索引我们刚比较过）
                middleIndex = (minIndex + maxIndex) / 2;
                if((minIndex + maxIndex) % 2 > 0){
                    middleIndex++;
                }
                continue;
            }
        }
        
    }

    // 获取目录的所有文件
    static std::vector<std::shared_ptr<Document>> getDocuments(std::shared_ptr<DFFile> file)
    {
        std::vector<std::shared_ptr<Document>> files;

        if(!file->isDir){
            return files;
        }

        std::shared_ptr<Directories> dir = std::static_pointer_cast<Directories>(file);
        for(auto file : dir->childs) {
            if(file->isDir){
                auto childFiles = getDocuments(file);
                for(auto childFile : childFiles){
                    files.push_back(childFile);
                }
                continue;
            }

            files.push_back(std::static_pointer_cast<Document>(file));
        }

        return files;
    }

    // 字符串替换
    static std::string subreplace(std::string resource_str, std::string sub_str, std::string new_str)
    {
        std::string::size_type pos = 0;
        while((pos = resource_str.find(sub_str)) != std::string::npos)   //替换所有指定子串
        {
            resource_str.replace(pos, sub_str.length(), new_str);
        }
        return resource_str;
    }

    // 从文件读取KeyWordToDoc
    void DocumentManager::readKeyWordToDocFromFile()
    {
        // 实例 keyWordToDocs 列表
        keyWordToDocs = std::make_shared<std::vector<KeyWordToDoc>>(std::vector<KeyWordToDoc>());

        // 如果文件不存在，则创建文件
        if(!FileOperate::isExistFile(AppConfiguration::getKeyWordToDocsPath(_dirPath))){
            std::string path = DirectoriesOperate::getDirPath(AppConfiguration::getKeyWordToDocsPath(_dirPath));
            DirectoriesOperate::createDir(path);

            FileOperate::createFile(AppConfiguration::getKeyWordToDocsPath(_dirPath));
            return;
        }

        std::string text = FileOperate::getFileText(AppConfiguration::getKeyWordToDocsPath(_dirPath));

        std::stringstream keyWordToDocFile(text);

        std::string line;
        while (std::getline(keyWordToDocFile, line))
        {
            std::istringstream lineStringStram;
            lineStringStram.str(line);

            // 第一个为路径
            std::string path;
            lineStringStram >> path;
            path = subreplace(path, "%20", " ");

            // 其余为关键字
            std::vector<std::string> keys;
            std::string key;
            while (lineStringStram >> key)
            {
                keys.push_back(key);
            }
            
            KeyWordToDoc keyWordToDoc(path,  keys);
            keyWordToDocs->push_back(keyWordToDoc);
        }
    }

    // 将KeyWordToDoc写入到文件
    void DocumentManager::writeKeyWordToDocToFile()
    {
        std::stringstream file;

        for(auto keyWordToDoc : *keyWordToDocs){
            file << subreplace(keyWordToDoc.relativePath, " ", "%20") + " ";
            for(auto key : keyWordToDoc.keys)
            {
                file << key + " ";
            }
            file << std::endl;
        }

        FileOperate::writeFileText(AppConfiguration::getKeyWordToDocsPath(_dirPath), file.str());
    }

    // 将关键字添加到文档对象中
    void DocumentManager::addKeysToDocObject(std::vector<std::shared_ptr<Document>> &docs)
    {
        for(auto keyWordToDoc : *keyWordToDocs){
            int index = getDocIndexForPath(docs, keyWordToDoc.relativePath);
            if(index < 0){
                continue;
            }

            for(auto key : keyWordToDoc.keys){
                docs[index]->keys.push_back(key);
            }
        }
    }

    void DocumentManager::deleteKeyWordToDocOfNoExistDoc(std::vector<std::shared_ptr<Document>> &docs){
        bool isNeedUpdateFile = false;
        std::vector<KeyWordToDoc>::iterator removeItems;
        for(auto keyWordToDoc = keyWordToDocs->begin();
            keyWordToDoc != keyWordToDocs->end();
            keyWordToDoc++
        ){
            int index = getDocIndexForPath(docs, keyWordToDoc->relativePath);
            if(index >= 0){
                continue;
            }

            keyWordToDocs->erase(keyWordToDoc);
            keyWordToDoc--;
            isNeedUpdateFile = true;
        }

        if(isNeedUpdateFile == true){
            writeKeyWordToDocToFile();
        }
    }

    void DocumentManager::readDocTitleFromFile(){
        _documentTitles = std::make_shared<std::map<std::string, DocumentTitle>>();

        // 如果文件不存在，则创建文件
        if(!FileOperate::isExistFile(AppConfiguration::getDocumentTitlesPath(_dirPath)))
        {
            std::string path = DirectoriesOperate::getDirPath(AppConfiguration::getDocumentTitlesPath(_dirPath));
            DirectoriesOperate::createDir(path);

            FileOperate::createFile(AppConfiguration::getDocumentTitlesPath(_dirPath));
            return;
        }

        std::string text = FileOperate::getFileText(AppConfiguration::getDocumentTitlesPath(_dirPath));
        std::stringstream file(text);
        std::string line;
        while (std::getline(file, line)){
            std::istringstream lineStringStram;
            lineStringStram.str(line);

            // 第一个为路径
            std::string path;
            lineStringStram >> path;
            path = subreplace(path, "%20", " ");

            // 第二个为最后修改时间
            time_t lastModifiedTime;
            lineStringStram >> lastModifiedTime;

            // 最后都是标题
            std::vector<std::string> titles;
            std::string title;
            while (lineStringStram >> title)
            {
                titles.push_back(title);
            }

            _documentTitles->insert(std::make_pair(path, DocumentTitle(path, lastModifiedTime, titles)));
        }
    }

    void DocumentManager::writeDocTitleToFile(){
        std::stringstream file;

        for(auto docTitlePair : *_documentTitles){
            auto docTitle = docTitlePair.second;
            file << subreplace(docTitle.relativePath, " ", "%20") + " ";
            file << docTitle.lastModifiedTime << " ";
            for(auto title : docTitle.titles)
            {
                file << title + " ";
            }
            file << std::endl;
        }

        FileOperate::writeFileText(AppConfiguration::getDocumentTitlesPath(_dirPath), file.str());
    }

    // 读取文档内容，将文档内容的标题作为关键字添加到文档对象中
    void DocumentManager::addTitleToDocObject(std::vector<std::shared_ptr<Document>> &docs){
        // 是否需要更新存放标题的文件
        bool isNeedUpdateTitleFile = false;
        for(auto doc : docs){

            // 如果 _documentTitles 中不存在
            if(_documentTitles->find(doc->relativePath) == _documentTitles->end()){
                auto reader = _documentReaderFactory->getDocumentReader(FileOperate::getPostfix(doc->relativePath));
                // 没有对应的文档读取器
                if(reader == nullptr){
                    continue;
                }
                
                // 说明文档是新建的
                std::vector<std::string> titles;
                try{
                    titles = reader->getDocTitle(_dirPath + doc->relativePath);
                }
                catch(std::exception& ex){
                    continue;
                }

                _documentTitles->insert(std::make_pair(doc->relativePath, DocumentTitle(doc->relativePath, doc->lastModifiedTime, titles)));
                isNeedUpdateTitleFile = true;
            }

            DocumentTitle& docTitle = _documentTitles->at(doc->relativePath);

            // 如果文件有更新
            if(doc->lastModifiedTime > docTitle.lastModifiedTime){
                // 更新标题
                auto reader = _documentReaderFactory->getDocumentReader(FileOperate::getPostfix(doc->relativePath));

                std::vector<std::string> titles;
                try{
                    titles = reader->getDocTitle(_dirPath + doc->relativePath);
                }
                catch(std::exception& ex){
                    continue;
                }

                docTitle.titles = titles;
                isNeedUpdateTitleFile = true;
            }

            // 将标题添加到关键字
            for(auto title : docTitle.titles){
                doc->keys.push_back(title);
            }
        }

        if(isNeedUpdateTitleFile){
            writeDocTitleToFile();
        }
    }

    // 删除不存在对应文档的标题
    void DocumentManager::deleteTitleOfNoExitstDoc(std::vector<std::shared_ptr<Document>> &docs){
        std::vector<std::string> removeItems;
        for(auto docTitle : *_documentTitles){
            auto docIndex = getDocIndexForPath(docs, docTitle.first);
            if(docIndex == -1){
                removeItems.push_back(docTitle.first);
                continue;
            }
        }

        // 是否需要更新存放标题的文件
        bool isNeedUpdateTitleFile = false;
        for(auto removeItem : removeItems)
        {
            _documentTitles->erase(removeItem);
            isNeedUpdateTitleFile = true;
        }

        if(isNeedUpdateTitleFile){
            writeDocTitleToFile();
        }
    }
    
    std::shared_ptr<Directories> DocumentManager::createDirectories(std::string relativePath, std::vector<std::string> keys)
    {
        // 过滤 程序文件
        if(relativePath == AppConfiguration::DataFileDirPath){
            return nullptr;
        }

        std::map<std::string, bool> childFiles;
        try{
            childFiles = DirectoriesOperate::getFiles(_dirPath + relativePath);
        }
        catch(std::exception&)
        {
            return nullptr;
        }
        std::vector<std::shared_ptr<DFFile>> childs;

        for(auto childFile : childFiles){
            // 一个 zz 的 bug，对与很奇葩的目录字符（如：ﾒﾀﾀｵjar），子文件的 name 会为空
            if(childFile.first == ""){
                continue;
            }
            std::vector<std::string> childKeys = keys;
            childKeys.push_back(childFile.first);

            std::string childFileRelativePath = relativePath + "/" + childFile.first;

            if(childFile.second == true){
                auto pt = createDirectories(childFileRelativePath, childKeys);
                if(pt != nullptr){
                    childs.push_back(pt);
                }
            }
            else{
                childs.push_back(std::make_shared<Document>(
                        Document(
                            childFileRelativePath,
                            FileOperate::getModifiedTime(_dirPath + childFileRelativePath),
                            childKeys)));
            }
        }

        // 对子文件进行排序
        std::sort(childs.begin(), childs.end(), [](std::shared_ptr<DFFile>  left, std::shared_ptr<DFFile>  right){
            return right->relativePath.compare(left->relativePath) > 0 ? true : false;
        });

        return std::make_shared<Directories>(
            Directories(
                relativePath, 
                keys, 
                childs));
    }

    DocumentManager::DocumentManager(std::string dirPath):_dirPath(dirPath)
    {
        _dir = createDirectories("", {});
        DocumentReaderFactory::RegisterBuiltInReader();
        _documentReaderFactory = std::make_shared<DocumentReaderFactory>();
        readKeyWordToDocFromFile();
        readDocTitleFromFile();

        std::vector<std::shared_ptr<Document>> docs = DocFind::getDocuments(_dir);
        addKeysToDocObject(docs);
        deleteKeyWordToDocOfNoExistDoc(docs);
        addTitleToDocObject(docs);
        deleteTitleOfNoExitstDoc(docs);
        keyDocument = std::make_shared<std::vector<std::shared_ptr<Document>>>(docs);
    }
    
    // 将关键字关联到文档
    void DocumentManager::addKeyWordToDoc(std::string key, std::shared_ptr<Document> doc)
    {
        KeyWordToDoc *oldKeyWordToDoc = nullptr;
        
        for(auto keyWordToDoc = keyWordToDocs->begin(); keyWordToDoc != keyWordToDocs->end(); keyWordToDoc++)
        {
            if(keyWordToDoc->relativePath == doc->relativePath){
                oldKeyWordToDoc = &*keyWordToDoc;
            }
        }

        if(oldKeyWordToDoc){
            // 判断旧的 oldKeyWordToDoc 是否包含该关键字
            bool isHadKey = false;
            for(auto oldKey : oldKeyWordToDoc->keys){
                if(oldKey.find(key) != oldKey.npos) {
                    isHadKey = true;
                    break;
                }
            }

            if(!isHadKey)
                oldKeyWordToDoc->keys.push_back(key);
        }
        else{
            KeyWordToDoc newKeyWordToDoc(doc->relativePath, { key });
            keyWordToDocs->push_back(newKeyWordToDoc);
        }

        doc->keys.push_back(key);

        writeKeyWordToDocToFile();
    }

    void DocumentManager::addKeyWordToDoc(std::string key, std::string docPath){
        int index = getDocIndexForPath(*keyDocument, docPath);
        if(index < 0){
            return;
        }

        addKeyWordToDoc(key, (*keyDocument)[index]);
    }

    // 获取文档
    std::vector<std::shared_ptr<Document>> DocumentManager::getDocuments()
    {
        return *keyDocument;
    }

    // 获取文件完整路径
    std::string DocumentManager::getFullPath(std::shared_ptr<DFFile> file){
        return getFullPath(file.get());
    }

    std::string DocumentManager::getFullPath(DFFile* file){
        return getFullPath(file->relativePath);
    }

    std::string DocumentManager::getFullPath(std::string relativePath){
        return _dirPath + relativePath;
    }
} // namespace DocFind
