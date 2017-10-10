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
			using ThisArgs::ArgUnsignedChar::eArgUnsignedChar;
		};

			

		struct ArgColor:
			public ArgumentsEx<Button::ArgColor>,
			public ThisArgs::ArgColor
		{
			using ThisArgs::ArgColor::eArgColor;
		};

		struct Arguments:
			public ArgColor,
			public ArgUnsignedChar,
			public Button::Arguments
		{
		};
		
		void setChecked(bool val);
		bool getChecked() const;
	
	protected:
		typedef ResourceFrom<Button::WidgetResourcesSingleton>::
			Define::Scalar<ThisArgs::ArgUnsignedChar::eArgUnsignedChar, unsigned char>::
			Define::Color<ThisArgs::ArgColor::eArgColor>::

		resource_type WidgetResourcesSingleton;

		virtual void check();

						
	public:
		WidgetResourcesSingleton resource;

		ToggleButton(int abn);
		ToggleButton(PtWidget_t *wdg);
		
		ToggleButton(const ToggleButton&);

		ToggleButton &operator=(const ToggleButton &rhs);
		
		void Check(bool val);
		void Uncheck(bool val);
				
		property<bool>::bind<ToggleButton, &ToggleButton::getChecked, &ToggleButton::setChecked> Checked;
	};
	
}


#endif
