#ifndef WIDGET_RESOURCE_HPP
#define WIDGET_RESOURCE_HPP

#include <photon/PhT.h>
#include <photon/PtWidget.h>

#include "./service/stdex/stdex.h"
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
		public:
			virtual PtWidget_t *widget() const = 0;
		};

		template<typename ArgT>
		class WidgetResourceBase
		{
		protected:

			ArgT _arg;
			IPtWidget *_rwidget;

			WidgetResourceBase(IPtWidget *widget, ArgT arg) :
				_arg(arg),
				_rwidget(widget)
			{}

			inline int setScalar(const void *scval)
			{
				return PtSetResource(_rwidget->widget(), _arg, scval, 0);
			}

			inline int setColor(PgColor_t color)
			{
				return setScalar(reinterpret_cast<const void*>(color));
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
			inline void addLinkBefore(PtRawCallback_t const (&callbacks)[count])
			{
				PtAddFilterCallbacks(_rwidget->widget(), callbacks, count);
			}

			template<size_t count>
			inline void addLinkAfter(PtRawCallback_t const (&callbacks)[count])
			{
				PtAddEventHandlers(_rwidget->widget(), callbacks, count);
			}

			inline void addLinkBefore(PtRawCallback_t callback)
			{
				PtRawCallback_t callbacks [] = { callback };

				addLinkBefore(callbacks);
			}

			inline void addLinkAfter(PtRawCallback_t callback)
			{
				PtRawCallback_t callbacks[] = { callback };

				addLinkAfter(callbacks);
			}

			inline void addLinkBefore(int(*callback)(PtWidget_t *, void *, PtCallbackInfo_t *), void *data = nullptr)
			{
				// Invoked before the event is processed by the widget. 
				// They let you perform actions based on the event before the widget sees it. 
				// They also give you the opportunity to decide if the event should be ignored, discarded, or allowed to be processed by the widget. 
				PtAddFilterCallback(_rwidget->widget(), _arg, callback, data);
			}

			inline void addLinkAfter(int(*callback)(PtWidget_t *, void *, PtCallbackInfo_t *), void *data = nullptr)
			{
				// invoked after the widget has processed the event, even if the widget's class methods consume it
				PtAddEventHandler(_rwidget->widget(), _arg, callback, data); 
			}

			inline void addLink(int(*callback)(PtWidget_t *, void *, PtCallbackInfo_t *), KeyModes::eKeyModes keymode = KeyModes::none, bool chained = false, void *data = nullptr)
			{
				PtAddHotkeyHandler(_rwidget->widget(), _arg, keymode, chained ? Pt_HOTKEY_CHAINED : 0, data, callback);
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
			inline void removeLinkBefore(PtRawCallback_t const (&callbacks)[count])
			{
				PtRemoveFilterHandlers(_rwidget->widget(), callbacks, count);
			}

			template<size_t count>
			inline void removeLinkAfter(PtRawCallback_t const (&callbacks)[count])
			{
				PtRemoveEventHandlers(_rwidget->widget(), callbacks, count);
			}

			inline void removeLinkBefore(PtRawCallback_t callback)
			{
				PtRawCallback_t callbacks [] = { callback };

				removeLinkBefore(callbacks);
			}

			inline void removeLinkAfter(PtRawCallback_t callback)
			{
				PtRawCallback_t callbacks[] = { callback };

				removeLinkAfter(callbacks);
			}

			inline void removeLinkBefore(int(*callback)(PtWidget_t *, void *, PtCallbackInfo_t *), void *data = nullptr)
			{
				PtRemoveFilterCallback(_rwidget->widget(), _arg, callback, data);
			}

			inline void removeLinkAfter(int(*callback)(PtWidget_t *, void *, PtCallbackInfo_t *), void *data = nullptr)
			{
				PtRemoveEventHandler(_rwidget->widget(), _arg, callback, data);
			}

			inline void removeLink(int(*callback)(PtWidget_t *, void *, PtCallbackInfo_t *), KeyModes::eKeyModes keymode = KeyModes::none, bool chained = false, void *data = nullptr)
			{
				PtRemoveHotkeyHandler(_rwidget->widget(), _arg, keymode, chained ? Pt_HOTKEY_CHAINED : 0, data, callback);
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

			inline PtRawCallbackList_t *getLinkAfter() const
			{
				PtRawCallbackList_t *cl;

				cl = reinterpret_cast<PtRawCallbackList_t *>(PtGetCallbackList(_rwidget->widget(), Pt_CB_RAW));

				return cl;
			}

			inline PtRawCallbackList_t *getLinkBefore() const
			{
				PtRawCallbackList_t *cl;

				cl = reinterpret_cast<PtRawCallbackList_t *>(PtGetCallbackList(_rwidget->widget(), Pt_CB_FILTER));

				return cl;
			}

			inline void emitLink(PtCallbackInfo_t *info) const
			{
				PtCallbackList_t *cl = this->getLink();

				if (nullptr == cl)
					return;

				PtWidget_t *w = _rwidget->widget();

				PtInvokeCallbackList(cl, w, info);
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
				return this->setAlloc(&pdata, size);
			}

			inline int set(const void *pdata)
			{
				return this->setPointer(pdata);
			}

			inline const void* get() const
			{
				//return this->getAlloc<const void>();
				return nullptr;
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
				return this->setAlloc(&pdata, size);
			}

			inline int set(const void *pdata)
			{
				return this->setPointer(pdata);
			}

			inline const void* get() const
			{
				//return this->getAlloc<const void>();
				return nullptr;
			}

		};

		class NotImplemented
		{
			NotImplemented();
			~NotImplemented();
		};

		template<typename ArgT, class ResourceT>
		struct WidgetArgument<ArgT, WidgetResourceGroupType::WidgetArgumentGroupType::array_type, ResourceT> :
			private NotImplemented//WidgetResourceBase<ArgT>
		{
			typedef WidgetResourceGroupType::WidgetArgumentGroupType::array_type resource_group_type;
			typedef ResourceT resource_type;

			// not impelemented
		};

		template<typename ArgT, class ResourceT>
		struct WidgetArgument<ArgT, WidgetResourceGroupType::WidgetArgumentGroupType::boolean_type, ResourceT> :
			private NotImplemented//WidgetResourceBase<ArgT>
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

			inline int set(resource_type color)
			{
				return this->setColor(color);
			}

			inline resource_type get() const
			{
				//return this->getScalar<PgColor_t>();
				return resource_type();
			}

		};

		template<typename ArgT>
		struct WidgetArgument<ArgT, WidgetResourceGroupType::WidgetArgumentGroupType::color_type, void> :
			private WidgetResourceBase<ArgT>
		{
			typedef WidgetResourceGroupType::WidgetArgumentGroupType::color_type resource_group_type;
			typedef PgColor_t resource_type;

			WidgetArgument(IPtWidget *widget, ArgT arg) :
				WidgetResourceBase<ArgT>(widget, arg)
			{}

			~WidgetArgument()
			{}

			inline int set(resource_type color)
			{
				return this->setColor(color);
			}

			inline resource_type get() const
			{
				//return this->getScalar<PgColor_t>();
				return resource_type();
			}

		};

		template<typename ArgT, class ResourceT>
		struct WidgetArgument<ArgT, WidgetResourceGroupType::WidgetArgumentGroupType::complex_type, ResourceT> :
			private NotImplemented//WidgetResourceBase<ArgT>
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
				return this->setFlag(flag, static_cast<typename flag_detail::mask_type<A2>::type>(mask));
			}
			
			template<typename A1>
			inline int set(A1 bitmask)
			{
				int err = this->setFlag(bitmask, true);
				if(0 != err)
					return err;
				return this->setFlag(~bitmask, false);
			}

			inline resource_type get() const
			{
				//return this->getScalar<resource_type>();
				return resource_type();
			}

			template<typename A1>
			inline bool get(A1 flag) const
			{
				return ((get() & flag) == flag);
			}

		};

		template<typename ArgT, class ResourceT>
		struct WidgetArgument<ArgT, WidgetResourceGroupType::WidgetArgumentGroupType::function_type, ResourceT> :
			private NotImplemented//WidgetResourceBase<ArgT>
		{
			typedef WidgetResourceGroupType::WidgetArgumentGroupType::function_type resource_group_type;
			typedef ResourceT resource_type;

			// not impelemented
		};

		template<typename ArgT, class ResourceT>
		struct WidgetArgument<ArgT, WidgetResourceGroupType::WidgetArgumentGroupType::image_type, ResourceT> :
			private NotImplemented//WidgetResourceBase<ArgT>
		{
			typedef WidgetResourceGroupType::WidgetArgumentGroupType::image_type resource_group_type;
			typedef ResourceT resource_type;

			// not impelemented
		};

		template<typename ArgT, class ResourceT>
		struct WidgetArgument<ArgT, WidgetResourceGroupType::WidgetArgumentGroupType::pointer_type, ResourceT> :
			private NotImplemented//WidgetResourceBase<ArgT>
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
				return this->setScalar(reinterpret_cast<const void*>(static_cast<resource_type>(value)));
			}

			inline resource_type get() const
			{
				//return this->getScalar<resource_type>();
				return resource_type();
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
				return this->setString(str);
			}

			inline const char* get() const
			{
				//return this->getString<const char*>();
				return nullptr;
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
				return this->setString(str);
			}

			inline const char* get() const
			{
				//return this->getString<const char*>();
				return nullptr;
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
				return this->setStruct(reinterpret_cast<const void*>(&static_cast<const resource_type&>(value)));
			}

			template<typename T>
			inline int set(T *value)
			{
				return this->setStruct(reinterpret_cast<const void*>(static_cast<const resource_type>(value)));
			}

			inline resource_type get() const
			{
				//typedef remove_p<resource_type>::type ret_t;
				
				//ret_t *ptr = this->getStruct<ret_t>();
				//return *get(ptr);
				
				return resource_type();
			}

		private:

			inline resource_type* get(resource_type *&ptr) { return ptr; }
			inline resource_type* get(resource_type &ptr) { return &ptr; }
		};

		struct WidgetArgumentsBase
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

			WidgetArgumentsBase(IPtWidget *widget) :
				_widget(widget)
			{
			}

			~WidgetArgumentsBase()
			{
			}

		public:

			template<class ArgT, class ResourceGroupT, class ResourceT>
			inline WidgetArgument<ArgT, ResourceGroupT, ResourceT> resource(const ArgT indx) const
			{
				return WidgetArgument <ArgT, ResourceGroupT, ResourceT>(_widget, indx);
			}
		};

		template<typename LinkT, class ResourceT = PtCallback_t*>
		struct WidgetCallback :
			private WidgetResourceBase<LinkT>
		{
			typedef WidgetResourceGroupType::WidgetCallbackGroupType::callback_type resource_group_type;
			typedef ResourceT resource_type;

			WidgetCallback(IPtWidget *widget, LinkT arg) :
				WidgetResourceBase<LinkT>(widget, arg)
			{}

			~WidgetCallback()
			{}


			inline void add(resource_type callback)
			{
				this->addLink(callback);
			}

			inline void add(int(*callback)(PtWidget_t *, void *, PtCallbackInfo_t *), void *data = nullptr)
			{
				this->addLink(callback, data);
			}

			inline void remove(resource_type callback)
			{
				this->removeLink(callback);
			}

			inline void remove(int(*callback)(PtWidget_t *, void *, PtCallbackInfo_t *), void *data = nullptr)
			{
				this->removeLink(callback, data);
			}

			inline PtCallbackList_t* get() const
			{
				return this->getLink();
			}

			inline void raise(PtCallbackInfo_t * info) const
			{
				this->emitLink(info);
			}
		};

		/*
		template<typename LinkT>
		struct WidgetCallback<LinkT, WidgetResourceGroupType::WidgetCallbackGroupType::hotkey_type, PtHotkeyCallback_t*> :
			private WidgetResourceBase<LinkT>
		{
			typedef WidgetResourceGroupType::WidgetCallbackGroupType::hotkey_type resource_group_type;
			typedef PtHotkeyCallback_t* resource_type;

			WidgetCallback(IPtWidget *widget, LinkT arg) :
				WidgetResourceBase<LinkT>(widget, arg)
			{}
				
			~WidgetCallback()
			{}
				
				
			inline void add(int(*callback)(PtWidget_t *, void *, PtCallbackInfo_t *), Hotkeys::eHotkeys hotkey, KeyModes::eKeyModes keymode = KeyModes::none)
			{
				this->addLink(callback, hotkey, keymode); 
			}
				
			inline void remove(int(*callback)(PtWidget_t *, void *, PtCallbackInfo_t *), Hotkeys::eHotkeys hotkey, KeyModes::eKeyModes keymode = KeyModes::none)
			{
				this->removeLink(callback, hotkey, keymode); 
			}
				
			inline PtCallbackList_t* get() const
			{
				return this->getLink(); 
			}

			inline void raise(PtCallbackInfo_t * info) const
			{
				this->emitLink(info);
			}
		};

		template<typename LinkT>
		struct WidgetCallback<LinkT, WidgetResourceGroupType::WidgetCallbackGroupType::hotkey_type, void> :
			private WidgetResourceBase<LinkT>
		{
			typedef WidgetResourceGroupType::WidgetCallbackGroupType::hotkey_type resource_group_type;
			typedef PtHotkeyCallback_t* resource_type;

			WidgetCallback(IPtWidget *widget, LinkT arg) :
				WidgetResourceBase<LinkT>(widget, arg)
			{}

			~WidgetCallback()
			{}


			inline void add(int(*callback)(PtWidget_t *, void *, PtCallbackInfo_t *), Hotkeys::eHotkeys hotkey, KeyModes::eKeyModes keymode = KeyModes::none)
			{
				this->addLink(callback, hotkey, keymode);
			}

			inline void remove(int(*callback)(PtWidget_t *, void *, PtCallbackInfo_t *), Hotkeys::eHotkeys hotkey, KeyModes::eKeyModes keymode = KeyModes::none)
			{
				this->removeLink(callback, hotkey, keymode);
			}

			inline PtCallbackList_t* get() const
			{
				return this->getLink();
			}

			inline void raise(PtCallbackInfo_t * info) const
			{
				this->emitLink(info);
			}
		};
		*/

		struct WidgetCallbacksBase
		{

		protected:

			IPtWidget *_widget; // pointer to parent widget!!!

			WidgetCallbacksBase(IPtWidget *widget) :
				_widget(widget)
			{
			}

			~WidgetCallbacksBase()
			{
			}
		
		public:
			template<class LinkT, class ResourceT>
			inline WidgetCallback<LinkT, ResourceT> resource(const LinkT indx) const
			{
				return WidgetCallback <LinkT, ResourceT>(_widget, indx);
			}

		};

		template<typename EventT = Events::eEvents, class ResourceT = PtRawCallback_t*>
		struct WidgetRawCallback:
			private WidgetResourceBase<EventT>
		{
			typedef WidgetResourceGroupType::WidgetCallbackGroupType::raw_type resource_group_type;
			typedef ResourceT resource_type;

			WidgetRawCallback(IPtWidget *widget, EventT arg) :
				WidgetResourceBase<EventT>(widget, arg)
			{}
			
				
			~WidgetRawCallback()
			{}
				
				
			inline void add(resource_type callback)
			{
				this->addLinkAfter(callback); 
			}
				
			inline void add(int(*callback)(PtWidget_t *, void *, PtCallbackInfo_t *), void *data = nullptr)
			{
				this->addLinkAfter(callback, data); 
			}
				
			inline void remove(resource_type callback)
			{
				this->removeLinkAfter(callback); 
			}
				
			inline void remove(int(*callback)(PtWidget_t *, void *, PtCallbackInfo_t *), void *data = nullptr)
			{
				this->removeLinkAfter(callback, data); 
			}
				
			inline PtRawCallbackList_t* get() const
			{
				return this->getLinkAfter(); 
			}

			// can't raise this type of callbacks
		};

		struct WidgetRawCallbacksBase
		{

		protected:

			IPtWidget *_widget; // pointer to parent widget!!!

			WidgetRawCallbacksBase(IPtWidget *widget) :
				_widget(widget)
			{
			}

			~WidgetRawCallbacksBase()
			{
			}
		
		public:
			template<class EventT, class ResourceT>
			inline WidgetRawCallback<EventT, ResourceT> resource(const EventT indx) const
			{
				return WidgetRawCallback <EventT, ResourceT>(_widget, indx);
			}

		};

		template<typename EventT = Events::eEvents, class ResourceT = PtRawCallback_t*>
		struct WidgetFilterCallback:
			private WidgetResourceBase<EventT>
		{
			typedef WidgetResourceGroupType::WidgetCallbackGroupType::raw_type resource_group_type;
			typedef ResourceT resource_type;

			WidgetFilterCallback(IPtWidget *widget, EventT arg) :
				WidgetResourceBase<EventT>(widget, arg)
			{}
			
				
			~WidgetFilterCallback()
			{}
				
				
			inline void add(resource_type callback)
			{
				this->addLinkAfter(callback); 
			}
				
			inline void add(int(*callback)(PtWidget_t *, void *, PtCallbackInfo_t *), void *data = nullptr)
			{
				this->addLinkBefore(callback, data); 
			}
				
			inline void remove(resource_type callback)
			{
				this->removeLinkBefore(callback); 
			}
				
			inline void remove(int(*callback)(PtWidget_t *, void *, PtCallbackInfo_t *), void *data = nullptr)
			{
				this->removeLinkBefore(callback, data); 
			}
				
			inline PtRawCallbackList_t* get() const
			{
				return this->getLinkBefore(); 
			}

			// can't raise this type of callbacks
		};

		struct WidgetFilterCallbacksBase
		{

		protected:

			IPtWidget *_widget; // pointer to parent widget!!!

			WidgetFilterCallbacksBase(IPtWidget *widget) :
				_widget(widget)
			{
			}

			~WidgetFilterCallbacksBase()
			{
			}
		
		public:
			template<class EventT, class ResourceT>
			inline WidgetFilterCallback<EventT, ResourceT> resource(const EventT indx) const
			{
				return WidgetFilterCallback <EventT, ResourceT>(_widget, indx);
			}

		};
		
		
		namespace def_help
		{
			struct BasePrevType
			{
				typedef WidgetCallbacksBase WidgetCallbacks;
				typedef WidgetArgumentsBase WidgetArguments;
			};


			template<class PrevT>
			struct Define;
		}

		namespace def_orig
		{
			template< class WidgetArgumentsT, class WidgetCallbacksT, class LinkT, class ResourceT >
			struct LinkType
			{
				struct WidgetCallbacks :
					public WidgetCallbacksT

				{
					using WidgetCallbacksT::operator [];

					inline WidgetCallback<LinkT, ResourceT> operator [](const LinkT indx) const
					{
						typedef WidgetCallbacksBase Base; 
						
						return static_cast<const Base*>(this)->resource<LinkT, ResourceT>(indx);
					}

				protected:


					friend class LinkType<WidgetArgumentsT, WidgetCallbacksT, LinkT, ResourceT>;

					template<class, class, class, class, class>
					friend class ArgumentType;

					WidgetCallbacks(IPtWidget *widget) :
						WidgetCallbacksT(widget)
					{
					}

					~WidgetCallbacks()
					{
					}
				};

				typedef WidgetArgumentsT WidgetArguments;

				WidgetArguments argument;
				WidgetCallbacks callback;

				LinkType(IPtWidget *widget) :
					argument(widget),
					callback(widget)
				{}


			private:
				LinkType(const LinkType&);
			};

			template< class WidgetArgumentsT, class LinkT, class ResourceT >
			struct LinkType<WidgetArgumentsT, WidgetCallbacksBase, LinkT, ResourceT>
			{
				struct WidgetCallbacks:
					protected WidgetCallbacksBase
				{

					inline WidgetCallback<LinkT, ResourceT> operator [](const LinkT indx) const
					{
						typedef WidgetCallbacksBase Base; 
						
						return static_cast<const Base*>(this)->resource<LinkT, ResourceT>(indx);
					}

				protected:

					friend class LinkType<WidgetArgumentsT, WidgetCallbacksBase, LinkT, ResourceT>;

					template<class, class, class, class, class>
					friend class ArgumentType;

					WidgetCallbacks(IPtWidget *widget) :
						WidgetCallbacksBase(widget)
					{
					}

					~WidgetCallbacks()
					{
					}
				};

				typedef WidgetArgumentsT WidgetArguments;

				WidgetArguments argument;
				WidgetCallbacks callback;

				LinkType(IPtWidget *widget) :
					argument(widget),
					callback(widget)
				{}


			private:
				LinkType(const LinkType&);
			};

			template< class WidgetCallbacksT, class LinkT, class ResourceT >
			struct LinkType<WidgetArgumentsBase, WidgetCallbacksT, LinkT, ResourceT>
			{
				struct WidgetCallbacks :
					public WidgetCallbacksT

				{
					using WidgetCallbacksT::operator [];

					inline WidgetCallback<LinkT, ResourceT> operator [](const LinkT indx) const
					{
						typedef WidgetCallbacksBase Base; 
						
						return static_cast<const Base*>(this)->resource<LinkT, ResourceT>(indx);
					}

				protected:

					friend class LinkType<WidgetArgumentsBase, WidgetCallbacksT, LinkT, ResourceT>;

					template<class, class, class, class, class>
					friend class ArgumentType;

					WidgetCallbacks(IPtWidget *widget) :
						WidgetCallbacksT(widget)
					{
					}

					~WidgetCallbacks()
					{
					}
				};

				typedef WidgetArgumentsBase WidgetArguments;

				WidgetCallbacks callback;

				LinkType(IPtWidget *widget) :
					callback(widget)
				{}


			private:
				LinkType(const LinkType&);
			};

			template< class LinkT, class ResourceT >
			struct LinkType<WidgetArgumentsBase, WidgetCallbacksBase, LinkT, ResourceT>
			{
				struct WidgetCallbacks:
					protected WidgetCallbacksBase
				{

					inline WidgetCallback<LinkT, ResourceT> operator [](const LinkT indx) const
					{
						typedef WidgetCallbacksBase Base; 
						
						return static_cast<const Base*>(this)->resource<LinkT, ResourceT>(indx);
					}

				protected:

					friend class LinkType<WidgetArgumentsBase, WidgetCallbacksBase, LinkT, ResourceT>;

					template<class, class, class, class, class>
					friend class ArgumentType;

					WidgetCallbacks(IPtWidget *widget) :
						WidgetCallbacksBase(widget)
					{
					}

					~WidgetCallbacks()
					{
					}
				};

				typedef WidgetArgumentsBase WidgetArguments;

				WidgetCallbacks callback;

				LinkType(IPtWidget *widget) :
					callback(widget)
				{}


			private:
				LinkType(const LinkType&);
			};



			template< class WidgetArgumentsT, class WidgetCallbacksT, class ArgT, class ResourceGroupT, class ResourceT >
			struct ArgumentType
			{
				struct WidgetArguments :
					public WidgetArgumentsT

				{
					using WidgetArgumentsT::operator [];

					inline WidgetArgument<ArgT, ResourceGroupT, ResourceT> operator [](const ArgT indx) const
					{
						typedef WidgetArgumentsBase Base; 
						
						return static_cast<const Base*>(this)->resource<ArgT, ResourceGroupT, ResourceT>(indx);
					}

				protected:

					friend class ArgumentType<WidgetArgumentsT, WidgetCallbacksT, ArgT, ResourceGroupT, ResourceT>;

					template<class, class, class, class>
					friend class LinkType;

					WidgetArguments(IPtWidget *widget) :
						WidgetArgumentsT(widget)
					{
					}

					~WidgetArguments()
					{
					}
				};

				typedef WidgetCallbacksT WidgetCallbacks;

				WidgetArguments argument;
				WidgetCallbacks callback;

				ArgumentType(IPtWidget *widget) :
					argument(widget),
					callback(widget)
				{}


			private:
				ArgumentType(const ArgumentType&);
			};

			template< class WidgetCallbacksT, class ArgT, class ResourceGroupT, class ResourceT >
			struct ArgumentType<WidgetArgumentsBase, WidgetCallbacksT, ArgT, ResourceGroupT, ResourceT>
			{
				struct WidgetArguments:
					protected WidgetArgumentsBase
				{
					inline WidgetArgument<ArgT, ResourceGroupT, ResourceT> operator [](const ArgT indx) const
					{
						typedef WidgetArgumentsBase Base; 
						
						return static_cast<const Base*>(this)->resource<ArgT, ResourceGroupT, ResourceT>(indx);
					}

				protected:

					friend class ArgumentType<WidgetArgumentsBase, WidgetCallbacksT, ArgT, ResourceGroupT, ResourceT>;

					template<class, class, class, class>
					friend class LinkType;

					WidgetArguments(IPtWidget *widget) :
						WidgetArgumentsBase(widget)
					{
					}

					~WidgetArguments()
					{
					}
				};

				typedef WidgetCallbacksT WidgetCallbacks;

				WidgetArguments argument;
				WidgetCallbacks callback;

				ArgumentType(IPtWidget *widget) :
					argument(widget),
					callback(widget)
				{}


			private:
				ArgumentType(const ArgumentType&);
			};

			template< class WidgetArgumentsT, class ArgT, class ResourceGroupT, class ResourceT >
			struct ArgumentType<WidgetArgumentsT, WidgetCallbacksBase, ArgT, ResourceGroupT, ResourceT>
			{
				struct WidgetArguments :
					public WidgetArgumentsT

				{
					using WidgetArgumentsT::operator [];

					inline WidgetArgument<ArgT, ResourceGroupT, ResourceT> operator [](const ArgT indx) const
					{
						typedef WidgetArgumentsBase Base; 
						
						return static_cast<const Base*>(this)->resource<ArgT, ResourceGroupT, ResourceT>(indx);
					}

				protected:

					friend class ArgumentType<WidgetArgumentsT, WidgetCallbacksBase, ArgT, ResourceGroupT, ResourceT>;

					template<class, class, class, class>
					friend class LinkType;

					WidgetArguments(IPtWidget *widget) :
						WidgetArgumentsT(widget)
					{
					}

					~WidgetArguments()
					{
					}
				};

				typedef WidgetCallbacksBase WidgetCallbacks;

				WidgetArguments argument;

				ArgumentType(IPtWidget *widget) :
					argument(widget)
				{}


			private:
				ArgumentType(const ArgumentType&);
			};

			template< class ArgT, class ResourceGroupT, class ResourceT >
			struct ArgumentType<WidgetArgumentsBase, WidgetCallbacksBase, ArgT, ResourceGroupT, ResourceT>
			{
				struct WidgetArguments:
					protected WidgetArgumentsBase
				{
					inline WidgetArgument<ArgT, ResourceGroupT, ResourceT> operator [](const ArgT indx) const
					{
						typedef WidgetArgumentsBase Base; 
						
						return static_cast<const Base*>(this)->resource<ArgT, ResourceGroupT, ResourceT>(indx);
					}

				protected:

					friend class ArgumentType<WidgetArgumentsBase, WidgetCallbacksBase, ArgT, ResourceGroupT, ResourceT>;

					template<class, class, class, class>
					friend class LinkType;

					WidgetArguments(IPtWidget *widget) :
						WidgetArgumentsBase(widget)
					{
					}

					~WidgetArguments()
					{
					}
				};

				typedef WidgetCallbacksBase WidgetCallbacks;

				WidgetArguments argument;

				ArgumentType(IPtWidget *widget) :
					argument(widget)
				{}


			private:
				ArgumentType(const ArgumentType&);
			};


			template<class PrevT, class LinkT, class ResourceT>
			struct Link;

			template<class PrevT, class LinkT>
			struct Link<PrevT, LinkT, PtCallback_t*>
			{
				typedef typename PrevT::WidgetCallbacks prev_widget_callbacks_type;
				typedef typename PrevT::WidgetArguments prev_widget_arguments_type;
				typedef WidgetResourceGroupType::WidgetCallbackGroupType::callback_type resource_group_type;

				typedef LinkType<prev_widget_arguments_type, prev_widget_callbacks_type, LinkT, PtCallback_t*> resource_type;
				typedef def_help::Define<resource_type> Define;
			};

			template<class PrevT, class LinkT>
			struct Link<PrevT, LinkT, PtRawCallback_t*>
			{
				typedef typename PrevT::WidgetCallbacks prev_widget_callbacks_type;
				typedef typename PrevT::WidgetArguments prev_widget_arguments_type;
				typedef WidgetResourceGroupType::WidgetCallbackGroupType::raw_type resource_group_type;

				typedef LinkType<prev_widget_arguments_type, prev_widget_callbacks_type, LinkT, PtRawCallback_t*> resource_type;
				typedef def_help::Define<resource_type> Define;
			};

			template<class PrevT, class LinkT>
			struct Link<PrevT, LinkT, PtHotkeyCallback_t*>
			{
				typedef typename PrevT::WidgetCallbacks prev_widget_callbacks_type;
				typedef typename PrevT::WidgetArguments prev_widget_arguments_type;
				typedef WidgetResourceGroupType::WidgetCallbackGroupType::hotkey_type resource_group_type;

				typedef LinkType<prev_widget_arguments_type, prev_widget_callbacks_type, LinkT, PtHotkeyCallback_t*> resource_type;
				typedef def_help::Define<resource_type> Define;
			};

			template<class PrevT, class LinkT, class ResourceT>
			struct Callback
			{
				typedef typename PrevT::WidgetCallbacks prev_widget_callbacks_type;
				typedef typename PrevT::WidgetArguments prev_widget_arguments_type;
				typedef WidgetResourceGroupType::WidgetCallbackGroupType::callback_type resource_group_type;

				typedef LinkType<prev_widget_arguments_type, prev_widget_callbacks_type, LinkT, ResourceT> resource_type;
				typedef def_help::Define<resource_type> Define;
			};

			template<class PrevT, class LinkT, class ResourceT>
			struct RawCallback
			{
				typedef typename PrevT::WidgetCallbacks prev_widget_callbacks_type;
				typedef typename PrevT::WidgetArguments prev_widget_arguments_type;
				typedef WidgetResourceGroupType::WidgetCallbackGroupType::raw_type resource_group_type;

				typedef LinkType<prev_widget_arguments_type, prev_widget_callbacks_type, LinkT, ResourceT> resource_type;
				typedef def_help::Define<resource_type> Define;
			};

			template<class PrevT, class LinkT, class ResourceT>
			struct HotKeyCallback
			{
				typedef typename PrevT::WidgetCallbacks prev_widget_callbacks_type;
				typedef typename PrevT::WidgetArguments prev_widget_arguments_type;
				typedef WidgetResourceGroupType::WidgetCallbackGroupType::hotkey_type resource_group_type;

				typedef LinkType<prev_widget_arguments_type, prev_widget_callbacks_type, LinkT, ResourceT> resource_type;
				typedef def_help::Define<resource_type> Define;
			};


			template<class PrevT, class LinkT, class ResourceT = void>
			struct Alloc
			{
				typedef typename PrevT::WidgetCallbacks prev_widget_callbacks_type;
				typedef typename PrevT::WidgetArguments prev_widget_arguments_type;
				typedef WidgetResourceGroupType::WidgetArgumentGroupType::alloc_type resource_group_type;

				typedef ArgumentType<prev_widget_arguments_type, prev_widget_callbacks_type, LinkT, resource_group_type, ResourceT> resource_type;
				typedef def_help::Define<resource_type> Define;
			};

			template<class PrevT, class LinkT, class ResourceT>
			struct Array
			{
				typedef typename PrevT::WidgetCallbacks prev_widget_callbacks_type;
				typedef typename PrevT::WidgetArguments prev_widget_arguments_type;
				typedef WidgetResourceGroupType::WidgetArgumentGroupType::array_type resource_group_type;

				typedef ArgumentType<prev_widget_arguments_type, prev_widget_callbacks_type, LinkT, resource_group_type, ResourceT> resource_type;
				typedef def_help::Define<resource_type> Define;
			};

			template<class PrevT, class LinkT, class ResourceT>
			struct Boolean
			{
				typedef typename PrevT::WidgetCallbacks prev_widget_callbacks_type;
				typedef typename PrevT::WidgetArguments prev_widget_arguments_type;
				typedef WidgetResourceGroupType::WidgetArgumentGroupType::boolean_type resource_group_type;

				typedef ArgumentType<prev_widget_arguments_type, prev_widget_callbacks_type, LinkT, resource_group_type, ResourceT> resource_type;
				typedef def_help::Define<resource_type> Define;
			};

			template<class PrevT, class LinkT, class ResourceT = void>
			struct Color
			{
				typedef typename PrevT::WidgetCallbacks prev_widget_callbacks_type;
				typedef typename PrevT::WidgetArguments prev_widget_arguments_type;
				typedef WidgetResourceGroupType::WidgetArgumentGroupType::color_type resource_group_type;

				typedef ArgumentType<prev_widget_arguments_type, prev_widget_callbacks_type, LinkT, resource_group_type, ResourceT> resource_type;
				typedef def_help::Define<resource_type> Define;
			};

			template<class PrevT, class LinkT, class ResourceT>
			struct Complex
			{
				typedef typename PrevT::WidgetCallbacks prev_widget_callbacks_type;
				typedef typename PrevT::WidgetArguments prev_widget_arguments_type;
				typedef WidgetResourceGroupType::WidgetArgumentGroupType::complex_type resource_group_type;

				typedef ArgumentType<prev_widget_arguments_type, prev_widget_callbacks_type, LinkT, resource_group_type, ResourceT> resource_type;
				typedef def_help::Define<resource_type> Define;
			};

			template<class PrevT, class LinkT, class ResourceT>
			struct Flag
			{
				typedef typename PrevT::WidgetCallbacks prev_widget_callbacks_type;
				typedef typename PrevT::WidgetArguments prev_widget_arguments_type;
				typedef WidgetResourceGroupType::WidgetArgumentGroupType::flag_type resource_group_type;

				typedef ArgumentType<prev_widget_arguments_type, prev_widget_callbacks_type, LinkT, resource_group_type, ResourceT> resource_type;
				typedef def_help::Define<resource_type> Define;
			};

			template<class PrevT, class LinkT, class ResourceT>
			struct Function
			{
				typedef typename PrevT::WidgetCallbacks prev_widget_callbacks_type;
				typedef typename PrevT::WidgetArguments prev_widget_arguments_type;
				typedef WidgetResourceGroupType::WidgetArgumentGroupType::function_type resource_group_type;

				typedef ArgumentType<prev_widget_arguments_type, prev_widget_callbacks_type, LinkT, resource_group_type, ResourceT> resource_type;
				typedef def_help::Define<resource_type> Define;
			};

			template<class PrevT, class LinkT, class ResourceT>
			struct Image
			{
				typedef typename PrevT::WidgetCallbacks prev_widget_callbacks_type;
				typedef typename PrevT::WidgetArguments prev_widget_arguments_type;
				typedef WidgetResourceGroupType::WidgetArgumentGroupType::image_type resource_group_type;

				typedef ArgumentType<prev_widget_arguments_type, prev_widget_callbacks_type, LinkT, resource_group_type, ResourceT> resource_type;
				typedef def_help::Define<resource_type> Define;
			};

			template<class PrevT, class LinkT, class ResourceT>
			struct Pointer
			{
				typedef typename PrevT::WidgetCallbacks prev_widget_callbacks_type;
				typedef typename PrevT::WidgetArguments prev_widget_arguments_type;
				typedef WidgetResourceGroupType::WidgetArgumentGroupType::pointer_type resource_group_type;

				typedef ArgumentType<prev_widget_arguments_type, prev_widget_callbacks_type, LinkT, resource_group_type, ResourceT> resource_type;
				typedef def_help::Define<resource_type> Define;
			};

			template<class PrevT, class LinkT, class ResourceT>
			struct Scalar
			{
				typedef typename PrevT::WidgetCallbacks prev_widget_callbacks_type;
				typedef typename PrevT::WidgetArguments prev_widget_arguments_type;
				typedef WidgetResourceGroupType::WidgetArgumentGroupType::scalar_type resource_group_type;

				typedef ArgumentType<prev_widget_arguments_type, prev_widget_callbacks_type, LinkT, resource_group_type, ResourceT> resource_type;
				typedef def_help::Define<resource_type> Define;
			};

			template<class PrevT, class LinkT, class ResourceT = void>
			struct String
			{
				typedef typename PrevT::WidgetCallbacks prev_widget_callbacks_type;
				typedef typename PrevT::WidgetArguments prev_widget_arguments_type;
				typedef WidgetResourceGroupType::WidgetArgumentGroupType::string_type resource_group_type;

				typedef ArgumentType<prev_widget_arguments_type, prev_widget_callbacks_type, LinkT, resource_group_type, ResourceT> resource_type;
				typedef def_help::Define<resource_type> Define;
			};

			template<class PrevT, class LinkT, class ResourceT>
			struct Struct
			{
				typedef typename PrevT::WidgetCallbacks prev_widget_callbacks_type;
				typedef typename PrevT::WidgetArguments prev_widget_arguments_type;
				typedef WidgetResourceGroupType::WidgetArgumentGroupType::struct_type resource_group_type;

				typedef ArgumentType<prev_widget_arguments_type, prev_widget_callbacks_type, LinkT, resource_group_type, ResourceT> resource_type;
				typedef def_help::Define<resource_type> Define;
			};
		}

		namespace def_help
		{
			template<class PrevT>
			struct Define
			{
				template<class LinkT, class ResourceT>
				struct Link : def_orig::Link<PrevT, LinkT, ResourceT> {};

				template<class LinkT, class ResourceT>
				struct Callback : def_orig::Callback<PrevT, LinkT, ResourceT> {};

				template<class LinkT, class ResourceT>
				struct RawCallback : def_orig::RawCallback<PrevT, LinkT, ResourceT> {};

				template<class LinkT, class ResourceT>
				struct HotKeyCallback : def_orig::HotKeyCallback<PrevT, LinkT, ResourceT> {};

				template<class ArgT, class ResourceT = void>
				struct Alloc : def_orig::Alloc<PrevT, ArgT, ResourceT> {};

				template<class ArgT, class ResourceT>
				struct Array : def_orig::Array<PrevT, ArgT, ResourceT> {};

				template<class ArgT, class ResourceT>
				struct Boolean : def_orig::Boolean<PrevT, ArgT, ResourceT> {};

				template<class ArgT, class ResourceT = void>
				struct Color : def_orig::Color<PrevT, ArgT, ResourceT> {};

				template<class ArgT, class ResourceT>
				struct Complex : def_orig::Complex<PrevT, ArgT, ResourceT> {};

				template<class ArgT, class ResourceT>
				struct Flag : def_orig::Flag<PrevT, ArgT, ResourceT> {};

				template<class ArgT, class ResourceT>
				struct Function : def_orig::Function<PrevT, ArgT, ResourceT> {};

				template<class ArgT, class ResourceT>
				struct Image : def_orig::Image<PrevT, ArgT, ResourceT> {};

				template<class ArgT, class ResourceT>
				struct Pointer : def_orig::Pointer<PrevT, ArgT, ResourceT> {};

				template<class ArgT, class ResourceT>
				struct Scalar : def_orig::Scalar<PrevT, ArgT, ResourceT> {};

				template<class ArgT, class ResourceT = void>
				struct String : def_orig::String<PrevT, ArgT, ResourceT> {};

				template<class ArgT, class ResourceT>
				struct Struct : def_orig::Struct<PrevT, ArgT, ResourceT> {};
			};
		}


		

	}

	template<class PrevT = detail::def_help::BasePrevType>
	struct ResourceFrom
	{
		struct Define :
			detail::def_help::Define<PrevT>
		{};

	};
}

#endif // WIDGET_RESOURCE_HPP