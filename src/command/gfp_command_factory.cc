#ifndef GFP_COMMAND_GFP_COMMAND_FACTORY_H_
#include "command/gfp_command_factory.h"
#endif

#ifndef GFP_COMMAND_GFP_OPCODE_H_
#include "command/gfp_opcode.h"
#endif

/* ugly code, I know */

namespace gfp{

Command* CommandFactory::CreateCommand(unsigned char opcode){
    if(opcode >= opcode::PAINT_0 && opcode <= opcode::PAINT_63) {
        return (new Paint_N())->WithOpcode(opcode);
    }else if(opcode >= opcode::PAINT1 && opcode <= opcode::PAINT3) {
        return (new PaintN())->WithOpcode(opcode);
    }else if(opcode == opcode::BOC) {
        return (new Boc())->WithOpcode(opcode);
    }else if(opcode == opcode::BOCl) {
        return (new Boc1())->WithOpcode(opcode);
    }else if(opcode == opcode::EOC) {
        return (new Eoc())->WithOpcode(opcode);
    }else if(opcode >= opcode::SKIP0 && opcode <= opcode::SKIP2) {
        return (new SkipN())->WithOpcode(opcode);
    }else if(opcode >= opcode::NEW_ROW_0 && opcode <= opcode::NEW_ROW_164) {
        return (new NewRow_N())->WithOpcode(opcode);
    }else if(opcode >= opcode::XXX1 && opcode <= opcode::XXX4){
        return (new XxxN())->WithOpcode(opcode);
    }else if(opcode == opcode::yyy) {
        return (new Yyy())->WithOpcode(opcode);
    }else if(opcode == opcode::NO_OP){
        return (new NoOp())->WithOpcode(opcode);
    }else if(opcode == opcode::CHAR_LOC) {
        return (new CharLoc())->WithOpcode(opcode);
    }else if(opcode == opcode::CHAR_LOC0) {
        return (new CharLoc0())->WithOpcode(opcode);
    }else if(opcode == opcode::PRE){
        return (new Pre())->WithOpcode(opcode);
    }else if(opcode == opcode::POST) {
        return (new Post())->WithOpcode(opcode);
    }else if(opcode == opcode::POST_POST) {
        return (new PostPost())->WithOpcode(opcode);
    }else{
        return (new Undefined())->WithOpcode(opcode);
    }
}

} // namespace gfp