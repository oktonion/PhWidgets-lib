#ifndef PHWIDGETS_COLOR_H
#define PHWIDGETS_COLOR_H

#include <photon/PhT.h>
#include <photon/PtT.h>

namespace PhWidgets
{
    //! The PhWidgets::Drawing namespace provides access to basic graphics functionality.
    namespace Drawing
    {
        //! Provides a collection of standard colors for use by a Photon microGUI application.
        /*!
            @see
            - Drawing::Color 
            - Basic::Color
            - Basic::LightFillColor
            - Basic::DarkFillColor
            - Basic::LightBevelColor
            - Basic::DarkBevelColor
        */
        struct Colors
        {
            //! @name Properties
            //! > Colors::eColors Collection of standard colors for use by a Photon microGUI application
            //! @{
            enum eColors
            {
                AliceBlue = static_cast<unsigned>(0xFFF0F8FF), //!< System-defined color that has an ARGB value of #FFF0F8FF.
                AntiqueWhite = static_cast<unsigned>(0xFFFAEBD7), //!< System-defined color that has an ARGB value of #FFFAEBD7.
                Aqua = static_cast<unsigned>(0xFF00FFFF), //!< System-defined color that has an ARGB value of #FF00FFFF.
                Aquamarine = static_cast<unsigned>(0xFF7FFFD4), //!< System-defined color that has an ARGB value of #FF7FFFD4.
                Azure = static_cast<unsigned>(0xFFF0FFFF), //!< System-defined color that has an ARGB value of #FFF0FFFF.
                Beige = static_cast<unsigned>(0xFFF5F5DC), //!< System-defined color that has an ARGB value of #FFF5F5DC.
                Bisque = static_cast<unsigned>(0xFFFFE4C4), //!< System-defined color that has an ARGB value of #FFFFE4C4.
                Black = static_cast<unsigned>(0xFF000000), //!< System-defined color that has an ARGB value of #FF000000.
                BlanchedAlmond = static_cast<unsigned>(0xFFFFEBCD), //!< System-defined color that has an ARGB value of #FFFFEBCD.
                Blue = static_cast<unsigned>(0xFF0000FF), //!< System-defined color that has an ARGB value of #FF0000FF.
                BlueViolet = static_cast<unsigned>(0xFF8A2BE2), //!< System-defined color that has an ARGB value of #FF8A2BE2.
                Brown = static_cast<unsigned>(0xFFA52A2A), //!< System-defined color that has an ARGB value of #FFA52A2A.
                BurlyWood = static_cast<unsigned>(0xFFDEB887), //!< System-defined color that has an ARGB value of #FFDEB887.
                CadetBlue = static_cast<unsigned>(0xFF5F9EA0), //!< System-defined color that has an ARGB value of #FF5F9EA0.
                Chartreuse = static_cast<unsigned>(0xFF7FFF00), //!< System-defined color that has an ARGB value of #FF7FFF00.
                Chocolate = static_cast<unsigned>(0xFFD2691E), //!< System-defined color that has an ARGB value of #FFD2691E.
                Coral = static_cast<unsigned>(0xFFFF7F50), //!< System-defined color that has an ARGB value of #FFFF7F50.
                CornflowerBlue = static_cast<unsigned>(0xFF6495ED), //!< System-defined color that has an ARGB value of #FF6495ED.
                Cornsilk = static_cast<unsigned>(0xFFFFF8DC), //!< System-defined color that has an ARGB value of #FFFFF8DC.
                Crimson = static_cast<unsigned>(0xFFDC143C), //!< System-defined color that has an ARGB value of #FFDC143C.
                Cyan = static_cast<unsigned>(0xFF00FFFF), //!< System-defined color that has an ARGB value of #FF00FFFF.
                DarkBlue = static_cast<unsigned>(0xFF00008B), //!< System-defined color that has an ARGB value of #FF00008B.
                DarkCyan = static_cast<unsigned>(0xFF008B8B), //!< System-defined color that has an ARGB value of #FF008B8B.
                DarkGoldenrod = static_cast<unsigned>(0xFFB8860B), //!< System-defined color that has an ARGB value of #FFB8860B.
                DarkGray = static_cast<unsigned>(0xFFA9A9A9), //!< System-defined color that has an ARGB value of #FFA9A9A9.
                DarkGreen = static_cast<unsigned>(0xFF006400), //!< System-defined color that has an ARGB value of #FF006400.
                DarkKhaki = static_cast<unsigned>(0xFFBDB76B), //!< System-defined color that has an ARGB value of #FFBDB76B.
                DarkMagenta = static_cast<unsigned>(0xFF8B008B), //!< System-defined color that has an ARGB value of #FF8B008B.
                DarkOliveGreen = static_cast<unsigned>(0xFF556B2F), //!< System-defined color that has an ARGB value of #FF556B2F.
                DarkOrange = static_cast<unsigned>(0xFFFF8C00), //!< System-defined color that has an ARGB value of #FFFF8C00.
                DarkOrchid = static_cast<unsigned>(0xFF9932CC), //!< System-defined color that has an ARGB value of #FF9932CC.
                DarkRed = static_cast<unsigned>(0xFF8B0000), //!< System-defined color that has an ARGB value of #FF8B0000.
                DarkSalmon = static_cast<unsigned>(0xFFE9967A), //!< System-defined color that has an ARGB value of #FFE9967A.
                DarkSeaGreen = static_cast<unsigned>(0xFF8FBC8F), //!< System-defined color that has an ARGB value of #FF8FBC8F.
                DarkSlateBlue = static_cast<unsigned>(0xFF483D8B), //!< System-defined color that has an ARGB value of #FF483D8B.
                DarkSlateGray = static_cast<unsigned>(0xFF2F4F4F), //!< System-defined color that has an ARGB value of #FF2F4F4F.
                DarkTurquoise = static_cast<unsigned>(0xFF00CED1), //!< System-defined color that has an ARGB value of #FF00CED1.
                DarkViolet = static_cast<unsigned>(0xFF9400D3), //!< System-defined color that has an ARGB value of #FF9400D3.
                DeepPink = static_cast<unsigned>(0xFFFF1493), //!< System-defined color that has an ARGB value of #FFFF1493.
                DeepSkyBlue = static_cast<unsigned>(0xFF00BFFF), //!< System-defined color that has an ARGB value of #FF00BFFF.
                DimGray = static_cast<unsigned>(0xFF696969), //!< System-defined color that has an ARGB value of #FF696969.
                DodgerBlue = static_cast<unsigned>(0xFF1E90FF), //!< System-defined color that has an ARGB value of #FF1E90FF.
                Firebrick = static_cast<unsigned>(0xFFB22222), //!< System-defined color that has an ARGB value of #FFB22222.
                FloralWhite = static_cast<unsigned>(0xFFFFFAF0), //!< System-defined color that has an ARGB value of #FFFFFAF0.
                ForestGreen = static_cast<unsigned>(0xFF228B22), //!< System-defined color that has an ARGB value of #FF228B22.
                Fuchsia = static_cast<unsigned>(0xFFFF00FF), //!< System-defined color that has an ARGB value of #FFFF00FF.
                Gainsboro = static_cast<unsigned>(0xFFDCDCDC), //!< System-defined color that has an ARGB value of #FFDCDCDC.
                GhostWhite = static_cast<unsigned>(0xFFF8F8FF), //!< System-defined color that has an ARGB value of #FFF8F8FF.
                Gold = static_cast<unsigned>(0xFFFFD700), //!< System-defined color that has an ARGB value of #FFFFD700.
                Goldenrod = static_cast<unsigned>(0xFFDAA520), //!< System-defined color that has an ARGB value of #FFDAA520.
                Gray = static_cast<unsigned>(0xFF808080), //!< System-defined color that has an ARGB value of #FF808080.
                Green = static_cast<unsigned>(0xFF008000), //!< System-defined color that has an ARGB value of #FF008000.
                GreenYellow = static_cast<unsigned>(0xFFADFF2F), //!< System-defined color that has an ARGB value of #FFADFF2F.
                Honeydew = static_cast<unsigned>(0xFFF0FFF0), //!< System-defined color that has an ARGB value of #FFF0FFF0.
                HotPink = static_cast<unsigned>(0xFFFF69B4), //!< System-defined color that has an ARGB value of #FFFF69B4.
                IndianRed = static_cast<unsigned>(0xFFCD5C5C), //!< System-defined color that has an ARGB value of #FFCD5C5C.
                Indigo = static_cast<unsigned>(0xFF4B0082), //!< System-defined color that has an ARGB value of #FF4B0082.
                Ivory = static_cast<unsigned>(0xFFFFFFF0), //!< System-defined color that has an ARGB value of #FFFFFFF0.
                Khaki = static_cast<unsigned>(0xFFF0E68C), //!< System-defined color that has an ARGB value of #FFF0E68C.
                Lavender = static_cast<unsigned>(0xFFE6E6FA), //!< System-defined color that has an ARGB value of #FFE6E6FA.
                LavenderBlush = static_cast<unsigned>(0xFFFFF0F5), //!< System-defined color that has an ARGB value of #FFFFF0F5.
                LawnGreen = static_cast<unsigned>(0xFF7CFC00), //!< System-defined color that has an ARGB value of #FF7CFC00.
                LemonChiffon = static_cast<unsigned>(0xFFFFFACD), //!< System-defined color that has an ARGB value of #FFFFFACD.
                LightBlue = static_cast<unsigned>(0xFFADD8E6), //!< System-defined color that has an ARGB value of #FFADD8E6.
                LightCoral = static_cast<unsigned>(0xFFF08080), //!< System-defined color that has an ARGB value of #FFF08080.
                LightCyan = static_cast<unsigned>(0xFFE0FFFF), //!< System-defined color that has an ARGB value of #FFE0FFFF.
                LightGoldenrodYellow = static_cast<unsigned>(0xFFFAFAD2), //!< System-defined color that has an ARGB value of #FFFAFAD2.
                LightGray = static_cast<unsigned>(0xFFD3D3D3), //!< System-defined color that has an ARGB value of #FFD3D3D3.
                LightGreen = static_cast<unsigned>(0xFF90EE90), //!< System-defined color that has an ARGB value of #FF90EE90.
                LightPink = static_cast<unsigned>(0xFFFFB6C1), //!< System-defined color that has an ARGB value of #FFFFB6C1.
                LightSalmon = static_cast<unsigned>(0xFFFFA07A), //!< System-defined color that has an ARGB value of #FFFFA07A.
                LightSeaGreen = static_cast<unsigned>(0xFF20B2AA), //!< System-defined color that has an ARGB value of #FF20B2AA.
                LightSkyBlue = static_cast<unsigned>(0xFF87CEFA), //!< System-defined color that has an ARGB value of #FF87CEFA.
                LightSlateGray = static_cast<unsigned>(0xFF778899), //!< System-defined color that has an ARGB value of #FF778899.
                LightSteelBlue = static_cast<unsigned>(0xFFB0C4DE), //!< System-defined color that has an ARGB value of #FFB0C4DE.
                LightYellow = static_cast<unsigned>(0xFFFFFFE0), //!< System-defined color that has an ARGB value of #FFFFFFE0.
                Lime = static_cast<unsigned>(0xFF00FF00), //!< System-defined color that has an ARGB value of #FF00FF00.
                LimeGreen = static_cast<unsigned>(0xFF32CD32), //!< System-defined color that has an ARGB value of #FF32CD32.
                Linen = static_cast<unsigned>(0xFFFAF0E6), //!< System-defined color that has an ARGB value of #FFFAF0E6.
                Magenta = static_cast<unsigned>(0xFFFF00FF), //!< System-defined color that has an ARGB value of #FFFF00FF.
                Maroon = static_cast<unsigned>(0xFF800000), //!< System-defined color that has an ARGB value of #FF800000.
                MediumAquamarine = static_cast<unsigned>(0xFF66CDAA), //!< System-defined color that has an ARGB value of #FF66CDAA.
                MediumBlue = static_cast<unsigned>(0xFF0000CD), //!< System-defined color that has an ARGB value of #FF0000CD.
                MediumOrchid = static_cast<unsigned>(0xFFBA55D3), //!< System-defined color that has an ARGB value of #FFBA55D3.
                MediumPurple = static_cast<unsigned>(0xFF9370DB), //!< System-defined color that has an ARGB value of #FF9370DB.
                MediumSeaGreen = static_cast<unsigned>(0xFF3CB371), //!< System-defined color that has an ARGB value of #FF3CB371.
                MediumSlateBlue = static_cast<unsigned>(0xFF7B68EE), //!< System-defined color that has an ARGB value of #FF7B68EE.
                MediumSpringGreen = static_cast<unsigned>(0xFF00FA9A), //!< System-defined color that has an ARGB value of #FF00FA9A.
                MediumTurquoise = static_cast<unsigned>(0xFF48D1CC), //!< System-defined color that has an ARGB value of #FF48D1CC.
                MediumVioletRed = static_cast<unsigned>(0xFFC71585), //!< System-defined color that has an ARGB value of #FFC71585.
                MidnightBlue = static_cast<unsigned>(0xFF191970), //!< System-defined color that has an ARGB value of #FF191970.
                MintCream = static_cast<unsigned>(0xFFF5FFFA), //!< System-defined color that has an ARGB value of #FFF5FFFA.
                MistyRose = static_cast<unsigned>(0xFFFFE4E1), //!< System-defined color that has an ARGB value of #FFFFE4E1.
                Moccasin = static_cast<unsigned>(0xFFFFE4B5), //!< System-defined color that has an ARGB value of #FFFFE4B5.
                NavajoWhite = static_cast<unsigned>(0xFFFFDEAD), //!< System-defined color that has an ARGB value of #FFFFDEAD.
                Navy = static_cast<unsigned>(0xFF000080), //!< System-defined color that has an ARGB value of #FF000080.
                OldLace = static_cast<unsigned>(0xFFFDF5E6), //!< System-defined color that has an ARGB value of #FFFDF5E6.
                Olive = static_cast<unsigned>(0xFF808000), //!< System-defined color that has an ARGB value of #FF808000.
                OliveDrab = static_cast<unsigned>(0xFF6B8E23), //!< System-defined color that has an ARGB value of #FF6B8E23.
                Orange = static_cast<unsigned>(0xFFFFA500), //!< System-defined color that has an ARGB value of #FFFFA500.
                OrangeRed = static_cast<unsigned>(0xFFFF4500), //!< System-defined color that has an ARGB value of #FFFF4500.
                Orchid = static_cast<unsigned>(0xFFDA70D6), //!< System-defined color that has an ARGB value of #FFDA70D6.
                PaleGoldenrod = static_cast<unsigned>(0xFFEEE8AA), //!< System-defined color that has an ARGB value of #FFEEE8AA.
                PaleGreen = static_cast<unsigned>(0xFF98FB98), //!< System-defined color that has an ARGB value of #FF98FB98.
                PaleTurquoise = static_cast<unsigned>(0xFFAFEEEE), //!< System-defined color that has an ARGB value of #FFAFEEEE.
                PaleVioletRed = static_cast<unsigned>(0xFFDB7093), //!< System-defined color that has an ARGB value of #FFDB7093.
                PapayaWhip = static_cast<unsigned>(0xFFFFEFD5), //!< System-defined color that has an ARGB value of #FFFFEFD5.
                PeachPuff = static_cast<unsigned>(0xFFFFDAB9), //!< System-defined color that has an ARGB value of #FFFFDAB9.
                Peru = static_cast<unsigned>(0xFFCD853F), //!< System-defined color that has an ARGB value of #FFCD853F.
                Pink = static_cast<unsigned>(0xFFFFC0CB), //!< System-defined color that has an ARGB value of #FFFFC0CB.
                Plum = static_cast<unsigned>(0xFFDDA0DD), //!< System-defined color that has an ARGB value of #FFDDA0DD.
                PowderBlue = static_cast<unsigned>(0xFFB0E0E6), //!< System-defined color that has an ARGB value of #FFB0E0E6.
                Purple = static_cast<unsigned>(0xFF800080), //!< System-defined color that has an ARGB value of #FF800080.
                Red = static_cast<unsigned>(0xFFFF0000), //!< System-defined color that has an ARGB value of #FFFF0000.
                RosyBrown = static_cast<unsigned>(0xFFBC8F8F), //!< System-defined color that has an ARGB value of #FFBC8F8F.
                RoyalBlue = static_cast<unsigned>(0xFF4169E1), //!< System-defined color that has an ARGB value of #FF4169E1.
                SaddleBrown = static_cast<unsigned>(0xFF8B4513), //!< System-defined color that has an ARGB value of #FF8B4513.
                Salmon = static_cast<unsigned>(0xFFFA8072), //!< System-defined color that has an ARGB value of #FFFA8072.
                SandyBrown = static_cast<unsigned>(0xFFF4A460), //!< System-defined color that has an ARGB value of #FFF4A460.
                SeaGreen = static_cast<unsigned>(0xFF2E8B57), //!< System-defined color that has an ARGB value of #FF2E8B57.
                SeaShell = static_cast<unsigned>(0xFFFFF5EE), //!< System-defined color that has an ARGB value of #FFFFF5EE.
                Sienna = static_cast<unsigned>(0xFFA0522D), //!< System-defined color that has an ARGB value of #FFA0522D.
                Silver = static_cast<unsigned>(0xFFC0C0C0), //!< System-defined color that has an ARGB value of #FFC0C0C0.
                SkyBlue = static_cast<unsigned>(0xFF87CEEB), //!< System-defined color that has an ARGB value of #FF87CEEB.
                SlateBlue = static_cast<unsigned>(0xFF6A5ACD), //!< System-defined color that has an ARGB value of #FF6A5ACD.
                SlateGray = static_cast<unsigned>(0xFF708090), //!< System-defined color that has an ARGB value of #FF708090.
                Snow = static_cast<unsigned>(0xFFFFFAFA), //!< System-defined color that has an ARGB value of #FFFFFAFA.
                SpringGreen = static_cast<unsigned>(0xFF00FF7F), //!< System-defined color that has an ARGB value of #FF00FF7F.
                SteelBlue = static_cast<unsigned>(0xFF4682B4), //!< System-defined color that has an ARGB value of #FF4682B4.
                Tan = static_cast<unsigned>(0xFFD2B48C), //!< System-defined color that has an ARGB value of #FFD2B48C.
                Teal = static_cast<unsigned>(0xFF008080), //!< System-defined color that has an ARGB value of #FF008080.
                Thistle = static_cast<unsigned>(0xFFD8BFD8), //!< System-defined color that has an ARGB value of #FFD8BFD8.
                Tomato = static_cast<unsigned>(0xFFFF6347), //!< System-defined color that has an ARGB value of #FFFF6347.
                Transparent = static_cast<unsigned>(0x00FFFFFF), //!< System-defined color that has an ARGB value of #00FFFFFF.
                Turquoise = static_cast<unsigned>(0xFF40E0D0), //!< System-defined color that has an ARGB value of #FF40E0D0.
                Violet = static_cast<unsigned>(0xFFEE82EE), //!< System-defined color that has an ARGB value of #FFEE82EE.
                Wheat = static_cast<unsigned>(0xFFF5DEB3), //!< System-defined color that has an ARGB value of #FFF5DEB3.
                White = static_cast<unsigned>(0xFFFFFFFF), //!< System-defined color that has an ARGB value of #FFFFFFFF.
                WhiteSmoke = static_cast<unsigned>(0xFFF5F5F5), //!< System-defined color that has an ARGB value of #FFF5F5F5.
                Yellow = static_cast<unsigned>(0xFFFFFF00), //!< System-defined color that has an ARGB value of #FFFFFF00.
                YellowGreen = static_cast<unsigned>(0xFF9ACD32) //!< System-defined color that has an ARGB value of #FF9ACD32.
            };
            //! @}
        };

