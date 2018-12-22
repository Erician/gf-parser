#ifndef GFP_CORE_GFP_PARSER_H_
#include "core/gfp_parser.h"
#endif

#include <fstream> 

using namespace gfp;

Parser::Parser(std::string file_name) {
    file_name_ = file_name;
}

int Parser::Parse() {
    std::ifstream ifs;
    ifs.open(file_name_, std::ifstream::in);
    char opcode;
    while(!ifs.eof()) {
        ifs.get(opcode);
        
    }
}