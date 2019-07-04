#ifndef PT_COMPOUND_H
#define PT_COMPOUND_H

#include <photon/PtCompound.h>

#include "./Container.h"


namespace PhWidgets
{
		
	class Compound:
		public Container
	{
	public:

		struct Arguments:
			public Container::Arguments
        { };

	protected:
		virtual void check();
						
	public:
		Compound(int abn);
		Compound(PtWidget_t *wdg);
		
		
	};
		
}


#endif