        template<bool>
        struct ColorImpl;
        typedef ColorImpl<((1&0xFF) == 1)> ColorBase;
        
        template<>
        struct ColorImpl<false>
        {
            PgColor_t A : 8;
            PgColor_t R : 8;
            PgColor_t G : 8;
            PgColor_t B : 8;
        };

        template<>
        struct ColorImpl<true>
        {
            PgColor_t B : 8;
            PgColor_t G : 8;
            PgColor_t R : 8;
            PgColor_t A : 8;
        };

        //! Represents an ARGB (alpha, red, green, blue) color.
        /*!
            @remark
            The color of each pixel is represented as a 32-bit number: 
            8 bits each for alpha, red, green, and blue (ARGB). 
            Each of the four components is a number from 0 through 255, 
            with 0 representing no intensity and 255 representing full intensity. 
            The alpha component specifies the transparency of the color: 
            0 is fully transparent, and 255 is fully opaque. 
            To determine the alpha, red, green, or blue component of a color, 
            use the Color::A, Color::R, Color::G, or Color::B property, respectively. 
            You can create a custom color by using one of the Color::FromARGB, Color::FromCMY, Color::FromHSV methods.

            @see
            - Drawing::Colors
            - Basic::Color
        */
        class Color:
            public Colors,
            public ColorBase
        {
        public:
            //! (constructor) 
            /*!
                Constructs a Color class by `PgColor_t` ARGB.
                @param[in] argb ARGB `PgColor_t` value.
                
                @remark
                You can create a custom color by using one of the Color::FromARGB, Color::FromCMY, Color::FromHSV methods.

                @see
                - Drawing::Colors
            */
            Color(PgColor_t argb = Colors::Black);

            //! @name Properties
            //! > Colors::eColors Collection of standard colors for use by a Photon microGUI application. 
            //! @{ 

            //! Gets the alpha component value of this Color class.
            /*!
                ### Property Value ### 
                
                > `PgColor_t` : 8

                The alpha component value of this Color.

                @remark
                The color of each pixel is represented as a 32-bit number: 
                8 bits each for alpha, red, green, and blue (ARGB). 
                The alpha component specifies the transparency of the color: 
                0 is fully transparent, and 255 is fully opaque. 
                Likewise, an Color::A value of 255 represents an opaque color. 
                An Color::A value from 1 through 254 represents a semitransparent color. 
                The color becomes more opaque as Color::A approaches 255.

                @see
                - Colors
                - Color::R
                - Color::G
                - Color::B
            */
#ifdef __DOXYGEN__ // ugly hack for Doxygen docs
            PgColor_t A : 8;
#endif
            using ColorBase::A;

            //! Gets the red component value of this Color class.
            /*!
                ### Property Value ### 
                
                > `PgColor_t` : 8

                The red component value of this Color.

                @remark
                The color of each pixel is represented as a 32-bit number: 
                8 bits each for alpha, red, green, and blue (ARGB). 
                Each of the four components is a number from 0 through 255, 
                with 0 representing no intensity and 255 representing full intensity. 
                Likewise, Color::R is a value from 0 to 255 with 0 representing no red and 255 representing fully red.

                @see
                - Colors
                - Color::A
                - Color::G
                - Color::B
            */
#ifdef __DOXYGEN__ // ugly hack for Doxygen docs
            PgColor_t R : 8;
#endif
            using ColorBase::R;

            //! Gets the green component value of this Color class.
            /*!
                ### Property Value ### 
                
                > `PgColor_t` : 8

                The green component value of this Color.

                @remark
                The color of each pixel is represented as a 32-bit number: 
                8 bits each for alpha, red, green, and blue (ARGB). 
                Each of the four components is a number from 0 through 255, 
                with 0 representing no intensity and 255 representing full intensity. 
                Likewise, Color::G is a value from 0 to 255 with 0 representing no green and 255 representing fully green.

                @see
                - Colors
                - Color::A
                - Color::R
                - Color::B
            */
#ifdef __DOXYGEN__ // ugly hack for Doxygen docs
            PgColor_t G : 8;
#endif
            using ColorBase::G;

            //! Gets the blue component value of this Color class.
            /*!
                ### Property Value ### 
                
                > `PgColor_t` : 8

                The blue component value of this Color.

                @remark
                The color of each pixel is represented as a 32-bit number: 
                8 bits each for alpha, red, green, and blue (ARGB). 
                Each of the four components is a number from 0 through 255, 
                with 0 representing no intensity and 255 representing full intensity. 
                Likewise, Color::B is a value from 0 to 255 with 0 representing no blue and 255 representing fully blue.

                @see
                - Colors
                - Color::A
                - Color::R
                - Color::G
            */
#ifdef __DOXYGEN__ // ugly hack for Doxygen docs
            PgColor_t B : 8;
#endif
            using ColorBase::B;
            //! @}
            
            //@{
            //! Creates a Color class from the four ARGB component (alpha, red, green, and blue) values.
            /*!
                @param[in] alpha The alpha component. Valid values are 0 through 255.
                @param[in] red The red component. Valid values are 0 through 255.
                @param[in] green The green component. Valid values are 0 through 255.
                @param[in] blue The blue component. Valid values are 0 through 255.
                @return The Color that this method creates.

                @remark
                To create an opaque color, set alpha to 255. To create a semitransparent color, set alpha to any value from 1 through 254.
            */
            static Color FromARGB(unsigned char alpha, unsigned char red, unsigned char green, unsigned char blue);

            //! Creates a Color class from the specified 8-bit color values (red, green, and blue). The alpha value is implicitly 255 (fully opaque).
            /*!
                @param[in] red The red component. Valid values are 0 through 255.
                @param[in] green The green component. Valid values are 0 through 255.
                @param[in] blue The blue component. Valid values are 0 through 255.
                @return The Color that this method creates.
            */
            static Color FromARGB(unsigned char red, unsigned char green, unsigned char blue);

            //! Creates a Color class from the specified Color class, but with the new specified alpha value.
            /*!
                @param[in] alpha The alpha component. Valid values are 0 through 255.
                @param[in] color The Color from which to create the new Color.
                @return The Color that this method creates.
                
                @remark
                To create an opaque color, set alpha to 255. To create a semitransparent color, set alpha to any value from 1 through 254.
            */
            static Color FromARGB(unsigned char alpha, Color color);

            //! Creates a Color structure from a 32-bit ARGB value.
            /*!
                @param[in] argb The alpha component. Valid values are 0 through 255.
                @return The Color that this method creates.
                
                @remark
                The byte-ordering of the 32-bit ARGB value is AARRGGBB. 
                The most significant byte (MSB), represented by AA, is the alpha component value. 
                The second, third, and fourth bytes, represented by RR, GG, and BB, respectively, 
                are the color components red, green, and blue, respectively.
            */
            static Color FromARGB(PgColor_t argb);
            //@}

            //! Creates a Color class from the specified 8-bit color values (cyan, magenta, and yellow). The alpha value is implicitly 255 (fully opaque).
            /*!
                @param[in] cyan The cyan component. Valid values are 0 through 255.
                @param[in] magenta The magenta component. Valid values are 0 through 255.
                @param[in] yellow The yellow component. Valid values are 0 through 255.
                @return The Color that this method creates.
            */
            static Color FromCMY(unsigned char cyan, unsigned char magenta, unsigned char yellow);

            //! Creates a Color class from the specified 8-bit hue, saturation, and value. The alpha value is implicitly 255 (fully opaque).
            /*!
                @param[in] hue  A color circle is divided into 65536 gradations (called binary gradations or bi-grads). 
                                Hue is in bi-grads, starting with red at 0 (0 degrees), green at 0x5555 (120 degrees), and blue at 0xAAAA (240 degrees)
                @param[in] saturation The saturation. Valid values are 0 through 255.
                @param[in] value The value. Valid values are 0 through 255.
                @return The Color that this method creates.
            */
            static Color FromHSV(unsigned short hue, unsigned char saturation, unsigned char value);
        
            //! Gets the 32-bit ARGB value of this Color class.
            /*!
                @return The 32-bit ARGB value `PgColor_t` of this Color.
            */
            PgColor_t ToArgb () const;

            //! Converts to the 32-bit ARGB value of this Color class.
            /*!
                @return The 32-bit ARGB value `PgColor_t` of this Color.
            */
            operator PgColor_t () const;
        };

