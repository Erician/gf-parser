#ifndef GFP_COMMAND_GFP_COMMAND_H_
#include "command/gfp_command.h"
#endif

#ifndef GFP_COMMAND_GFP_CONST_H_
#include "command/gfp_const.h"
#endif

#ifndef GFP_COMMAND_GFP_OPCODE_H_
#include "command/gfp_opcode.h"
#endif

#ifndef GFP_UTILS_GFP_STRINGUTIL_H_
#include "utils/gfp_stringutil.h"
#endif

#ifndef GFP_LOGGING_GFP_LOGGING_H_
#include "logging/gfp_logging.h"
#endif

namespace gfp {

/******** Command ********/
Command::Command(){
    opcode_ = 255;      /* 255 is not defined */
}
Command::Command(unsigned char opcode){
    opcode_ = opcode;
}
Command* Command::WithOpcode(unsigned char opcode) {
    opcode_ = opcode;
    return this;
}
void Command::SetOpcode(unsigned char opcode){
    opcode_ = opcode;
}
unsigned char Command::GetOpcode(){
    return opcode_;
}

int Command::Draw(Pen *pen, DrawingBoard *drawing_board) {
    return 0;
}

/******** Paint_N ********/
Paint_N::Paint_N(){
    // nothing to do
}
Paint_N::Paint_N(unsigned char opcode){
    opcode_ = opcode;
}

Command* Paint_N::Parse(std::ifstream *ifs) {
    return this;
}

int Paint_N::Draw(Pen *pen, DrawingBoard *drawing_board){
    int d = opcode_;
    while(d--) {
        drawing_board->Draw(pen);
    }
    pen->ChangePainterSwitch();
    return 0;
}

/******** PaintN ********/
PaintN::PaintN(){
    distance_= 0;
}
PaintN::PaintN(unsigned char opcode, \
               unsigned int distance){
    opcode_ = opcode_;
    distance_ = distance;
}

unsigned int PaintN::GetDistance(){
    return distance_;
}
void PaintN::SetDistance(unsigned int distance){
    distance_ = distance;
}

Command* PaintN::Parse(std::ifstream *ifs){
    char * buffer = new char [4];
    int length = opcode_-opcode::PAINT1 + 1;
    ifs->read(buffer, length);
    distance_ = gfp::utils::stringutil::BytesToIntWithBigEndian(
        buffer, 0, length);
    delete[] buffer;
    return this;
}

int PaintN::Draw(Pen *pen, DrawingBoard *drawing_board) {
    int d = distance_;
    while(d--) {
        drawing_board->Draw(pen);
    }
    pen->ChangePainterSwitch();
    return 0;
}

/******** Boc ********/
Boc::Boc(){
    character_code_ = 0;
    pointer_ = -1;      /* if there was no prior character with an equivalent code */

}
Boc::Boc(unsigned char opcode, \
         unsigned int character_code, \
         int pointer, \
         int min_m, \
         int max_m, \
         int min_n, \
         int max_n){
    opcode_ = opcode;
    character_code_ = character_code;
    pointer_ = pointer;
    min_m_ = min_m;
    max_m_ = max_m;
    min_n_ = min_n;
    max_n_ = max_n;
}

unsigned int BeginningOfCharacter::GetCharacterCode(){
    return character_code_;    
}

Command* Boc::Parse(std::ifstream *ifs){
    int length = 6 * 4;
    char * buffer = new char [length];
    ifs->read(buffer, length);
    character_code_ = utils::stringutil::BytesToIntWithBigEndian(buffer, 0, 4);
    pointer_ = utils::stringutil::BytesToIntWithBigEndian(buffer, 4, 8);
    min_m_ = utils::stringutil::BytesToIntWithBigEndian(buffer, 8, 12);
    max_m_ = utils::stringutil::BytesToIntWithBigEndian(buffer, 12, 16);
    min_n_ = utils::stringutil::BytesToIntWithBigEndian(buffer, 16, 20);
    max_n_ = utils::stringutil::BytesToIntWithBigEndian(buffer, 20, 24);

    LOG.Info(std::string(buffer));

    delete[] buffer;
    
    LOG.Info("Boc");
    LOG.Info("character_code: " + std::to_string(character_code_));
    LOG.Info("pointer: " + pointer_);
    LOG.Info("min_m: " + std::to_string(min_m_));
    LOG.Info("max_m: " + std::to_string(max_m_));
    LOG.Info("min_n: " + std::to_string(min_n_));
    LOG.Info("max_n: " + std::to_string(max_n_));

    return this;
}

/* paint-switch-white */
/* just set painter, ignore m,n now */
int Boc::Draw(Pen *pen, DrawingBoard *drawing_board) {
    drawing_board->Draw(painting::kDrawNextLine);
    pen->SetPainterSwitch(gfp::gf::kPainterSwitchWhite);
    return 0;
}

/******** Boc1 ********/
Boc1::Boc1(){
    character_code_ = 0;
}
Boc1::Boc1(char opcode, \
           char character_code, \
           char del_m, \
           char max_m, \
           char del_n, \
           char max_n){
    opcode_ = opcode;
    character_code_ = character_code;
    del_m_ = del_m;
    max_m_ = max_m;
    del_n_ = del_n;
    max_n_ = max_n;
}

Command* Boc1::Parse(std::ifstream *ifs){
    int length = 5 * 1;
    char * buffer = new char [length];
    ifs->read(buffer, length);
    character_code_ = utils::stringutil::BytesToIntWithBigEndian(buffer, 0, 1);
    del_m_ = utils::stringutil::BytesToIntWithBigEndian(buffer, 1, 2);
    max_m_ = utils::stringutil::BytesToIntWithBigEndian(buffer, 2, 3);
    del_n_ = utils::stringutil::BytesToIntWithBigEndian(buffer, 3, 4);
    max_n_ = utils::stringutil::BytesToIntWithBigEndian(buffer, 4, 5);
    delete[] buffer;

    LOG.Info("Boc1");
    LOG.Info("character_code: " + std::to_string(character_code_));
    LOG.Info("pointer: -1");
    LOG.Info("del_m: " + std::to_string(del_m_));
    LOG.Info("max_m: " + std::to_string(max_m_));
    LOG.Info("del_n: " + std::to_string(del_n_));
    LOG.Info("max_n: " + std::to_string(max_n_));

    return this;
}

/* paint-switch-white */
/* just set painter, ignore m,n now */
int Boc1::Draw(Pen *pen, DrawingBoard *drawing_board) {
    pen->SetPainterSwitch(gfp::gf::kPainterSwitchWhite);
    return 0;
}

/******** Eoc ********/
Eoc::Eoc(){
    // nothing to do
}
Eoc::Eoc(unsigned char opcode){
    opcode_ = opcode;
}
Command* Eoc::Parse(std::ifstream *ifs){
    LOG.Info("Eoc");
    LOG.Info("\n");
    return this;
}
int Eoc::Draw(Pen *pen, DrawingBoard *drawing_board) {
    drawing_board->Draw(painting::kDrawNextLine);
    drawing_board->Draw(painting::kDrawNextLine);
    return 0;
}
/******** SkipN ********/
SkipN::SkipN(){
    distance_ = 0;
}
SkipN::SkipN(unsigned char opcode, \
             unsigned int distance){
    
    opcode_ = opcode;
    distance_ = distance;
}
Command* SkipN::Parse(std::ifstream *ifs){
    if(opcode_ == opcode::SKIP0) {
        distance_ = 0;
    }else {
        int length = opcode_ - opcode::SKIP0;
        char * buffer = new char [length];
        ifs->read(buffer, length);
        distance_ = utils::stringutil::BytesToIntWithBigEndian(buffer, 0, length);
        delete[] buffer;
    }
    return this;
}
/* Decrease n by 1 and set m-min-m, paint-switch-white. */
int SkipN::Draw(Pen *pen, DrawingBoard *drawing_board) {
    int d = distance_;
    drawing_board->Draw(painting::kDrawNextLine);
    while(d--) {
        drawing_board->Draw(painting::kDrawNextLine);
    }
    pen->SetPainterSwitch(gfp::gf::kPainterSwitchWhite);
    return 0;
}
/******** NewRow_N ********/
NewRow_N::NewRow_N(){
    // nothing to do
}
NewRow_N::NewRow_N(unsigned char opcode){
    opcode_ = opcode;
}
Command* NewRow_N::Parse(std::ifstream *ifs){
    return this;
}

/* Decrease n by 1 and set m-min-m, paint-switch-black. */
int NewRow_N::Draw(Pen *pen, DrawingBoard *drawing_board) {
    int d = opcode_ - opcode::NEW_ROW_0;
    drawing_board->Draw(painting::kDrawNextLine);
    while(d--) {
        drawing_board->Draw(painting::kPainterSwitchWhiteDefaultCharacter);
    }
    pen->SetPainterSwitch(gfp::gf::kPainterSwitchBlack);
    return 0;
}

/******** XxxN ********/
XxxN::XxxN(){
    k_ = 0;
    x_ = std::string();
}
XxxN::XxxN(unsigned char opcode, \
            unsigned int k, \
            std::string x) {
    opcode_ = opcode;
    k_ = k;
    x_ = x;
}
Command* XxxN::Parse(std::ifstream *ifs){
    int length = opcode_ - opcode::XXX1 + 1;
    char * buffer1 = new char [length];
    ifs->read(buffer1, length);
    k_ = utils::stringutil::BytesToIntWithBigEndian(buffer1, 0, length);

    char * buffer2 = new char [k_];
    ifs->read(buffer2, k_);
    x_ = std::string(buffer2);

    delete[] buffer1;
    delete[] buffer2;

    LOG.Info("XxxN");
    LOG.Info("k: " + std::to_string(k_));
    LOG.Info("x: " + x_);
    LOG.Info("\n");

    return this;
}

int XxxN::Draw(Pen *pen, DrawingBoard *drawing_board){
    return 0;
}

/******** Yyy ********/
Yyy::Yyy(){
    y_ = 0;
}
Yyy::Yyy(unsigned char opcode, \
         unsigned int y){
    opcode_ = opcode;
    y_ = y;
}
Command* Yyy::Parse(std::ifstream *ifs){
    int length = 4;
    char * buffer = new char [length];
    ifs->read(buffer, length);
    y_ = utils::stringutil::BytesToIntWithBigEndian(buffer, 0, 4);
    delete[] buffer;
    return this;
}
int Yyy::Draw(Pen *pen, DrawingBoard *drawing_board) {
    return 0;
}
/******** NoOp ********/
NoOp::NoOp(){
    // nothing to do
}
NoOp::NoOp(unsigned char opcode){
    opcode_ = opcode;
}
Command* NoOp::Parse(std::ifstream *ifs){
    return this;
}
int NoOp::Draw(Pen *pen, DrawingBoard *drawing_board) {
    return 0;
}

/******** CharacterLocator ********/
CharacterLocator::CharacterLocator(){
    character_residue_ = 0;
    width_ = 0;
    pointer_ = 0;
}
unsigned char CharacterLocator::GetCharacterResidue() {
    return character_residue_;
}

/******** CharLoc ********/
CharLoc::CharLoc(){
    dx_ = 0;
    dy_ = 0;
}

CharLoc::CharLoc(unsigned char opcode, \
            unsigned char character_residue, \
            unsigned int dx, \
            unsigned int dy, \
            unsigned int width, \
            unsigned int pointer){
    opcode_ = opcode;
    character_residue_ = character_residue;
    dx_ = dx;
    dy_ = dy;
    width_ = width;
    pointer_ = pointer;
}

Command* CharLoc::Parse(std::ifstream *ifs){
    int length = 1*1 + 4*4;
    char * buffer = new char [length];
    ifs->read(buffer, length);
    character_residue_ = utils::stringutil::BytesToIntWithBigEndian(buffer, 0, 1);
    dx_ = utils::stringutil::BytesToIntWithBigEndian(buffer, 1, 5);
    dy_ = utils::stringutil::BytesToIntWithBigEndian(buffer, 5, 9);
    width_ = utils::stringutil::BytesToIntWithBigEndian(buffer, 9, 13);
    pointer_ = utils::stringutil::BytesToIntWithBigEndian(buffer, 13, 17);
    delete[] buffer;

    LOG.Info("CharLoc");
    LOG.Info("character_residue: " + std::to_string(character_residue_));
    LOG.Info("dx: " + std::to_string(dx_));
    LOG.Info("dy: " + std::to_string(dy_));
    LOG.Info("width: " + std::to_string(width_));
    LOG.Info("pointer: " + std::to_string(pointer_));
    LOG.Info("\n");

    return this;
}

/******** CharLoc0 ********/
CharLoc0::CharLoc0(){
    dm_ = 0;
}
CharLoc0::CharLoc0(unsigned char opcode, \
             unsigned char character_residue, \
             unsigned char dm, \
             unsigned int width, \
             unsigned int pointer){
    opcode_ = opcode;
    character_residue_ = character_residue;
    dm_ = dm;
    width_ = width;
    pointer_ = pointer;
}

Command* CharLoc0::Parse(std::ifstream *ifs){
    int length = 1*2 + 4*2;
    char * buffer = new char [length];
    ifs->read(buffer, length);
    character_residue_ = utils::stringutil::BytesToIntWithBigEndian(buffer, 0, 1);
    dm_ = utils::stringutil::BytesToIntWithBigEndian(buffer, 1, 2);
    width_ = utils::stringutil::BytesToIntWithBigEndian(buffer, 2, 6);
    pointer_ = utils::stringutil::BytesToIntWithBigEndian(buffer, 6, 10);
    delete[] buffer;

    LOG.Info("CharLoc0");
    LOG.Info("character_residue: " + std::to_string(character_residue_));
    LOG.Info("dm: " + std::to_string(dm_));
    LOG.Info("width: " + std::to_string(width_));
    LOG.Info("pointer: " + std::to_string(pointer_));
    LOG.Info("\n");

    return this;
}

/******** Pre ********/
Pre::Pre(){
    id_num_ = gf::kIdNum;
    k_ = 0;
    x_ = std::string();
}

Pre::Pre(unsigned char opcode, \
         unsigned id_num, \
         unsigned char k, \
         std::string x){
    opcode_ = opcode;
    id_num_ = id_num;
    k_ = k;
    x_ = x;
}

Command* Pre::Parse(std::ifstream *ifs){
    int length = 1*2;
    char * buffer1 = new char [length];
    ifs->read(buffer1, length);
    id_num_ = utils::stringutil::BytesToIntWithBigEndian(buffer1, 0, 1);
    k_ = utils::stringutil::BytesToIntWithBigEndian(buffer1, 1, 2);

    char * buffer2 = new char [k_];
    ifs->read(buffer2, k_);
    x_ = std::string(buffer2);

    LOG.Info("Pre");
    LOG.Info("id_name: " + std::to_string(id_num_));
    LOG.Info("k: " + std::to_string(k_));
    LOG.Info("x: " + std::string(buffer2));
    LOG.Info("\n");

    delete[] buffer1;
    delete[] buffer2;
    return this;
}

// next, after the matrix test
// start again
// how sad am I !
/******** Post ********/
Post::Post(){
    opcode_ = 0;
    pointer_ = 0;
    design_size_ = 0;
    check_sum_ = 0;
    hppp_ = 0;
    vppp_ = 0;
    min_m_ = 0;
    max_m_ = 0;
    min_n_ = 0;
    max_n_ = 0;
}

Post::Post(unsigned char opcode, \
           unsigned int pointer, \
           unsigned int design_size, \
           unsigned int check_sum, \
           unsigned int hppp, \
           unsigned int vppp, \
           unsigned int min_m, \
           unsigned int max_m, \
           unsigned int min_n, \
           unsigned int max_n){
    opcode_ = opcode;
    pointer_ = pointer;
    design_size_ = design_size;
    check_sum_ = check_sum;
    hppp_ = hppp;
    vppp_ = vppp;
    min_m_ = min_m;
    max_m_ = max_m;
    min_n_ = min_n;
    max_n_ = max_n;
}

Command* Post::Parse(std::ifstream *ifs){
    int length = 4*9;
    char * buffer = new char [length];
    ifs->read(buffer, length);
    pointer_ = utils::stringutil::BytesToIntWithBigEndian(buffer, 0, 4);
    design_size_ = utils::stringutil::BytesToIntWithBigEndian(buffer, 4, 8);
    check_sum_ = utils::stringutil::BytesToIntWithBigEndian(buffer, 8, 12);
    hppp_ = utils::stringutil::BytesToIntWithBigEndian(buffer, 12, 16);
    vppp_ = utils::stringutil::BytesToIntWithBigEndian(buffer, 16, 20);
    min_m_ = utils::stringutil::BytesToIntWithBigEndian(buffer, 20, 24);
    max_m_ = utils::stringutil::BytesToIntWithBigEndian(buffer, 24, 28);
    min_n_ = utils::stringutil::BytesToIntWithBigEndian(buffer, 28, 32);
    max_n_ = utils::stringutil::BytesToIntWithBigEndian(buffer, 32, 36);
    delete[] buffer;

    LOG.Info("Post");
    LOG.Info("pointer: " + std::to_string(pointer_));
    LOG.Info("design_size: " + std::to_string(design_size_));
    LOG.Info("\n");

    return this;
}

/******** PostPost ********/
PostPost::PostPost(){
    q_ = 0;
    id_num_ = gf::kIdNum;
    padding_bytes_ = std::string();
}

PostPost::PostPost(unsigned char opcode, \
                   unsigned int q, \
                   unsigned char id_num, \
                   std::string padding_bytes){
    opcode_ = opcode;
    q_ = q;
    id_num_ = id_num;
    padding_bytes_ = padding_bytes;
}

Command* PostPost::Parse(std::ifstream *ifs){
    int length = 4*1 + 1*1;
    char * buffer1 = new char [length];
    ifs->read(buffer1, length);
    q_ = utils::stringutil::BytesToIntWithBigEndian(buffer1, 0, 4);
    id_num_ = utils::stringutil::BytesToIntWithBigEndian(buffer1, 4, 5);

    int max_padding_byte_length = 7;
    char * buffer2 = new char [max_padding_byte_length];
    ifs->read(buffer2, max_padding_byte_length);
    padding_bytes_ = std::string(buffer2);

    delete[] buffer1;
    delete[] buffer2;

    LOG.Info("PostPost");
    LOG.Info("q: " + std::to_string(q_));
    LOG.Info("id_num: " + std::to_string(id_num_));
    LOG.Info("padding_bytes: " + std::string(padding_bytes_));
    LOG.Info("\n");

    return this;
}

/******** Undefined ********/
Undefined::Undefined(){
    // nothing to do
}
Undefined::Undefined(unsigned char opcode){
    opcode_ = opcode;
}

Command* Undefined::Parse(std::ifstream *ifs){
    return NULL;
}


} // namespace gfp