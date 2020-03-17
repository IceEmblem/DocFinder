#include "../HeaderFiles/DocumentReaderFactory.hpp"
#include "../HeaderFiles/DocumentReaders/TxtReader.hpp"
#include "../HeaderFiles/DocumentReaders/DocxReader.hpp"

namespace DocFind
{
    std::vector<std::shared_ptr<DocumentReader>> DocumentReaderFactory::_docReaders = std::vector<std::shared_ptr<DocumentReader>>();

    void DocumentReaderFactory::Register(std::shared_ptr<DocumentReader> reader){
        _docReaders.push_back(reader);
    }

    void DocumentReaderFactory::RegisterBuiltInReader(){
        static bool isRegister = false;
        if(isRegister){
            return;
        }

        isRegister = true;
        Register(std::make_shared<TxtReader>());
        Register(std::make_shared<DocxReader>());
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