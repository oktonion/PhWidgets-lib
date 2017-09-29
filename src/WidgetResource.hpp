#ifndef WIDGET_RESOURCE_HPP
#define WIDGET_RESOURCE_HPP

#include <photon/PhT.h>

#include "./WidgetEvents.h"
#include "./WidgetKeys.h"

namespace PhWidgets
{
	struct WidgetResourceID
	{
		enum WidgetArgumentID {
			arg_id_alloc,
			arg_id_array,
			arg_id_boolean,
			arg_id_color,
			arg_id_complex,
			arg_id_flag,
			arg_id_function,
			arg_id_image,
			arg_id_pointer,
			arg_id_scalar,
			arg_id_string,
			arg_id_struct,
			arg_id_unknown
		};

		enum WidgetLinkID {
			link_id_callback,
			link_id_raw,
			link_id_hotkey
		};
	};

	template<class ResT>
	struct ResourceID // each class should overload this for it's resources
	{
		static const WidgetResourceID::WidgetArgumentID id = WidgetResourceID::arg_id_unknown;
	};

	namespace detail
	{
		class Widget;

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

			inline int setStruct(const void *pdata)
			{
				return setPointer(pdata);
			}

			inline int setBoolean(bool val)
			{
				return PtSetResource(_rwidget->widget(), _arg, val ? 1 : 0, 0);
			}

			template<size_t count>
			inline void addLink(PtCallback_t const (&callbacks)[count])
			{
				PtAddCallbacks(_rwidget->widget(), _arg, callbacks, count);
			}

			inline void addLink(PtCallback_t callback)
			{
				PtCallback_t callbacks [] = { callback };

				addLink(callbacks);
			}

			inline void addLink(int(*callback)(PtWidget_t *, void *, PtCallbackInfo_t *), void *data = nullptr)
			{
				PtAddCallback(_rwidget->widget(), _arg, callback, data);
			}

			template<size_t count>
			inline void addLink(PtRawCallback_t const (&callbacks)[count])
			{
				PtAddEventHandlers(_rwidget->widget(), callbacks, count);
			}

			inline void addLink(PtRawCallback_t callback)
			{
				PtRawCallback_t callbacks [] = { callback };

				addLink(callbacks);
			}

			inline void addLink(int(*callback)(PtWidget_t *, void *, PtCallbackInfo_t *), Events::eEvents event, void *data = nullptr)
			{
				PtAddEventHandler(_rwidget->widget(), event, callback, data);
			}

			inline void addLink(int(*callback)(PtWidget_t *, void *, PtCallbackInfo_t *), Hotkeys::eHotkeys hotkey, KeyModes::eKeyModes keymode = KeyModes::none, bool chained = false, void *data = nullptr)
			{
				PtAddHotkeyHandler(_rwidget->widget(), hotkey, keymode, chained ? Pt_HOTKEY_CHAINED : 0, data, callback);
			}

			template<size_t count>
			inline void removeLink(PtCallback_t const (&callbacks)[count])
			{
				PtRemoveCallbacks(_rwidget->widget(), _arg, callbacks, count);
			}

			inline void removeLink(PtCallback_t callback)
			{
				PtCallback_t callbacks [] = { callback };

				removeLink(callbacks);
			}

			inline void removeLink(int(*callback)(PtWidget_t *, void *, PtCallbackInfo_t *), void *data = nullptr)
			{
				PtRemoveCallback(_rwidget->widget(), _arg, callback, data);
			}

			template<size_t count>
			inline void removeLink(PtRawCallback_t const (&callbacks)[count])
			{
				PtRemoveEventHandlers(_rwidget->widget(), callbacks, count);
			}

			inline void removeLink(PtRawCallback_t callback)
			{
				PtRawCallback_t callbacks [] = { callback };

				removeLink(callbacks);
			}

