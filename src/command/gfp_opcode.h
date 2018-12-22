#ifndef GFP_COMMAND_GFP_OPCODE_H_
#define GFP_COMMAND_GFP_OPCODE_H_

namespace gfp
{
    namespace opcode
    {
    
        typedef enum {
            PAINT_0 = 0,            /* This is a paint command with d = 0; it does nothing but change the paint-switch 
                                       from black to white or vice versa */
            PAINT_1 = 1,            /* These are paint commands with d = 1 to 63, defined as follows: If paint-switch = black, 
                                       blacken d pixels of the current row n, in columns m through m + d - 1 inclusive. 
                                       Then, in any case, complement the paint-switch and advance m by d */
            PAINT_63 = 63,          /* like PAINT_1, just d = 63 */

            PAINT1 = 64,            /* This is a paint command with a specified value of d; METAFONT uses it to paint when 64 5 d < 256 */
            PAINT2 = 65,            /* Same as PAINTl , but d can be as high as 65535 */
            PAINT3 = 66,            /* Same as paintl , but d can be as high as power(2, 24)-1 */

            BOC = 67,               /* beginning of a character */
            BOCl = 68,              /* short form of boc */
            EOC = 69,               /* end of a character */
            
            SKIP0 = 70,             /* skip no blank rows */
            SKIP1 = 71,             /* skip over blank rows */
            SKIP2 = 72,             /* skip over blank rows */


            NEW_ROW_0 = 74,         /* move down one row and then right */
            NEW_ROW_1 = 75,
            NEW_ROW_164 = 238,       

            XXX1 = 239,             /* for special strings */
            XXX2 = 240,
            XXX3 = 241,
            XXX4 = 242,
            xxx9 = 241,             /* for long special strings */
            yyy = 243,              /* for numspecial numbers */

            NO_OP = 244,            /* No operation, do nothing */

            CHAR_LOC = 245,         /* character locators in the postamble */
            CHAR_LOC0 = 246,
            PRE = 247,              /* preamble */
            POST = 248,             /* postamble beginning */
            POST_POST = 249         /* postamble ending */

        }GfOperations;
    
    }; // namespace opcode

}; // namespace gfp

#endif