        bool operator==(const PgColor_t &pg_color, Colors::eColors ph_color)
        {
            const PgColorModel_t * cm = PgGetColorModel();

            PgColor_t 
                lhs = pg_color,
                rhs = ph_color;

            if(!(cm && cm->id != Pg_CM_RGB->id))
            {
                lhs &= 0x00FFFFFF;
                rhs &= 0x00FFFFFF;
            }

            return (lhs == rhs);  
        }

        bool operator!=(const PgColor_t &pg_color, Colors::eColors ph_color)
        {
            return !(pg_color == ph_color);
        }

        bool operator<(const PgColor_t &pg_color, Colors::eColors ph_color)
        {
            if (pg_color == ph_color)
                return false;
            return pg_color < static_cast<PgColor_t>(ph_color);
        }

        bool operator<=(const PgColor_t &pg_color, Colors::eColors ph_color)
        {
            if (pg_color == ph_color)
                return true;
            return pg_color < static_cast<PgColor_t>(ph_color);
        }

        bool operator>(const PgColor_t &pg_color, Colors::eColors ph_color)
        {
            if (pg_color == ph_color)
                return false;
            return pg_color > static_cast<PgColor_t>(ph_color);
        }

        bool operator>=(const PgColor_t &pg_color, Colors::eColors ph_color)
        {
            if (pg_color == ph_color)
                return true;
            return pg_color > static_cast<PgColor_t>(ph_color);
        }

