#include <vector>
#include <sstream>
#include <regex>
#include "../../../DuckX/src/duckx.hpp"
#include "../../HeaderFiles/DocumentReaders/DocxReader.hpp"

namespace DocFind
{
    bool DocxReader::isCanReader(std::string docPostfix){
        static std::vector<std::string> postfixs = {"docx"};
        for(auto postfix : postfixs){
            if(docPostfix == postfix){
                return true;
            }
        }

        return false;
    }

    std::string DocxReader::getDocText(std::string docPath){
        duckx::Document doc(docPath);   
        doc.open();

        std::stringstream textStream;
        for (auto p = doc.paragraphs(); p.has_next() ; p.next()) {
            for (auto r = p.runs(); r.has_next(); r.next()) {
                textStream << r.get_text() << std::endl;
            }
        }

        return textStream.str();
    }

    std::vector<std::string> DocxReader::getDocTitle(std::string docPath){
        duckx::Document doc(docPath);   
        doc.open();

        std::vector<std::string> titles;
        for (auto p = doc.paragraphs(); p.has_next() ; p.next()) {
            for (auto r = p.runs(); r.has_next(); r.next()) {
                // 获取 w:rPr 节点
                auto wrpr = r.get_current().child("w:rPr");
                // 获取 w:b 节点
                auto wb = wrpr.child("w:b");
                // 获取 w:val 特性
                auto att = wb.attribute("w:val");
                // 如果特性值为 0 则表示不是粗体
                if(att && att.value() == "0"){
                    continue;
                }
                
                std::string text = r.get_text();
                static std::regex textRegex("^([a-zA-Z]+|.){1,15}$");
                std::smatch sresult;
                if(std::regex_search(text, sresult, textRegex)){
                    titles.push_back(text);
                }
            }
        }

        return titles;
    }
} // namespace DocFind
