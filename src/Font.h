
#ifndef PHWIDGETS_FONT_H
#define PHWIDGETS_FONT_H

#include "./service/property.hpp"
#include "./service/bitmask.hpp"

#include <photon/Pf.h>


#include <string>
#include <vector>

namespace PhWidgets
{
    using namespace cppproperties;

    namespace Drawing
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
                    Button1.Font = Font(FontFamily::Generic, 12.0f, FontStyle::Bold);
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

        namespace typedefs
        {
            typedef
            cppbitmasks::bitmask<
                unsigned short,    
                FontStyle::eFontStyle, 
                FontStyle::Antialias |
                FontStyle::Bitmap |
                FontStyle::Bold |
                FontStyle::DoubleUnderline |
                FontStyle::Italic |
                FontStyle::Regular |
                FontStyle::Scalable |
                FontStyle::Underline
            > font_style_bitmask;
        }

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
        class FontFamily
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
                Initializes a new FontFamily from the specified photon FontDetails.
                @param[in] fdetails The FontDetails from which to create the new FontFamily.
                @throw std::invalid_argument
            */
            FontFamily(const FontDetails &fdetails);

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

            //! (copy constructor) 
            /*!
                Constructs a FontFamily by copy.
                @param[in] other another FontFamily to be used as source to initialize the elements of the container with.
            */
            FontFamily(const FontFamily &other);
            
            //! Assigns value in FontFamily 
            /*!
                Replaces the contents of the FontFamily.
                @param[in] other another FontFamily to use as data source.
            */
            FontFamily &operator=(const FontFamily &other);

            //! Compares FontFamilys
            /*!
                Compares the FontFamilys by their Photon FontDetails.
                @param[in] other FontFamily whose contents to compare.
            */
            bool operator==(const FontFamily &other) const;

            //! Compares FontFamilys
            /*!
                Compares the FontFamilys by their Photon FontDetails.
                @param[in] other FontFamily whose contents to compare.
            */
            bool operator!=(const FontFamily &other) const;

            //! Compares FontFamilys
            /*!
                Compares the FontFamilys by their Photon FontDetails.
                @param[in] other FontFamily whose contents to compare.
            */
            bool operator<(const FontFamily &other) const;

            //! Returns the line spacing, in design units, of the FontFamily of the specified style. 
            //! The line spacing is the vertical distance between the base lines of two consecutive lines of text.
            /*!
                @param[in] fstyle The FontStyle::eFontStyle to apply.
            */
            int GetLineSpacing(typedefs::font_style_bitmask fstyle) const;

            //! Indicates whether the specified FontStyle::eFontStyle enumeration is available.
            /*!
                @param[in] fstyle The FontStyle::eFontStyle to test.
            */
            bool IsStyleAvailable(typedefs::font_style_bitmask fstyle) const;

            operator FontDetails() const;

        private:
            FontDetails _fdetails;
            std::string _name;
            
