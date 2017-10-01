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
		};

			

		struct ArgPChar:
			public ArgumentsEx<Compound::ArgPChar>,
			public ThisArgs::ArgPChar
		{
		};	

		struct Arguments:
			public ArgUnsignedShort,
			public ArgPChar,
			public Compound::Arguments
		{
		};

	protected:
		virtual void check();
						
	public:
		Numeric(int abn);
		Numeric(PtWidget_t *wdg);
		
		
	};
	
	DEFINE_OPERATOR0(Numeric::ThisArgs::ArgPChar::eArgPChar, String);
	
	DEFINE_OPERATOR1(Numeric::ThisArgs::ArgUnsignedShort::eArgUnsignedShort, unsigned short, Scalar);
	
	DEFINE_OPERATOR2(Numeric::ThisArgs::ArgUnsignedShortFlag::eArgUnsignedShortFlag, unsigned short, unsigned short, Flag);
}


#endif
