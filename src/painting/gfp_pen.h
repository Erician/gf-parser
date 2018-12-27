#ifndef GFP_CORE_GFP_PEN_H_
#define GFP_CORE_GFP_PEN_H_

namespace gfp
{

class Pen{
private:
    int painter_switch_;    /* black(1) or white(0) */
public:
    Pen();
    Pen(int painter_switch);
    void InitPainterSwitch();
    int GetPainterSwitch();
    void SetPainterSwitch(int painter_switch);
    void ChangePainterSwitch();
};

} // namespace gfp

#endif