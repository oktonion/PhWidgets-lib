#ifndef PHWIDGETS_TEXT_H
#define PHWIDGETS_TEXT_H

#include <photon/PtText.h>

#include <string>

#include "./Label.h"


namespace PhWidgets
{
	/*!
		@struct PhWidgets::Text
		@ingroup Widgets
	*/

	//! Single-line text
	/*!
		The Photon text widgets let you type textual information into a text-entry box. 
		The widgets provide basic editing features, so you can alter text that's entered. 
		They also support a point-and-click model of editing, so that you can operate on blocks of text as a unit. 
	*/	
	typedef
	class TextWidget:
		public Label
	{
	public:

		//! Contains resource IDs for Text arguments. @ingroup Resources
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

		//! Contains resource IDs for Text callbacks. @ingroup Resources
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

		//! Contains resource IDs for complex arguments. @ingroup Resources
		struct ArgComplex:
			public ThisArgs::ArgComplex
        { };

		//! Contains resource IDs for callbacks of type `PtCallback_t`. @ingroup Resources
		struct Callback:
			public ArgumentsEx<ThisCallbacks::Callback>,
			public Label::Callback
		{
			typedef ThisCallbacks::Callback::eCallback eCallback;
		};

		//! Contains resource IDs for all Text arguments. @ingroup Resources
		struct Arguments:
			public ArgComplex,
			public Label::Arguments
        { };

		//! Contains resource IDs for all Text callbacks. @ingroup Resources
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
		explicit TextWidget(int abn);

		//! (constructor) 
		/*!
			Constructs a Text widget by pointer to widget.
			@param[in] wdg pointer to Photon widget.
		*/		
		explicit TextWidget(PtWidget_t *wdg);

		//! (copy constructor) 
		/*!
			Constructs a Text widget by copy.
			@param[in] other another Text widget to be used as source to initialize the elements of the container with.
		*/
		TextWidget(const TextWidget &other);

		//! Assigns value in Text widget 
		/*!
			Replaces the contents of the Text widget.
			@param[in] other another Text widget to use as data source.
		*/
		TextWidget &operator=(const TextWidget &other);
		//! @name Properties
		//! Properties are used to simplify use of widget resources.
		//@{

		//@}
		
		phwidgets_event<TextWidget, TextWidget::Callbacks::modify_notify>	ModifyNotify;
		phwidgets_event<TextWidget, TextWidget::Callbacks::modify_verify>	ModifyVerify;
		phwidgets_event<TextWidget, TextWidget::Callbacks::motion_notify>	MotionNotify;
		phwidgets_event<TextWidget, TextWidget::Callbacks::motion_verify>	MotionVerify;
		phwidgets_event<TextWidget, TextWidget::Callbacks::text_changed> 	TextChanged;
	} Text;
	
}  // namespace PhWidgets


#endif // PHWIDGETS_TEXT_H
