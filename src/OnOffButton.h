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
        { };

		struct Callback :
			public ArgumentsEx<ThisCallbacks::Callback>,
			public Button::Callback
		{
			typedef ThisCallbacks::Callback::eCallback eCallback;
		};


		struct Arguments:
			public Button::Arguments,
			public ArgBool
        { };

		struct Callbacks :
			public Callback,
			public Button::Callbacks
        { };
		
	protected:
		typedef ResourceFrom<Button::WidgetResourcesSingleton>::
			Define::Scalar<ThisArgs::ArgBool::eArgBool, bool>::

			Define::Link<ThisCallbacks::Callback::eCallback, PtCallback_t*>::

		resource_type WidgetResourcesSingleton;

		virtual void check();
						
	public:
		WidgetResourcesSingleton resource;

		OnOffButton(int abn);
		OnOffButton(PtWidget_t* wdg);
		
		OnOffButton(const OnOffButton&);

		OnOffButton &operator=(const OnOffButton &rhs);
		
		void Check(bool val = true);
		void Uncheck(bool val = true);
		
		phproperty<bool>::bind<OnOffButton, ArgBool::eArgBool, Arguments::onoff_state> Checked;

		phwidgets_event<OnOffButton, OnOffButton::Callbacks::new_value>		NewValue;
	};

}


#endif
