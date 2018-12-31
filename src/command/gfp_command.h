#ifndef GFP_COMMAND_GFP_COMMAND_H_
#define GFP_COMMAND_GFP_COMMAND_H_

#ifndef GFP_PAINTING_GFP_DRAWINGBOARD_H_
#include "painting/gfp_drawing_board.h"
#endif

#ifndef GFP_PAINTING_GFP_PEN_H_
#include "painting/gfp_pen.h"
#endif

#include <fstream> 
#include <string>

namespace gfp 
{

class Command {
public:
    unsigned char opcode_;
    Command();
    Command(unsigned char opcode);
    Command* WithOpcode(unsigned char opcode);
    void SetOpcode(unsigned char opcode);
    unsigned char GetOpcode();
    virtual Command* Parse(std::ifstream *ifs) = 0;
    virtual int Draw(Pen *pen, DrawingBoard *drawing_board);
};

class Paint_N : public Command {
public:
    Paint_N();
    Paint_N(unsigned char opcode);
    Command* Parse(std::ifstream *ifs);
    int Draw(Pen *pen, DrawingBoard *drawing_board);
};

class PaintN : public Command {
public:
    unsigned int distance_;
    PaintN();
    PaintN(unsigned char opcode, \
           unsigned int distance);
    unsigned int GetDistance();
    void SetDistance(unsigned int distance);
    Command* Parse(std::ifstream *ifs);
    int Draw(Pen *pen, DrawingBoard *drawing_board);
};

class BeginningOfCharacter : public Command {
private:

public:
    unsigned int character_code_;
    unsigned int GetCharacterCode();
    
};

/* the order is: boc 67 c [4] p[4] min-m [4] max-m [4] min-n [4] max-n [4]. */
/*  (a) the current column number, m; and (b) the current row number, n. 
**  These are 32-bit signed integers 
*/

/*  and p points to the previous character beginning (if any) 
** for characters having this code number modulo 256. 
*/
class Boc : public BeginningOfCharacter {
public:
    int pointer_;
    int min_m_;
    int max_m_;
    int min_n_;
    int max_n_;

    Boc();
    Boc(unsigned char opcode, \
        unsigned int character_code, \
        int pointer, \
        int min_m, \
        int max_m, \
        int min_n, \
        int max_n);
    Command* Parse(std::ifstream *ifs);
    int Draw(Pen *pen, DrawingBoard *drawing_board);
};

/* the order is: bocl 68 c[l] del-m[l] max-m [1] deLn[l] max-n[l] */
/* pointer assumed to be -1 */
class Boc1 : public BeginningOfCharacter {
public:
    char del_m_;
    char max_m_;
    char del_n_;
    char max_n_;

    Boc1();
    Boc1(char opcode, \
         char character_code, \
         char del_m, \
         char max_m, \
         char del_n, \
         char max_n);
    Command* Parse(std::ifstream *ifs);
    int Draw(Pen *pen, DrawingBoard *drawing_board);
};

class Eoc : public Command {
public:
    Eoc();
    Eoc(unsigned char opcode);
    Command* Parse(std::ifstream *ifs);
    int Draw(Pen *pen, DrawingBoard *drawing_board);
};

class SkipN : public Command{                         
public:
    unsigned int distance_;
    SkipN();
    SkipN(unsigned char opcode, \
          unsigned int distance);
    Command* Parse(std::ifstream *ifs);
    int Draw(Pen *pen, DrawingBoard *drawing_board);
};

class NewRow_N : public Command {
public:
    NewRow_N();
    NewRow_N(unsigned char opcode);
    Command* Parse(std::ifstream *ifs);
    int Draw(Pen *pen, DrawingBoard *drawing_board);
};

/* this occurs in the GF file only between characters, 
** after the preamble, and before the postamble. 
*/
class XxxN : public Command {
public:
    unsigned int k_;
    std::string x_;
    XxxN();
    XxxN(unsigned char opcode, \
         unsigned int k, \
         std::string x);
    Command* Parse(std::ifstream *ifs);
    int Draw(Pen *pen, DrawingBoard *drawing_board);
};

class Yyy : public Command {
public:
    unsigned int y_;
    Yyy();
    Yyy(unsigned char opcode, \
        unsigned int y);
    Command* Parse(std::ifstream *ifs);
    int Draw(Pen *pen, DrawingBoard *drawing_board);
};

class NoOp : public Command {
public:
    NoOp();
    NoOp(unsigned char opcode);
    Command* Parse(std::ifstream *ifs);
    int Draw(Pen *pen, DrawingBoard *drawing_board);
};

/* this should be abstract  */
/* a pointer p to the beginning of that character. 
** (If two or more characters have the same code c modulo 256, 
** only the last will be indicated;
** the others can be located by following backpointers) */
class CharacterLocator : public Command {
private:

public:
    unsigned char character_residue_;       /* don't know the meaning */
    unsigned int width_;
    unsigned int pointer_;
    CharacterLocator();
    unsigned char GetCharacterResidue();
};

/* the order is: char-loc 245 c[l] dx[4] dy [4] w[4] p[4]. */
class CharLoc : public CharacterLocator {
public:
    unsigned int dx_, dy_;
    CharLoc();
    CharLoc(unsigned char opcode, \
            unsigned char character_residue, \
            unsigned int dx, \
            unsigned int dy, \
            unsigned int width, \
            unsigned int pointer);
    Command* Parse(std::ifstream *ifs);
};

/* the order is: char-loco 246 c[l] dm[l] w[4] p[4]. */
class CharLoc0 : public CharacterLocator {
public:
    unsigned char dm_;
    CharLoc0();
    CharLoc0(unsigned char opcode, \
             unsigned char character_residue, \
             unsigned char dm, \
             unsigned int width, \
             unsigned int pointer);
    Command* Parse(std::ifstream *ifs);
};

class Pre : public Command {
public:
    unsigned char id_num_;       /* 131 currently */
    unsigned char k_;
    std::string x_;
    Pre();
    Pre(unsigned char opcode, \
        unsigned id_num, \
        unsigned char k, \
        std::string x);
    Command* Parse(std::ifstream *ifs);
};

class Post : public Command {
public:
    unsigned int pointer_;          /* poiater to the byte following the final eoc in the file 
                                    (or to the byte following the preamble, if there are no characters) */
    unsigned int design_size_;
    unsigned int check_sum_;
    unsigned int hppp_, vppp_;      /* not fully understand the two parameters */
    unsigned int min_m_, max_m_;
    unsigned int min_n_, max_n_;
    Post();
    Post(unsigned char opcode, \
         unsigned int pointer, \
         unsigned int design_size, \
         unsigned int check_sum, \
         unsigned int hppp, \
         unsigned int vppp, \
         unsigned int min_m, \
         unsigned int max_m, \
         unsigned int min_n, \
         unsigned int max_n);
    Command* Parse(std::ifstream *ifs);
};

class PostPost : public Command {
public:
    unsigned int q_;                /* a pointer to the post command that started the postamble */
    unsigned char id_num_;  
    std::string padding_bytes_;     /* the length of padding_butes >= 4 && <= 7 */
    PostPost();
    PostPost(unsigned char opcode, \
             unsigned int q, \
             unsigned char id_num, \
             std::string padding_bytes);
    Command* Parse(std::ifstream *ifs);
};

class Undefined : public Command {
public:
    Undefined();
    Undefined(unsigned char opcode);
    Command* Parse(std::ifstream *ifs);
};

} // namespace gfp

#endif