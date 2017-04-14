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
		};

			

		struct ArgColor:
			public ArgumentsEx<Button::ArgColor>,
			public ThisArgs::ArgColor
		{
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
		virtual void check();

						
	public:
		ToggleButton(int abn);
		ToggleButton(PtWidget_t *wdg);
		
		ToggleButton(const ToggleButton&);
		
		void Check(bool val);
		void Uncheck(bool val);
				
		property<bool>::bind<ToggleButton, &ToggleButton::getChecked, &ToggleButton::setChecked> Checked;
	};
	

	INIT_WIDGET_RESOURCE1(ToggleButton::ThisArgs::ArgColor::eArgColor, PgColor_t, Color);
	
	INIT_WIDGET_RESOURCE1(ToggleButton::ThisArgs::ArgUnsignedChar::eArgUnsignedChar, unsigned char, Scalar);
	
}


#endif
