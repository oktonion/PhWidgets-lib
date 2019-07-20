#ifndef PHWIDGETS_DISJOINT_H
#define PHWIDGETS_DISJOINT_H

#include <photon/PtDisjoint.h>

#include "./Container.h"


namespace PhWidgets
{
	//! Superclass for disjoint widgets
	/*!
		Disjoint is the superclass for the Widget classes that are disjoint (i.e. are instantiated without a parent).

		@see
		- Window
	*/	
	class Disjoint:
		public Container
	{
	public:

        //! Contains resource IDs for Disjoint arguments.
		struct ThisArgs
		{		
            //! Contains resource IDs for Disjoint arguments of type `PhSysInfo_t`.
			struct ArgPSysInfo
			{
                //! Resource IDs for Disjoint arguments of type `PhSysInfo_t`.

				/*!
                	@code
                        typedef struct Ph_sys_info {
                            PhGeneralSysInfo_t  gen; // General information. Always examine this. 
                            PhGrafxInfo_t       gfx; // Information for graphics regions. 
                            PhKbdInfo_t         kbd; // Information for keyboard regions.  
                            PhPtrInfo_t         ptr; // Information for graphics regions.
                            PhIgInfo_t          ig;  // Information for input-group regions. 
                        } PhSysInfo_t;
                    @endcode

					### Aliases ###
					
					PhWidgets::Disjoint::Arguments::eArgPSysInfo,
					PhWidgets::Disjoint::ArgPSysInfo::eArgPSysInfo

					See Widget::resource for usage description.
				*/
				enum eArgPSysInfo
				{
					sysinfo = Pt_ARG_SYSINFO //!< A `PhSysInfo_t` structure that contains system information.
				};
			};	
		};

        //! Contains resource IDs for Disjoint callbacks.
		struct ThisCallbacks
		{
            //! Contains resource IDs for Disjoint callbacks of type `PtCallback_t`.
			struct Callback
			{
                //! Resource IDs for Disjoint arguments of type `PtCallback_t`.
				/*!
					### Aliases ###
					
					PhWidgets::Disjoint::Callbacks::eCallback,
					PhWidgets::Disjoint::Callback::eCallback

					See Widget::resource for usage description.
				*/
				enum eCallback
				{
					sysinfo = Pt_CB_SYSINFO
				};
			};
		};
		
        //! Contains resource IDs for Disjoint arguments of type `PhSysInfo_t`.
		struct ArgPSysInfo:
			public ThisArgs::ArgPSysInfo
        { };	

        //! Contains resource IDs for Disjoint callbacks of type `PtCallback_t`.
		struct Callback:
			public ArgumentsEx<ThisCallbacks::Callback>,
			public Container::Callback
		{
			typedef ThisCallbacks::Callback::eCallback eCallback;
		};

        //! Contains resource IDs for all Disjoint arguments.
		struct Arguments:
			public ArgPSysInfo,
			public Container::Arguments
        { };

        //! Contains resource IDs for all Disjoint callbacks.
		struct Callbacks:
			public Callback,
			public Container::Callbacks
        { };

	protected:
		typedef ResourceFrom<Container::WidgetResourcesSingleton>::
			Define::Struct<ThisArgs::ArgPSysInfo::eArgPSysInfo, PhSysInfo_t>::

			Define::Link<ThisCallbacks::Callback::eCallback, PtCallback_t*>::

		resource_type WidgetResourcesSingleton;

		virtual void check();
						
	public:
		WidgetResourcesSingleton resource;

		Disjoint(int abn);
		Disjoint(PtWidget_t *wdg);

		Disjoint(const Disjoint &rhs);

		Disjoint &operator=(const Disjoint &rhs);
		
        //! @name Events
		//@{ 
		phwidgets_event<Disjoint, Disjoint::Callbacks::sysinfo>	SysInfo;
        //@}
	};
} // namespace PhWidgets


#endif // PHWIDGETS_DISJOINT_H
