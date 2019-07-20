#ifndef PHWIDGETS_NUMERIC_FLOAT_H
#define PHWIDGETS_NUMERIC_FLOAT_H

#include <photon/PtNumericFloat.h>

#include "./Numeric.h"


namespace PhWidgets
{
	//! Floating-point numeric widget
	/*!
		The NumericFloat class is a numeric widget that lets you enter 
		floating-point values between given minimum and maximum values. 
		You can also use an incorporated Scrollbar to increase or decrease the value by a set amount. 
	*/	
	class NumericFloat:
		public Numeric
	{
	public:

		//! Contains resource IDs for NumericFloat arguments.
		struct ThisArgs
		{												
			//! Contains resource IDs for NumericFloat arguments of type **int**.
			struct ArgInt
			{
				//! Resource IDs for NumericFloat arguments of type **long**.

				/*!
					### Aliases ###
					
					PhWidgets::NumericFloat::Arguments::eArgInt,
					PhWidgets::NumericFloat::ArgInt::eArgInt

					See Widget::resource for usage description.
				*/				
				enum eArgInt
				{
					numeric_precision = Pt_ARG_NUMERIC_PRECISION
				};
			};
			
			struct ArgDoubleP
			{
				enum eArgDoubleP
				{
					numeric_increment = Pt_ARG_NUMERIC_INCREMENT,
					numeric_max = Pt_ARG_NUMERIC_MAX,
					numeric_min = Pt_ARG_NUMERIC_MIN,
					numeric_value = Pt_ARG_NUMERIC_VALUE
				};
			};


		};

		//! Contains resource IDs for NumericFloat callbacks.
		struct ThisCallbacks
		{
			//! Contains resource IDs for NumericFloat callbacks of type `PtCallback_t`.
			struct Callback
			{
				//! Resource IDs for NumericFloat arguments of type `PtCallback_t`.
				/*!
					### Aliases ###
					
					PhWidgets::NumericFloat::Callbacks::eCallback,
					PhWidgets::NumericFloat::Callback::eCallback

					See Widget::resource for usage description.
				*/
				enum eCallback
				{
					numeric_changed = Pt_CB_NUMERIC_CHANGED
				};
			};
		};
		
		//! Contains resource IDs for arguments of type **int**.
		struct ArgInt:
			public ThisArgs::ArgInt
        { };
		
		struct ArgDoubleP:
			public ThisArgs::ArgDoubleP
        { };

		//! Contains resource IDs for callbacks of type `PtCallback_t`.
		struct Callback:
			public ArgumentsEx<ThisCallbacks::Callback>,
			public Numeric::Callback
		{
			typedef ThisCallbacks::Callback::eCallback eCallback;
		};

		//! Contains resource IDs for all NumericFloat arguments.
		struct Arguments:
			public ArgInt,
			public ArgDoubleP,
			public Numeric::Arguments
        { };

		//! Contains resource IDs for all NumericFloat callbacks.
		struct Callbacks:
			public Callback,
			public Numeric::Callbacks
        { };


	protected:
		typedef ResourceFrom<Numeric::WidgetResourcesSingleton>::
			Define::Struct<ThisArgs::ArgDoubleP::eArgDoubleP, double>::
			Define::Scalar<ThisArgs::ArgInt::eArgInt, int>::
			
			Define::Link<ThisCallbacks::Callback::eCallback, PtCallback_t*>::

		resource_type WidgetResourcesSingleton;

		virtual void check();
		
		double getValue() const;
		void setValue(double val);
		
		double getMaxValue() const;
		void setMaxValue(double val);
		
		double getMinValue() const;
		void setMinValue(double val);

						
	public:
		//! Resources of the NumericFloat
		/*!
			@see
			- Widget::resource
		*/
		WidgetResourcesSingleton resource;

		//! (constructor) 
		/*!
			Constructs a NumericFloat widget by ID.
			@param[in] abn ID given by PhAB to widget (like 'ABN_WIDGET_NAME').
		*/
		NumericFloat(int abn);

		//! (constructor) 
		/*!
			Constructs a NumericFloat widget by pointer to widget.
			@param[in] wdg pointer to Photon widget.
		*/
		NumericFloat(PtWidget_t *wdg);
		
		//! (copy constructor) 
		/*!
			Constructs a NumericFloat widget by copy.
			@param[in] other another NumericFloat widget to be used as source to initialize the elements of the container with.
		*/
		NumericFloat(const NumericFloat &other);

		//! Assigns value in NumericFloat widget 
		/*!
			Replaces the contents of the NumericFloat widget.
			@param[in] other another NumericFloat widget to use as data source.
		*/
		NumericFloat &operator=(const NumericFloat &other);
		
		//! @name Properties
		//! Properties are used to simplify use of widget resources.
		//@{
		property<double>::bind<NumericFloat, &NumericFloat::getValue, &NumericFloat::setValue> Value;
		property<double>::bind<NumericFloat, &NumericFloat::getMaxValue, &NumericFloat::setMaxValue> MaxValue;
		property<double>::bind<NumericFloat, &NumericFloat::getMinValue, &NumericFloat::setMinValue> MinValue;
		//@}

		phwidgets_event<NumericFloat, NumericFloat::Callbacks::numeric_changed>		NumericChanged;
		
	};

} // namespace PhWidgets


#endif // PHWIDGETS_NUMERIC_FLOAT_H
