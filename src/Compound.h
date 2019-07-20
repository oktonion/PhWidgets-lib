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
		//! (constructor) 
		/*!
			Constructs a Compound widget by ID.
			@param[in] abn ID given by PhAB to widget (like 'ABN_WIDGET_NAME').
		*/
		Compound(int abn);

		//! (constructor) 
		/*!
			Constructs a Compound widget by pointer to widget.
			@param[in] wdg pointer to Photon widget.
		*/		
		Compound(PtWidget_t *wdg);
		
		
	};
		
} // namespace PhWidgets


#endif // PHWIDGETS_COMPOUND_H
