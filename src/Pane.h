#ifndef PHWIDGETS_PANE_H
#define PHWIDGETS_PANE_H

#include <photon/PtPane.h>

#include "./Container.h"


namespace PhWidgets
{
	/*!
		@struct PhWidgets::Pane
		@ingroup Widgets
	*/

	//! A container for organizing widgets
	/*!
		Pane is a container widget that's useful for logically or visually grouping widgets in an application. 
        Any child widgets that extend beyond the canvas of the Pane widget are clipped.
	*/		
	class Pane:
		public Container
	{
	public:

		//! Contains resource IDs for all Pane arguments. @ingroup Resources
		struct Arguments:
			public Container::Arguments
        { };

	protected:
		virtual void check();
						
	public:
		//! (constructor) 
		/*!
			Constructs a Pane widget by ID.
			@param[in] abn ID given by PhAB to widget (like 'ABN_WIDGET_NAME').
		*/
		explicit Pane(int abn);

		//! (constructor) 
		/*!
			Constructs a Pane widget by pointer to widget.
			@param[in] wdg pointer to Photon widget.
		*/		
		explicit Pane(PtWidget_t *wdg);
		
		//! @name Properties
		//! Properties are used to simplify use of widget resources.
		//@{
			
		//@}
	};
		
} // namespace PhWidgets


#endif // PHWIDGETS_PANE_H
