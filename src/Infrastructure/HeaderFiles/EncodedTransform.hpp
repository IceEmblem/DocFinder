#ifndef EncodedTransform_H
#define EncodedTransform_H

#include <string>
#include <locale>
#include <codecvt>
#include <string>

namespace Infrastructure
{
    class EncodedTransform
    {
    private:
        /* data */
    public:
        static std::string UTF8ToGBK(std::string src);
        static std::string GBKToUTF8(std::string src);

        static std::string SystemEncodedToUT8(std::string src);
        static std::string UT8ToSystemEncoded(std::string src);
    };
    
} // namespace Infrastructure

#endif