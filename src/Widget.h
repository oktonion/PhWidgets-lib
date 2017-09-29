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
		
	class Widget
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

		class WidgetArguments :
			detail::WidgetArguments
		{
			inline detail::WidgetArgument<ThisArgs::ArgPChar::eArgPChar> operator [](const ThisArgs::ArgPChar::eArgPChar indx) const
			{
				return resource(indx);
			}

			WidgetArguments(Widget *widget) :
				detail::WidgetArguments(widget)
			{
			}

			~WidgetArguments()
			{
			}
		};

		class WidgetLinks :
			detail::WidgetLinks
		{
			inline detail::WidgetLink<ThisArgs::ArgPChar::eArgPChar> operator [](const ThisArgs::ArgPChar::eArgPChar indx) const
			{
				return resource(indx);
			}

			WidgetLinks(Widget *widget) :
				detail::WidgetLinks(widget)
			{
			}

			~WidgetLinks()
			{
			}
		};

		class WidgetResourcesSingleton
		{	
		public:

			WidgetResourcesSingleton(Widget *widget):
				argument(WidgetArguments(widget)),
				callback(WidgetLinks(widget))
			{}

			WidgetArguments argument;
			WidgetLinks callback;

		private:
			WidgetResourcesSingleton(const WidgetResourcesSingleton &rhs);
				
		};
	
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

#define INIT_DISABLED ;


#define INIT_WIDGET_RESOURCE_Alloc(ArgT)\
	template<>\
	class Widget::WidgetResourcesSingleton::WidgetArguments::WidgetArgument<ArgT>:\
		private WidgetResourceBase<ArgT>\
	{\
		friend class WidgetArguments;\
\
		WidgetArgument(Widget *widget, ArgT arg):\
			WidgetResourceBase<ArgT>(widget, arg)\
		{}\
\
	public:\
\
		~WidgetArgument()\
		{}\
\
\
		inline int set(const void *pdata, size_t size)\
		{\
			return setAlloc(&pdata, size);\
		}\
\
		inline int set(const void *pdata)\
		{\
			return setPointer(pdata);\
		}\
\
		inline const void* get()\
		{\
			return getAlloc<const void*>();\
		}\
\
	};

#define INIT_WIDGET_RESOURCE_Array(ArgT) INIT_DISABLED
#define INIT_WIDGET_RESOURCE_Boolean(ArgT) INIT_DISABLED

#define INIT_WIDGET_RESOURCE_Color(ArgT, T1)\
	template<>\
	class Widget::WidgetResourcesSingleton::WidgetArguments::WidgetArgument<ArgT>:\
		private WidgetResourceBase<ArgT>\
	{\
		friend class WidgetArguments;\
\
		WidgetArgument(Widget *widget, ArgT arg):\
			WidgetResourceBase<ArgT>(widget, arg)\
		{}\
\
	public:\
\
		typedef T1 argument_t;\
\
		~WidgetArgument()\
		{}\
\
\
		template<typename T>\
		inline int set(T color)\
		{\
			return setColor(reinterpret_cast<const void*>(static_cast<PgColor_t>(color)));\
		}\
\
		inline T1 get()\
		{\
			return getScalar<PgColor_t>();\
		}\
\
	};
	
#define INIT_WIDGET_RESOURCE_Complex(ArgT) INIT_DISABLED

namespace detail
{
	template<typename T> struct mask_type {typedef long type;};
	template<> struct mask_type<bool> {typedef bool type;};
}

#define INIT_WIDGET_RESOURCE_Flag(ArgT, T1, T2)\
	template<>\
	class Widget::WidgetResourcesSingleton::WidgetArguments::WidgetArgument<ArgT>:\
		private WidgetResourceBase<ArgT>\
	{\
		friend class WidgetArguments;\
\
		WidgetArgument(Widget *widget, ArgT arg):\
			WidgetResourceBase<ArgT>(widget, arg)\
		{}\
\
	public:\
\
		typedef T1 argument_t;\
\
		~WidgetArgument()\
		{}\
\
\
		template<typename A1, typename A2>\
		inline int set(A1 flag, A2 mask)\
		{\
			return setFlag(flag, static_cast<typename detail::mask_type<A2>::type>(mask));\
		}\
\
		inline T1 get()\
		{\
			return getScalar<T1>();\
		}\
\
		template<typename A1>\
		inline bool get(A1 flag)\
		{\
			return ((get() & flag) == flag);\
		}\
\
	};

#define INIT_WIDGET_RESOURCE_Function(ArgT) INIT_DISABLED
#define INIT_WIDGET_RESOURCE_Image(ArgT) INIT_DISABLED

