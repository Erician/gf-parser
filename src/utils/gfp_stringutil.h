#ifndef GFP_UTILS_GFP_STRINGUTIL_H_
#define GFP_UTILS_GFP_STRINGUTIL_H_

#include <iostream>
#include <vector>

namespace gfp
{
    namespace utils
    {
        namespace stringutil
        {
            std::vector<std::string> split(std::string src, std::string str_to_find);
            std::string strip(std::string src,char c); 
            int BytesToIntWithBigEndian(char *bytes, int start, int end);

        }; // namespace stringutil
    }; // namespace utils 

}; // namespace gfp
#endif