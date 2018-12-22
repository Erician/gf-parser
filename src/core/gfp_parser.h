#ifndef GFP_CORE_GFP_PARSER_H_
#define GFP_CORE_GFP_PARSER_H_

#include <string>

namespace gfp {

class Parser {
private:
    std::string file_name_;
public:
    Parser(std::string file_name);
    int Parse();
};

} //name space gfp

#endif