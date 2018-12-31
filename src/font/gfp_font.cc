#ifndef GFP_FONT_GFP_FONT_H_
#include "font/gfp_font.h"
#endif

#ifndef GFP_COMMAND_GFP_COMMAND_FACTORY_H_
#include "command/gfp_command_factory.h"
#endif

#ifndef GFP_COMMAND_GFP_OPCODE_H_
#include "command/gfp_opcode.h"
#endif

#ifndef GFP_FONT_GFP_CHARACTER_H_
#include "font/gfp_character.h"
#endif

#include <fstream> 

namespace gfp {

Font::Font(){
    pre_ = NULL;
    post_ = NULL;
    post_post_ = NULL;
    character_locator_map_ = std::map<unsigned char, CharacterLocator *>();
    character_map_ = std::map<unsigned int, Character *>();
    xxxn_vector_ = std::vector<XxxN *>();
}

Font::Font(std::string font_file_name){
    font_file_name_ = font_file_name;
    pre_ = NULL;
    post_ = NULL;
    post_post_ = NULL;
    character_locator_map_ = std::map<unsigned char, CharacterLocator *>();
    character_map_ = std::map<unsigned int, Character *>();
    xxxn_vector_ = std::vector<XxxN *>();
}

void Font::SetPre(Pre *pre){
    pre_ = pre;
}
void Font::SetPost(Post *post){
    post_ = post;
}
void Font::SetPostPost(PostPost *post_post){
    post_post_ = post_post;
}

int Font::AddCharacterLocator(CharacterLocator *character_locator){
    if(character_locator_map_.find(character_locator->GetCharacterResidue()) \
        != character_locator_map_.end()){
        return -1;
    }else {
        character_locator_map_.insert(std::pair<unsigned char, CharacterLocator *>(
            character_locator->GetCharacterResidue(), character_locator
        ));
        return 0;
    }
}

/* if there is a character with the same character code, return -1, or 0 */
int Font::AddCharacter(Character *character){
    if(character_map_.find(character->GetCharacterCode()) != character_map_.end()){
        return -1;
    }else {
        character_map_.insert(std::pair<unsigned int, Character*>(
            character->GetCharacterCode(), character
        ));
        return 0;
    }
}

int Font::AddXxxN(XxxN *xxxn) {
    xxxn_vector_.push_back(xxxn);
    return 0;
}

/* always return 0 */
int Font::Parse() {
    std::ifstream *ifs = new std::ifstream();
    ifs->open(font_file_name_, std::ifstream::in);
    unsigned char opcode;
    while(!ifs->eof()) {
        ifs->get((char&)opcode);
        Command * command = CommandFactory::CreateCommand(opcode);
        if(opcode == opcode::PRE){
            pre_ = command->Parse(ifs);
        }else if(opcode == opcode::POST){
            post_ = command->Parse(ifs);
        }else if(opcode == opcode::POST_POST){
            post_post_ = command->Parse(ifs);
        }else if(opcode == opcode::BOC || opcode == opcode::BOCl){
            Command * boc = command->Parse(ifs);
            Character *character = new Character();
            character->SetCharacterCode(((BeginningOfCharacter*)boc)->GetCharacterCode());
            character->AddCommand(boc);
            this->AddCharacter(character->Parse(ifs));
        }else if(opcode == opcode::CHAR_LOC || opcode == opcode::CHAR_LOC0){
            this->AddCharacterLocator((CharacterLocator *)(command->Parse(ifs)));
        }else if(opcode >= opcode::XXX1 && opcode <= opcode::XXX4) {
            this->AddXxxN((XxxN* )command->Parse(ifs));
        }
    }
    return 0;
}

int Font::Draw(Pen *pen, DrawingBoard *drawing_board) {
    std::map<unsigned int, Character *>::iterator it;
    it = character_map_.begin();
    while(it != character_map_.end()){
        if(it->second->Draw(pen, drawing_board) != 0){
            return -1;
        }
        it++;
    }
    return 0;
}

} // namespace gfp