        public:
            //! Gets the name of this FontFamily.
            /*!
                ### Property Value ### 
                
                > `std::string`

                A `std::string` that represents the name of this FontFamily.
            */
            const std::string &Name;
        };

        //! Defines a particular format for text, including font face, size, and style attributes. This class cannot be inherited.
        class Font
        {
            typedef FontID* font_id_type;

        public:

            //! (constructor) 
            /*!
                Initializes a new Font that uses the specified existing Font and FontStyle::eFontStyle enumeration.
                @param[in] other The existing Font from which to create the new Font.
                @param[in] fstyle   The FontStyle::eFontStyle to apply to the new Font. 
                                    Multiple values of the FontStyle::eFontStyle enumeration can be combined with the OR operator.
                @throw std::invalid_argument
            */
            Font(const Font &other, typedefs::font_style_bitmask fstyle);

            //! (constructor) 
            /*!
                Initializes a new Font using a specified size and style.
                @param[in] ffamily The FontFamily of the new Font.
                @param[in] size The em-size, in points, of the new font.
                @param[in] fstyle The FontStyle::eFontStyle combination of flags.
            */
            Font(FontFamily ffamily, std::uint32_t size, typedefs::font_style_bitmask fstyle = FontStyle::Regular);

            //! (constructor) 
            /*!
                Initializes a new Font using a Photon FontID.
                @param[in] fid Photon FontID.
            */
            Font(font_id_type fid);

            //Font(FontFamily, float, FontStyle, GraphicsUnit);		
            //Font(FontFamily, float, GraphicsUnit) 	       

            //! (copy constructor) 
            /*!
                Constructs a Font by copy.
                @param[in] other another Font to be used as source to initialize the elements of the container with.
            */
            Font(const Font &other);
            
            //! Assigns value in Font 
            /*!
                Replaces the contents of the Font.
                @param[in] other another Font to use as data source.
            */
            Font &operator=(const Font &other);

            //! Compares Fonts
            /*!
                Compares the Fonts by their Photon FontID.
                @param[in] other Font whose contents to compare.
            */
            bool operator==(const Font &other) const;
            
            //! Compares Fonts
            /*!
                Compares the Fonts by their Photon FontID.
                @param[in] other Font whose contents to compare.
            */
            bool operator!=(const Font &other) const;

            //! Compares Fonts
            /*!
                Compares the Fonts by their Photon FontID.
                @param[in] other Font whose contents to compare.
            */
            bool operator<(const Font &other) const;

            //! Converts Font to Photon FontID
            operator const font_id_type() const;

            //! @name Properties
            //! Properties are used to simplify use of fonts.
            //@{

            //! Gets a value that indicates whether this Font is bold.
            const bool &Bold;
            
            //! Gets the FontFamily associated with this Font.
            const FontFamily &Family;

            //! Gets the line spacing of this Font.
            const std::uint32_t &Height;

            //! Gets a value that indicates whether this Font has the italic style applied.
            const bool &Italic;

            //! Gets the face name of this Font.
            const std::string &Name;

            //! Gets the em-size, in points, of this Font.
            const std::uint32_t &Size;
            
            // Gets the name of the Font originally specified.
            //const std::string &OriginalFontName;

            /*
            

            // Gets a byte value that specifies the GDI character set that this Font uses.
            // GdiCharSet 	

            // Gets a Boolean value that indicates whether this Font is derived from a GDI vertical Font.
            // GdiVerticalFont 	

            
            // Gets a value indicating whether the Font is a member of SystemFonts.
            // IsSystemFont 		

                

            Gets the em-size of this Font measured in the units specified by the Unit property.
            SizeInPoints 	

            
            Strikeout 	

            Gets a value that indicates whether this Font specifies a horizontal line through the Font.
            Style 	

            Gets style information for this Font.
            SystemFontName 	

            Gets the name of the system Font if the IsSystemFont property returns true.
            Underline 	

            Gets a value that indicates whether this Font is underlined.
            Unit 	

            Gets the unit of measure for this Font.*/
            //@}

            /*Methods

            Returns the line spacing, in pixels, of this Font.
            GetHeight() 	*/

        private:

            font_id_type _fid;
            std::string _fname;
            bool _bold, _italic;
            std::uint32_t _height, _size;
            FontFamily _ffamily;
        };

        bool operator==(const GenericFontFamilies::eGenericFontFamilies &lhs, const FontFamily &rhs);
        bool operator!=(const GenericFontFamilies::eGenericFontFamilies &lhs, const FontFamily &rhs);
        bool operator<(const GenericFontFamilies::eGenericFontFamilies &lhs, const FontFamily &rhs);
    } // namespace Drawing
} // namespace PhWidgets

PhWidgets::Drawing::typedefs::font_style_bitmask operator|(const PhWidgets::Drawing::FontStyle::eFontStyle &flag1, const PhWidgets::Drawing::FontStyle::eFontStyle &flag2);
PhWidgets::Drawing::typedefs::font_style_bitmask operator&(const PhWidgets::Drawing::FontStyle::eFontStyle &flag1, const PhWidgets::Drawing::FontStyle::eFontStyle &flag2);
PhWidgets::Drawing::typedefs::font_style_bitmask operator^(const PhWidgets::Drawing::FontStyle::eFontStyle &flag1, const PhWidgets::Drawing::FontStyle::eFontStyle &flag2);

#endif // PHWIDGETS_FONT_H