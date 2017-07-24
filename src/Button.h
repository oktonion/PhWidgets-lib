#ifndef PT_BUTTON_H
#define PT_BUTTON_H

#include <photon/PtButton.h>

#include "./Label.h"


namespace PhWidgets
{
		
	class Button:
		public Label
	{
		
	public:
		struct ThisArgs
		{
			struct ArgColor
			{
				enum eArgColor
				{
					arm_color = Pt_ARG_ARM_COLOR
				};
			};
			
			struct ArgUnsignedChar
			{
				enum eArgUnsignedChar
				{
					arm_fill = Pt_ARG_ARM_FILL
				};
			};
			
			struct ArgPImage
			{
				enum eArgPImage
				{
					arm_image = Pt_ARG_ARM_IMAGE
				};
			};
			
		};
		
		struct ArgColor:
			public ArgumentsEx<Label::ArgColor>,
			public ThisArgs::ArgColor
		{
		};
		
		struct ArgUnsignedChar:
			public ArgumentsEx<Label::ArgUnsignedChar>,
			public ThisArgs::ArgUnsignedChar
		{
		};
		
		struct ArgPImage:
			public ArgumentsEx<Label::ArgPImage>,
			public ThisArgs::ArgPImage
		{
		};



		struct Arguments:
			public ArgColor,
			public ArgUnsignedChar,
			public ArgPImage,
			public Label::Arguments
		{			
		};
	
	protected:
		virtual void check();

		void setArmColor(PgColor_t);
		PgColor_t getArmColor() const;

						
	public:
		Button(int abn);
		Button(PtWidget_t *wdg);

		Button(const Button &rhs);

		Button &operator=(const Button &rhs);

		property<PgColor_t>::bind<Button, &Button::getArmColor, &Button::setArmColor> ArmColor;
	};
	
	
	INIT_WIDGET_RESOURCE0(Button::ThisArgs::ArgPImage::eArgPImage, Image);
	
	INIT_WIDGET_RESOURCE1(Button::ThisArgs::ArgColor::eArgColor, PgColor_t, Color);
	INIT_WIDGET_RESOURCE1(Button::ThisArgs::ArgUnsignedChar::eArgUnsignedChar, unsigned char, Scalar);

}


#endif
