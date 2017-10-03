#ifndef WIDGET_RESOURCE_HPP
#define WIDGET_RESOURCE_HPP

#include <photon/PhT.h>

#include "./WidgetEvents.h"
#include "./WidgetKeys.h"

namespace PhWidgets
{
	struct WidgetResourceGroupType
	{
		struct unknown_type;

		struct WidgetArgumentGroupType
		{
			struct alloc_type;
			struct array_type;
			struct boolean_type;
			struct color_type;
			struct complex_type;
			struct flag_type;
			struct function_type;
			struct image_type;
			struct pointer_type;
			struct scalar_type;
			struct string_type;
			struct struct_type;
		};

		struct WidgetCallbackGroupType
		{
			struct callback_type;
			struct raw_type;
			struct hotkey_type;
		};


		typedef WidgetArgumentGroupType::alloc_type			alloc_type;
		typedef WidgetArgumentGroupType::array_type			array_type;
		typedef WidgetArgumentGroupType::boolean_type		boolean_type;
		typedef WidgetArgumentGroupType::color_type			color_type;
		typedef WidgetArgumentGroupType::complex_type		complex_type;
		typedef WidgetArgumentGroupType::flag_type			flag_type;
		typedef WidgetArgumentGroupType::function_type		function_type;
		typedef WidgetArgumentGroupType::image_type			image_type;
		typedef WidgetArgumentGroupType::pointer_type		pointer_type;
		typedef WidgetArgumentGroupType::scalar_type		scalar_type;
		typedef WidgetArgumentGroupType::string_type		string_type;
		typedef WidgetArgumentGroupType::struct_type		struct_type;

		typedef WidgetCallbackGroupType::callback_type		callback_type;
		typedef WidgetCallbackGroupType::raw_type			callback_raw_type;
		typedef WidgetCallbackGroupType::hotkey_type		callback_hotkey_type;
	};

	namespace detail
	{
		
		class IPtWidget
		{
			virtual PtWidget_t *widget() const = 0;
		};

		template<typename ArgT>
		class WidgetResourceBase
		{
		protected:

			ArgT _arg;
			IPtWidget *_rwidget;

			WidgetResourceBase(IPtIPtWidget *widget, ArgT arg) :
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

		template<typename ArgT, class ResourceGroupT, class ResourceT>
		struct WidgetArgument :
			private WidgetResourceBase<ArgT>
		{
			typedef WidgetResourceGroupType::unknown_type resource_group_type;

			// not impelemented
		};

