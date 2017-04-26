#ifndef PT_WIDGET_H
#define PT_WIDGET_H

#include <photon/PtWidget.h>
#include <photon/PtContainer.h>
#include <photon/PtGridLayout.h>
#include <photon/PtRowLayout.h>

#include <map>
#include <string>

#include "./service/mystd/my_exception.h"
#include "./service/code_extensions.h"
#include "./service/property.hpp"

namespace PhWidgets
{
	using namespace cppproperties;
	
	class Widget
	{
	public:
	
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

				
	private:
	
		int _abn;
		mutable PtWidget_t *_widget;
		
		
	protected:

		template<class ParentArgs>
		struct ArgumentsEx:
			public ParentArgs
		{
		};

		class WidgetResourcesSingleton
		{
			template<typename ArgT>
			class WidgetResourceBase
			{
			protected:

				ArgT _arg;
				Widget *_rwidget;

				WidgetResourceBase(Widget *widget, ArgT arg) :
					_arg(arg),
					_rwidget(widget)
				{}

				inline int setScalar(const void *scval)
				{
					return PtSetResource(_rwidget->widget(), _arg, scval, 0);
				}

				inline int setColor(const void *color)
				{
					return setScalar(color);
				}

				inline int setString(const char *str)
				{
					return setScalar(str);
				}

				/*inline int setString(const wchar_t *str)
				{
				return PtSetResource(widget(), _arg, str, wcslen(str));
				}*/

				inline int setAlloc(const void **pdata, size_t size)//pointer to data and size of data
				{
					return PtSetResource(_rwidget->widget(), _arg, pdata, size);
				}

				inline int setImage(const void **pimage)
				{
					return setAlloc(pimage, 0);
				}

				template<typename T, size_t count>
				inline int setArray(T(&arr)[count])
				{
					return PtSetResource(_rwidget->widget(), _arg, arr, count);
				}

				inline int setArray(const void *parr, size_t count)
				{
					return PtSetResource(_rwidget->widget(), _arg, parr, count);
				}

				inline int setFlag(long flag, long bits)
				{
					return PtSetResource(_rwidget->widget(), _arg, bits, flag);
				}

				inline int setFlag(long flag, bool on)
				{
					return PtSetResource(_rwidget->widget(), _arg, on ? Pt_TRUE : Pt_FALSE, flag);
				}

				inline int setPointer(const void *p)
				{
					return setScalar(p);
				}

				inline int setLink(const void *parr, size_t num)
				{
					return PtSetResource(_rwidget->widget(), _arg, parr, num);
				}

				inline int setStruct(const void *pdata)
				{
					return setPointer(pdata);
				}

				inline int setBoolean(bool val)
				{
					return PtSetResource(_rwidget->widget(), _arg, val ? 1 : 0, 0);
				}

				template<typename T>
				inline T getScalar() const
				{
					PtArg_t arg;

					PtSetArg(&arg, _arg, 0, 0);
					PtGetResources(_rwidget->widget(), 1, &arg);

					return static_cast<T>(arg.value);
				}

				template<typename T>
				inline T getString() const
				{
					PtArg_t arg;

					PtSetArg(&arg, _arg, 0, 0);
					PtGetResources(_rwidget->widget(), 1, &arg);

					return static_cast<T>(reinterpret_cast<char*>(arg.value));
				}

				inline bool getBoolean() const
				{
					PtArg_t arg;

					PtSetArg(&arg, _arg, 0, 0);
					PtGetResources(_rwidget->widget(), 1, &arg);

					return (arg.value != 0);
				}


				template<typename T>
				inline T* getStruct() const
				{
					T *p = nullptr;
					PtArg_t arg;

					PtSetArg(&arg, _arg, &p, 0);
					PtGetResources(_rwidget->widget(), 1, &arg);

					return p;
				}


				template<typename T>
				inline T* getAlloc() const
				{
					T *p = nullptr;
					PtArg_t arg;

					PtSetArg(&arg, _arg, &p, 0);
					PtGetResources(_rwidget->widget(), 1, &arg);

					return p;
				}


			public:

				~WidgetResourceBase()
				{}
			};

			class WidgetArguments
			{
				friend class WidgetResourcesSingleton;			

				template<typename ArgT>
				class WidgetArgument:
					private WidgetResourceBase<ArgT>
				{
					friend class WidgetArguments;

					WidgetArgument(Widget *widget, ArgT arg):
						WidgetResourceBase<ArgT>(widget, arg)
					{}
					
					WidgetArgument(const WidgetArgument &rhs):
						WidgetResourceBase<ArgT>(rhs._widget, rhs._arg)
					{}


				public:
			
					~WidgetArgument()
					{}

				};

