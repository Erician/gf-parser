#ifndef GFP_PAINTING_GFP_PEN_H_
#include "painting/gfp_pen.h"
#endif 

#ifndef GFP_COMMAND_GFP_CONST_H_
#include "command/gfp_const.h"
#endif 

namespace gfp 
{

Pen::Pen(){
    InitPainterSwitch();
}

Pen::Pen(int painter_switch){
    painter_switch_ = painter_switch;
}

/* the initial color is white */
void Pen::InitPainterSwitch(){
    painter_switch_ = gf::kPainterSwitchWhite;
}

int Pen::GetPainterSwitch(){
    return painter_switch_;
}

void Pen::SetPainterSwitch(int painter_switch){
    painter_switch_ = painter_switch;
}

void Pen::ChangePainterSwitch(){
    painter_switch_ = painter_switch_ == gf::kPainterSwitchBlack ? \
                gf::kPainterSwitchWhite : gf::kPainterSwitchBlack;    
}

} // namespace gfp