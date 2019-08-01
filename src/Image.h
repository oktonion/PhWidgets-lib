#ifndef PHWIDGETS_IMAGE_H
#define PHWIDGETS_IMAGE_H

#include <photon/PhT.h>
#include <photon/PtT.h>

#include <string>

namespace PhWidgets
{
    namespace Drawing
    {
        //! Provides a collection of bitmap image types for use by a Photon microGUI application.
        /*!
            @see
            - Drawing::DirectImageType 
            - Drawing::GradientImageType
            - Drawing::PaletteImageType
            - Drawing::ImageType

             @ingroup Values
        */
        struct BitmapImageType
        {
            //! @name Properties
            //! > Colors::eColors Collection of standard colors for use by a Photon microGUI application
            //! @{
            enum eBitmapImageType
            {
                BitmapBackfill = Pg_BITMAP_BACKFILL, //!< A bitonal image; the two colors are specified in the color palette. 
                BitmapTransparent = Pg_BITMAP_TRANSPARENT  //!< A monochrome image with transparent regions. 
                                                           //!< The bits in the image data that are set to 1 are drawn using color palette entry 1; 
                                                           //!< zeros are treated as transparent, so they're not drawn.
            };
        };

        //! Provides a collection of direct image types for use by a Photon microGUI application.
        /*!
            @see
            - Drawing::BitmapImageType 
            - Drawing::GradientImageType
            - Drawing::PaletteImageType
            - Drawing::ImageType
            
             @ingroup Values
        */
        struct DirectImageType
        {
            //! @name Properties
            //! > Colors::eColors Collection of standard colors for use by a Photon microGUI application
            //! @{
            enum eDirectImageType
            {
                ImageDirect1555 = Pg_IMAGE_DIRECT_1555, //!< This format has, for each pixel, one bit of alpha, and 5 bits each of red, green, and blue.
                ImageDirect4444 = Pg_IMAGE_DIRECT_4444, //!< This format has 4 bits of alpha, and 4 bits each of red, green, and blue. 
                ImageDirect444 = Pg_IMAGE_DIRECT_444, //!< This format requires 2 bytes per pixel. 
                                                      //!< It matches the high-speed color lookup tables used by palette-based graphics drivers 
                                                      //!< and provides the fastest method of drawing direct-color images with palette-based graphics drivers. 
                                                      //!< Here's the bit order: xxxx.RRRR.GGGG.BBBB
                ImageDirect565 = Pg_IMAGE_DIRECT_565, //!< This format packs each pixel into 2 bytes and matches the display format of most 16-bit, direct-color, graphics drivers. 
                                                      //!< Here's the bit order: RRRR.RGGG.GGGB.BBBB
                ImageDirect8888 = Pg_IMAGE_DIRECT_8888, //!< This format is an array of 4-byte color entries. 
                                                        //!< The least significant byte is the blue component, after that there is the green component, 
                                                        //!< following that there is the red component and the most significant byte is reserved. 
                ImageDirect888 = Pg_IMAGE_DIRECT_888  //!< This format packs each pixel into 3 bytes. Using this format, you can represent a full 24 bit color image. 
                                                      //!< Here's the bit order: RRRR.RRRR.GGGG.GGGG.BBBB.BBBB
            };
        };

        //! Provides a collection of gradient image types for use by a Photon microGUI application.
        /*!
            @see
            - Drawing::BitmapImageType 
            - Drawing::DirectImageType
            - Drawing::PaletteImageType
            - Drawing::ImageType
            
             @ingroup Values
        */
        struct GradientImageType
        {
            //! @name Properties
            //! > Colors::eColors Collection of standard colors for use by a Photon microGUI application
            //! @{
            enum eGradientImageType
            {
                ImageGradientByte = Pg_IMAGE_GRADIENT_BYTE, //!< This format uses 1 byte per pixel. 
                                                            //!< The colors are algorithmically generated as a gradient between the fill color and the text color. 
                                                            //!< A pixel value of 0 produces the fill color, a pixel value of 255 produces the text color, and a pixel value of 128 produces an even blend of the two.
                ImageGradientNibble = Pg_IMAGE_GRADIENT_NIBBLE  //!< This format packs 2 pixels per byte, allowing up to 16 levels. 
                                                                //!< The first pixel is in the upper half of the byte and the second pixel is in the lower half. 
                                                                //!< The colors are algorithmically generated as a gradient between the fill color and the text color. 
                                                                //!< A pixel value of 0 produces the fill color, a pixel value of 15 produces the text color, and a pixel value of 8 produces an even blend of the two.

            };
        };