#define INIT_WIDGET_RESOURCE_Link_PtCallback_t(ArgT)\
	template<>\
	class Widget::WidgetResourcesSingleton::WidgetCallbacks::WidgetCallback<ArgT>:\
		private WidgetResourceBase<ArgT>\
	{\
		friend class WidgetCallbacks;\
\
		WidgetCallback(Widget *widget, ArgT arg):\
			WidgetResourceBase<ArgT>(widget, arg)\
		{}\
\
	public:\
\
		typedef PtCallback_t callback_t;\
\
		~WidgetCallback()\
		{}\
\
\
		inline void add(PtCallback_t callback)\
		{\
			addLink(callback);\
		}\
\
		inline void add(int(*callback)( PtWidget_t *, void *, PtCallbackInfo_t * ), void *data = nullptr)\
		{\
			addLink(callback, data);\
		}\
\
		inline void remove(PtCallback_t callback)\
		{\
			removeLink(callback);\
		}\
\
		inline void remove(int(*callback)( PtWidget_t *, void *, PtCallbackInfo_t * ), void *data = nullptr)\
		{\
			removeLink(callback, data);\
		}\
\
		inline PtCallbackList_t* get()\
		{\
			return getLink();\
		}\
	};

#define INIT_WIDGET_RESOURCE_Link_PtRawCallback_t(ArgT)\
	template<>\
	class Widget::WidgetResourcesSingleton::WidgetCallbacks::WidgetCallback<ArgT>:\
		private WidgetResourceBase<ArgT>\
	{\
		friend class WidgetCallbacks;\
\
		WidgetCallback(Widget *widget, ArgT arg):\
			WidgetResourceBase<ArgT>(widget, arg)\
		{}\
\
	public:\
\
		typedef PtRawCallback_t callback_t;\
\
		~WidgetCallback()\
		{}\
\
\
		inline void add(PtRawCallback_t callback)\
		{\
			addLink(callback);\
		}\
\
		inline void add(int(*callback)( PtWidget_t *, void *, PtCallbackInfo_t * ), Widget::Events::eEvents event, void *data = nullptr)\
		{\
			addLink(callback, event, data);\
		}\
\
		inline void remove(PtRawCallback_t callback)\
		{\
			removeLink(callback);\
		}\
\
		inline void remove(int(*callback)( PtWidget_t *, void *, PtCallbackInfo_t * ), Widget::Events::eEvents event, void *data = nullptr)\
		{\
			removeLink(callback, event, data);\
		}\
\
		inline PtCallbackList_t* get()\
		{\
			return getLink();\
		}\
	};

#define INIT_WIDGET_RESOURCE_Link_PtHotkeyCallback_t(ArgT)\
	template<>\
	class Widget::WidgetResourcesSingleton::WidgetCallbacks::WidgetCallback<ArgT>:\
		private WidgetResourceBase<ArgT>\
	{\
		friend class WidgetCallbacks;\
\
		WidgetCallback(Widget *widget, ArgT arg):\
			WidgetResourceBase<ArgT>(widget, arg)\
		{}\
\
	public:\
\
		typedef PtHotkeyCallback_t callback_t;\
\
		~WidgetCallback()\
		{}\
\
\
		inline void add(int(*callback)( PtWidget_t *, void *, PtCallbackInfo_t * ), Widget::Hotkeys::eHotkeys hotkey, Widget::KeyModes::eKeyModes keymode = Widget::KeyModes::none)\
		{\
			addLink(callback, hotkey, keymode);\
		}\
\
		inline void remove(int(*callback)( PtWidget_t *, void *, PtCallbackInfo_t * ), Widget::Hotkeys::eHotkeys hotkey, Widget::KeyModes::eKeyModes keymode = Widget::KeyModes::none)\
		{\
			removeLink(callback, hotkey, keymode);\
		}\
\
		inline PtCallbackList_t* get()\
		{\
			return getLink();\
		}\
	};

#define INIT_WIDGET_RESOURCE_Link(ArgT, T1) INIT_WIDGET_RESOURCE_Link_##T1(ArgT)


#define INIT_WIDGET_RESOURCE_Pointer(ArgT) INIT_DISABLED


#define INIT_WIDGET_RESOURCE_Scalar(ArgT, T1)\
	template<>\
	class Widget::WidgetResourcesSingleton::WidgetArguments::WidgetArgument<ArgT>:\
		private WidgetResourceBase<ArgT>\
	{\
		friend class WidgetArguments;\
\
		WidgetArgument(Widget *widget, ArgT arg):\
			WidgetResourceBase<ArgT>(widget, arg)\
		{}\
\
	public:\
\
		typedef T1 argument_t;\
\
		~WidgetArgument()\
		{}\
\
\
		template<typename T>\
		inline int set(T value)\
		{\
			return setScalar(reinterpret_cast<const void*>(static_cast<T1>(value)));\
		}\
\
		inline T1 get()\
		{\
			return getScalar<T1>();\
		}\
	};

#define INIT_WIDGET_RESOURCE_String(ArgT)\
	template<>\
	class Widget::WidgetResourcesSingleton::WidgetArguments::WidgetArgument<ArgT>:\
		private WidgetResourceBase<ArgT>\
	{\
		friend class WidgetArguments;\
\
		WidgetArgument(Widget *widget, ArgT arg):\
			WidgetResourceBase<ArgT>(widget, arg)\
		{}\
\
	public:\
\
		typedef const char * argument_t;\
\
		~WidgetArgument()\
		{}\
\
\
		inline int set(const char *str)\
		{\
			return setString(str);\
		}\
\
		inline const char* get()\
		{\
			return getString<const char*>();\
		}\
\
	};
	
