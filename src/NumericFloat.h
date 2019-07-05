#ifndef PHWIDGETS_NUMERIC_FLOAT_H
#define PHWIDGETS_NUMERIC_FLOAT_H

#include <photon/PtNumericFloat.h>

#include "./Numeric.h"


namespace PhWidgets
{
		
	class NumericFloat:
		public Numeric
	{
	public:

		struct ThisArgs
		{												
			struct ArgInt
			{				
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

		struct ThisCallbacks
		{
			struct Callback
			{
				enum eCallback
				{
					numeric_changed = Pt_CB_NUMERIC_CHANGED
				};
			};
		};
		
		struct ArgInt:
			public ThisArgs::ArgInt
        { };
		
		struct ArgDoubleP:
			public ThisArgs::ArgDoubleP
        { };

		struct Callback :
			public ArgumentsEx<ThisCallbacks::Callback>,
			public Numeric::Callback
		{
			typedef ThisCallbacks::Callback::eCallback eCallback;
		};


			
		struct Arguments:
			public ArgInt,
			public ArgDoubleP,
			public Numeric::Arguments
        { };

		struct Callbacks :
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
		WidgetResourcesSingleton resource;

		NumericFloat(int abn);
		NumericFloat(PtWidget_t *wdg);
		
		NumericFloat(const NumericFloat&);

		NumericFloat &operator=(const NumericFloat &rhs);
		
		property<double>::bind<NumericFloat, &NumericFloat::getValue, &NumericFloat::setValue> Value;
		property<double>::bind<NumericFloat, &NumericFloat::getMaxValue, &NumericFloat::setMaxValue> MaxValue;
		property<double>::bind<NumericFloat, &NumericFloat::getMinValue, &NumericFloat::setMinValue> MinValue;

		phwidgets_event<NumericFloat, NumericFloat::Callbacks::numeric_changed>		NumericChanged;
		
	};

} // namespace PhWidgets


#endif // PHWIDGETS_NUMERIC_FLOAT_H
