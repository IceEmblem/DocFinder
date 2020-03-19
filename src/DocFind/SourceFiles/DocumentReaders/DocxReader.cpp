#include <vector>
#include <sstream>
#include <regex>
#include "../../../DuckX/src/duckx.hpp"
#include "../../HeaderFiles/DocumentReaders/DocxReader.hpp"
#include "../../../Infrastructure/HeaderFiles/EncodedTransform.hpp"

using namespace Infrastructure;

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
        duckx::Document doc(EncodedTransform::UT8ToSystemEncoded(docPath));   
        doc.open();

        std::stringstream textStream;
        for (auto p = doc.paragraphs(); p.has_next() ; p.next()) {
            for (auto r = p.runs(); r.has_next(); r.next()) {
                textStream << r.get_text() << std::endl;
            }
        }

        return textStream.str();
    }

    // 移除空格
    static std::string trim(std::string s){
        int index = 0;
        if( !s.empty())
        {
            while( (index = s.find(' ',index)) != std::string::npos)
            {
                s.erase(index,1);
            }
        }

        return s;
    }

    // 获取 doxc 一段内容
    static std::string getParagraphText(duckx::Paragraph & p){
        std::string text;
        for (auto r = p.runs(); r.has_next(); r.next()) {
            text = text + r.get_text();
        }
        return text;
    }

    std::vector<std::string> DocxReader::getDocTitle(std::string docPath){
        duckx::Document doc(EncodedTransform::UT8ToSystemEncoded(docPath));   
        doc.open();

        std::vector<std::string> titles;
        for (auto p = doc.paragraphs(); p.has_next() ; p.next()) {
            std::string text = getParagraphText(p);

            // 获取 w:rPr 节点
            auto wrpr = p.get_current().child("w:pPr").child("w:rPr");
            // 获取 w:b 节点
            auto wb = wrpr.child("w:b");
            // 如果不存在wb,则不是粗体
            if(!wb){
                continue;
            }
            // 获取 w:val 特性
            auto att = wb.attribute("w:val");
            // 如果特性值为 0 则表示不是粗体
            if(att || att.value() == "0"){
                continue;
            }

            // 匹配只有符号和数字的文本
            static std::regex textRegex("^[\\x20-\\x40\\x5b-\\x60\\x7b-\\x7e\\u3002\\uff1f\\uff01\\uff0c\\u3001\\uff1b\\uff1a\\u201c\\u201d\\u2018\\u2019\\uff08\\uff09\\u300a\\u300b\\u3008\\u3009\\u3010\\u3011\\u300e\\u300f\\u300c\\u300d\\ufe43\\ufe44\\u3014\\u3015\\u2026\\u2014\\uff5e\\ufe4f\\uffe5]*$");
            std::smatch sresult;
            if(std::regex_search(text, sresult, textRegex)){
                continue;
            }

            if(text.size() > 1 && text.size() < 45){
                titles.push_back(trim(text));
            }
        }

        return titles;
    }
} // namespace DocFind
