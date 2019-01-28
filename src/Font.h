
#ifndef PT_FONT_H
#define PT_FONT_H

#include "./service/property.hpp"

#include <photon/Pf.h>


#include <string>
#include <vector>

namespace PhWidgets
{
    using namespace cppproperties;

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
            Underline = PF_STYLE_ULINE, //!< Underlined text.
            DoubleUnderline = PF_STYLE_DULINE, //!< Double underlined text.
            Antialias = PF_STYLE_ANTIALIAS, //!< Antialias text.
            Scalable = PF_SCALABLE, //!< Scalable text.
            Bitmap = PF_BITMAP //!< Bitmap text.
        };
    };

    //! Specifies a generic FontFamily object.
    struct GenericFontFamilies
    {
        enum eGenericFontFamilies
        {
            Monospace = PHFONT_INFO_PROP, //!< A generic Monospace FontFamily object.
            SansSerif = PHFONT_INFO_SANSERIF, //!< A generic Sans Serif FontFamily object.
            Serif = PHFONT_INFO_SERIF //!< A generic Serif FontFamily object.
        };
    };

    //! Provides a base class for installed and private font collections.
    /*!
        The FontCollection allows you to get a list of the font families 
        contained in the collection with its Families property.

        @see
        - InstalledFontCollection
        - PrivateFontCollection
    */
    class FontCollection
    {
    protected:
        FontCollection() {}
    private:
        struct FontCollectionDetail
        {
            static const std::vector<FontDetails>& getFamilies();
        };
    public:
        static const property<const std::vector<FontDetails>&>::
            bind_static<&FontCollectionDetail::getFamilies> Families;
    };

    //! Represents the fonts installed on the system. This class cannot be inherited.
    class InstalledFontCollection:
        public FontCollection
    {
    public:
        InstalledFontCollection();
    };

    //! (not implemented)
    //! Provides a collection of font families built from font files that are provided by the client application.
    class PrivateFontCollection;

    //! Defines a group of type faces having a similar basic design and certain variations in styles. This class cannot be inherited.
    class FontFamily:
        public GenericFontFamilies
    {
    public:
        //! (constructor) 
		/*!
			Initializes a new FontFamily from the specified generic font family.
			@param[in] ffamily The GenericFontFamilies::eGenericFontFamilies from which to create the new FontFamily.
            @throw std::invalid_argument
		*/
        FontFamily(GenericFontFamilies::eGenericFontFamilies ffamily);

        //! (constructor) 
		/*!
			Initializes a new FontFamily with the specified name.
			@param[in] name The name of the new FontFamily.
            @throw std::invalid_argument
		*/
        FontFamily(std::string name);

        //! (constructor) 
		/*!
			Initializes a new FontFamily with the specified name.
			@param[in] name A std::string that represents the name of the new FontFamily.
            @param[in] fcollection The FontCollection that contains this FontFamily.
            @throw std::invalid_argument
		*/
        FontFamily(std::string name, const FontCollection &fcollection);

        //! Returns the line spacing, in design units, of the FontFamily of the specified style. 
        //! The line spacing is the vertical distance between the base lines of two consecutive lines of text.
		/*!
			@param[in] fstyle The FontStyle::eFontStyle to apply.
		*/
        int GetLineSpacing(FontStyle::eFontStyle fstyle) const;

        //! Indicates whether the specified FontStyle::eFontStyle enumeration is available.
		/*!
			@param[in] fstyle The FontStyle::eFontStyle to test.
		*/
        bool IsStyleAvailable(FontStyle::eFontStyle fstyle) const;

        //! Converts FontFamily to Photon FontDetails type
        operator FontDetails() const;
    private:
        FontDetails _fdetails;
        
    public:
        //! Gets the name of this FontFamily.
		/*!
			### Property Value ### 
			
			> `std::string`

			A `std::string` that represents the name of this FontFamily.
		*/
        const std::string Name;
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