        //! Provides a collection of palette image types for use by a Photon microGUI application.
        /*!
            @see
            - Drawing::BitmapImageType 
            - Drawing::DirectImageType
            - Drawing::GradientImageType
            - Drawing::ImageType
            
             @ingroup Values
        */
        struct PaletteImageType
        {
            //! @name Properties
            //! > Colors::eColors Collection of standard colors for use by a Photon microGUI application
            //! @{
            enum ePaletteImageType
            {
                ImagePaletteByte = Pg_IMAGE_PALETTE_BYTE, //!< This format packs 1 pixel per byte, allowing up to 256 colors. 
                                                          //!< This format indexes directly into the current palette;
                                                          //!< If no palette is set, the function chooses colors from the global palette; this may cause colors to look different on each system.
                ImagePaletteNibble = Pg_IMAGE_PALETTE_NIBBLE  //!< This format packs 2 pixels per byte, allowing up to 16 colors. 
                                                              //!< The first pixel is in the upper half of the byte, the second is in the lower half. 
                                                              //!< These pixel values index directly into the current palette. 
                                                              //!< If no palette is set, the function chooses colors from the global palette.
            };
        };

        //! Provides a collection of all image types for use by a Photon microGUI application.
        /*!
            @see
            - Drawing::BitmapImageType 
            - Drawing::DirectImageType
            - Drawing::GradientImageType
            - Drawing::PaletteImageType
            
             @ingroup Values
        */
        struct ImageType:
            BitmapImageType,
            DirectImageType,
            GradientImageType,
            PaletteImageType
        { 
            //! @name Members
            //@{
            /*!
                - ImageType::BitmapBackfill 
                - ImageType::BitmapTransparent
            */
           using BitmapImageType::eBitmapImageType;
            /*!
                - ImageType::ImageDirect1555
                - ImageType::ImageDirect4444
                - ImageType::ImageDirect444
                - ImageType::ImageDirect565
                - ImageType::ImageDirect8888
                - ImageType::ImageDirect888
            */
           using DirectImageType::eDirectImageType;
            /*!
                - ImageType::ImageGradientByte
                - ImageType::ImageGradientNibble
            */
           using GradientImageType::eGradientImageType;
            /*!
                - ImageType::ImagePaletteByte
                - ImageType::ImagePaletteNibble
            */
           using PaletteImageType::ePaletteImageType;
            //@}
        };
    } // namespace Drawing

    namespace Drawing
    {
        //! An abstract base class that provides functionality for the Drawing::Bitmap class.
        /*!
            @remark
            To draw an Image on a Form, you should use one of the Drawing::Graphics::DrawImage methods.

            @see
            - Drawing::ImageType
            - Label::Image

             @ingroup Classes
        */
        class Image
        {
        public:
		    //! (copy constructor) 
		    /*!
			    Constructs an Image from PhImage_t.
			    @param[in] image PhImage_t to be used as source to initialize the elements of the container with.

                @attention
                Image class makes copy of image provided so input PhImage_t remains untouched.

                @remark
                You can create an Image using Image::FromFile(), Image::FromHbitmap(), Image::FromStream() functions.

                @see
                - Image::FromFile()
                - Image::FromHbitmap()
                - Image::FromStream()
            */
            Image(const PhImage_t &image);

            //! (copy constructor) 
		    /*!
			    Constructs an Image by copy.
			    @param[in] other Another Image to be used as source to initialize the elements of the container with.

                @remark
                You can create an Image using Image::FromFile(), Image::FromHbitmap(), Image::FromStream() functions.

                @see
                - Image::FromFile()
                - Image::FromHbitmap()
                - Image::FromStream()
            */
            Image(const Image &other);

            //! @name Properties
            //! @{ 

            //! Gets the width and height, in pixels, of this Image.
            /*!
                ### Property Value ### 
                
                > PhDim_t

                The `PhDim_t` that represents the width and height, in pixels, of this image.

                @see 
                - Width
                - Height
            */
            const PhDim_t Size;

            //! Gets the width, in pixels, of this Image.
            /*!
                ### Property Value ### 
                
                > **unsigned short**

                The width, in pixels, of this Image.

                @see 
                - Size
                - Height
            */
            const unsigned short Width;

            //! Gets the height, in pixels, of this Image.
            /*!
                ### Property Value ### 
                
                > **unsigned short**

                The height, in pixels, of this Image.

                @see 
                - Size
                - Width
            */
            const unsigned short Height;
            
            //! @}    


		    //! Creates an Image from the specified file.
		    /*!
			    @param[in] filename A string that contains the name of the file from which to create the Image.
                @returns The Image this method creates.
                @throws std::ios_base::failure

                @remark
                Photon has built-in encoders and decoders that support the following file types:
                - BMP
                - GIF
                - JPEG
                - PNG
                - PCX
                - SGI

                The file remains locked until the Image is disposed.

                @note
                The Image class does not support alpha transparency in bitmaps. To enable alpha transparency, use PNG images with 32 bits per pixel.

                @see
                - Image::FromHbitmap()
                - Image::FromStream()
            */
            static Image FromFile(std::string filename);

            //! Converts to the pointer to `PhImage_t` struct.
            /*!
                @return The pointer to `PhImage_t` struct with the Image or nullptr.
            */
            operator PhImage_t* () const;

        private:
            PhImage_t *_image;

            struct ImageInfo;

            Image(const ImageInfo&);
        };
    }
} // namespace PhWidgets

#endif // PHWIDGETS_IMAGE_H