#define INIT_WIDGET_RESOURCE_Struct(ArgT, T1)\
	template<>\
	class Widget::WidgetResourcesSingleton::WidgetArguments::WidgetArgument<ArgT>:\
		private WidgetResourceBase<ArgT>\
	{\
		friend class WidgetArguments;\
\
		WidgetArgument(Widget *widget, ArgT arg):\
			WidgetResourceBase<ArgT>(widget, arg)\
		{}\
		template<typename T> struct remove_p {typedef T type;};\
		template<typename T> struct remove_p<T*> {typedef T type;};\
\
		inline T1* get(T1 *&ptr) {return ptr;}\
		inline T1* get(T1 &ptr) {return &ptr;}\
\
	public:\
\
		typedef T1 argument_t;\
\
		~WidgetArgument()\
		{}\
\
\
		template<typename T>\
		inline int set(const T &value)\
		{\
			return setStruct(reinterpret_cast<const void*>(&static_cast<const T1&>(value)));\
		}\
\
		template<typename T>\
		inline int set(T *value)\
		{\
			return setStruct(reinterpret_cast<const void*>(static_cast<const T1>(value)));\
		}\
\
		inline T1 get()\
		{\
			typedef remove_p<T1>::type ret_t;\
			ret_t *ptr = getStruct<ret_t>();\
			return *get(ptr);\
		}\
	};



	#define INIT_WIDGET_RESOURCE0(ArgT, PtType) INIT_WIDGET_RESOURCE_##PtType(ArgT)
	#define INIT_WIDGET_RESOURCE1(ArgT, T1, PtType) INIT_WIDGET_RESOURCE_##PtType(ArgT, T1)
	#define INIT_WIDGET_RESOURCE2(ArgT, T1, T2, PtType) INIT_WIDGET_RESOURCE_##PtType(ArgT, T1, T2)

	INIT_WIDGET_RESOURCE0(Widget::ThisArgs::ArgPChar::eArgPChar, String);
	INIT_WIDGET_RESOURCE0(Widget::ThisArgs::ArgPVoid::eArgPVoid, Alloc);

	INIT_WIDGET_RESOURCE1(Widget::ThisArgs::ArgColor::eArgColor, PgColor_t, Color);
	INIT_WIDGET_RESOURCE1(Widget::ThisArgs::ArgPCursorDef::eArgPCursorDef, PhCursorDef_t, Struct);
	INIT_WIDGET_RESOURCE1(Widget::ThisArgs::ArgPGridLayoutData::eArgPGridLayoutData, PtGridLayoutData_t, Struct);
	INIT_WIDGET_RESOURCE1(Widget::ThisArgs::ArgPoint::eArgPoint, PhPoint_t, Struct);
	INIT_WIDGET_RESOURCE1(Widget::ThisArgs::ArgPRowLayoutData::eArgPRowLayoutData, PtRowLayoutData_t, Struct);
	INIT_WIDGET_RESOURCE1(Widget::ThisArgs::ArgArea::eArgArea, PhArea_t, Struct);
	INIT_WIDGET_RESOURCE1(Widget::ThisArgs::ArgRect::eArgRect, PhRect_t, Struct);
	INIT_WIDGET_RESOURCE1(Widget::ThisArgs::ArgUnsignedShort::eArgUnsignedShort, unsigned short, Scalar);
	INIT_WIDGET_RESOURCE1(Widget::ThisArgs::ArgDim::eArgDim, PhDim_t, Struct);
	INIT_WIDGET_RESOURCE1(Widget::ThisCallbacks::Callback::eCallback, PtCallback_t, Link);
	INIT_WIDGET_RESOURCE1(Widget::ThisCallbacks::RawCallback::eRawCallback, PtRawCallback_t, Link);
	INIT_WIDGET_RESOURCE1(Widget::ThisCallbacks::HotkeyCallback::eHotkeyCallback, PtHotkeyCallback_t, Link);

	INIT_WIDGET_RESOURCE2(Widget::ThisArgs::ArgLong::eArgLong, long, long, Flag);
	INIT_WIDGET_RESOURCE2(Widget::ThisArgs::ArgUnsignedLong::eArgUnsignedLong, unsigned long, unsigned long, Flag);
	INIT_WIDGET_RESOURCE2(Widget::ThisArgs::ArgUnsigned::eArgUnsigned, unsigned, unsigned, Flag);


	template<>
	struct ArgumentID<PhWidgets::Widget::ThisArgs::ArgPChar::eArgPChar> // each class should overload this for it's arguments
	{
		static const PhWidgets::WidgetArgumentID::eWidgetArgumentID id = PhWidgets::WidgetArgumentID::arg_id_string;
	};

}//namespace PhWidgets


#endif
