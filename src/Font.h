
#ifndef PT_FONT_H
#define PT_FONT_H

#include <photon/Pf.h>

#include <string>

namespace PhWidgets
{
    //! Specifies style information applied to text.
    /*!
        ### Examples ###

        The following code example demonstrates how to set the Font property of a button to a new bold-style font using the FontStyle::eFontStyle enumeration. 
        Create a form containing a button named Button1 and paste the following code into it. 

        @code
            // You have somewhere:
            PtWidget_t *ptwidget; // pointer to button widget

            using namespace PhWidgets;

            // constructing Button
            Button Button1(ptwidget);
            
            if (Button1.Font().Style != FontStyle::Bold)
                Button1.Font = FontDef(FontFamily::Generic, 12.0f, FontStyle::Bold);
        @endcode

        @see
        - Label
        - Button
    */
    struct FontStyle
    {
        enum eFontStyle
        {
            Bold = PF_STYLE_BOLD, //!< Bold text.
            Italic = PF_STYLE_ITALIC, //!< Italic text.
            Regular = 0, //!< Normal text.
            Antialias = PF_STYLE_ANTIALIAS, //!< Antialias text.
            Scalable = PF_SCALABLE, //!< Scalable text.
            Bitmap = PF_BITMAP //!< Bitmap text.
        };
    };

    //! Defines a particular format for text, including font face, size, and style attributes. This class cannot be inherited.
    class FontDef
    {
    public:

        //! (constructor) 
		/*!
			Initializes a new FontDef that uses the specified existing FontDef and FontStyle::eFontStyle enumeration.
			@param[in] other The existing FontDef from which to create the new FontDef.
            @param[in] fstyle   The FontStyle::eFontStyle to apply to the new Font. 
                                Multiple values of the FontStyle::eFontStyle enumeration can be combined with the OR operator.
		*/
        FontDef(const FontDef &other, FontStyle::eFontStyle fstyle);

        // (constructor) 
		/*
			Initializes a new FontDef using a specified size.
		*/
        //FontDef(FontFamily, float); 	

        // (constructor) 
		/*
			Initializes a new FontDef using a specified size and style.
		*/
        //FontDef(FontFamily, float, FontStyle::eFontStyle fstyle);

        // (constructor) 
		/*
			Initializes a new FontDef using a specified size, style, and unit.
		*/
        //FontDef(FontFamily, float, FontStyle, GraphicsUnit);		

        //FontDef(FontFamily, float, GraphicsUnit) 	

        //! (constructor) 
		/*!
			Initializes a new FontDef using a specified size.
			@param[in] family_name A string representation of the FontFamily for the new FontDef.
            @param[in] fsize The em-size of the new font
		*/
        FontDef(std::string family_name, float fsize);

        //! (constructor) 
		/*!
			Initializes a new FontDef using a specified size and style.
			@param[in] family_name A string representation of the FontFamily for the new FontDef.
            @param[in] fsize The em-size of the new font
            @param[in] fstyle   The FontStyle::eFontStyle to apply to the new Font. 
                                Multiple values of the FontStyle::eFontStyle enumeration can be combined with the OR operator.
		*/
        FontDef(std::string family_name, float fsize, FontStyle::eFontStyle fstyle);
        
        //! @name Properties
		//! Properties are used to simplify use of fonts.
		//@{
        
        /*Bold 	

        Gets a value that indicates whether this FontDef is bold.
        FontFamily 	

        Gets the FontFamily associated with this FontDef.
        GdiCharSet 	

        Gets a byte value that specifies the GDI character set that this FontDef uses.
        GdiVerticalFontDef 	

        Gets a Boolean value that indicates whether this FontDef is derived from a GDI vertical FontDef.
        Height 	

        Gets the line spacing of this FontDef.
        IsSystemFontDef 	

        Gets a value indicating whether the FontDef is a member of SystemFontDefs.
        Italic 	

        Gets a value that indicates whether this FontDef has the italic style applied.
        Name 	

        Gets the face name of this FontDef.
        OriginalFontDefName 	

        Gets the name of the FontDef originally specified.
        Size 	

        Gets the em-size of this FontDef measured in the units specified by the Unit property.
        SizeInPoints 	

        Gets the em-size, in points, of this FontDef.
        Strikeout 	

        Gets a value that indicates whether this FontDef specifies a horizontal line through the FontDef.
        Style 	

        Gets style information for this FontDef.
        SystemFontDefName 	

        Gets the name of the system FontDef if the IsSystemFontDef property returns true.
        Underline 	

        Gets a value that indicates whether this FontDef is underlined.
        Unit 	

        Gets the unit of measure for this FontDef.*/
        //@}

        /*Methods

        Returns the line spacing, in pixels, of this FontDef.
        GetHeight() 	*/

        
    };
} // PhWidgets

#endif // PT_FONT_H