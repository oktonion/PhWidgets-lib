#ifndef PHWIDGETS_TOGGLE_BUTTON_H
#define PHWIDGETS_TOGGLE_BUTTON_H

#include <photon/PtToggleButton.h>

#include "./Button.h"


namespace PhWidgets
{
	//! Specifies how the indicator of ToggleButton is drawn.
	/*! 
		Apply to ToggleButton::IndicatorType property.

		@see
    	- ToggleButton::IndicatorType
		- ToggleButton::Arguments::indicator_type

		@ingroup Values
	*/
	struct ToggleIndicatorType
	{
		//! Toggle indicator types for ToggleButton resource ToggleButton::Arguments::indicator_type.
		/*!
			Determines how the indicator of ToggleButton is drawn.
		*/
		enum eToggleIndicatorType
		{
			Radio = Pt_TOGGLE_RADIO, //!< *
			Check = Pt_TOGGLE_CHECK, //!< **[x]**
			Outline = Pt_TOGGLE_OUTLINE //!< I>
		};
	};

	/*!
		@struct PhWidgets::ToggleButton
		@ingroup Widgets
	*/

	//! A toggle switch that's either off or on
	/*!
		A ToggleButton widget is like a toggle switch, although it behaves like a button. 
		It has on and off states, and pressing the button inverts the current state of the button.
	*/		
	class ToggleButton:
		public Button
	{
	public:

		//! Contains resource IDs for ToggleButton arguments. @ingroup Resources
		struct ThisArgs
		{
			//! Contains resource IDs for ToggleButton arguments of type **unsigned char**.
			struct ArgUnsignedChar
			{				
				//! Resource IDs for ToggleButton arguments of type **unsigned char**.

				/*!
					### Aliases ###
					
					PhWidgets::ToggleButton::Arguments::eArgUnsignedChar,
					PhWidgets::ToggleButton::ArgUnsignedChar::eArgUnsignedChar

					See Widget::resource for usage description.
				*/
				enum eArgUnsignedChar
				{
					indicator_type = Pt_ARG_INDICATOR_TYPE 	//!< Determines how the indicator is drawn. 
															//!< Possible values are ToggleIndicatorType::Radio, ToggleIndicatorType::Check, ToggleIndicatorType::Outline.
				};
			};	
			
			//! Contains resource IDs for ToggleButton arguments of type `PgColor_t`.
			struct ArgColor
			{
				//! Resource IDs for ToggleButton arguments of type `PgColor_t`.

				/*!
					### Aliases ###
					
					PhWidgets::ToggleButton::Arguments::eArgColor,
					PhWidgets::ToggleButton::ArgColor::eArgColor

					See Widget::resource for usage description.
				*/
				enum eArgColor
				{
					indicator_color = Pt_ARG_INDICATOR_COLOR //!< The fill color for the toggle button's indicator.
				};
			};

		};

		//! Contains resource IDs for arguments of type **unsigned char**.
		struct ArgUnsignedChar:
			public ArgumentsEx<Button::ArgUnsignedChar>,
			public ThisArgs::ArgUnsignedChar
		{
			typedef ThisArgs::ArgUnsignedChar::eArgUnsignedChar eArgUnsignedChar;
		};

		//! Contains resource IDs for arguments of type `PgColor_t`.
		struct ArgColor:
			public ArgumentsEx<Button::ArgColor>,
			public ThisArgs::ArgColor
		{
			typedef ThisArgs::ArgColor::eArgColor eArgColor;
		};

		//! Contains resource IDs for all ToggleButton arguments.
		struct Arguments:
			public ArgColor,
			public ArgUnsignedChar,
			public Button::Arguments
        { };
	
	protected:
		typedef ResourceFrom<Button::WidgetResourcesSingleton>::
			Define::Scalar<ThisArgs::ArgUnsignedChar::eArgUnsignedChar, unsigned char>::
			Define::Color<ThisArgs::ArgColor::eArgColor>::

		resource_type WidgetResourcesSingleton;

		virtual void check();

		void setChecked(bool val);
		bool getChecked() const;

		void setIndicatorType(ToggleIndicatorType::eToggleIndicatorType val);
		ToggleIndicatorType::eToggleIndicatorType getIndicatorType() const;
						
	public:
		//! (constructor) 
		/*!
			Constructs a ToggleButton by ID.
			@param[in] abn ID given by PhAB to widget (like 'ABN_WIDGET_NAME').
		*/
		explicit ToggleButton(int abn);

		//! (constructor) 
		/*!
			Constructs a ToggleButton by pointer to widget.
			@param[in] wdg pointer to Photon widget.
		*/
		explicit ToggleButton(PtWidget_t *wdg);
		
		//! (copy constructor) 
		/*!
			Constructs a ToggleButton by copy.
			@param[in] other another ToggleButton to be used as source to initialize the elements of the container with.
		*/
		ToggleButton(const ToggleButton &other);

		//! Assigns value in ToggleButton 
		/*!
			Replaces the contents of the ToggleButton.
			@param[in] other another ToggleButton to use as data source.
		*/
		ToggleButton &operator=(const ToggleButton &other);

		//! Resources of the ToggleButton
		/*!
			@see
			- Widget::resource
		*/
		WidgetResourcesSingleton resource;

		//! @name Properties
		//! Properties are used to simplify use of widget resources.
		//@{		

		//! Gets or sets whether the ToggleButton is checked.
		/*!
			### Property Value ### 
			
			> **bool**

			`true` if the ToggleButton is checked; `false` if the ToggleButton is unchecked; The default is `false`.

			@see
			- IndicatorType
		*/
		property<bool>::bind<ToggleButton, &ToggleButton::getChecked, &ToggleButton::setChecked> IsChecked;

		//! Gets or sets the type for the toggle button's indicator.
		/*!
			### Property Value ### 
			
			> ToggleIndicatorType::eToggleIndicatorType

			Determines how the indicator is drawn.

			Possible values are:
			- ToggleIndicatorType::Radio 
			- ToggleIndicatorType::Check 
			- ToggleIndicatorType::Outline

			### Examples ###

			@code
				using PhWidgets::ToggleButton;
				using PhWidgets::ToggleIndicatorType;

				ToggleButton tgbutton(ABN_MYTOGGLE_BUTTON);

				tgbutton.IndicatorType = ToggleIndicatorType::Check;
				tgbutton.IsChecked = true;
			@endcode
		*/
		property<ToggleIndicatorType::eToggleIndicatorType>::
			bind<ToggleButton, &ToggleButton::getIndicatorType, &ToggleButton::setIndicatorType> IndicatorType;

		//! Gets or sets the fill color for the toggle button's indicator.
		/*!
			### Property Value ### 
			
			> Drawing::Color

			The `Drawing::Color` of the toggle button's indicator.

			### Examples ###

			@code
				using namespace PhWidgets;

				ToggleButton tgbutton(ABN_MYTOGGLE_BUTTON);

				tgbutton.IndicatorColor = Drawing::Color::FromARGB(200, 23, 23);
				tgbutton.IndicatorType = ToggleIndicatorType::Radio;
			@endcode

			@see
			- Drawing::Colors
			- ToggleIndicatorType
		*/
		phproperty<Drawing::Color>::bind<ToggleButton, ThisArgs::ArgColor::eArgColor, Arguments::indicator_color> IndicatorColor;
		//@}
	};
	
} // namespace PhWidgets


#endif // PHWIDGETS_TOGGLE_BUTTON_H
