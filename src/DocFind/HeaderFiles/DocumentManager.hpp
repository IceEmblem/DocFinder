#ifndef DocumentManager_H
#define DocumentManager_H

#include <string>
#include <vector>
#include <memory>
#include "./Document.hpp"
#include "./Directories.hpp"
#include "./KeyWordToDoc.hpp"

namespace DocFind
{
    class DocumentManager
    {
    private:
        std::shared_ptr<Directories> _dir;
    public:
        DocumentManager(std::string dirPath);

        void addKeyWordToDoc(std::string key, Document doc) const;

        std::vector<std::shared_ptr<Document>> getDocuments() const;
    };
} // namespace DocFind
#endif