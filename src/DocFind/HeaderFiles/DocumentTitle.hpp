#ifndef DocumentTitle_H
#define DocumentTitle_H

#include <string>
#include <vector>

namespace DocFind
{
    class DocumentTitle
    {
    private:
        /* data */
    public:
        DocumentTitle(
            std::string relativePath, 
            time_t lastModifiedTime, 
            std::vector<std::string> titles): 
            relativePath(relativePath), 
            lastModifiedTime(lastModifiedTime),
            titles(titles)
        {
        }
        
        std::string relativePath;
        time_t lastModifiedTime;
        std::vector<std::string> titles;
    };
} // namespace DocFind

#endif