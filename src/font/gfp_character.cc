#ifndef GFP_Font_GFP_CHARACTER_H_
#include "font/gfp_character.h"
#endif

#ifndef GFP_COMMAND_GFP_COMMAND_FACTORY_H_
#include "command/gfp_command_factory.h"
#endif

#ifndef GFP_COMMAND_GFP_OPCODE_H_
#include "command/gfp_opcode.h"
#endif

namespace gfp{

Character::Character(){
    commands_ = std::vector<gfp::Command *>();
}

void Character::SetCharacterCode(unsigned int character_code){
    character_code_ = character_code;
}

unsigned int Character::GetCharacterCode(){
    return character_code_;
}

void Character::AddCommand(gfp::Command* command){
    commands_.push_back(command);
}

Character * Character::Parse(std::ifstream *ifs) {
    char opcode;
    while(!ifs->eof()) {
        ifs->get(opcode);
        Command * command = CommandFactory::CreateCommand((unsigned char)opcode);
        this->AddCommand(command->Parse(ifs));
        if(opcode == opcode::EOC){
            return this;
        }
    }
    return this;
}

int Character::Draw(Pen *pen, DrawingBoard *drawing_board){
    for(int i=0; i<commands_.size(); i++){
        if(commands_[i]->Draw(pen, drawing_board) != 0){
            return -1;
        }
    }
    return 0;
}

} // namespace gfp