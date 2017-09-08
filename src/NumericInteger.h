#ifndef PT_NUMERIC_INTEGER_H
#define PT_NUMERIC_INTEGER_H

#include <photon/PtNumericInteger.h>

#include "./Numeric.h"


namespace PhWidgets
{
		
	class NumericInteger: //TODO::implement all properties
		public Numeric
	{
	public:

		struct ThisArgs
		{												
			struct ArgInt
			{
				enum eArgInt
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

		struct Callback :
			public ArgumentsEx<ThisCallbacks::Callback>,
			public Numeric::Callback
		{
		};

			
		struct Arguments:
			public ArgInt,
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
		
		int getValue() const;
		void setValue(int);
		
		int getMaxValue() const;
		void setMaxValue(int);

		int getMinValue() const;
		void setMinValue(int);
						
	public:
		NumericInteger(int abn);
		NumericInteger(PtWidget_t *wdg);
		
		NumericInteger(const NumericInteger&);

		NumericInteger &operator=(const NumericInteger &rhs);
		
		property<int>::bind<NumericInteger, &NumericInteger::getValue, &NumericInteger::setValue> Value;
		property<int>::bind<NumericInteger, &NumericInteger::getMaxValue, &NumericInteger::setMaxValue> MaxValue;
		property<int>::bind<NumericInteger, &NumericInteger::getMinValue, &NumericInteger::setMinValue> MinValue;

		phwidgets_event<NumericInteger, NumericInteger::Callbacks::numeric_changed>		NumericChanged;
	};
	
	
	INIT_WIDGET_RESOURCE1(NumericInteger::ThisArgs::ArgInt::eArgInt, int, Scalar);

	INIT_WIDGET_RESOURCE1(NumericInteger::ThisCallbacks::Callback::eCallback, PtCallback_t, Link);
		
}


#endif
