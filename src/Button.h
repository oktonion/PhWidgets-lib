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
			using ThisArgs::ArgColor::eArgColor;
		};
		
		struct ArgUnsignedChar:
			public ArgumentsEx<Label::ArgUnsignedChar>,
			public ThisArgs::ArgUnsignedChar
		{
			using ThisArgs::ArgUnsignedChar::eArgUnsignedChar;
		};
		
		struct ArgPImage:
			public ArgumentsEx<Label::ArgPImage>,
			public ThisArgs::ArgPImage
		{
			using ThisArgs::ArgPImage::eArgPImage;
		};



		struct Arguments:
			public ArgColor,
			public ArgUnsignedChar,
			public ArgPImage,
			public Label::Arguments
		{			
		};
	
	protected:
		typedef ResourceFrom<Label::WidgetResourcesSingleton>::
			//Define::Image<ArgPImage::eArgPImage>:: // not implemented
			Define::Color<ArgColor::eArgColor>::
			Define::Scalar<ArgUnsignedChar::eArgUnsignedChar, unsigned char>::

		resource_type WidgetResourcesSingleton;

		virtual void check();

		void setArmColor(PgColor_t);
		PgColor_t getArmColor() const;

						
	public:
		WidgetResourcesSingleton resource;

		Button(int abn);
		Button(PtWidget_t *wdg);

		Button(const Button &rhs);

		Button &operator=(const Button &rhs);

		property<PgColor_t>::bind<Button, &Button::getArmColor, &Button::setArmColor> ArmColor;
	};

}


#endif