		template<typename ArgT>//const void * always
		struct WidgetArgument<ArgT, WidgetResourceGroupType::WidgetArgumentGroupType::alloc_type, const void *> :
			private WidgetResourceBase<ArgT>
		{
			typedef WidgetResourceGroupType::WidgetArgumentGroupType::alloc_type resource_group_type;
			typedef const void * resource_type;

			WidgetArgument(IPtWidget *widget, ArgT arg) :
				WidgetResourceBase<ArgT>(widget, arg)
			{}

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

		template<typename ArgT>//const void * always
		struct WidgetArgument<ArgT, WidgetResourceGroupType::WidgetArgumentGroupType::alloc_type, void> :
			private WidgetResourceBase<ArgT>
		{
			typedef WidgetResourceGroupType::WidgetArgumentGroupType::alloc_type resource_group_type;
			typedef const void * resource_type;

			WidgetArgument(IPtWidget *widget, ArgT arg) :
				WidgetResourceBase<ArgT>(widget, arg)
			{}

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

		template<typename ArgT, class ResourceT>
		struct WidgetArgument<ArgT, WidgetResourceGroupType::WidgetArgumentGroupType::array_type, ResourceT> :
			private WidgetResourceBase<ArgT>
		{
			typedef WidgetResourceGroupType::WidgetArgumentGroupType::array_type resource_group_type;
			typedef ResourceT resource_type;

			// not impelemented
		};

		template<typename ArgT, class ResourceT>
		struct WidgetArgument<ArgT, WidgetResourceGroupType::WidgetArgumentGroupType::boolean_type, ResourceT> :
			private WidgetResourceBase<ArgT>
		{
			typedef WidgetResourceGroupType::WidgetArgumentGroupType::boolean_type resource_group_type;
			typedef ResourceT resource_type;

			// not impelemented
		};

		template<typename ArgT, class ResourceT>
		struct WidgetArgument<ArgT, WidgetResourceGroupType::WidgetArgumentGroupType::color_type, ResourceT> :
			private WidgetResourceBase<ArgT>
		{
			typedef WidgetResourceGroupType::WidgetArgumentGroupType::color_type resource_group_type;
			typedef ResourceT resource_type;

			WidgetArgument(IPtWidget *widget, ArgT arg) :
				WidgetResourceBase<ArgT>(widget, arg)
			{}

			~WidgetArgument()
			{}


			template<typename T>
			inline int set(T color)
			{
				return setColor(reinterpret_cast<const void*>(static_cast<PgColor_t>(color)));
			}

			inline resource_type get()
			{
				return getScalar<PgColor_t>();
			}

		};

		template<typename ArgT, class ResourceT>
		struct WidgetArgument<ArgT, WidgetResourceGroupType::WidgetArgumentGroupType::complex_type, ResourceT> :
			private WidgetResourceBase<ArgT>
		{
			typedef WidgetResourceGroupType::WidgetArgumentGroupType::complex_type resource_group_type;
			typedef ResourceT resource_type;

			// not impelemented
		};

		namespace flag_detail
		{
			template<typename T> struct mask_type { typedef long type; };
			template<> struct mask_type<bool> { typedef bool type; };
		}

		template<typename ArgT, class ResourceT>
		struct WidgetArgument<ArgT, WidgetResourceGroupType::WidgetArgumentGroupType::flag_type, ResourceT> :
			private WidgetResourceBase<ArgT>
		{
			typedef WidgetResourceGroupType::WidgetArgumentGroupType::flag_type resource_group_type;
			typedef ResourceT resource_type;

			WidgetArgument(IPtWidget *widget, ArgT arg) :
				WidgetResourceBase<ArgT>(widget, arg)
			{}

			~WidgetArgument()
			{}


			template<typename A1, typename A2>
			inline int set(A1 flag, A2 mask)
			{
				return setFlag(flag, static_cast<typename flag_detail::mask_type<A2>::type>(mask));
			}

			inline resource_type get()
			{
				return getScalar<resource_type>();
			}

			template<typename A1>
			inline bool get(A1 flag)
			{
				return ((get() & flag) == flag);
			}

		};

		template<typename ArgT, class ResourceT>
		struct WidgetArgument<ArgT, WidgetResourceGroupType::WidgetArgumentGroupType::function_type, ResourceT> :
			private WidgetResourceBase<ArgT>
		{
			typedef WidgetResourceGroupType::WidgetArgumentGroupType::function_type resource_group_type;
			typedef ResourceT resource_type;

			// not impelemented
		};

		template<typename ArgT, class ResourceT>
		struct WidgetArgument<ArgT, WidgetResourceGroupType::WidgetArgumentGroupType::image_type, ResourceT> :
			private WidgetResourceBase<ArgT>
		{
			typedef WidgetResourceGroupType::WidgetArgumentGroupType::image_type resource_group_type;
			typedef ResourceT resource_type;

			// not impelemented
		};

		template<typename ArgT, class ResourceT>
		struct WidgetArgument<ArgT, WidgetResourceGroupType::WidgetArgumentGroupType::pointer_type, ResourceT> :
			private WidgetResourceBase<ArgT>
		{
			typedef WidgetResourceGroupType::WidgetArgumentGroupType::pointer_type resource_group_type;
			typedef ResourceT resource_type;

			// not impelemented
		};

		template<typename ArgT, class ResourceT>
		struct WidgetArgument<ArgT, WidgetResourceGroupType::WidgetArgumentGroupType::scalar_type, ResourceT> :
			private WidgetResourceBase<ArgT>
		{
			typedef WidgetResourceGroupType::WidgetArgumentGroupType::scalar_type resource_group_type;
			typedef ResourceT resource_type;

			WidgetArgument(IPtWidget *widget, ArgT arg) :
				WidgetResourceBase<ArgT>(widget, arg)
			{}

			~WidgetArgument()
			{}


			template<typename T>
			inline int set(T value)
			{
				return setScalar(reinterpret_cast<const void*>(static_cast<resource_type>(value)));
			}

			inline resource_type get()
			{
				return getScalar<resource_type>();
			}
		};

		template<typename ArgT>//const char * always
		struct WidgetArgument<ArgT, WidgetResourceGroupType::WidgetArgumentGroupType::string_type, const char *> :
			private WidgetResourceBase<ArgT>
		{
			typedef WidgetResourceGroupType::WidgetArgumentGroupType::string_type resource_group_type;
			typedef const char * resource_type;

			WidgetArgument(IPtWidget *widget, ArgT arg) :
				WidgetResourceBase<ArgT>(widget, arg)
			{}

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

		template<typename ArgT>//const char * always
		struct WidgetArgument<ArgT, WidgetResourceGroupType::WidgetArgumentGroupType::string_type, void> :
			private WidgetResourceBase<ArgT>
		{
			typedef WidgetResourceGroupType::WidgetArgumentGroupType::string_type resource_group_type;
			typedef const char * resource_type;

			WidgetArgument(IPtWidget *widget, ArgT arg) :
				WidgetResourceBase<ArgT>(widget, arg)
			{}

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

		template<typename ArgT, class ResourceT>
		struct WidgetArgument<ArgT, WidgetResourceGroupType::WidgetArgumentGroupType::struct_type, ResourceT> :
			private WidgetResourceBase<ArgT>
		{
		private:
			template<typename T> struct remove_p { typedef T type; };
			template<typename T> struct remove_p<T*> { typedef T type; };

		public:
			typedef WidgetResourceGroupType::WidgetArgumentGroupType::struct_type resource_group_type;
			typedef ResourceT resource_type;

			WidgetArgument(IPtWidget *widget, ArgT arg) :
				WidgetResourceBase<ArgT>(widget, arg)
			{}

			~WidgetArgument()
			{}


			template<typename T>
			inline int set(const T &value)
			{
				return setStruct(reinterpret_cast<const void*>(&static_cast<const resource_type&>(value)));
			}

			template<typename T>
			inline int set(T *value)
			{
				return setStruct(reinterpret_cast<const void*>(static_cast<const resource_type>(value)));
			}

			inline T1 get()
			{
				typedef remove_p<resource_type>::type ret_t;
				ret_t *ptr = getStruct<ret_t>();
				return *get(ptr);
			}

		private:

			inline resource_type* get(resource_type *&ptr) { return ptr; }
			inline resource_type* get(resource_type &ptr) { return &ptr; }
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

			IPtWidget *_widget; // pointer to parent widget!!!

			WidgetArguments(IPtWidget *widget) :
				_widget(widget)
			{
			}

			~WidgetArguments()
			{
			}

			template<class ArgT, class ResourceGroupT, class ResourceT>
			inline WidgetArgument<ArgT, ResourceGroupT, ResourceT> resource(const ArgT indx) const
			{
				return WidgetArgument <ArgT, ResourceGroupT, ResourceT>(_widget, indx);
			}
		};

		template<typename LinkT, class ResourceGroupT, class ResourceT = void>
		struct WidgetCallback :
			private WidgetResourceBase<LinkT>
		{
			typedef WidgetResourceGroupType::unknown_type resource_group_type;

			// not impelemented
		};

		template<typename LinkT>
		struct WidgetCallback<LinkT, WidgetResourceGroupType::WidgetCallbackGroupType::callback_type, PtCallback_t> :
			private WidgetResourceBase<LinkT>
		{
			typedef WidgetResourceGroupType::WidgetCallbackGroupType::callback_type resource_group_type;
			typedef PtCallback_t resource_t;

			WidgetCallback(IPtWidget *widget, LinkT arg) :
				WidgetResourceBase<LinkT>(widget, arg)
			{}
				
			~WidgetCallback()
			{}
				
				
			inline void add(resource_t callback)
			{
				addLink(callback); 
			}
				
			inline void add(int(*callback)(PtWidget_t *, void *, PtCallbackInfo_t *), void *data = nullptr)
			{
				addLink(callback, data); 
			}
				
			inline void remove(resource_t callback)
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
		struct WidgetCallback<LinkT, WidgetResourceGroupType::WidgetCallbackGroupType::callback_type, void> :
			private WidgetResourceBase<LinkT>
		{
			typedef WidgetResourceGroupType::WidgetCallbackGroupType::callback_type resource_group_type;
			typedef PtCallback_t resource_t;

			WidgetCallback(IPtWidget *widget, LinkT arg) :
				WidgetResourceBase<LinkT>(widget, arg)
			{}

			~WidgetCallback()
			{}


			inline void add(resource_t callback)
			{
				addLink(callback);
			}

			inline void add(int(*callback)(PtWidget_t *, void *, PtCallbackInfo_t *), void *data = nullptr)
			{
				addLink(callback, data);
			}

			inline void remove(resource_t callback)
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
		struct WidgetCallback<LinkT, WidgetResourceGroupType::WidgetCallbackGroupType::raw_type, PtRawCallback_t> :
			private WidgetResourceBase<LinkT>
		{
			typedef WidgetResourceGroupType::WidgetCallbackGroupType::raw_type resource_group_type;
			typedef PtRawCallback_t resource_t;

			WidgetCallback(IPtWidget *widget, LinkT arg) :
				WidgetResourceBase<LinkT>(widget, arg)
			{}
			
				
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
		struct WidgetCallback<LinkT, WidgetResourceGroupType::WidgetCallbackGroupType::raw_type, void> :
			private WidgetResourceBase<LinkT>
		{
			typedef WidgetResourceGroupType::WidgetCallbackGroupType::raw_type resource_group_type;
			typedef PtRawCallback_t resource_t;

			WidgetCallback(IPtWidget *widget, LinkT arg) :
				WidgetResourceBase<LinkT>(widget, arg)
			{}


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
		struct WidgetCallback<LinkT, WidgetResourceGroupType::WidgetCallbackGroupType::hotkey_type, PtHotkeyCallback_t> :
			private WidgetResourceBase<LinkT>
		{
			typedef WidgetResourceGroupType::WidgetCallbackGroupType::hotkey_type resource_group_type;
			typedef PtHotkeyCallback_t resource_t;

			WidgetCallback(IPtWidget *widget, LinkT arg) :
				WidgetResourceBase<LinkT>(widget, arg)
			{}
				
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

		template<typename LinkT>
		struct WidgetCallback<LinkT, WidgetResourceGroupType::WidgetCallbackGroupType::hotkey_type, void> :
			private WidgetResourceBase<LinkT>
		{
			typedef WidgetResourceGroupType::WidgetCallbackGroupType::hotkey_type resource_group_type;
			typedef PtHotkeyCallback_t resource_t;

			WidgetCallback(IPtWidget *widget, LinkT arg) :
				WidgetResourceBase<LinkT>(widget, arg)
			{}

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

		class WidgetCallbacks
		{

		protected:

			IPtWidget *_widget; // pointer to parent widget!!!

			WidgetCallbacks(IPtWidget *widget) :
				_widget(widget)
			{
			}

			~WidgetCallbacks()
			{
			}

			template<class LinkT, class ResourceT>
			inline WidgetCallback<LinkT, ResourceT> resource(const LinkT indx) const
			{
				return WidgetCallback <LinkT, ResourceT>(_widget, indx);
			}

		};

		struct Void
		{
		};

		namespace detail
		{
			template<class PrevT>
			struct Next;
		}

		namespace original
		{
			template<class PrevT, class ArgT, class ResourceGroupT, class ResourceT>
			struct To
			{
				struct type :
					PrevT
				{
					using PrevT::operator [];

					inline WidgetArgument<ArgT, ResourceGroupT, ResourceT> operator [](const ArgT indx) const
					{
						return static_cast<const WidgetArguments*>(this)->resource<ArgT, ResourceGroupT, ResourceT>(indx);
					}
				};

				typedef detail::Next<type> Next;
			};

			template<class PrevT, class LinkT, class ResourceT>
			struct To<PrevT, LinkT, WidgetResourceGroupType::WidgetCallbackGroupType::callback_type, ResourceT>
			{
				struct type :
					PrevT
				{
					using PrevT::operator [];

					inline WidgetCallback<LinkT, WidgetResourceGroupType::WidgetCallbackGroupType::callback_type> operator [](const LinkT indx) const
					{
						return static_cast<const WidgetArguments*>(this)->resource<LinkT, WidgetResourceGroupType::WidgetCallbackGroupType::callback_type>(indx);
					}
				};

				typedef detail::Next<type> Next;
			};

			template<class PrevT, class LinkT, class ResourceT>
			struct To<PrevT, LinkT, WidgetResourceGroupType::WidgetCallbackGroupType::hotkey_type, ResourceT>
			{
				struct type :
					PrevT
				{
					using PrevT::operator [];

					inline WidgetCallback<LinkT, WidgetResourceGroupType::WidgetCallbackGroupType::hotkey_type> operator [](const LinkT indx) const
					{
						return static_cast<const WidgetArguments*>(this)->resource<LinkT, WidgetResourceGroupType::WidgetCallbackGroupType::hotkey_type>(indx);
					}
				};

				typedef detail::Next<type> Next;
			};

			template<class PrevT, class LinkT, class ResourceT>
			struct To<PrevT, LinkT, WidgetResourceGroupType::WidgetCallbackGroupType::raw_type, ResourceT>
			{
				struct type :
					PrevT
				{
					using PrevT::operator [];

					inline WidgetCallback<LinkT, WidgetResourceGroupType::WidgetCallbackGroupType::raw_type> operator [](const LinkT indx) const
					{
						return static_cast<const WidgetArguments*>(this)->resource<LinkT, WidgetResourceGroupType::WidgetCallbackGroupType::raw_type>(indx);
					}
				};

				typedef detail::Next<type> Next;
			};

		}

		namespace detail
		{
			template<class PrevT>
			struct Next
			{
				template<class ArgT, class ResourceGroupT, class ResourceT>
				struct To :
					original::To<PrevT, ArgT, ResourceGroupT, ResourceT>
				{

				};
			};
		}

		template<class PrevT, class ArgT, class RusourceGroupT, class ResourceT>
		struct ResourceFrom:
			original::To<PrevT, ArgT, RusourceGroupT, ResourceT>
		{

		};


		template<class ArgumentsT, class CallbacksT>
		struct DefineResourcesSingleton
		{
			def_callback::op<Callbacks::eCallback>::
			def_string::op<Arguments::ePConstChar>::
				singleton_type;

		};


	}
}

#endif // WIDGET_RESOURCE_HPP