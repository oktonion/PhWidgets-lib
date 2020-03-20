#include "Color.h"

#include "./../service/stdex/stdex.h"

#include <cstring>
#include <functional>

namespace PhWidgets
{
    namespace Drawing
    {
        Color Color::FromARGB(unsigned char alpha, unsigned char red, unsigned char green, unsigned char blue)
        {
            STATIC_ASSERT(sizeof(Color) == sizeof(PgColor_t), PhWidgets_Color_should_contain_only_PgColor_t);
            
            return FromARGB(PgARGB(alpha, red, green, blue));
        }

        Color Color::FromARGB(unsigned char red, unsigned char green, unsigned char blue)
        {
            return FromARGB(PgRGB(red, green, blue));
        }

        Color Color::FromARGB(unsigned char alpha, Color color)
        {
            return FromARGB(PgARGB(alpha, color.R, color.G, color.B));
        }

        Color Color::FromARGB(PgColor_t argb)
        {
            return Color(argb);
        }

        Color Color::FromCMY(unsigned char cyan, unsigned char magenta, unsigned char yellow)
        {
            return FromARGB(PgCMY(cyan, magenta, yellow));
        }

        Color Color::FromHSV(unsigned short hue, unsigned char saturation, unsigned char value)
        {
            return FromARGB(PgHSV(hue, saturation, value));
        }

        static const ColorBase MakeColorBase(const PgColor_t &argb)
        {
            ColorBase result;
            result.A = PgAlphaValue(argb);
            result.R = PgRedValue(argb);
            result.G = PgGreenValue(argb);
            result.B = PgBlueValue(argb);
            return result;
        }

        Color::Color(PgColor_t argb):
            ColorBase(MakeColorBase(argb))
        { }

        PgColor_t Color::ToARGB () const 
        {
            return PgARGB(A, R, G, B);
        }

        Color::operator PgColor_t () const 
        {
            return PgARGB(A, R, G, B);
        }
    }
}