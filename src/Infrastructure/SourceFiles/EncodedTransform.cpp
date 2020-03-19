#include <vector>
#include <locale>
#include "../HeaderFiles/EncodedTransform.hpp"

#ifdef _WIN32

#include <windows.h>

std::string GbkToUtf8(std::string src)
{
    const char *src_str = src.c_str();
	int len = MultiByteToWideChar(CP_ACP, 0, src_str, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_ACP, 0, src_str, -1, wstr, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
	std::string strTemp = str;
	if (wstr) delete[] wstr;
	if (str) delete[] str;
	return strTemp;
}

std::string Utf8ToGbk(std::string src)
{
    const char *src_str = src.c_str();

	int len = MultiByteToWideChar(CP_UTF8, 0, src_str, -1, NULL, 0);
	wchar_t* wszGBK = new wchar_t[len + 1];
	memset(wszGBK, 0, len * 2 + 2);
	MultiByteToWideChar(CP_UTF8, 0, src_str, -1, wszGBK, len);
	len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
	char* szGBK = new char[len + 1];
	memset(szGBK, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, len, NULL, NULL);
	std::string strTemp(szGBK);
	if (wszGBK) delete[] wszGBK;
	if (szGBK) delete[] szGBK;
    
	return strTemp;
}
#else
#include <iconv.h>

int code_convert(char *from_charset, char *to_charset, char *inbuf, size_t inlen,  
        char *outbuf, size_t outlen) {  
    iconv_t cd;  
    char **pin = &inbuf;  
    char **pout = &outbuf;  
  
    cd = iconv_open(to_charset, from_charset);  
    if (cd == 0)  
        return -1;  
    memset(outbuf, 0, outlen);  
    if (iconv(cd, pin, &inlen, pout, &outlen) == -1)  
        return -1;  
    iconv_close(cd);  
    *pout = '\0';  
  
    return 0;  
}  
  
int u2g(char *inbuf, size_t inlen, char *outbuf, size_t outlen) {  
    return code_convert("utf-8", "gb2312", inbuf, inlen, outbuf, outlen);  
}  
  
int g2u(char *inbuf, size_t inlen, char *outbuf, size_t outlen) {  
    return code_convert("gb2312", "utf-8", inbuf, inlen, outbuf, outlen);  
} 
#endif

namespace Infrastructure{
    #ifdef _SysEncodeGBK
    std::string EncodedTransform::SystemEncodedToUT8(std::string src){
        return GbkToUtf8(src);
    }

    std::string EncodedTransform::UT8ToSystemEncoded(std::string src){
        return Utf8ToGbk(src);
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