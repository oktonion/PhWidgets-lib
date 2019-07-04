#ifndef PT_NUMERIC_H
#define PT_NUMERIC_H

#include <photon/PtNumeric.h>

#include "./Compound.h"


namespace PhWidgets
{
		
	class Numeric:
		public Compound
	{
	public:

		struct ThisArgs
		{
												
			struct ArgPChar
			{
				enum eArgPChar
				{
					numeric_prefix = Pt_ARG_NUMERIC_PREFIX,
					numeric_suffix = Pt_ARG_NUMERIC_SUFFIX
				};
			};	
			
			struct ArgUnsignedShort
			{
				enum eArgUnsignedShort
				{
					numeric_spacing = Pt_ARG_NUMERIC_SPACING,
					numeric_updown_width = Pt_ARG_NUMERIC_UPDOWN_WIDTH
				};
			};
			
			struct ArgUnsignedShortFlag
			{
				enum eArgUnsignedShortFlag
				{
					numeric_flags = Pt_ARG_NUMERIC_FLAGS
				};
			};


		};

			
		struct ArgUnsignedShort:
			public ArgumentsEx<Compound::ArgUnsignedShort>,
			public ThisArgs::ArgUnsignedShort,
			public ThisArgs::ArgUnsignedShortFlag
		{
			typedef ThisArgs::ArgUnsignedShort::eArgUnsignedShort eArgUnsignedShort;
		};

			

		struct ArgPChar:
			public ArgumentsEx<Compound::ArgPChar>,
			public ThisArgs::ArgPChar
		{
			typedef ThisArgs::ArgPChar::eArgPChar eArgPChar;
		};	

		struct Arguments:
			public ArgUnsignedShort,
			public ArgPChar,
			public Compound::Arguments
        { };

		typedef ResourceFrom<Compound::WidgetResourcesSingleton>::
			Define::String<ThisArgs::ArgPChar::eArgPChar>::
			Define::Scalar<ThisArgs::ArgUnsignedShort::eArgUnsignedShort, unsigned short>::
			Define::Flag<ThisArgs::ArgUnsignedShortFlag::eArgUnsignedShortFlag, unsigned short>::

		resource_type WidgetResourcesSingleton;

	protected:
		virtual void check();
						
	public:
		WidgetResourcesSingleton resource;

		Numeric(int abn);
		Numeric(PtWidget_t *wdg);
		
		Numeric(const Numeric &rhs);
		
	};
	
}


#endif