			inline void removeLink(int(*callback)(PtWidget_t *, void *, PtCallbackInfo_t *), Events::eEvents event, void *data = nullptr)
			{
				PtRemoveEventHandler(_rwidget->widget(), event, callback, data);
			}

			inline void removeLink(int(*callback)(PtWidget_t *, void *, PtCallbackInfo_t *), Hotkeys::eHotkeys hotkey, KeyModes::eKeyModes keymode = KeyModes::none, bool chained = false, void *data = nullptr)
			{
				PtRemoveHotkeyHandler(_rwidget->widget(), hotkey, keymode, chained ? Pt_HOTKEY_CHAINED : 0, data, callback);
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

			inline PtCallbackList_t *getLink() const
			{
				PtCallbackList_t *cl;

				cl = reinterpret_cast<PtCallbackList_t *>(PtGetCallbackList(_rwidget->widget(), _arg));

				return cl;
			}


		public:

			~WidgetResourceBase()
			{}
		};

		template<typename ArgT, WidgetResourceID::WidgetArgumentID ID = ResourceID<ArgT>::id>
		class WidgetArgument :
			private WidgetResourceBase<ArgT>
		{
			// not impelemented
		};

		template<typename ArgT>
		class WidgetArgument<ArgT, arg_id_alloc> :
			private WidgetResourceBase<ArgT>
		{
			friend class WidgetArguments;

			WidgetArgument(Widget *widget, ArgT arg) :
				WidgetResourceBase<ArgT>(widget, arg)
			{}

		public:

			~WidgetArgument()
			{}


			inline int set(const void *pdata, size_t size)
			{
				return setAlloc(&pdata, size);
			}

			inline int set(const void *pdata)
			{
				return setPointer(pdata);
			}

			inline const void* get()
			{
				return getAlloc<const void*>();
			}

		};

		template<typename ArgT>
		class WidgetArgument<ArgT, WidgetResourceID::arg_id_array> :
			private WidgetResourceBase<ArgT>
		{
			// not impelemented
		};

		template<typename ArgT>
		class WidgetArgument<ArgT, WidgetResourceID::arg_id_boolean> :
			private WidgetResourceBase<ArgT>
		{
			// not impelemented
		};

		template<typename ArgT>
		class WidgetArgument<ArgT, WidgetResourceID::arg_id_color> :
			private WidgetResourceBase<ArgT>
		{
			friend class WidgetArguments;

			WidgetArgument(Widget *widget, ArgT arg) :
				WidgetResourceBase<ArgT>(widget, arg)
			{}

		public:

			typedef T1 argument_t;

			~WidgetArgument()
			{}


			template<typename T>
			inline int set(T color)
			{
				return setColor(reinterpret_cast<const void*>(static_cast<PgColor_t>(color)));
			}

			inline T1 get()
			{
				return getScalar<PgColor_t>();
			}

		};

		template<typename ArgT>
		class WidgetArgument<ArgT, WidgetResourceID::arg_id_complex> :
			private WidgetResourceBase<ArgT>
		{
			// not impelemented
		};

		namespace detail
		{
			template<typename T> struct mask_type { typedef long type; };
			template<> struct mask_type<bool> { typedef bool type; };
		}

		template<typename ArgT>
		class WidgetArgument<ArgT, WidgetResourceID::arg_id_flag> :
			private WidgetResourceBase<ArgT>
		{
			friend class WidgetArguments;

			WidgetArgument(Widget *widget, ArgT arg) :
				WidgetResourceBase<ArgT>(widget, arg)
			{}

		public:

			typedef T1 argument_t;

			~WidgetArgument()
			{}


			template<typename A1, typename A2>
			inline int set(A1 flag, A2 mask)
			{
				return setFlag(flag, static_cast<typename detail::mask_type<A2>::type>(mask));
			}

			inline T1 get()
			{
				return getScalar<T1>();
			}

			template<typename A1>
			inline bool get(A1 flag)
			{
				return ((get() & flag) == flag);
			}

		};

