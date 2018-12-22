#ifndef GFP_LOGGING_GFP_LOGGING_H_
#include "logging/gfp_logging.h"
#endif

#ifndef GFP_CORE_GFP_PARSER_H_
#include "core/gfp_parser.h"
#endif

int main(int argc,char *argv[]) {
    
    if(argc < 2) {
        std::cout << "Usage Error: gf-parser <input file>" << std::endl;
        return -1;
    }

    gfp::Parser parser(argv[1]);
    if(parser.Parse() != 0) {
        return -1;
    }    
    return 0;
}
