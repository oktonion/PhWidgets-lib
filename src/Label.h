#ifndef PHWIDGETS_LABEL_H
#define PHWIDGETS_LABEL_H

#include <photon/PtLabel.h>

#include <string>

#include "./Basic.h"
#include "./Font.h"


namespace PhWidgets
{
	//! Indicates where the balloon with the Label 's text pops up.
	/*! 
		Apply to Label::BalloonPosition property.

		@see
    	- Label::BalloonPosition
		- Label::Arguments::balloon_position
	*/
	struct BalloonPosition
	{
		//! Possible Label balloon positions.
		/*!
			@see
			- Label::BalloonPosition
			- Label::Arguments::balloon_position
		*/
		enum eBalloonPosition
		{
			Inplace = Pt_BALLOON_INPLACE, //!< keep Label balloon inplace.
			Top = Pt_BALLOON_TOP, //!< place Label balloon to top.
			Left = Pt_BALLOON_LEFT, //!< place Label balloon to left.
			Right = Pt_BALLOON_RIGHT, //!< place Label balloon to right.
			Bottom = Pt_BALLOON_BOTTOM //!< place Label balloon to bottom.
		};
	};

	//! The type of information displayed by the Label.
	/*! 
		Apply to Label::Type property.

		@see
    	- Label::Type
		- Label::Arguments::label_type
	*/
	struct LabelType
	{
		//! Possible type of information displayed by the Label.
		/*!
			@see
			- Label::Type
			- Label::Arguments::label_type
			- Label::Arguments::label_image
			- Label::Text
		*/
		enum eLabelType
		{
			String = Pt_Z_STRING, //!< Use Label::Text (Label::Argument::text_string resource) to display the text.
			Image = Pt_IMAGE, //!< Use Label::Image (Label::Argument::label_image resource) to display an image. 
			TextImage = Pt_TEXT_IMAGE //!< Display the image and text of the Label. 
									  //!< You can specify the positioning of these two elements relative to each other by setting Label::BalloonPosition property.
		};
	};

	//! The type of Label underline.
	/*! 
		Apply to Label::UnderlineType property.

		@see
		- Label::UnderlineType
		- Label::Arguments::underline_type
		- Label::Arguments::underline1
		- Label::Arguments::underline2
	*/
	struct UnderlineType
	{
		//! Possible type of Label underline.
		/*!
			@see
			- Label::UnderlineType
			- Label::Arguments::underline_type
			- Label::Arguments::underline1
			- Label::Arguments::underline2
		*/
		enum eUnderlineType
		{		
			NoUline = Pt_NO_ULINE, //!< no
			DoubleUline = Pt_DOUBLE_ULINE, //!< (use with underline color)
			SingleUline = Pt_SINGLE_ULINE, //!< (use with underline color)
			UlineEtchedIn = Pt_ULINE_ETCHED_IN, //!< (use with border color)
			UlineEtchedOut = Pt_ULINE_ETCHED_OUT //!< (use with border color)
		};
	};

