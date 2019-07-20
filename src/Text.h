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

		//! Contains resource IDs for Text arguments.
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

		//! Contains resource IDs for Text callbacks.
		struct ThisCallbacks
		{
			//! Contains resource IDs for Text callbacks of type `PtCallback_t`.
			struct Callback
			{
				//! Resource IDs for Text arguments of type `PtCallback_t`.
				/*!
					### Aliases ###
					
					PhWidgets::Text::Callbacks::eCallback,
					PhWidgets::Text::Callback::eCallback

					See Widget::resource for usage description.
				*/
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

		//! Contains resource IDs for callbacks of type `PtCallback_t`.
		struct Callback:
			public ArgumentsEx<ThisCallbacks::Callback>,
			public Label::Callback
		{
			typedef ThisCallbacks::Callback::eCallback eCallback;
		};

		//! Contains resource IDs for all Text arguments.
		struct Arguments:
			public ArgComplex,
			public Label::Arguments
        { };

		//! Contains resource IDs for all Text callbacks.
		struct Callbacks:
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
		//! Resources of the Text
		/*!
			@see
			- Widget::resource
		*/
		WidgetResourcesSingleton resource;

		//! (constructor) 
		/*!
			Constructs a Text widget by ID.
			@param[in] abn ID given by PhAB to widget (like 'ABN_WIDGET_NAME').
		*/
		Text(int abn);

		//! (constructor) 
		/*!
			Constructs a Text widget by pointer to widget.
			@param[in] wdg pointer to Photon widget.
		*/		
		Text(PtWidget_t *wdg);

		//! (copy constructor) 
		/*!
			Constructs a Text widget by copy.
			@param[in] other another Text widget to be used as source to initialize the elements of the container with.
		*/
		Text(const Text &other);

		//! Assigns value in Text widget 
		/*!
			Replaces the contents of the Text widget.
			@param[in] other another Text widget to use as data source.
		*/
		Text &operator=(const Text &other);
		//! @name Properties
		//! Properties are used to simplify use of widget resources.
		//@{

		//@}
		
		phwidgets_event<Text, Text::Callbacks::modify_notify>	ModifyNotify;
		phwidgets_event<Text, Text::Callbacks::modify_verify>	ModifyVerify;
		phwidgets_event<Text, Text::Callbacks::motion_notify>	MotionNotify;
		phwidgets_event<Text, Text::Callbacks::motion_verify>	MotionVerify;
		phwidgets_event<Text, Text::Callbacks::text_changed> 	TextChanged;
	};
	
}  // namespace PhWidgets


#endif // PHWIDGETS_TEXT_H
