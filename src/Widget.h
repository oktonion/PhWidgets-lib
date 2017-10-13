#ifndef PT_WIDGET_H
#define PT_WIDGET_H

#include <photon/PhT.h>
#include <photon/PtWidget.h>
#include <photon/PtContainer.h>
#include <photon/PtGridLayout.h>
#include <photon/PtRowLayout.h>

#include <map>
#include <string>
#include <list>

#include "./service/mystd/my_exception.h"
#include "./service/stdex/stdex.h"
#include "./service/phproperty.hpp"
#include "./service/phevent.hpp"

#include "./WidgetResource.hpp"

//typedef Ph_rect PhRect_t;

#ifndef __QNXNTO__
	typedef struct Ph_rect   PhRect_t;
#endif

namespace PhWidgets
{
	using namespace cppproperties;
	using namespace phevents;
		
	class Widget:
		protected detail::IPtWidget,
		public IPhWidgetsProperty
	{
	public:

		
		typedef phevent::ph_callback_t callback_t;//!< An event handler that is raised when an \link Widget::phwidgets_event event \endlink occur.
		
		//! An event, which raise a notification to registered subscribers (event handlers) that something of interest has occurred.

		//! Event handlers must be Widget::callback_t type or convertable to it.
		template<class ParentT, typename ParentT::ThisCallbacks::Callback::eCallback CallbackID>
		class phwidgets_event
		{
			
		public:
			phwidgets_event(ParentT *parent) :
				_obj(parent)
			{}

			//! add an event handler
			inline void add(callback_t value)
			{
				_obj->resource.callback[CallbackID].add(value);
			}

			//! remove an event handler
			inline void remove(callback_t value)
			{
				_obj->resource.callback[CallbackID].remove(value);
			}

			//! raise an event

			//! invokes all event handlers that are subscribed to this event
			inline void raise(PtCallbackInfo_t * info) const
			{
				_obj->resource.callback[CallbackID].raise(info);
			}

			//! add an event handler
			inline void operator+=(callback_t value)
			{
				add(value);
			}

			//! remove an event handler
			inline void operator-=(callback_t value)
			{
				remove(value);
			}

			//! raise an event

			//! invokes all event handlers that are subscribed to this event
			inline void operator()(PtCallbackInfo_t * info) const
			{
				raise(info);
			}


		private:
			ParentT *_obj;

			phwidgets_event(const phwidgets_event &rhs);

			inline phwidgets_event &operator=(callback_t);
			inline phwidgets_event &operator=(phwidgets_event const &);
		};


		/*template<class ParentT, ParentT::Callbacks::eRawCallback callback>
		class phwidgets_event
		{
			typedef phevent::ph_callback_t value_t;

		public:
			phwidgets_event(ParentT *parent) :
				_obj(parent)
			{}

			inline void add(value_t value)
			{
				_obj->resource.callback[callback].add(value);
			}

			inline void remove(value_t value)
			{
				_obj->resource.callback[callback].remove(value);
			}

			inline void operator+=(value_t value)
			{
				add(value);
			}

			inline void operator-=(value_t value)
			{
				remove(value);
			}


		private:
			ParentT *_obj;

			phwidgets_event(const phwidgets_event &rhs);

			inline phwidgets_event &operator=(value_t);
			inline phwidgets_event &operator=(phwidgets_event const &);
		};*/
	
		struct ThisArgs
		{
			struct ArgArea
			{
				enum eArgArea
				{			
					area = Pt_ARG_AREA //!< A PhArea_t structure (see the Photon Library Reference) that contains the x, y, height, and width values for the widget. 
				};
			};
			
			struct ArgUnsigned
			{
				enum eArgUnsigned
				{
					anchor_flags = Pt_ARG_ANCHOR_FLAGS //!< This resource specifies how the widget is anchored to its parent.
				};
			};
			
			struct ArgUnsignedShort
			{
				enum eArgUnsignedShort
				{
					bevel_width = Pt_ARG_BEVEL_WIDTH, //!< The width of the widget's bevel if the widget is highlighted and is to draw a bevel.
					cursor_type = Pt_ARG_CURSOR_TYPE, //!< The type of cursor.
					height = Pt_ARG_HEIGHT, //!< The height of the widget.
					width = Pt_ARG_WIDTH //!< The width of the widget.
				};
			};
			
			struct ArgUnsignedLong
			{
				enum eArgUnsignedLong
				{
					eflags = Pt_ARG_EFLAGS //!< Extended flags inherited by all widgets:
										   //!< Documentation in progress...
				};
			};
			
			struct ArgLong
			{
				enum eArgLong
				{
					flags = Pt_ARG_FLAGS, //!< Common flags used by all widgets. Except for those indicated as read-only, these flags are all read/write. 
					resize_flags = Pt_ARG_RESIZE_FLAGS //!< Controls a widget's resize policy in both the x and y directions.
													   //!< Documentation in progress...
				};
			};

			struct ArgPChar
			{
				enum eArgPChar
				{
					help_topic = Pt_ARG_HELP_TOPIC //!< The meaning of this resource depends on the bits set in Pt_ARG_EFLAGS:
												   //!< If Pt_INTERNAL_HELP isn't set, Widget::ArgPChar::help_topic is used to set the topic position within the HTML help file.
												   //!< If Pt_INTERNAL_HELP is set, Widget::ArgPChar::help_topic is the help information to be displayed.

				};
			};
			
			struct ArgPVoid
			{
				enum eArgPVoid
				{
					pointer = Pt_ARG_POINTER, //!< A pointer to any data that you want to associate with the widget.
					layout_data = Pt_ARG_LAYOUT_DATA, //!< This resource provides a convenient method to get or set either of the Pt_ARG_*_LAYOUT_DATA resources.
													  //!< Documentation in progress...
					data = Pt_ARG_DATA, //!< This resource is used internally by PhAB applications as well as by compound widgets.
					user_data = Pt_ARG_USER_DATA //!< Data that you want to store in the widget's internal memory.
				};
			};

			struct ArgRect
			{
				enum eArgRect
				{
					enchor_offsets = Pt_ARG_ANCHOR_OFFSETS, //!< The four values in this PhRect_t structure (see the Photon Library Reference) determine the anchor offsets of each of the widget's sides. (An anchor offset is the distance between the anchoring side of the parent and corresponding side of the child.) 
					extent = Pt_ARG_EXTENT //!< A PhRect_t structure that contains the extent of the widget, a rectangle that specifies the upper-left and lower-right corners of the widget.
				};
			};
			
			struct ArgColor
			{
				enum eArgColor
				{
					cursor_color = Pt_ARG_CURSOR_COLOR //!< The color of the pointer when it's inside the widget.
				};	
			};
			
			struct ArgPCursorDef
			{
				enum eArgPCursorDef
				{
					bitmap_cursor = Pt_ARG_BITMAP_CURSOR //!< Defines bitmaps for the cursor when the cursor type (Pt_ARG_CURSOR_TYPE) is set to Ph_CURSOR_BITMAP. 
				};
			};
			
			struct ArgPGridLayoutData
			{
				enum eArgPGridLayoutData
				{
					grid_layout_data = Pt_ARG_GRID_LAYOUT_DATA //!< A PtGridLayoutData_t structure that defines additional layout data for the widget when its container widget uses a PtGridLayout type layout. 
															   //!< Documentation in progress...
				};
			};
			
			struct ArgPoint
			{
				enum eArgPoint
				{
					pos = Pt_ARG_POS //!< A PhPoint_t structure that stores the x and y coordinates for the widget.
				};
			};

			struct ArgPRowLayoutData
			{
				enum eArgPRowLayoutData
				{
					row_layout_data = Pt_ARG_ROW_LAYOUT_DATA //!< A PtRowLayoutData_t structure that defines additional layout data for the widget when its container widget uses a PtRowLayout type layout. 
				};
			};

			struct ArgDim
			{
				enum eArgDim
				{
					dim = Pt_ARG_DIM, //!< A PhDim_t structure (see the Photon Library Reference) that defines the height and width values for the widget.
					max_dim = Pt_ARG_MAXIMUM_DIM, //!< A PhDim_t structure (see the Photon Library Reference) that defines the maximum size that a widget can be.
					min_dim = Pt_ARG_MINIMUM_DIM //!< A PhDim_t structure (see the Photon Library Reference) that defines the minimum size that a widget can be.
				};
			};
		};

		struct ThisCallbacks
		{
			struct RawCallback
			{
				enum eRawCallback
				{
					filter = Pt_CB_FILTER, //!< A list of raw callbacks invoked when an event that matches the provided event mask is to be passed to the widget. 
										   //!< These callbacks are invoked before the event is processed by the widget. Contrast this resource with Widget::Callbacks::raw.
										   //!< Documentation in progress...

					raw = Pt_CB_RAW //!< A list of PtRawCallback_t structures that defines the raw callbacks that the widget invokes if the event it receives matches the event mask provided in the PtRawCallback_t structure.
									//!< Documentation in progress...

				};
			};

			struct Callback
			{
				enum eCallback
				{
					blocked = Pt_CB_BLOCKED, //!< A list of PtCallback_t structures that define the callbacks that the widget invokes whenever it must ignore an event due to being blocked.
											 //!< Documentation in progress...

					destroyed = Pt_CB_DESTROYED, //!< A list of PtCallback_t structures that define the callbacks invoked when the widget is marked for destruction and is no longer visible. 
												 //!< You can use these callbacks, for example, to adjust the appearance of the widgets around the one being destroyed.
												 //!< In contrast, the Widget::Callbacks::is_destroyed callbacks are invoked when the widget's resources are actually being released.
												 //!< Documentation in progress...

					dnd = Pt_CB_DND, //!< A list of PtCallback_t structures that define the callbacks called when a drag-and-drop (Events::dndrop) event is received.
									 //!< Documentation in progress...

					is_destroyed = Pt_CB_IS_DESTROYED, //!< A list of PtCallback_t structures that define the callbacks invoked when the widget's resources are being released. 
													   //!< You'll find this resource useful for cleaning up variables or memory associated with the widget. 
													   //!< Documentation in progress...

					outbound = Pt_CB_OUTBOUND, //!< A list of PtCallback_t structures that define the callbacks invoked when you press the pointer button on the widget and then move out of the "hot spot" with the button still depressed. 
											   //!< This callback is particularly useful for initiating drag or drag-and-drop operations.
											   //!< Documentation in progress...

					realized = Pt_CB_REALIZED, //!< A list of PtCallback_t structures that define the callbacks that the widget invokes whenever it is realized. 
											   //!< Documentation in progress...

					unrealized = Pt_CB_UNREALIZED //!< A list of PtCallback_t structures that define the callbacks that the widget invokes whenever it's unrealized. 
												  //!< Documentation in progress...
				};
			};

			struct HotkeyCallback
			{
				enum eHotkeyCallback
				{
					//! A list of PtHotkeyCallback_t structures. 
					
					//! If the widget receives a key event that matches a structure's key cap and key modifiers, the widget calls the function specified in that structure. 
					//! If a function isn't specified, the widget invokes its Basic::Callbacks::activate callback list with a reason_subtype of Widget::Callbacks::hotkey. 
					//! \remark A hotkey isn't invoked if any ancestor of the widget that owns it is blocked.
					//! Documentation in progress...
					hotkey = Pt_CB_HOTKEY
				};
			};
		};

		struct ArgArea:
			public ThisArgs::ArgArea
		{
		};
		
		struct ArgUnsigned:
			public ThisArgs::ArgUnsigned
		{
		};
		
		struct ArgUnsignedShort:
			public ThisArgs::ArgUnsignedShort
		{
		};
		
		struct ArgUnsignedLong:
			public ThisArgs::ArgUnsignedLong
		{
		};
		
		struct ArgLong:
			public ThisArgs::ArgLong
		{
		};

		struct ArgPChar:
			public ThisArgs::ArgPChar
		{
		};
		
		struct ArgPVoid:
			public ThisArgs::ArgPVoid
		{
		};

		struct ArgRect:
			public ThisArgs::ArgRect
		{
		};
		
		struct ArgColor:
			public ThisArgs::ArgColor
		{
		};
		
		struct ArgPCursorDef:
			public ThisArgs::ArgPCursorDef
		{
		};
		
		struct ArgPGridLayoutData:
			public ThisArgs::ArgPGridLayoutData
		{
		};
		
		struct ArgPoint:
			public ThisArgs::ArgPoint
		{
		};

		struct ArgPRowLayoutData:
			public ThisArgs::ArgPRowLayoutData
		{
		};

		struct ArgDim:
			public ThisArgs::ArgDim
		{
		};

		struct RawCallback:
			public ThisCallbacks::RawCallback
		{
		};

		struct Callback:
			public ThisCallbacks::Callback
		{
		};

		struct HotkeyCallback:
			public ThisCallbacks::HotkeyCallback
		{
		};
	
		struct Arguments:
			public ArgArea,
			public ArgColor,
			public ArgLong,
			public ArgPChar,
			public ArgPCursorDef,
			public ArgPGridLayoutData,
			public ArgPoint,
			public ArgPRowLayoutData,
			public ArgPVoid,
			public ArgRect,
			public ArgUnsigned,
			public ArgUnsignedLong, 
			public ArgUnsignedShort,
			public ArgDim
		{
		};

		struct Callbacks :
			public RawCallback,
			public Callback,
			public HotkeyCallback
		{
		};

		

				
	private:
	
		int _abn;
		mutable PtWidget_t *_widget;
		
		using IPhWidgetsProperty::setArgument;
		using IPhWidgetsProperty::getArgument;
		
	protected:

		template<class ParentArgs>
		struct ArgumentsEx:
			public ParentArgs
		{
		};

		typedef ResourceFrom<>::
			Define::String<ArgPChar::eArgPChar>::
			Define::Alloc<ArgPVoid::eArgPVoid>::
			Define::Color<ArgColor::eArgColor>::
			Define::Struct<ArgPCursorDef::eArgPCursorDef, PhCursorDef_t>::
			Define::Struct<ArgPGridLayoutData::eArgPGridLayoutData, PtGridLayoutData_t>::
			Define::Struct<ArgPoint::eArgPoint, PhPoint_t>::
			Define::Struct<ArgPRowLayoutData::eArgPRowLayoutData, PtRowLayoutData_t>::
			Define::Struct<ArgArea::eArgArea, PhArea_t>::
			Define::Struct<ArgRect::eArgRect, PhRect_t>::
			Define::Scalar<ArgUnsignedShort::eArgUnsignedShort, unsigned short>::
			Define::Struct<ArgDim::eArgDim, PhDim_t>::
			Define::Flag<ArgLong::eArgLong, long>::
			Define::Flag<ArgUnsignedLong::eArgUnsignedLong, unsigned long>::
			Define::Flag<ArgUnsigned::eArgUnsigned, unsigned>::

			Define::Link<Callback::eCallback, PtCallback_t*>::
			Define::Link<RawCallback::eRawCallback, PtRawCallback_t*>::
			Define::Link<HotkeyCallback::eHotkeyCallback, PtHotkeyCallback_t*>::

		resource_type WidgetResourcesSingleton;
	
		PtWidget_t *widget() const;
		virtual void check();
		
		//for properties:

		void setEnabled(bool);
		bool getEnabled() const;

		void setHelpTopic(std::string);
		std::string getHelpTopic() const;
						
	public:
		//! (constructor)

		//! Constructs a Widget by ID.
		Widget(int abn/**< [in] - ID given by PhAB to widget (like 'ABN_WIDIGET_NAME'). */);

		//! (constructor)

		//! Constructs a Widget by pointer to widget.
		Widget(PtWidget_t *wdg /**< [in] - pointer to Photon widget. */);
		
		//! (copy constructor)

		//! Constructs a Widget by copy.
		Widget(const Widget &rhs /**< [in] - another Widget to be used as source to initialize the elements of the container with. */);
		
		//! Assigns value in Widget

		//! Replaces the contents of the Widget.
		Widget &operator=(const Widget &rhs/**< [in] - another Widget to use as data source. */);

		//! Compares Widgets

		//! Compares the Widgets by their Photon widget pointers. 
		bool operator==(const Widget &rhs/**< [in] - Widgets whose contents to compare . */);

		//! Compares Widgets

		//! Compares the Widgets by their Photon widget pointers. 
		bool operator<(const Widget &rhs/**< [in] - Widgets whose contents to compare . */);

		
		//! Converts Widget to Photon widget pointer
		operator PtWidget_t*();

		//! Converts Widget to constant Photon widget pointer
		operator const PtWidget_t*() const;

		//! Resources of the Widget
		WidgetResourcesSingleton resource;
	
		property<bool>::bind<Widget, &Widget::getEnabled, &Widget::setEnabled>							Enabled; //!< Gets or sets a value indicating whether the widget can respond to user interaction.
		property<std::string>::bind<Widget, &Widget::getHelpTopic, &Widget::setHelpTopic>				HelpTopic; //!< Gets or sets the help topic of the widget.

		phproperty<unsigned short>::bind<Widget, Arguments::eArgUnsignedShort, Arguments::width>		Width; //!< Gets or sets the width of the widget.
		phproperty<unsigned short>::bind<Widget, Arguments::eArgUnsignedShort, Arguments::height>		Height; //!< Gets or sets the hight of the widget.
		phproperty<unsigned short>::bind<Widget, Arguments::eArgUnsignedShort, Arguments::bevel_width>	BevelWidth; //!< Gets or sets the bevel width of the widget.
		phproperty<PhDim_t>::bind<Widget, Arguments::eArgDim, Arguments::dim>							Size; //!< Gets or sets the size of the widget.
		phproperty<PhPoint_t>::bind<Widget, Arguments::eArgPoint, Arguments::pos>						Location; //!< Gets or sets the position of the widget.

		phwidgets_event<Widget, Widget::Callbacks::destroyed>		Destroyed; //!< Occurs when the widget is destroyed.
		phwidgets_event<Widget, Widget::Callbacks::blocked>			Blocked; //!< Occurs when the widget is blocked.
		phwidgets_event<Widget, Widget::Callbacks::dnd>				DragDrop; //!< Occurs when a drag-and-drop operation is completed.
		phwidgets_event<Widget, Widget::Callbacks::is_destroyed>	IsDestroyed; //!< Occurs when the widget's resources are being released.
		phwidgets_event<Widget, Widget::Callbacks::outbound>		Outbound; //!< Occurs when you press the pointer button on the widget and then move out of the "hot spot" with the button still depressed.
		phwidgets_event<Widget, Widget::Callbacks::realized>		Realized; //!<  Occurs when the widget is realized.
		phwidgets_event<Widget, Widget::Callbacks::unrealized>		Unrealized; //!<  Occurs when the widget is unrealized.

		void OnDestroyed(PtCallbackInfo_t *info); //!< Raises the Widget::Destroyed event.
		void OnBlocked(PtCallbackInfo_t *info); //!< Raises the Widget::Blocked event.
		void OnDragDrop(PtCallbackInfo_t *info); //!< Raises the Widget::DragDrop event.
		void OnOutbound(PtCallbackInfo_t *info); //!< Raises the Widget::Outbound event.
		void OnRealized(PtCallbackInfo_t *info); //!< Raises the Widget::Realized event.
		void OnUnrealized(PtCallbackInfo_t *info); //!< Raises the Widget::Unrealized event.

		

	};
	
	

}//namespace PhWidgets


#endif
