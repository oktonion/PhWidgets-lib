#ifndef PT_NUMERIC_FLOAT_H
#define PT_NUMERIC_FLOAT_H

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
		{
		};
		
		struct ArgDoubleP:
			public ThisArgs::ArgDoubleP
		{
		};

		struct Callback :
			public ArgumentsEx<ThisCallbacks::Callback>,
			public Numeric::Callback
		{
		};


			
		struct Arguments:
			public ArgInt,
			public ArgDoubleP,
			public Numeric::Arguments
		{
		};

		struct Callbacks :
			public Callback,
			public Numeric::Callbacks
		{
		};


	protected:
		virtual void check();
		
		double getValue() const;
		void setValue(double val);
		
		double getMaxValue() const;
		void setMaxValue(double val);
		
		double getMinValue() const;
		void setMinValue(double val);

		void addNumericChangedCallback(callback_t callback);
						
	public:
		NumericFloat(int abn);
		NumericFloat(PtWidget_t *wdg);
		
		NumericFloat(const NumericFloat&);

		NumericFloat &operator=(const NumericFloat &rhs);
		
		property<double>::bind<NumericFloat, &NumericFloat::getValue, &NumericFloat::setValue> Value;
		property<double>::bind<NumericFloat, &NumericFloat::getMaxValue, &NumericFloat::setMaxValue> MaxValue;
		property<double>::bind<NumericFloat, &NumericFloat::getMinValue, &NumericFloat::setMinValue> MinValue;

		phevent::bind<NumericFloat, &NumericFloat::addNumericChangedCallback>		NumericChanged;
		
	};
	
	INIT_WIDGET_RESOURCE1(NumericFloat::ThisArgs::ArgDoubleP::eArgDoubleP, double*, Struct);
	INIT_WIDGET_RESOURCE1(NumericFloat::ThisCallbacks::Callback::eCallback, PtCallback_t, Link);
	
	INIT_WIDGET_RESOURCE1(NumericFloat::ThisArgs::ArgInt::eArgInt, int, Scalar);

}


#endif
