#ifndef GFP_COMMAND_GFP_COMMAND_FACTORY_H_
#define GFP_COMMAND_GFP_COMMAND_FACTORY_H_

#ifndef GFP_COMMAND_GFP_COMMAND_H_
#include "command/gfp_command.h"
#endif


namespace gfp{

class CommandFactory {
private:

public:
    static Command* CreateCommand(unsigned char opcode);
};

} // namespace gfp

#endif