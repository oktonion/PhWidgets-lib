#ifndef PT_TOGGLE_BUTTON_H
#define PT_TOGGLE_BUTTON_H

#include <photon/PtToggleButton.h>

#include "./Button.h"


namespace PhWidgets
{
		
	class ToggleButton:
		public Button
	{
	public:

		struct ThisArgs
		{
												
			struct ArgUnsignedChar
			{
				enum eArgUnsignedChar
				{
					indicator_type = Pt_ARG_INDICATOR_TYPE
				};
			};	
			
			struct ArgColor
			{
				enum eArgColor
				{
					indicator_color = Pt_ARG_INDICATOR_COLOR
				};
			};

		};

			
		struct ArgUnsignedChar:
			public ArgumentsEx<Button::ArgUnsignedChar>,
			public ThisArgs::ArgUnsignedChar
		{
			typedef ThisArgs::ArgUnsignedChar::eArgUnsignedChar eArgUnsignedChar;
		};

			

		struct ArgColor:
			public ArgumentsEx<Button::ArgColor>,
			public ThisArgs::ArgColor
		{
			typedef ThisArgs::ArgColor::eArgColor eArgColor;
		};

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
				
		property<bool>::bind<ToggleButton, &ToggleButton::getChecked, &ToggleButton::setChecked> Checked;
	};
	
}


#endif