        bool operator==(Colors::eColors ph_color, const PgColor_t &pg_color)
        {
            return (pg_color == ph_color);
        }

        bool operator!=(Colors::eColors ph_color, const PgColor_t &pg_color)
        {
            return !(ph_color == pg_color);
        }

        bool operator<(Colors::eColors ph_color, const PgColor_t &pg_color)
        {
            if (pg_color == ph_color)
                return false;
            return static_cast<PgColor_t>(ph_color) < pg_color;
        }

        bool operator<=(Colors::eColors ph_color, const PgColor_t &pg_color)
        {
            if (pg_color == ph_color)
                return true;
            return static_cast<PgColor_t>(ph_color) < pg_color;
        }

        bool operator>(Colors::eColors ph_color, const PgColor_t &pg_color)
        {
            if (pg_color == ph_color)
                return false;
            return static_cast<PgColor_t>(ph_color) > pg_color;
        }

        bool operator>=(Colors::eColors ph_color, const PgColor_t &pg_color)
        {
            if (pg_color == ph_color)
                return true;
            return static_cast<PgColor_t>(ph_color) > pg_color;
        }

        bool operator==(const PgColor_t &pg_color, const Color &ph_color)
        {
            return (pg_color == static_cast<PgColor_t>(ph_color));
        }

