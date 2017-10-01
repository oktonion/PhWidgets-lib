#ifndef PT_LABEL_H
#define PT_LABEL_H

#include <photon/PtLabel.h>

#include <string>

#include "./Basic.h"


namespace PhWidgets
{
	
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
		};	
			
		struct ArgColor:
			public ArgumentsEx<Basic::ArgColor>,
			public ThisArgs::ArgColor
		{
		};

		struct ArgShort:
			public ThisArgs::ArgShort
		{
		};	

		struct ArgUnsignedShort:
			public ArgumentsEx<Basic::ArgUnsignedShort>,
			public ThisArgs::ArgUnsignedShort
		{
		};	

		struct ArgSignedShort:
			public ThisArgs::ArgSignedShort
		{
		};	

		struct ArgUnsignedChar:
			public ArgumentsEx<Basic::ArgUnsignedChar>,
			public ThisArgs::ArgUnsignedChar
		{
		};

		struct ArgPWidget:
			public ThisArgs::ArgPWidget
		{
		};	

		struct ArgChar:
			public ArgumentsEx<Basic::ArgChar>,
			public ThisArgs::ArgChar
		{
		};	

		struct ArgPImage:
			public ThisArgs::ArgPImage
		{
		};	

		struct ArgInt:
			public ThisArgs::ArgInt
		{
		};	



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
		std::string getCaption() const;
		void setCaption(std::string caption);

		void setBalloonColor(PgColor_t);
		PgColor_t getBalloonColor() const;

		virtual void check();
						
	public:
		Label(int abn);
		Label(PtWidget_t *wdg);
		
		Label(const Label&);

		Label &operator=(const Label &rhs);
		
		property<std::string>::bind<Label, &Label::getCaption, &Label::setCaption> Caption;
		property<PgColor_t>::bind<Label, &Label::getBalloonColor, &Label::setBalloonColor> BalloonColor;
	};
	
	//TODO:: add more macro for all resources:
	
	DEFINE_OPERATOR0(Label::ThisArgs::ArgPChar::eArgPChar, String);

	DEFINE_OPERATOR1(Label::ThisArgs::ArgColor::eArgColor, PgColor_t, Color);
	DEFINE_OPERATOR1(Label::ThisArgs::ArgUnsignedShort::eArgUnsignedShort, unsigned short, Scalar);
	DEFINE_OPERATOR1(Label::ThisArgs::ArgShort::eArgShort, short, Scalar);
	DEFINE_OPERATOR1(Label::ThisArgs::ArgSignedShort::eArgSignedShort, signed short, Scalar);
	DEFINE_OPERATOR1(Label::ThisArgs::ArgUnsignedChar::eArgUnsignedChar, unsigned char, Scalar);

}


#endif
