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
#include "./service/property.hpp"
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
		detail::IPtWidget
	{
	public:
		typedef phevent::ph_callback_t callback_t;
		
		template<class ParentT, typename ParentT::ThisCallbacks::Callback::eCallback callback>
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
					area = Pt_ARG_AREA //A PhArea_t structure (see the Photon Library Reference) that contains the x, y, height, and width values for the widget. 
				};
			};
			
			struct ArgUnsigned
			{
				enum eArgUnsigned
				{
					anchor_flags = Pt_ARG_ANCHOR_FLAGS //This resource specifies how the widget is anchored to its parent
				};
			};
			
			struct ArgUnsignedShort
			{
				enum eArgUnsignedShort
				{
					bevel_width = Pt_ARG_BEVEL_WIDTH, //The width of the widget's bevel if the widget is highlighted and is to draw a bevel
					cursor_type = Pt_ARG_CURSOR_TYPE, //The type of cursor
					height = Pt_ARG_HEIGHT,
					width = Pt_ARG_WIDTH
				};
			};
			
			struct ArgUnsignedLong
			{
				enum eArgUnsignedLong
				{
					eflags = Pt_ARG_EFLAGS
				};
			};
			
			struct ArgLong
			{
				enum eArgLong
				{
					flags = Pt_ARG_FLAGS
				};
			};

			struct ArgPChar
			{
				enum eArgPChar
				{
					help_topic = Pt_ARG_HELP_TOPIC
				};
			};
			
			struct ArgPVoid
			{
				enum eArgPVoid
				{
					pointer = Pt_ARG_POINTER,
					layout_data = Pt_ARG_LAYOUT_DATA,
					data = Pt_ARG_DATA, //This resource is used internally by PhAB applications as well as by compound widgets
					user_data = Pt_ARG_USER_DATA
				};
			};

			struct ArgRect
			{
				enum eArgRect
				{
					enchor_offsets = Pt_ARG_ANCHOR_OFFSETS, //The four values in this PhRect_t structure (see the Photon Library Reference) determine the anchor offsets of each of the widget's sides. (An anchor offset is the distance between the anchoring side of the parent and corresponding side of the child.) 
					extent = Pt_ARG_EXTENT
				};
			};
			
			struct ArgColor
			{
				enum eArgColor
				{
					cursor_color = Pt_ARG_CURSOR_COLOR //The color of the pointer when it's inside the widget
				};	
			};
			
			struct ArgPCursorDef
			{
				enum eArgPCursorDef
				{
					bitmap_cursor = Pt_ARG_BITMAP_CURSOR //Defines bitmaps for the cursor when the cursor type (Pt_ARG_CURSOR_TYPE) is set to Ph_CURSOR_BITMAP. 
				};
			};
			
			struct ArgPGridLayoutData
			{
				enum eArgPGridLayoutData
				{
					grid_layout_data = Pt_ARG_GRID_LAYOUT_DATA
				};
			};
			
			struct ArgPoint
			{
				enum eArgPoint
				{
					pos = Pt_ARG_POS
				};
			};

			struct ArgPRowLayoutData
			{
				enum eArgPRowLayoutData
				{
					row_layout_data = Pt_ARG_ROW_LAYOUT_DATA
				};
			};

			struct ArgDim
			{
				enum eArgDim
				{
					dim = Pt_ARG_DIM //A PhDim_t structure (see the Photon Library Reference) that defines the height and width values for the widget
				};
			};
		};

		struct ThisCallbacks
		{
			struct RawCallback
			{
				enum eRawCallback
				{
					filter = Pt_CB_FILTER,
					raw = Pt_CB_RAW

				};
			};

			struct Callback
			{
				enum eCallback
				{
					blocked = Pt_CB_BLOCKED, 
					destroyed = Pt_CB_DESTROYED,
					dnd = Pt_CB_DND,
					is_destroyed = Pt_CB_IS_DESTROYED,
					outbound = Pt_CB_OUTBOUND,
					realized = Pt_CB_REALIZED,
					unrealized = Pt_CB_UNREALIZED
				};
			};

			struct HotkeyCallback
			{
				enum eHotkeyCallback
				{
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
		
		void setWidth(unsigned short);
		unsigned short getWidth() const;
		
		void setHeight(unsigned short);
		unsigned short getHeight() const;

		void setDim(PhDim_t);
		PhDim_t getDim() const;
		
		void setBevelWidth(unsigned short);
		unsigned short getBevelWidth() const;
		
		void setHelpTopic(std::string);
		std::string getHelpTopic() const;
		
		void setLocation(PhPoint_t);
		PhPoint_t getLocation() const;

		void onEvent(PtCallbackList_t *cl, PtCallbackInfo_t * info);
						
	public:
		
		Widget(int abn);
		Widget(PtWidget_t *wdg);
		
		Widget(const Widget &rhs);
		
		Widget &operator=(const Widget &rhs);
		bool operator==(const Widget &rhs);
		bool operator<(const Widget &rhs);	

				
		operator PtWidget_t*();
		operator const PtWidget_t*() const;

		WidgetResourcesSingleton resource;
	
		property<bool>::bind<Widget, &Widget::getEnabled, &Widget::setEnabled>					Enabled;
		property<unsigned short>::bind<Widget, &Widget::getWidth, &Widget::setWidth>			Width;
		property<unsigned short>::bind<Widget, &Widget::getHeight, &Widget::setHeight>			Height;
		property<PhDim_t>::bind<Widget, &Widget::getDim, &Widget::setDim>						Size;
		property<unsigned short>::bind<Widget, &Widget::getBevelWidth, &Widget::setBevelWidth>	BevelWidth;
		property<std::string>::bind<Widget, &Widget::getHelpTopic, &Widget::setHelpTopic>		HelpTopic;
		property<PhPoint_t>::bind<Widget, &Widget::getLocation, &Widget::setLocation>			Location;

		phwidgets_event<Widget, Widget::Callbacks::destroyed>		Destroyed;
		phwidgets_event<Widget, Widget::Callbacks::blocked>			Blocked;
		phwidgets_event<Widget, Widget::Callbacks::dnd>				DragDrop;
		phwidgets_event<Widget, Widget::Callbacks::is_destroyed>	IsDestroyed;
		phwidgets_event<Widget, Widget::Callbacks::outbound>		Outbound;
		phwidgets_event<Widget, Widget::Callbacks::realized>		Realized;
		phwidgets_event<Widget, Widget::Callbacks::unrealized>		Unrealized;

		void OnDestroyed(PtCallbackInfo_t *info);
		void OnBlocked(PtCallbackInfo_t *info);
		void OnDragDrop(PtCallbackInfo_t *info);
		void OnOutbound(PtCallbackInfo_t *info);
		void OnRealized(PtCallbackInfo_t *info);
		void OnUnrealized(PtCallbackInfo_t *info);

	};


}//namespace PhWidgets


#endif
