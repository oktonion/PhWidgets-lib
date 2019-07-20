#ifndef PHWIDGETS_TEXT_H
#define PHWIDGETS_TEXT_H

#include <photon/PtText.h>

#include <string>

#include "./Label.h"


namespace PhWidgets
{
	//! Single-line text
	/*!
		The Photon text widgets let you type textual information into a text-entry box. 
		The widgets provide basic editing features, so you can alter text that's entered. 
		They also support a point-and-click model of editing, so that you can operate on blocks of text as a unit.  
	*/	
	class Text:
		public Label
	{
	public:

		struct ThisArgs
		{												
			struct ArgComplex
			{
				enum eArgComplex
				{
					text_substring = Pt_ARG_TEXT_SUBSTRING
				};
			};

		};

		struct ThisCallbacks
		{
			struct Callback
			{
				enum eCallback
				{
					modify_notify = Pt_CB_MODIFY_NOTIFY,
					modify_verify = Pt_CB_MODIFY_VERIFY,
					motion_notify = Pt_CB_MOTION_NOTIFY,
					motion_verify = Pt_CB_MOTION_VERIFY,
					text_changed = Pt_CB_TEXT_CHANGED
				};
			};
		};
		
		struct ArgComplex:
			public ThisArgs::ArgComplex
        { };

		struct Callback :
			public ArgumentsEx<ThisCallbacks::Callback>,
			public Label::Callback
		{
			typedef ThisCallbacks::Callback::eCallback eCallback;
		};

		
		struct Arguments:
			public ArgComplex,
			public Label::Arguments
        { };

		struct Callbacks :
			public Callback,
			public Label::Callbacks
        { };
		
	protected:
		typedef ResourceFrom<Label::WidgetResourcesSingleton>::
			Define::Struct<ThisArgs::ArgComplex::eArgComplex, PtTextControl_t>::

			Define::Link<ThisCallbacks::Callback::eCallback, PtCallback_t*>::

		resource_type WidgetResourcesSingleton;

		virtual void check();
						
	public:
		WidgetResourcesSingleton resource;

		Text(int abn);
		Text(PtWidget_t *wdg);

		Text(const Text &rhs);

		Text &operator=(const Text &rhs);

		phwidgets_event<Text, Text::Callbacks::modify_notify>	ModifyNotify;
		phwidgets_event<Text, Text::Callbacks::modify_verify>	ModifyVerify;
		phwidgets_event<Text, Text::Callbacks::motion_notify>	MotionNotify;
		phwidgets_event<Text, Text::Callbacks::motion_verify>	MotionVerify;
		phwidgets_event<Text, Text::Callbacks::text_changed> 	TextChanged;
	};
	
}  // namespace PhWidgets


#endif // PHWIDGETS_TEXT_H