				/*template<typename ArgT>
				static std::map<ArgT, WidgetArgument <ArgT> >  &_resources()
				{
					static std::map<ArgT, WidgetArgument <ArgT> >  resources;
					
					return resources;
				}*/

				

				Widget *_widget;//pointer to parent widget!!!

				WidgetArguments(Widget *widget):
					_widget(widget) 
				{
				}
				
				~WidgetArguments() 
				{
				}
								

			public:

				/*
				template<typename ArgT>
				WidgetArgument<ArgT> &operator [](const ArgT indx) const
				{
					static std::map<ArgT, WidgetArgument <ArgT> >  &resources = _resources<ArgT>();

					if(resources.find(indx) == resources.end())
					{
						resources.insert(std::make_pair(indx, WidgetArgument <ArgT> ( _widget, indx )));
					}

					return resources.find(indx)->second;
				}
				*/
				
				template<typename ArgT>
				WidgetArgument<ArgT> operator [](const ArgT indx) const
				{
					return WidgetArgument <ArgT> ( _widget, indx );
				}

				
			};

			class WidgetCallbacks
			{
				friend class WidgetResourcesSingleton;

				template<typename ArgT>
				class WidgetCallback :
					private WidgetResourceBase<ArgT>
				{
					friend class WidgetArguments;

					WidgetCallback(Widget *widget, ArgT arg) :
						WidgetResourceBase<ArgT>(widget, arg)
					{}

					WidgetCallback(const WidgetCallback &rhs) :
						WidgetResourceBase<ArgT>(rhs._widget, rhs._arg)
					{}


				public:

					~WidgetCallback()
					{}

				};



				Widget *_widget;//pointer to parent widget!!!

				WidgetCallbacks(Widget *widget) :
					_widget(widget)
				{
				}

				~WidgetCallbacks()
				{
				}


			public:


				template<typename ArgT>
				WidgetCallback<ArgT> operator [](const ArgT indx) const
				{
					return WidgetCallback <ArgT>(_widget, indx);
				}


			};
			
		WidgetResourcesSingleton(const WidgetResourcesSingleton &rhs);

		//protected:
		public:

			WidgetResourcesSingleton(Widget *widget):
				argument(WidgetArguments(widget)),
				callback(WidgetCallbacks(widget))
			{}

			WidgetArguments argument;
			WidgetCallbacks callback;
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
						
	public:
		
		Widget(int abn);
		Widget(PtWidget_t *wdg);
		
		Widget(const Widget &rhs);
		
		Widget &operator=(const Widget &rhs);
		bool operator==(const Widget &rhs);
		bool operator<(const Widget &rhs);
		
		template<typename T, typename A1>
		inline int SetResource(T res, A1);
		
		template<typename T, typename A1, typename A2>
		inline int SetResource(T, A1, A2);
		
		template<typename T, typename A1, typename A2, typename A3>
		inline int SetResource(T, A1, A2, A3);


				
		operator PtWidget_t*();
		operator const PtWidget_t*() const;

		WidgetResourcesSingleton resource;
	
		property<bool>::bind<Widget, &Widget::getEnabled, &Widget::setEnabled> Enabled;
		property<unsigned short>::bind<Widget, &Widget::getWidth, &Widget::setWidth> Width;
		property<unsigned short>::bind<Widget, &Widget::getHeight, &Widget::setHeight> Height;
		property<PhDim_t>::bind<Widget, &Widget::getDim, &Widget::setDim> Size;
		property<unsigned short>::bind<Widget, &Widget::getBevelWidth, &Widget::setBevelWidth> BevelWidth;
		property<std::string>::bind<Widget, &Widget::getHelpTopic, &Widget::setHelpTopic> HelpTopic;
		property<PhPoint_t>::bind<Widget, &Widget::getLocation, &Widget::setLocation> Location;
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
		inline T1 get() const\
		{\
			return getScalar<T1>();\
		}\
\
		template<typename A1>\
		inline bool get(A1 flag) const\
		{\
			return ((get() & flag) == flag);\
		}\
\
	};

#define INIT_WIDGET_RESOURCE_Function(ArgT) INIT_DISABLED
#define INIT_WIDGET_RESOURCE_Image(ArgT) INIT_DISABLED
#define INIT_WIDGET_RESOURCE_Link(ArgT) INIT_DISABLED
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

	INIT_WIDGET_RESOURCE2(Widget::ThisArgs::ArgLong::eArgLong, long, long, Flag);
	INIT_WIDGET_RESOURCE2(Widget::ThisArgs::ArgUnsignedLong::eArgUnsignedLong, unsigned long, unsigned long, Flag);
	INIT_WIDGET_RESOURCE2(Widget::ThisArgs::ArgUnsigned::eArgUnsigned, unsigned, unsigned, Flag);
}//namespace PhWidgets


#endif