        bool operator!=(const PgColor_t &pg_color, const Color &ph_color)
        {
            return !(pg_color == ph_color);
        }

        bool operator<(const PgColor_t &pg_color, const Color &ph_color)
        {
            if (pg_color == ph_color)
                return false;
            return pg_color < static_cast<PgColor_t>(ph_color);
        }

        bool operator<=(const PgColor_t &pg_color, const Color &ph_color)
        {
            if (pg_color == ph_color)
                return true;
            return pg_color < static_cast<PgColor_t>(ph_color);
        }

        bool operator>(const PgColor_t &pg_color, const Color &ph_color)
        {
            if (pg_color == ph_color)
                return false;
            return pg_color > static_cast<PgColor_t>(ph_color);
        }

        bool operator>=(const PgColor_t &pg_color, const Color &ph_color)
        {
            if (pg_color == ph_color)
                return true;
            return pg_color > static_cast<PgColor_t>(ph_color);
        }

        bool operator==(const Color &ph_color, const PgColor_t &pg_color)
        {
            return (pg_color == ph_color);  
        }

        bool operator!=(const Color &ph_color, const PgColor_t &pg_color)
        {
            return !(pg_color == ph_color);
        }

        bool operator<(const Color &ph_color, const PgColor_t &pg_color)
        {
            if (pg_color == ph_color)
                return false;
            return static_cast<PgColor_t>(ph_color) < pg_color;
        }

        bool operator<=(const Color &ph_color, const PgColor_t &pg_color)
        {
            if (pg_color == ph_color)
                return true;
            return static_cast<PgColor_t>(ph_color) < pg_color;
        }

        bool operator>(const Color &ph_color, const PgColor_t &pg_color)
        {
            if (pg_color == ph_color)
                return false;
            return static_cast<PgColor_t>(ph_color) > pg_color;
        }

        bool operator>=(const Color &ph_color, const PgColor_t &pg_color)
        {
            if (pg_color == ph_color)
                return true;
            return static_cast<PgColor_t>(ph_color) > pg_color;
        }
    } // namespace Drawing
} // namespace PhWidgets


#endif // PHWIDGETS_COLOR_H