	namespace Drawing
	{
		//! Specifies alignment of content on the drawing surface.
		/*! 
			@see
			- Label::TextAlign
		*/
		struct ContentAlignment
		{
			#define	PHWIDGETS_VH(v,h) (((short)((v) & 0xFF) << 8) | (short)((h) & 0xFF))
			//! Possible alignment of content on the drawing surface.
			enum eContentAlignment
			{		
				BottomCenter = 	PHWIDGETS_VH(Pt_BOTTOM, Pt_CENTER), //!< Content is vertically aligned at the bottom, and horizontally aligned at the center.
				BottomLeft = 	PHWIDGETS_VH(Pt_BOTTOM, Pt_LEFT), //!< Content is vertically aligned at the bottom, and horizontally aligned on the left.
				BottomRight = 	PHWIDGETS_VH(Pt_BOTTOM, Pt_RIGHT), //!< Content is vertically aligned at the bottom, and horizontally aligned on the right.
				MiddleCenter = 	PHWIDGETS_VH(Pt_CENTER, Pt_CENTER), //!< Content is vertically aligned in the middle, and horizontally aligned at the center.
				MiddleLeft = 	PHWIDGETS_VH(Pt_CENTER, Pt_LEFT), //!< Content is vertically aligned in the middle, and horizontally aligned on the left.
				MiddleRight = 	PHWIDGETS_VH(Pt_CENTER, Pt_RIGHT), //!< Content is vertically aligned in the middle, and horizontally aligned on the right.
				TopCenter = 	PHWIDGETS_VH(Pt_TOP	  , Pt_CENTER), //!< Content is vertically aligned at the top, and horizontally aligned at the center.
				TopLeft = 		PHWIDGETS_VH(Pt_TOP	  , Pt_LEFT), //!< Content is vertically aligned at the top, and horizontally aligned on the left.
				TopRight = 		PHWIDGETS_VH(Pt_TOP	  , Pt_RIGHT)  //!< Content is vertically aligned at the top, and horizontally aligned on the right.
			};
			#undef	PHWIDGETS_VH
		};
	} // namespace Drawing

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
					accel_key = Pt_ARG_ACCEL_KEY, //!< The accelerator key to underline within the widget's text string. You typically use this resource for hotkeys.
					balloon_text = Pt_ARG_BALLOON_TEXT, //!< The text string to display in the balloon. If left blank, the Label::Text is used for balloons. 
					text_font = Pt_ARG_TEXT_FONT, //!< The font used for the label's text string. See Label::Font.
					text_string = Pt_ARG_TEXT_STRING //!< The text string to be displayed if Label::Arguments::label_type is LabelType::String or LabelType::Image, 
													 //!< as well as the text to display in the balloon if Label::Arguments::balloon_text is blank. See Label::Text.
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
					balloon_color = Pt_ARG_BALLOON_COLOR, //!< The balloon's text color. See Label::BalloonColor.
					balloon_fill_color = Pt_ARG_BALLOON_FILL_COLOR, //!< The balloon's fill color. See Label::BalloonFillColor.
					underline1 = Pt_ARG_UNDERLINE1, //!< The underline color for the first line. See Label::UnderlineColor1.
					underline2 = Pt_ARG_UNDERLINE2 //!< The underline color for the second line. See Label::UnderlineColor2.
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
					balloon_position = Pt_ARG_BALLOON_POSITION //!< Indicates where the balloon with the label's text pops up. See Label::BalloonPosition.
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
					line_spacing = Pt_ARG_LINE_SPACING, //!< The space, in pixels, between the lines of text in the label.
					margin_botton = Pt_ARG_MARGIN_BOTTOM, //!< The amount of space between the bottom of the label's canvas and the canvas defined by the Basic widget.
					margin_left = Pt_ARG_MARGIN_LEFT, //!< The amount of space between the left side of the label's canvas and the canvas defined by the Basic widget.
					margin_right = Pt_ARG_MARGIN_RIGHT, //!< The amount of space between the right side of the label's canvas and the canvas defined by the Basic widget.
					margin_top = Pt_ARG_MARGIN_TOP, //!< The amount of space between the top of the label's canvas and the canvas defined by the Basic widget.
					undeline_type = Pt_ARG_UNDERLINE_TYPE //!< The type of underline. See Label::UnderlineType.
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
					secondary_h_align = Pt_ARG_SECONDARY_H_ALIGN, //!< The horizontal alignment for the text string, if the text string is clipped. See Label::TextAlign.
					secondary_v_align = Pt_ARG_SECONDARY_V_ALIGN //!< The vertical alignment for the text string, if the text string is clipped. See Label::TextAlign.
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
					horizontal_alignment = Pt_ARG_HORIZONTAL_ALIGNMENT, //!< The horizontal alignment for the text string. See Label::TextAlign.
					vertical_alingment = Pt_ARG_VERTICAL_ALIGNMENT //!< The vertical alignment for the text string. See Label::TextAlign.
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
					label_baloon = Pt_ARG_LABEL_BALLOON //!< By default, when you pause the pointer over this widget, the widget displays a small balloon. 
														//!< If you want to change the look of the balloon, you can use this resource to override the default inflate function. 
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
			Define::Scalar<ThisArgs::ArgChar::eArgChar, char>::

		resource_type WidgetResourcesSingleton;

		std::string getText() const;
		void setText(std::string);

		Drawing::Font getFont() const;
		void setFont(Drawing::Font);

		void setBalloonPosition(PhWidgets::BalloonPosition::eBalloonPosition val);
		PhWidgets::BalloonPosition::eBalloonPosition getBalloonPosition() const;

		void setType(PhWidgets::LabelType::eLabelType val);
		PhWidgets::LabelType::eLabelType getType() const;

		void setUnderlineType(PhWidgets::UnderlineType::eUnderlineType val);
		PhWidgets::UnderlineType::eUnderlineType getUnderlineType() const;

		void setTextAlign(Drawing::ContentAlignment::eContentAlignment val);
		Drawing::ContentAlignment::eContentAlignment getTextAlign() const;

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

		//! Gets or sets the text associated with this widget.
		/*!
			### Property Value ### 
			
			> std::string

			The text associated with this widget.
			
			@see
			- Type
		*/
		property<std::string>::bind<Label, &Label::getText, &Label::setText> Text;

