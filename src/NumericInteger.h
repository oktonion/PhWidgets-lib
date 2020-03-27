#ifndef PHWIDGETS_NUMERIC_INTEGER_H
#define PHWIDGETS_NUMERIC_INTEGER_H

#include <photon/PtNumericInteger.h>

#include "./Numeric.h"


namespace PhWidgets
{
	/*!
		@struct PhWidgets::NumericInteger
		@ingroup Widgets
	*/

	//! Integer numeric widget
	/*!
		The NumericInteger class lets you specify integer values between given minimum and maximum values. 
	*/
	class NumericInteger: //TODO::implement all properties
		public Numeric
	{
	public:

		//! Contains resource IDs for NumericInteger arguments. @ingroup Resources
		struct ThisArgs
		{												
			//! Contains resource IDs for NumericInteger arguments of type **int**.
			struct ArgInt
			{
				//! Resource IDs for NumericInteger arguments of type **long**.

				/*!
					### Aliases ###
					
					PhWidgets::NumericInteger::Arguments::eArgInt,
					PhWidgets::NumericInteger::ArgInt::eArgInt

					See Widget::resource for usage description.
				*/
				enum eArgInt
				{
					numeric_increment = Pt_ARG_NUMERIC_INCREMENT,
					numeric_max = Pt_ARG_NUMERIC_MAX,
					numeric_min = Pt_ARG_NUMERIC_MIN,
					numeric_value = Pt_ARG_NUMERIC_VALUE
				};
			};

		};

		//! Contains resource IDs for NumericInteger callbacks. @ingroup Resources
		struct ThisCallbacks
		{
			//! Contains resource IDs for NumericInteger callbacks of type `PtCallback_t`.
			struct Callback
			{
				//! Resource IDs for NumericInteger arguments of type `PtCallback_t`.
				/*!
					### Aliases ###
					
					PhWidgets::NumericInteger::Callbacks::eCallback,
					PhWidgets::NumericInteger::Callback::eCallback

					See Widget::resource for usage description.
				*/
				enum eCallback
				{
					numeric_changed = Pt_CB_NUMERIC_CHANGED
				};
			};
		};
		
		//! Contains resource IDs for arguments of type **int**. @ingroup Resources
		struct ArgInt:
			public ThisArgs::ArgInt
        { };

		//! Contains resource IDs for callbacks of type `PtCallback_t`. @ingroup Resources
		struct Callback:
			public ArgumentsEx<ThisCallbacks::Callback>,
			public Numeric::Callback
		{
			typedef ThisCallbacks::Callback::eCallback eCallback;
		};

		//! Contains resource IDs for all NumericInteger arguments. @ingroup Resources
		struct Arguments:
			public ArgInt,
			public Numeric::Arguments
        { };

		//! Contains resource IDs for all NumericInteger callbacks. @ingroup Resources
		struct Callbacks:
			public Callback,
			public Numeric::Callbacks
        { };


	protected:
		typedef ResourceFrom<Numeric::WidgetResourcesSingleton>::
			Define::Scalar<ThisArgs::ArgInt::eArgInt, int>::

			Define::Link<ThisCallbacks::Callback::eCallback, PtCallback_t*>::

		resource_type WidgetResourcesSingleton;

		virtual void check();
	
						
	public:
		//! Resources of the NumericInteger
		/*!
			@see
			- Widget::resource
		*/
		WidgetResourcesSingleton resource;

		//! (constructor) 
		/*!
			Constructs a NumericInteger widget by ID.
			@param[in] abn ID given by PhAB to widget (like 'ABN_WIDGET_NAME').
		*/
		explicit NumericInteger(int abn);

		//! (constructor) 
		/*!
			Constructs a NumericInteger widget by pointer to widget.
			@param[in] wdg pointer to Photon widget.
		*/
		explicit NumericInteger(PtWidget_t *wdg);
		
		//! (copy constructor) 
		/*!
			Constructs a NumericInteger widget by copy.
			@param[in] other another NumericInteger widget to be used as source to initialize the elements of the container with.
		*/
		NumericInteger(const NumericInteger &other);

		//! Assigns value in NumericInteger widget 
		/*!
			Replaces the contents of the NumericInteger widget.
			@param[in] other another NumericInteger widget to use as data source.
		*/
		NumericInteger &operator=(const NumericInteger &other);
		
		//! @name Properties
		//! Properties are used to simplify use of widget resources.
		//@{
		phproperty<int>::bind<NumericInteger, ArgInt::eArgInt, Arguments::numeric_value> Value;
		phproperty<int>::bind<NumericInteger, ArgInt::eArgInt, Arguments::numeric_max> MaxValue;
		phproperty<int>::bind<NumericInteger, ArgInt::eArgInt, Arguments::numeric_min> MinValue;
		//@}

		phwidgets_event<NumericInteger, NumericInteger::Callbacks::numeric_changed>		NumericChanged;
	};
	
		
}  // namespace PhWidgets


#endif // PHWIDGETS_NUMERIC_INTEGER_H