		template<typename ArgT>
		class WidgetArgument<ArgT, WidgetResourceID::arg_id_function> :
			private WidgetResourceBase<ArgT>
		{
			// not impelemented
		};

		template<typename ArgT>
		class WidgetArgument<ArgT, WidgetResourceID::arg_id_image> :
			private WidgetResourceBase<ArgT>
		{
			// not impelemented
		};

		template<typename ArgT>
		class WidgetArgument<ArgT, WidgetResourceID::arg_id_pointer> :
			private WidgetResourceBase<ArgT>
		{
			// not impelemented
		};

		template<typename ArgT>
		class WidgetArgument<ArgT, WidgetResourceID::arg_id_scalar> :
			private WidgetResourceBase<ArgT>
		{
			friend class WidgetArguments;

			WidgetArgument(Widget *widget, ArgT arg) :
				WidgetResourceBase<ArgT>(widget, arg)
			{}

		public:

			typedef T1 argument_t;

			~WidgetArgument()
			{}


			template<typename T>
			inline int set(T value)
			{
				return setScalar(reinterpret_cast<const void*>(static_cast<T1>(value)));
			}

			inline T1 get()
			{
				return getScalar<T1>();
			}
		};

		template<typename ArgT>
		class WidgetArgument<ArgT, WidgetResourceID::arg_id_string> :
			private WidgetResourceBase<ArgT>
		{
			friend class WidgetArguments;

			WidgetArgument(Widget *widget, ArgT arg) :
				WidgetResourceBase<ArgT>(widget, arg)
			{}

		public:

			typedef const char * argument_t;

			~WidgetArgument()
			{}


			inline int set(const char *str)
			{
				return setString(str);
			}

			inline const char* get()
			{
				return getString<const char*>();
			}

		};

		template<typename ArgT>
		class WidgetArgument<ArgT, WidgetResourceID::arg_id_struct> :
			private WidgetResourceBase<ArgT>
		{
			friend class WidgetArguments;

			WidgetArgument(Widget *widget, ArgT arg) :
				WidgetResourceBase<ArgT>(widget, arg)
			{}
			template<typename T> struct remove_p { typedef T type; };
			template<typename T> struct remove_p<T*> { typedef T type; };

			inline T1* get(T1 *&ptr) { return ptr; }
			inline T1* get(T1 &ptr) { return &ptr; }

		public:

			typedef T1 argument_t;

			~WidgetArgument()
			{}


			template<typename T>
			inline int set(const T &value)
			{
				return setStruct(reinterpret_cast<const void*>(&static_cast<const T1&>(value)));
			}

			template<typename T>
			inline int set(T *value)
			{
				return setStruct(reinterpret_cast<const void*>(static_cast<const T1>(value)));
			}

			inline T1 get()
			{
				typedef remove_p<T1>::type ret_t;
				ret_t *ptr = getStruct<ret_t>();
				return *get(ptr);
			}
		};

		class WidgetArguments
		{
			//friend class WidgetResourcesSingleton;			

			/*template<typename ArgT>
			static std::map<ArgT, WidgetArgument <ArgT> >  &_resources()
			{
				static std::map<ArgT, WidgetArgument <ArgT> >  resources;

				return resources;
			}*/

		protected:

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

			/*template<typename ArgT>
			inline WidgetArgument<ArgT> operator [](const ArgT indx) const
			{
				return WidgetArgument <ArgT> ( _widget, indx );
			}*/

			Widget *_widget; // pointer to parent widget!!!

			WidgetArguments(Widget *widget) :
				_widget(widget)
			{
			}

			~WidgetArguments()
			{
			}

			template<class ArgT>
			inline WidgetArgument<ArgT> resource(const ArgT indx) const
			{
				return WidgetArgument <ArgT>(_widget, indx);
			}
		};

