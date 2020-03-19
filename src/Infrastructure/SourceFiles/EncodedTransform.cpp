#include <vector>
#include "../HeaderFiles/EncodedTransform.hpp"


static std::string gb2312_to_utf8(std::string& src)
{
    std::vector<wchar_t> buff(src.size());
    #ifdef _MSC_VER
    std::locale loc("zh-CN");
    #else
    std::locale loc("zh_CN.GB18030");
    #endif
    wchar_t* pwszNext = nullptr;
    const char* pszNext = nullptr;
    mbstate_t state = {};
    int res = std::use_facet<std::codecvt<wchar_t, char, mbstate_t> >
    (loc).in(state,
    src.data(), src.data() + src.size(), pszNext,
    buff.data(), buff.data() + buff.size(), pwszNext);

    if (std::codecvt_base::ok == res)
    {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> cutf8;
    return cutf8.to_bytes(std::wstring(buff.data(), pwszNext));
    }

    return "";
}

static std::string utf8_to_gb2312(std::string& src)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> cutf8;
    std::wstring wTemp = cutf8.from_bytes(src);
    #ifdef _MSC_VER
    std::locale loc("zh-CN");
    #else
    std::locale loc("zh_CN.GB18030");
    #endif
    const wchar_t* pwszNext = nullptr;
    char* pszNext = nullptr;
    mbstate_t state = {};

    std::vector<char> buff(wTemp.size() * 2);
    int res = std::use_facet<std::codecvt<wchar_t, char, mbstate_t> >
    (loc).out(state,
    wTemp.data(), wTemp.data() + wTemp.size(), pwszNext,
    buff.data(), buff.data() + buff.size(), pszNext);

    if (std::codecvt_base::ok == res)
    {
    return std::string(buff.data(), pszNext);
    }
    return "";
}
namespace Infrastructure{
    #ifdef _SysEncodeGBK
    std::string EncodedTransform::SystemEncodedToUT8(std::string src){
        return gb2312_to_utf8(src);
    }

    std::string EncodedTransform::UT8ToSystemEncoded(std::string src){
        return utf8_to_gb2312(src);
    }
    #endif

    #ifdef _SysEncodeUTF8
    std::string EncodedTransform::SystemEncodedToUT8(std::string src){
        return src;
    }

    std::string EncodedTransform::UT8ToSystemEncoded(std::string src){
        return src;
    }
    #endif
}