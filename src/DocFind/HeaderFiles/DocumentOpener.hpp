#ifndef DocumentOpener_H
#define DocumentOpener_H

#include <string>

namespace DocFind
{
    class DocumentOpener
    {
    private:

    public:
        // 生成通用命令
        static std::string createCommandCmd(std::string docPath, std::string execPath){
            std::string cmd;
            #ifdef _WIN32
                cmd =  = "\"\"" + execPath + "\"" + " " + "\"" + docPath + "\"\"";
            #else
                cmd = "\"" + execPath + "\"" + " " + "\"" + docPath + "\"";
            #endif
            return cmd;
        }
        virtual std::string getExecName() const = 0;
        virtual bool isCanOpen(std::string docPostfix) const = 0;
        virtual void open(std::string docPath, std::string execPath) const = 0;
    }; 
} // namespace DocFind
#endif