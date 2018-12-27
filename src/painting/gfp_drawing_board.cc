#ifndef GFP_PAINTING_GFP_DRAWING_BOARD_H_
#include "painting/gfp_drawing_board.h"
#endif

#ifndef GFP_COMMAND_GFP_CONST_H_
#include "command/gfp_const.h"
#endif

#include <iostream>

namespace gfp {

DrawingBoard::DrawingBoard(){
    output_file_name_ = std::string();
    board_ = &(std::cout);
    output_file_stream_ = NULL;
}

DrawingBoard::DrawingBoard(std::string output_file_name){
    output_file_name_ = output_file_name;
    output_file_stream_ =  new std::ofstream(output_file_name_, std::ofstream::out | std::ofstream::app);
    board_ = output_file_stream_;
}

void DrawingBoard::SetBoard(){
    board_ = &(std::cout);
}

void DrawingBoard::SetBoard(std::string output_file_name){
    if(output_file_stream_ != NULL){
        output_file_stream_->close();
    }
    output_file_stream_ =  new std::ofstream(output_file_name_, std::ofstream::out | std::ofstream::app);
    board_ = output_file_stream_;
}

void DrawingBoard::Draw(Pen *pen){
    if(pen->GetPainterSwitch() == gf::kPainterSwitchWhite) {
        this->Put(painting::kPainterSwitchWhiteDefaultCharacter);
    }else {
        this->Put(painting::kPainterSwitchBlackDefaultCharacter);
    }
}

void DrawingBoard::Draw(char c){
    Put(c);
}

void DrawingBoard::Put(char c) {
    (*board_)<<c;
}

void DrawingBoard::Close(){
    output_file_stream_->close();
}


} // namespace gfp