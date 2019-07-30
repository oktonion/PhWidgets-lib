#ifndef PHWIDGETS_BUTTON_H
#define PHWIDGETS_BUTTON_H

#include <photon/PtButton.h>

#include "./Label.h"


namespace PhWidgets
{
	/*!
		@struct PhWidgets::Button
		@ingroup Widgets
	*/

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

		//! Contains resource IDs for Button arguments. @ingroup Resources
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
					arm_color = Pt_ARG_ARM_COLOR //!< The background color used when the button is armed (pressed in).
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
					arm_fill = Pt_ARG_ARM_FILL //!< Determines whether or not to use Arguments::arm_color as the background color when the button is armed (pressed in).
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
					arm_image = Pt_ARG_ARM_IMAGE  //!< A pointer to a PhImage_t structure
												  //!< that defines the image to use when the button is armed. 
												  //!< It's used only if the label type (Label::Type) is LabelType::Image or LabelType::TextImage.
				};
			};
			
		};

		//! Contains resource IDs for arguments of type `PgColor_t`. @ingroup Resources
		struct ArgColor:
			public ArgumentsEx<Label::ArgColor>,
			public ThisArgs::ArgColor
		{
			typedef ThisArgs::ArgColor::eArgColor eArgColor;
		};
		
		//! Contains resource IDs for arguments of type **unsigned char**. @ingroup Resources
		struct ArgUnsignedChar:
			public ArgumentsEx<Label::ArgUnsignedChar>,
			public ThisArgs::ArgUnsignedChar
		{
			typedef ThisArgs::ArgUnsignedChar::eArgUnsignedChar eArgUnsignedChar;
		};
		
		//! Contains resource IDs for arguments of type `PhImage_t`. @ingroup Resources
		struct ArgPImage:
			public ArgumentsEx<Label::ArgPImage>,
			public ThisArgs::ArgPImage
		{
			typedef ThisArgs::ArgPImage::eArgPImage eArgPImage;
		};

		//! Contains resource IDs for all Button arguments. @ingroup Resources
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
		//! Resources of the Button
		/*!
			@see
			- Widget::resource
		*/
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

		//! @name Properties
		//! Properties are used to simplify use of widget resources.
		//@{

		//! Gets or sets the color of the widget when the Button is armed (pressed in).
		/*!
			### Property Value ### 
			
			> Drawing::Color

			A `Drawing::Color` that represents the arm color of the widget.

			@remark
			Color will change only if Button::ArmFill property is set to `true`.

			@see
			- ArmFill
			- Drawing::Colors
			- Drawing::Color
		*/
		phproperty<Drawing::Color>::bind<Button, ArgColor::eArgColor, Arguments::arm_color> ArmColor;

		//! Determines whether or not to use Button::ArmColor as the background color when the Button is armed (pressed in).
		/*!
			### Property Value ### 
			
			> **bool**

			`true` if the Button::ArmColor is used; `false` if the Button::ArmColor is not used.

			@see
			- ArmColor
		*/
		phproperty<bool>::bind<Button, ArgUnsignedChar::eArgUnsignedChar, Arguments::arm_fill> ArmFill;

		//@}
	};

} // namespace PhWidgets


#endif // PHWIDGETS_BUTTON_H