		template<typename LinkT, WidgetResourceID::WidgetLinkID ID = ResourceID<LinkT>::id>
		class WidgetLink :
			private WidgetResourceBase<ArgT>
		{
			// not impelemented
		};

		template<typename LinkT>
		class WidgetLink<LinkT, WidgetResourceID::link_id_callback> :
			private WidgetResourceBase<ArgT>
		{
			friend class WidgetLinks; 
				
			WidgetCallback(Widget *widget, ArgT arg) :
				WidgetResourceBase<ArgT>(widget, arg)
			{}
				
		public:
				
			typedef PtCallback_t callback_t; 
				
			~WidgetCallback()
			{}
				
				
			inline void add(PtCallback_t callback)
			{
				addLink(callback); 
			}
				
			inline void add(int(*callback)(PtWidget_t *, void *, PtCallbackInfo_t *), void *data = nullptr)
			{
				addLink(callback, data); 
			}
				
			inline void remove(PtCallback_t callback)
			{
				removeLink(callback); 
			}
				
			inline void remove(int(*callback)(PtWidget_t *, void *, PtCallbackInfo_t *), void *data = nullptr)
			{
				removeLink(callback, data); 
			}
				
			inline PtCallbackList_t* get()
			{
				return getLink(); 
			}
		};

		template<typename LinkT>
		class WidgetLink<LinkT, WidgetResourceID::link_id_raw> :
			private WidgetResourceBase<ArgT>
		{
			friend class WidgetLinks; 
				
			WidgetCallback(Widget *widget, ArgT arg) :
				WidgetResourceBase<ArgT>(widget, arg)
			{}
				
		public:
				
			typedef PtRawCallback_t callback_t; 
				
			~WidgetCallback()
			{}
				
				
			inline void add(PtRawCallback_t callback)
			{
				addLink(callback); 
			}
				
			inline void add(int(*callback)(PtWidget_t *, void *, PtCallbackInfo_t *), Events::eEvents event, void *data = nullptr)
			{
				addLink(callback, event, data); 
			}
				
			inline void remove(PtRawCallback_t callback)
			{
				removeLink(callback); 
			}
				
			inline void remove(int(*callback)(PtWidget_t *, void *, PtCallbackInfo_t *), Events::eEvents event, void *data = nullptr)
			{
				removeLink(callback, event, data); 
			}
				
			inline PtCallbackList_t* get()
			{
				return getLink(); 
			}
		};

		template<typename LinkT>
		class WidgetLink<LinkT, WidgetResourceID::link_id_hotkey> :
			private WidgetResourceBase<ArgT>
		{
			friend class WidgetLinks; 
				
			WidgetCallback(Widget *widget, ArgT arg) :
				WidgetResourceBase<ArgT>(widget, arg)
			{}
				
		public:
				
			typedef PtHotkeyCallback_t callback_t; 
				
			~WidgetCallback()
			{}
				
				
			inline void add(int(*callback)(PtWidget_t *, void *, PtCallbackInfo_t *), Hotkeys::eHotkeys hotkey, KeyModes::eKeyModes keymode = KeyModes::none)
			{
				addLink(callback, hotkey, keymode); 
			}
				
			inline void remove(int(*callback)(PtWidget_t *, void *, PtCallbackInfo_t *), Hotkeys::eHotkeys hotkey, KeyModes::eKeyModes keymode = KeyModes::none)
			{
				removeLink(callback, hotkey, keymode); 
			}
				
			inline PtCallbackList_t* get()
			{
				return getLink(); 
			}
		};

		class WidgetLinks
		{

		protected:

			Widget *_widget; // pointer to parent widget!!!

			WidgetLinks(Widget *widget) :
				_widget(widget)
			{
			}

			~WidgetLinks()
			{
			}

			template<class LinkT>
			inline WidgetLink<LinkT> resource(const LinkT indx) const
			{
				return WidgetArgument <LinkT>(_widget, indx);
			}

		};
	}
}

#endif // WIDGET_RESOURCE_HPP