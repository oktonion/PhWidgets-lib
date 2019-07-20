#ifndef PHWIDGETS_TOGGLE_BUTTON_H
#define PHWIDGETS_TOGGLE_BUTTON_H

#include <photon/PtToggleButton.h>

#include "./Button.h"


namespace PhWidgets
{
	//! A toggle switch that's either off or on
	/*!
		A ToggleButton widget is like a toggle switch, although it behaves like a button. 
		It has on and off states, and pressing the button inverts the current state of the button. 
	*/		
	class ToggleButton:
		public Button
	{
	public:

		//! Contains resource IDs for ToggleButton arguments.
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
					indicator_type = Pt_ARG_INDICATOR_TYPE
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
					indicator_color = Pt_ARG_INDICATOR_COLOR
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
		
		void setChecked(bool val);
		bool getChecked() const;
	
	protected:
		typedef ResourceFrom<Button::WidgetResourcesSingleton>::
			Define::Scalar<ThisArgs::ArgUnsignedChar::eArgUnsignedChar, unsigned char>::
			Define::Color<ThisArgs::ArgColor::eArgColor>::

		resource_type WidgetResourcesSingleton;

		virtual void check();

						
	public:
		//! (constructor) 
		/*!
			Constructs a ToggleButton by ID.
			@param[in] abn ID given by PhAB to widget (like 'ABN_WIDGET_NAME').
		*/
		ToggleButton(int abn);

		//! (constructor) 
		/*!
			Constructs a ToggleButton by pointer to widget.
			@param[in] wdg pointer to Photon widget.
		*/
		ToggleButton(PtWidget_t *wdg);
		
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
		
		void Check(bool val = true);
		void Uncheck(bool val = true);

		//! @name Properties
		//! Properties are used to simplify use of widget resources.
		//@{		
		property<bool>::bind<ToggleButton, &ToggleButton::getChecked, &ToggleButton::setChecked> Checked;
		//@}
	};
	
} // namespace PhWidgets


#endif // PHWIDGETS_TOGGLE_BUTTON_H