		//! Gets or sets the font of the text displayed by the widget.
		/*!
			### Property Value ### 
			
			> Drawing::Font

			The Drawing::Font to apply to the text displayed by the widget. The default is the value of the DefaultFont property.
			
			@remark
			The Label::Font property is an ambient property. 
			An ambient property is a widget property that, if not set, is retrieved from the parent widget. 
			For example, a Button will have the same BackColor as its parent PhWidgets::Window by default.
			@par
			Because the Label::Font is immutable (meaning that you cannot adjust any of its properties), 
			you can only assign the Label::Font property a new Drawing::Font. However, you can base the new font on the existing font. 

			@see
			- FontChanged
			- OnFontChanged(PtCallbackInfo_t*)
			- Drawing::Font
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

		//! Gets or sets the balloon fill color of the Label.
		/*!
			### Property Value ### 
			
			> Drawing::Color

			A `Drawing::Color` that represents the balloon fill color of the Label.

			@see
			- Drawing::Colors
			- Drawing::Color
		*/
		phproperty<Drawing::Color>::bind<Label, ArgColor::eArgColor, Arguments::balloon_fill_color> BalloonFillColor;

		//! Gets or sets where the balloon with the label's text pops up.
		/*!
			### Property Value ### 
			
			> BalloonPosition::eBalloonPosition

			Possible values are:
			- BalloonPosition::Inplace
			- BalloonPosition::Top
			- BalloonPosition::Left
			- BalloonPosition::Right
			- BalloonPosition::Bottom

			@remark
			If Label::Type is LabelType::TextImage, this resource also controls the positioning of the text and image elements relative to each other.

			@see
			- BalloonPosition::eBalloonPosition
			- Type
			- LabelType
		*/
		property<PhWidgets::BalloonPosition::eBalloonPosition>::
			bind<Label, &Label::getBalloonPosition, &Label::setBalloonPosition> BalloonPosition;

		//! Gets or sets the alignment of text in the label.
		/*!
			### Property Value ### 
			
			> Drawing::ContentAlignment

			@remark
			You can use this property to align the text within a label to match the layout of widgets on your form.
			For example, if your widgets are located to the right edge of the labels, 
			you can set the Label::TextAlign property to one of the right-aligned horizontal alignments 
			(Drawing::ContentAlignment::TopRight, Drawing::ContentAlignment::MiddleRight, Drawing::ContentAlignment::BottomRight) 
			and the text will be aligned with the right edge of the labels to align with your widgets.
			
			@see
			- Drawing::ContentAlignment::eContentAlignment
			- Type
			- LabelType
		*/
		property<Drawing::ContentAlignment::eContentAlignment>::
			bind<Label, &Label::getTextAlign, &Label::setTextAlign> TextAlign;

		//! Gets or sets the type of information displayed by the Label.
		/*!
			### Property Value ### 
			
			> LabelType::eLabelType

			Possible values are:
			- LabelType::String
			- LabelType::Image
			- LabelType::TextImage

			@see
			- BalloonPosition
			- LabelType
		*/
		property<PhWidgets::LabelType::eLabelType>::
			bind<Label, &Label::getType, &Label::setType> Type;

		//! Gets or sets the underline color for the first line of the Label.
		/*!
			### Property Value ### 
			
			> Drawing::Color

			A `Drawing::Color` that represents the underline color for the first line of the Label.

			@see
			- UnderlineType
			- Drawing::Colors
			- Drawing::Color
			- UnderlineColor2
		*/
		phproperty<Drawing::Color>::bind<Label, ArgColor::eArgColor, Arguments::underline1> UnderlineColor1;

		//! Gets or sets the underline color for the second line of the Label.
		/*!
			### Property Value ### 
			
			> Drawing::Color

			A `Drawing::Color` that represents the underline color for the second line of the Label.

			@see
			- UnderlineType
			- Drawing::Colors
			- Drawing::Color
			- UnderlineColor1
		*/
		phproperty<Drawing::Color>::bind<Label, ArgColor::eArgColor, Arguments::underline2> UnderlineColor2;

		//! Gets or sets the type of underline.
		/*!
			### Property Value ### 
			
			> UnderlineType::eUnderlineType

			Possible values are:
			- UnderlineType::NoUline
			- UnderlineType::DoubleUline
			- UnderlineType::SingleUline
			- UnderlineType::UlineEtchedIn
			- UnderlineType::UlineEtchedOut

			@see
			- UnderlineColor1
			- UnderlineColor2
		*/
		property<PhWidgets::UnderlineType::eUnderlineType>::
			bind<Label, &Label::getUnderlineType, &Label::setUnderlineType> UnderlineType;
		//@}
	};

} // namespace PhWidgets


#endif // PHWIDGETS_LABEL_H
