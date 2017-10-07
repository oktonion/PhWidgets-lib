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

		struct ThisCallbacks
		{
			struct Callback
			{
				enum eCallback
				{
					new_value = Pt_CB_ONOFF_NEW_VALUE
				};
			};
		};
		
		struct ArgBool:
			public ThisArgs::ArgBool
		{
		};

		struct Callback :
			public ArgumentsEx<ThisCallbacks::Callback>,
			public Button::Callback
		{
			using ThisCallbacks::Callback::eCallback;
		};


		struct Arguments:
			public Button::Arguments,
			public ArgBool
		{
		};

		struct Callbacks :
			public Callback,
			public Button::Callbacks
		{
		};
		
	protected:
		typedef ResourceFrom<Button::WidgetResourcesSingleton>::
			Define::Scalar<ArgBool::eArgBool, bool>::

			Define::Link<Callback::eCallback, PtCallback_t*>::

		resource_type WidgetResourcesSingleton;

		virtual void check();
		
		void setChecked(bool val);
		bool getChecked() const;
						
	public:
		WidgetResourcesSingleton resource;

		OnOffButton(int abn);
		OnOffButton(PtWidget_t* wdg);
		
		OnOffButton(const OnOffButton&);

		OnOffButton &operator=(const OnOffButton &rhs);
		
		void Check(bool val);
		void Uncheck(bool val);
		
		property<bool>::bind<OnOffButton, &OnOffButton::getChecked, &OnOffButton::setChecked> Checked;

		phwidgets_event<OnOffButton, OnOffButton::Callbacks::new_value>		NewValue;
	};

}


#endif
