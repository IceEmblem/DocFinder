#ifndef DocumentOpenerFactory_H
#define DocumentOpenerFactory_H

#include <string>
#include "./DocumentOpener.hpp"

namespace DocFind
{
    class DocumentOpenerFactory
    {
    private:
        /* data */
    public:
        // 注册 文档打开器，TDocumentOpener必须继承DocumentOpener
        template<typename TDocumentOpener>
        static void Register(TDocumentOpener* opener);

        // 获取 文档打开器
        std::shared_ptr<DocumentOpener> getDocumentOpener(std::string docPostfix) const;
    };    
} // namespace DocFind
#endif