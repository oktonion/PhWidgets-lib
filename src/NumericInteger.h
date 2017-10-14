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
			typedef ThisCallbacks::Callback::eCallback eCallback;
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
		typedef ResourceFrom<Numeric::WidgetResourcesSingleton>::
			Define::Scalar<ThisArgs::ArgInt::eArgInt, int>::

			Define::Link<ThisCallbacks::Callback::eCallback, PtCallback_t*>::

		resource_type WidgetResourcesSingleton;

		virtual void check();
	
						
	public:
		WidgetResourcesSingleton resource;

		NumericInteger(int abn);
		NumericInteger(PtWidget_t *wdg);
		
		NumericInteger(const NumericInteger&);

		NumericInteger &operator=(const NumericInteger &rhs);
		
		phproperty<int>::bind<NumericInteger, ArgInt::eArgInt, Arguments::numeric_value> Value;
		phproperty<int>::bind<NumericInteger, ArgInt::eArgInt, Arguments::numeric_max> MaxValue;
		phproperty<int>::bind<NumericInteger, ArgInt::eArgInt, Arguments::numeric_min> MinValue;

		phwidgets_event<NumericInteger, NumericInteger::Callbacks::numeric_changed>		NumericChanged;
	};
	
		
}


#endif
