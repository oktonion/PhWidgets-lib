#ifndef PT_ONOFF_BUTTON_H
#define PT_ONOFF_BUTTON_H

#include <photon/PtOnOffButton.h>

#include "./Button.h"


namespace PhWidgets
{
		
	class OnOffButton:
		public Button
	{
	public:
	
		struct ThisArgs
		{
			struct ArgBool
			{
				enum eArgBool
				{
					onoff_state = Pt_ARG_ONOFF_STATE
				};
			};
		};
		
		struct ArgBool:
			public ThisArgs::ArgBool
		{
		};


		struct Arguments:
			public Button::Arguments,
			public ArgBool
		{
		};
		
	protected:
		virtual void check();
		
		void setChecked(bool val);
		bool getChecked() const;

						
	public:
		OnOffButton(int abn);
		OnOffButton(PtWidget_t* wdg);
		
		OnOffButton(const OnOffButton&);
		
		void Check(bool val);
		void Uncheck(bool val);
		
		property<bool>::bind<OnOffButton, &OnOffButton::getChecked, &OnOffButton::setChecked> Checked;
	};
	
	
	
	INIT_WIDGET_RESOURCE1(OnOffButton::ThisArgs::ArgBool::eArgBool, bool, Scalar);

}


#endif
