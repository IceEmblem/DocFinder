#include "../HeaderFiles/DocumentReaderFactory.hpp"

namespace DocFind
{
    std::vector<std::shared_ptr<DocumentReader>> DocumentReaderFactory::_docReaders = std::vector<std::shared_ptr<DocumentReader>>();

    void DocumentReaderFactory::Register(std::shared_ptr<DocumentReader> reader){
        _docReaders.push_back(reader);
    }

    void DocumentReaderFactory::RegisterBuiltInReader(){

    }

    std::shared_ptr<DocumentReader> DocumentReaderFactory::getDocumentReader(std::string docPostfix) const{
        for(auto docReader : _docReaders){
            if(docReader->isCanReader(docPostfix)){
                return docReader;
            }
        }

        return nullptr;
    }
}