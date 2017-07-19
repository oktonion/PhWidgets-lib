#ifndef PT_TEXT_H
#define PT_TEXT_H

#include <photon/PtText.h>

#include <string>

#include "./Label.h"


namespace PhWidgets
{
		
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
		{
		};

		struct Callback :
			public ArgumentsEx<ThisCallbacks::Callback>,
			public Label::Callback
		{
		};

		
		struct Arguments:
			public ArgComplex,
			public Label::Arguments
		{
		};

		struct Callbacks :
			public Callback,
			public Label::Callbacks
		{
		};
		
	protected:
		virtual void check();

		template<ThisCallbacks::Callback::eCallback ID>
		void addCallback(callback_t callback);
						
	public:
		Text(int abn);
		Text(PtWidget_t *wdg);

		Text(const Text &rhs);

		phevent::bind<Text, &Text::addCallback<Callbacks::modify_notify> >		ModifyNotify;
		phevent::bind<Text, &Text::addCallback<Callbacks::modify_verify> >		ModifyVerify;
		phevent::bind<Text, &Text::addCallback<Callbacks::motion_notify> >		MotionNotify;
		phevent::bind<Text, &Text::addCallback<Callbacks::motion_verify> >		MotionVerify;
		phevent::bind<Text, &Text::addCallback<Callbacks::text_changed> >		TextChanged;
	};
	
	INIT_WIDGET_RESOURCE1(Text::ThisArgs::ArgComplex::eArgComplex, PtTextControl_t, Struct);
	INIT_WIDGET_RESOURCE1(Text::ThisCallbacks::Callback::eCallback, PtCallback_t, Link);


	template<Text::ThisCallbacks::Callback::eCallback ID>
	inline void Text::addCallback(callback_t callback)
	{
		resource.callback[ID].add(callback);
	}
}


#endif
