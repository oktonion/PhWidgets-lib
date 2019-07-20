#ifndef PHWIDGETS_LABEL_H
#define PHWIDGETS_LABEL_H

#include <photon/PtLabel.h>

#include <string>

#include "./Basic.h"
#include "./Font.h"


namespace PhWidgets
{
	//! A text, bitmap, or image label
	/*!
		The Label class provides a text string, bitmap, or image for labeling other widgets. 
		You can have text pop up in a balloon to provide further meaning to the label. 

		@see
		- Button
		- Text
	*/
	class Label:
		public Basic
	{
	public:

		//! Contains resource IDs for Label arguments.
		struct ThisArgs
		{
			//! Contains resource IDs for Label arguments of type <b>char*</b>.
			struct ArgPChar
			{
				//! Resource IDs for Label arguments of type <b>char*</b>.

				/*!
					### Aliases ###
					
					PhWidgets::Label::Arguments::eArgPChar,
					PhWidgets::Label::ArgPChar::eArgPChar

					See Widget::resource for usage description.
				*/
				enum eArgPChar
				{
					accel_key = Pt_ARG_ACCEL_KEY,
					balloon_text = Pt_ARG_BALLOON_TEXT,
					text_font = Pt_ARG_TEXT_FONT,
					text_string = Pt_ARG_TEXT_STRING
				};
			};	
			
			//! Contains resource IDs for Label arguments of type `PgColor_t`.
			struct ArgColor
			{
				//! Resource IDs for Label arguments of type `PgColor_t`.

				/*!
					### Aliases ###
					
					PhWidgets::Label::Arguments::eArgColor,
					PhWidgets::Label::ArgColor::eArgColor

					See Widget::resource for usage description.
				*/
				enum eArgColor
				{
					balloon_color = Pt_ARG_BALLOON_COLOR,
					balloon_fill_color = Pt_ARG_BALLOON_FILL_COLOR,
					underline1 = Pt_ARG_UNDERLINE1,
					underline2 = Pt_ARG_UNDERLINE2
				};
			};
			
            //! Contains resource IDs for Label arguments of type **short**.
			struct ArgShort
			{
                //! Resource IDs for Label arguments of type **short**.

				/*!
					### Aliases ###
					
					PhWidgets::Label::Arguments::eArgShort,
					PhWidgets::Label::ArgShort::eArgShort

					See Widget::resource for usage description.
				*/
				enum eArgShort
				{
					balloon_position = Pt_ARG_BALLOON_POSITION
				};
			};

			//! Contains resource IDs for Label arguments of type **unsigned short**.
			struct ArgUnsignedShort
			{
				//! Resource IDs for Label arguments of type **unsigned short**.

				/*!
					### Aliases ###
					
					PhWidgets::Label::Arguments::eArgUnsignedShort,
					PhWidgets::Label::ArgUnsignedShort::eArgUnsignedShort

					See Widget::resource for usage description.
				*/
				enum eArgUnsignedShort
				{
					line_spacing = Pt_ARG_LINE_SPACING,
					margin_botton = Pt_ARG_MARGIN_BOTTOM,
					margin_left = Pt_ARG_MARGIN_LEFT,
					margin_right = Pt_ARG_MARGIN_RIGHT,
					margin_top = Pt_ARG_MARGIN_TOP,
					undeline_type = Pt_ARG_UNDERLINE_TYPE				
				};
			};

			//! Contains resource IDs for Label arguments of type **signed short**.
			struct ArgSignedShort
			{
				//! Resource IDs for Label arguments of type **signed short**.

				/*!
					### Aliases ###
					
					PhWidgets::Label::Arguments::eArgSignedShort,
					PhWidgets::Label::ArgSignedShort::eArgSignedShort

					See Widget::resource for usage description.
				*/
				enum eArgSignedShort
				{
					secondary_h_align = Pt_ARG_SECONDARY_H_ALIGN,
					secondary_v_align = Pt_ARG_SECONDARY_V_ALIGN
				};
			};

			//! Contains resource IDs for Label arguments of type **unsigned char**.
			struct ArgUnsignedChar
			{
				//! Resource IDs for Label arguments of type **unsigned char**.

				/*!
					### Aliases ###
					
					PhWidgets::Label::Arguments::eArgUnsignedChar,
					PhWidgets::Label::ArgUnsignedChar::eArgUnsignedChar

					See Widget::resource for usage description.
				*/
				enum eArgUnsignedChar
				{
					horizontal_alignment = Pt_ARG_HORIZONTAL_ALIGNMENT,
					vertical_alingment = Pt_ARG_VERTICAL_ALIGNMENT
				};
			};

			//! Contains resource IDs for Label arguments of type `PtWidget_t * (*)()`.
			struct ArgPWidgetFunc
			{
				//! Resource IDs for Label arguments of type `PtWidget_t * (*)()`.

				/*!
					### Aliases ###
					
					PhWidgets::Label::Arguments::eArgPWidgetFunc,
					PhWidgets::Label::ArgPWidgetFunc::eArgPWidgetFunc

					See Widget::resource for usage description.
				*/
				enum eArgPWidgetFunc
				{
					label_baloon = Pt_ARG_LABEL_BALLOON
				};
			};

			//! Contains resource IDs for Label arguments of type **char**.
			struct ArgChar
			{		
				//! Resource IDs for Label arguments of type **char**.

				/*!
					### Aliases ###
					
					PhWidgets::Label::Arguments::eArgChar,
					PhWidgets::Label::ArgChar::eArgChar

					See Widget::resource for usage description.
				*/
				enum eArgChar
				{
					label_flags = Pt_ARG_LABEL_FLAGS,
					label_type = Pt_ARG_LABEL_TYPE
				};
			};

			//! Contains resource IDs for Label arguments of type `PhImage_t`.
			struct ArgPImage
			{
				//! Resource IDs for Label arguments of type `PhImage_t`.

				/*!
					### Aliases ###
					
					PhWidgets::Label::Arguments::eArgPImage,
					PhWidgets::Label::ArgPImage::eArgPImage

					See Widget::resource for usage description.
				*/
				enum eArgPImage
				{
					label_image = Pt_ARG_LABEL_IMAGE
				};
			};
			
			//! Contains resource IDs for Label arguments of type **int**.
			struct ArgInt
			{
				//! Resource IDs for Label arguments of type **long**.

				/*!
					### Aliases ###
					
					PhWidgets::Label::Arguments::eArgInt,
					PhWidgets::Label::ArgInt::eArgInt

					See Widget::resource for usage description.
				*/
				enum eArgInt
				{
					image_spacing = Pt_ARG_TEXT_IMAGE_SPACING
				};
			};


		};
		
		//! Contains resource IDs for arguments of type <b>char*</b>.
		struct ArgPChar:
			public ArgumentsEx<Basic::ArgPChar>,
			public ThisArgs::ArgPChar
		{
			typedef ThisArgs::ArgPChar::eArgPChar eArgPChar;
		};	
		
		//! Contains resource IDs for arguments of type `PgColor_t`.
		struct ArgColor:
			public ArgumentsEx<Basic::ArgColor>,
			public ThisArgs::ArgColor
		{
			typedef ThisArgs::ArgColor::eArgColor eArgColor;
		};

		//! Contains resource IDs for arguments of type **short**.
		struct ArgShort:
			public ThisArgs::ArgShort
        { };	

		//! Contains resource IDs for arguments of type **unsigned short**.
		struct ArgUnsignedShort:
			public ArgumentsEx<Basic::ArgUnsignedShort>,
			public ThisArgs::ArgUnsignedShort
		{
			typedef ThisArgs::ArgUnsignedShort::eArgUnsignedShort eArgUnsignedShort;
		};	

		//! Contains resource IDs for arguments of type **signed short**.
		struct ArgSignedShort:
			public ThisArgs::ArgSignedShort
        { };	

		//! Contains resource IDs for arguments of type **unsigned char**.
		struct ArgUnsignedChar:
			public ArgumentsEx<Basic::ArgUnsignedChar>,
			public ThisArgs::ArgUnsignedChar
		{
			typedef ThisArgs::ArgUnsignedChar::eArgUnsignedChar eArgUnsignedChar;
		};

		//! Contains resource IDs for arguments of type `PtWidget_t * (*)()`.
		struct ArgPWidgetFunc:
			public ThisArgs::ArgPWidgetFunc
        { };	

		//! Contains resource IDs for arguments of type **char**.
		struct ArgChar:
			public ArgumentsEx<Basic::ArgChar>,
			public ThisArgs::ArgChar
		{
			typedef ThisArgs::ArgChar::eArgChar eArgChar;
		};	

		//! Contains resource IDs for arguments of type `PhImage_t`.
		struct ArgPImage:
			public ThisArgs::ArgPImage
        { };

		//! Contains resource IDs for arguments of type **int**.
		struct ArgInt:
			public ThisArgs::ArgInt
        { };	


		//! Contains resource IDs for all Label arguments.
		struct Arguments:
			public ArgPChar,
			public ArgColor,
			public ArgShort,
			public ArgUnsignedShort,
			public ArgSignedShort,
			public ArgUnsignedChar,			
			public ArgPWidgetFunc,
			public ArgChar,
			public ArgPImage,
			public ArgInt,
			public Basic::Arguments
		{
																								
		};
		
	protected:

		typedef ResourceFrom<Basic::WidgetResourcesSingleton>::
			Define::String<ThisArgs::ArgPChar::eArgPChar>::
			Define::Color<ThisArgs::ArgColor::eArgColor>::
			Define::Scalar<ThisArgs::ArgUnsignedShort::eArgUnsignedShort, unsigned short>::
			Define::Scalar<ThisArgs::ArgShort::eArgShort, short>::
			Define::Scalar<ThisArgs::ArgSignedShort::eArgSignedShort, signed short>::
			Define::Scalar<ThisArgs::ArgUnsignedChar::eArgUnsignedChar, unsigned char>::

		resource_type WidgetResourcesSingleton;

		std::string getCaption() const;
		void setCaption(std::string);

		Drawing::Font getFont() const;
		void setFont(Drawing::Font);

		virtual void check();
						
	public:
		//! Resources of the Label
		/*!
			@see
			- Widget::resource
		*/
		WidgetResourcesSingleton resource;

		//! (constructor) 
		/*!
			Constructs a Label widget by ID.
			@param[in] abn ID given by PhAB to widget (like 'ABN_WIDGET_NAME').
		*/
		Label(int abn);

		//! (constructor) 
		/*!
			Constructs a Label widget by pointer to widget.
			@param[in] wdg pointer to Photon widget.
		*/		
		Label(PtWidget_t *wdg);
		
		//! (copy constructor) 
		/*!
			Constructs a Label widget by copy.
			@param[in] other another Label widget to be used as source to initialize the elements of the container with.
		*/
		Label(const Label &other);

		//! Assigns value in Label widget 
		/*!
			Replaces the contents of the Label widget.
			@param[in] other another Label widget to use as data source.
		*/
		Label &operator=(const Label &other);
		
		//! @name Properties
		//! Properties are used to simplify use of widget resources.
		//@{
		property<std::string>::bind<Label, &Label::getCaption, &Label::setCaption> Caption;

		//! Gets or sets the font of the text displayed by the widget.
		/*!
			### Property Value ### 
			
			> Font

			The Font to apply to the text displayed by the widget. The default is the value of the DefaultFont property.
			
			@remark
			The Font property is an ambient property. 
			An ambient property is a widget property that, if not set, is retrieved from the parent widget. 
			For example, a Button will have the same BackColor as its parent PhWidgets::Window by default. 
			@par
			Because the Font is immutable (meaning that you cannot adjust any of its properties), 
			you can only assign the Font property a new Font. However, you can base the new font on the existing font. 

			@see
			- FontChanged
			- OnFontChanged(PtCallbackInfo_t*)
			- Font
		*/
		property<Drawing::Font>::bind<Label, &Label::getFont, &Label::setFont> Font;

		//! Gets or sets the balloon color of the Label.
		/*!
			### Property Value ### 
			
			> Drawing::Color

			A `Drawing::Color` that represents the balloon color of the Label.

			@see
			- Drawing::Colors
			- Drawing::Color
		*/
		phproperty<Drawing::Color>::bind<Label, ArgColor::eArgColor, Arguments::balloon_color> BalloonColor;
		//@}
	};

} // namespace PhWidgets


#endif // PHWIDGETS_LABEL_H
