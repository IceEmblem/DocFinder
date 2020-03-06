#ifndef CommandContext_H
#define CommandContext_H

#include <map>
#include <string>
#include <memory>

class CommandContext
{
private:
    std::map<std::string, std::shared_ptr<void>> _datas;

    CommandContext() = default;
public:
    static std::shared_ptr<CommandContext> Instances();

    std::shared_ptr<void> getData(std::string key);

    void setData(std::string key, std::shared_ptr<void> data);
};

#endif