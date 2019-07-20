#ifndef PHWIDGETS_BUTTON_H
#define PHWIDGETS_BUTTON_H

#include <photon/PtButton.h>

#include "./Label.h"


namespace PhWidgets
{
	//! A button for initiating an action
	/*!
		The Button class draws a button. 
		Buttons let you initiate an action within your application; 
		clicking a button invokes an application callback. 
	*/			
	class Button:
		public Label
	{
		
	public:

		//! Contains resource IDs for Button arguments.
		struct ThisArgs
		{
			//! Contains resource IDs for Button arguments of type `PgColor_t`.
			struct ArgColor
			{
				//! Resource IDs for Button arguments of type `PgColor_t`.

				/*!
					### Aliases ###
					
					PhWidgets::Button::Arguments::eArgColor,
					PhWidgets::Button::ArgColor::eArgColor

					See Widget::resource for usage description.
				*/
				enum eArgColor
				{
					arm_color = Pt_ARG_ARM_COLOR
				};
			};
			
			//! Contains resource IDs for Button arguments of type **unsigned char**.
			struct ArgUnsignedChar
			{
				//! Resource IDs for Button arguments of type **unsigned char**.

				/*!
					### Aliases ###
					
					PhWidgets::Button::Arguments::eArgUnsignedChar,
					PhWidgets::Button::ArgUnsignedChar::eArgUnsignedChar

					See Widget::resource for usage description.
				*/
				enum eArgUnsignedChar
				{
					arm_fill = Pt_ARG_ARM_FILL
				};
			};
			
			//! Contains resource IDs for Button arguments of type `PhImage_t`.
			struct ArgPImage
			{
				//! Resource IDs for Button arguments of type `PhImage_t`.

				/*!
					### Aliases ###
					
					PhWidgets::Button::Arguments::eArgPImage,
					PhWidgets::Button::ArgPImage::eArgPImage

					See Widget::resource for usage description.
				*/
				enum eArgPImage
				{
					arm_image = Pt_ARG_ARM_IMAGE
				};
			};
			
		};

		//! Contains resource IDs for arguments of type `PgColor_t`.
		struct ArgColor:
			public ArgumentsEx<Label::ArgColor>,
			public ThisArgs::ArgColor
		{
			typedef ThisArgs::ArgColor::eArgColor eArgColor;
		};
		
		//! Contains resource IDs for arguments of type **unsigned char**.
		struct ArgUnsignedChar:
			public ArgumentsEx<Label::ArgUnsignedChar>,
			public ThisArgs::ArgUnsignedChar
		{
			typedef ThisArgs::ArgUnsignedChar::eArgUnsignedChar eArgUnsignedChar;
		};
		
		//! Contains resource IDs for arguments of type `PhImage_t`.
		struct ArgPImage:
			public ArgumentsEx<Label::ArgPImage>,
			public ThisArgs::ArgPImage
		{
			typedef ThisArgs::ArgPImage::eArgPImage eArgPImage;
		};

		//! Contains resource IDs for all Button arguments.
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
			Define::Color<ThisArgs::ArgColor::eArgColor>::
			Define::Scalar<ThisArgs::ArgUnsignedChar::eArgUnsignedChar, unsigned char>::

		resource_type WidgetResourcesSingleton;

		virtual void check();

						
	public:
		WidgetResourcesSingleton resource;

		//! (constructor) 
		/*!
			Constructs a Button widget by ID.
			@param[in] abn ID given by PhAB to widget (like 'ABN_WIDGET_NAME').
		*/
		Button(int abn);

		//! (constructor) 
		/*!
			Constructs a Button widget by pointer to widget.
			@param[in] wdg pointer to Photon widget.
		*/
		Button(PtWidget_t *wdg);

		//! (copy constructor) 
		/*!
			Constructs a Button widget by copy.
			@param[in] other another Button widget to be used as source to initialize the elements of the container with.
		*/
		Button(const Button &other);

		//! Assigns value in Button widget 
		/*!
			Replaces the contents of the Button widget.
			@param[in] other another Button widget to use as data source.
		*/
		Button &operator=(const Button &other);

		phproperty<PgColor_t>::bind<Button, ArgColor::eArgColor, Arguments::arm_color> ArmColor;
	};

} // namespace PhWidgets


#endif // PHWIDGETS_BUTTON_H
