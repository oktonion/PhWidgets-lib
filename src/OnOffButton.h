#ifndef PHWIDGETS_ONOFF_BUTTON_H
#define PHWIDGETS_ONOFF_BUTTON_H

#include <photon/PtOnOffButton.h>

#include "./Button.h"


namespace PhWidgets
{
	/*!
		@struct PhWidgets::OnOffButton
		@ingroup Widgets
	*/

	//! An on/off button that can be set or unset
	/*!
		A OnOffButton widget displays an on/off button that can be set or unset. 
		Instances of this class of widget are typically used in exclusive or nonexclusive groups. 
	*/	
	class OnOffButton:
		public Button
	{
	public:

		//! Contains resource IDs for OnOffButton arguments. @ingroup Resources
		struct ThisArgs
		{
			//! Contains resource IDs for OnOffButton arguments of type **bool**.
			struct ArgBool
			{
				//! Resource IDs for OnOffButton arguments of type **bool**.

				/*!
					### Aliases ###
					
					PhWidgets::OnOffButton::Arguments::eArgBool,
					PhWidgets::OnOffButton::ArgBool::eArgBool

					See Widget::resource for usage description.
				*/
				enum eArgBool
				{
					onoff_state = Pt_ARG_ONOFF_STATE
				};
			};
		};

		//! Contains resource IDs for OnOffButton callbacks. @ingroup Resources
		struct ThisCallbacks
		{
			//! Contains resource IDs for OnOffButton callbacks of type `PtCallback_t`.
			struct Callback
			{
				//! Resource IDs for OnOffButton arguments of type `PtCallback_t`.
				/*!
					### Aliases ###
					
					PhWidgets::OnOffButton::Callbacks::eCallback,
					PhWidgets::OnOffButton::Callback::eCallback

					See Widget::resource for usage description.
				*/
				enum eCallback
				{
					new_value = Pt_CB_ONOFF_NEW_VALUE
				};
			};
		};

		//! Contains resource IDs for arguments of type **bool**. @ingroup Resources
		struct ArgBool:
			public ThisArgs::ArgBool
        { };

		//! Contains resource IDs for callbacks of type `PtCallback_t`. @ingroup Resources
		struct Callback:
			public ArgumentsEx<ThisCallbacks::Callback>,
			public Button::Callback
		{
			typedef ThisCallbacks::Callback::eCallback eCallback;
		};

		//! Contains resource IDs for all OnOffButton arguments. @ingroup Resources
		struct Arguments:
			public Button::Arguments,
			public ArgBool
        { };

		//! Contains resource IDs for all OnOffButton callbacks. @ingroup Resources
		struct Callbacks:
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
		//! Resources of the OnOffButton
		/*!
			@see
			- Widget::resource
		*/
		WidgetResourcesSingleton resource;

		//! (constructor) 
		/*!
			Constructs a OnOffButton widget by ID.
			@param[in] abn ID given by PhAB to widget (like 'ABN_WIDGET_NAME').
		*/
		OnOffButton(int abn);
		OnOffButton(PtWidget_t* wdg);
		
		OnOffButton(const OnOffButton&);

		OnOffButton &operator=(const OnOffButton &rhs);
		
		void Check(bool val = true);
		void Uncheck(bool val = true);

		//! @name Properties
		//! Properties are used to simplify use of widget resources.
		//@{
		phproperty<bool>::bind<OnOffButton, ArgBool::eArgBool, Arguments::onoff_state> Checked;
		//@}

		phwidgets_event<OnOffButton, OnOffButton::Callbacks::new_value>		NewValue;
	};

}  // namespace PhWidgets


#endif // PHWIDGETS_ONOFF_BUTTON_H
