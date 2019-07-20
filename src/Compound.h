#ifndef PHWIDGETS_COMPOUND_H
#define PHWIDGETS_COMPOUND_H

#include <photon/PtCompound.h>

#include "./Container.h"


namespace PhWidgets
{
	//! Superclass for all compound widgets
	/*!
		The Compound superclass provides the ability to combine widgets into a compound. 
		A compound widget can export its subordinate children to let you get and set their resources, 
		or it can block access to them to provide a “canned” appearance.
	*/		
	class Compound:
		public Container
	{
	public:

		//! Contains resource IDs for all Compound arguments.
		struct Arguments:
			public Container::Arguments
        { };

	protected:
		virtual void check();
						
	public:
		Compound(int abn);
		Compound(PtWidget_t *wdg);
		
		
	};
		
} // namespace PhWidgets


#endif // PHWIDGETS_COMPOUND_H
