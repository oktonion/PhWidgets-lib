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
		struct ThisArgs
		{
			struct ArgPChar
			{
				enum eArgPChar
				{
					accel_key = Pt_ARG_ACCEL_KEY,
					balloon_text = Pt_ARG_BALLOON_TEXT,
					text_font = Pt_ARG_TEXT_FONT,
					text_string = Pt_ARG_TEXT_STRING
				};
			};	
			
			struct ArgColor
			{
				enum eArgColor
				{
					balloon_color = Pt_ARG_BALLOON_COLOR,
					balloon_fill_color = Pt_ARG_BALLOON_FILL_COLOR,
					underline1 = Pt_ARG_UNDERLINE1,
					underline2 = Pt_ARG_UNDERLINE2
				};
			};
			
			struct ArgShort
			{
				enum eArgShort
				{
					balloon_position = Pt_ARG_BALLOON_POSITION
				};
			};
			
			struct ArgUnsignedShort
			{
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
			
			struct ArgSignedShort
			{
				enum eArgSignedShort
				{
					secondary_h_align = Pt_ARG_SECONDARY_H_ALIGN,
					secondary_v_align = Pt_ARG_SECONDARY_V_ALIGN
				};
			};
			
			struct ArgUnsignedChar
			{
				enum eArgUnsignedChar
				{
					horizontal_alignment = Pt_ARG_HORIZONTAL_ALIGNMENT,
					vertical_alingment = Pt_ARG_VERTICAL_ALIGNMENT
				};
			};
			
			struct ArgPWidget
			{
				enum eArgPWidget
				{
					label_baloon = Pt_ARG_LABEL_BALLOON
				};
			};

			struct ArgChar
			{
				enum eArgChar
				{
					label_flags = Pt_ARG_LABEL_FLAGS,
					label_type = Pt_ARG_LABEL_TYPE
				};
			};
			
			struct ArgPImage
			{
				enum eArgPImage
				{
					label_image = Pt_ARG_LABEL_IMAGE
				};
			};
			
			struct ArgInt
			{
				enum eArgInt
				{
					image_spacing = Pt_ARG_TEXT_IMAGE_SPACING
				};
			};


		};
				
		struct ArgPChar:
			public ArgumentsEx<Basic::ArgPChar>,
			public ThisArgs::ArgPChar
		{
			typedef ThisArgs::ArgPChar::eArgPChar eArgPChar;
		};	
			
		struct ArgColor:
			public ArgumentsEx<Basic::ArgColor>,
			public ThisArgs::ArgColor
		{
			typedef ThisArgs::ArgColor::eArgColor eArgColor;
		};

		struct ArgShort:
			public ThisArgs::ArgShort
        { };	

		struct ArgUnsignedShort:
			public ArgumentsEx<Basic::ArgUnsignedShort>,
			public ThisArgs::ArgUnsignedShort
		{
			typedef ThisArgs::ArgUnsignedShort::eArgUnsignedShort eArgUnsignedShort;
		};	

		struct ArgSignedShort:
			public ThisArgs::ArgSignedShort
        { };	

		struct ArgUnsignedChar:
			public ArgumentsEx<Basic::ArgUnsignedChar>,
			public ThisArgs::ArgUnsignedChar
		{
			typedef ThisArgs::ArgUnsignedChar::eArgUnsignedChar eArgUnsignedChar;
		};

		struct ArgPWidget:
			public ThisArgs::ArgPWidget
        { };	

		struct ArgChar:
			public ArgumentsEx<Basic::ArgChar>,
			public ThisArgs::ArgChar
		{
			typedef ThisArgs::ArgChar::eArgChar eArgChar;
		};	

		struct ArgPImage:
			public ThisArgs::ArgPImage
        { };	

		struct ArgInt:
			public ThisArgs::ArgInt
        { };	



		struct Arguments:
			public ArgPChar,
			public ArgColor,
			public ArgShort,
			public ArgUnsignedShort,
			public ArgSignedShort,
			public ArgUnsignedChar,			
			public ArgPWidget,
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
		WidgetResourcesSingleton resource;

		Label(int abn);
		Label(PtWidget_t *wdg);
		
		Label(const Label&);

		Label &operator=(const Label &rhs);
		
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

		phproperty<PgColor_t>::bind<Label, ArgColor::eArgColor, Arguments::balloon_color> BalloonColor;
		//@}
	};

} // namespace PhWidgets


#endif // PHWIDGETS_LABEL_H
