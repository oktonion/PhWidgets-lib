#ifndef WIDGET_RESOURCE_HPP
#define WIDGET_RESOURCE_HPP

#include <photon/PhT.h>
#include <photon/PtWidget.h>

#include "./service/stdex/stdex.h"
#include "./WidgetEvents.h"
#include "./WidgetKeys.h"

#include <cstddef> // std::size_t

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


		typedef WidgetArgumentGroupType::alloc_type			alloc_type; // An arbitrarily sized memory object 
		typedef WidgetArgumentGroupType::array_type			array_type; // An array 
		typedef WidgetArgumentGroupType::boolean_type		boolean_type; // A bit that's either on or off 
		typedef WidgetArgumentGroupType::color_type			color_type; // A color 
		typedef WidgetArgumentGroupType::complex_type		complex_type; // A resource that's handled in a special way; see below. 
		typedef WidgetArgumentGroupType::flag_type			flag_type; // A value in which each bit has a different meaning
		typedef WidgetArgumentGroupType::function_type		function_type; // A pointer to a function 
		typedef WidgetArgumentGroupType::image_type			image_type; // A pointer to a PhImage_t structure 
		typedef WidgetArgumentGroupType::pointer_type		pointer_type; // A pointer to an address that you specify 
		typedef WidgetArgumentGroupType::scalar_type		scalar_type; // A value that can be represented within a single long
		typedef WidgetArgumentGroupType::string_type		string_type; // A null-terminated string 
		typedef WidgetArgumentGroupType::struct_type		struct_type; // A fixed-size data type, usually a structure, float, or double

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

		template<class ArgT>
		class WidgetResourceBase
		{
		protected:

			ArgT _arg;
			IPtWidget *_rwidget;

			WidgetResourceBase(IPtWidget *widget, ArgT arg) :
				_arg(arg),
				_rwidget(widget)
			{}

			// A value that can be represented within a single long
			// When setting a scalar value, you should specify the value as the third argument to PtSetArg(). 
			// The fourth argument isn't used and should be set to 0. 
			// When you call PtSetResources(), the widget copies the scalar value into its own internal data structure.
			template<class T>
			inline
			typename
			stdex::enable_if<
				sizeof(T) <= sizeof(long), 
				int
			>::type setScalar(T scval)
			{
				return PtSetResource(_rwidget->widget(), _arg, scval, 0);
			}

			// A color
			// Same as scalar.
			inline 
			int setColor(PgColor_t color)
			{
				return setScalar(color);
			}

			// A null-terminated string
			// Setting a string value is similar to setting a scalar value; 
			// you specify the string as the third argument to the PtSetArg() macro. 
			// The fourth argument is the number of bytes to copy; 
			// if it's 0, strlen() is used to determine the length of the string. 
			// When you call PtSetResources(), the widget copies the string into its own internal data structure. 
			inline 
			int setString(const char *str)
			{
				return setScalar(str);
			}

			/*inline int setString(const wchar_t *str)
			{
			return PtSetResource(widget(), _arg, str, wcslen(str));
			}*/

			// An arbitrarily sized memory object
			// Some resources are designed to store an allocated block of memory.
			// To set this resource, pass a pointer to the data as the third argument to PtSetArg(). 
			// The fourth argument is the size of the block of memory, in bytes.
			// The widget copies the number of bytes given into its internal memory when you call PtSetResources().
			inline 
			int setAlloc(const void *pdata, std::size_t size)//pointer to data and size of data
			{
				return PtSetResource(_rwidget->widget(), _arg, pdata, size);
			}

			// Image resources are designed to store a PhImage_t structure.
			// To set this resource, create and initialize the PhImage_t structure, 
			// and pass a pointer to it as the third argument to PtSetArg(). 
			// The fourth argument is 0.
			// The widget copies the image structure (but not any memory pointed to by the PhImage_t members) into its internal memory when you call PtSetResources(). 
			inline 
			int setImage(const void *pimage)
			{
				return setAlloc(pimage, 0);
			}

			// When setting an array value, the third argument to PtSetArg() is the address of the array. 
			// The fourth argument is the number of elements in the array.
			// The widget copies the contents of the array into its own internal data structure when you call PtSetResources().
			template<class T, std::size_t count>
			inline 
			int setArray(T(&arr)[count])
			{
				return PtSetResource(_rwidget->widget(), _arg, arr, count);
			}

			inline 
			int setArray(const void *parr, std::size_t count)
			{
				return PtSetResource(_rwidget->widget(), _arg, parr, count);
			}

			// When setting a flag, the third argument to PtSetArg() is a bit field specifying the value of the bits to be set. 
			// The fourth argument is a bit mask indicating which elements of the bit field should be used.
			// When you call PtSetResources(), the widget uses the bit mask to determine which bits of its internal flag resource representation to alter. 
			// It takes the bit values from the value specified.
			inline 
			int setFlag(long flag, long bits)
			{
				return PtSetResource(_rwidget->widget(), _arg, bits, flag);
			}

			inline 
			int setFlag(long flag, bool on)
			{
				return PtSetResource(_rwidget->widget(), _arg, on ? Pt_TRUE : Pt_FALSE, flag);
			}

			// When setting a pointer resource, the pointer must be given as the third argument to PtSetArg(). 
			// The fourth argument is ignored and should be set to 0.
			// When you call PtSetResources(), the widget simply does a shallow copy of the pointer into the resource.
			// The widget doesn't make a copy of the memory referenced by the pointer; 
			// don't free the memory while the widget is still referencing it.
			// The widget copies the value of the pointer into its internal memory when you call PtSetResources(). 
			inline 
			int setPointer(const void *p)
			{
				return setScalar(p);
			}

			// When setting a struct resource, pass the address of the data as the third argument to PtSetArg(). 
			// The fourth argument isn't used and should be set to 0. 
			// The widget copies the data into its internal memory when you call PtSetResources(). 
			inline 
			int setStruct(const void *pdata)
			{
				return setScalar(pdata); // photon will make a deep copy only if argument ID is known to be struct
			}

			// When setting a Boolean value, you should specify the value as the third argument to PtSetArg(), 
			// using 0 for false, and a nonzero value for true. The fourth argument isn't used, and should be set to 0. 
			// When you call PtSetResources(), the widget clears or sets one bit in its own internal data structure depending on whether or not the value is zero. 
			inline 
			int setBoolean(bool val)
			{
				return PtSetResource(_rwidget->widget(), _arg, val ? 1 : 0, 0);
			}

			template<std::size_t count>
			inline 
			void addLink(PtCallback_t const (&callbacks)[count])
			{
				PtAddCallbacks(_rwidget->widget(), _arg, callbacks, count);
			}

			inline 
			void addLink(PtCallback_t callback)
			{
				PtCallback_t callbacks [] = { callback };

				addLink(callbacks);
			}

			inline 
			void addLink(int(*callback)(PtWidget_t *, void *, PtCallbackInfo_t *), void *data = nullptr)
			{
				PtAddCallback(_rwidget->widget(), _arg, callback, data);
			}

			template<std::size_t count>
			inline
			void addLinkBefore(PtRawCallback_t const (&callbacks)[count])
			{
				PtAddFilterCallbacks(_rwidget->widget(), callbacks, count);
			}

			template<std::size_t count>
			inline 
			void addLinkAfter(PtRawCallback_t const (&callbacks)[count])
			{
				PtAddEventHandlers(_rwidget->widget(), callbacks, count);
			}

			inline 
			void addLinkBefore(PtRawCallback_t callback)
			{
				PtRawCallback_t callbacks [] = { callback };

				addLinkBefore(callbacks);
			}

			inline 
			void addLinkAfter(PtRawCallback_t callback)
			{
				PtRawCallback_t callbacks[] = { callback };

				addLinkAfter(callbacks);
			}

			inline 
			void addLinkBefore(int(*callback)(PtWidget_t *, void *, PtCallbackInfo_t *), void *data = nullptr)
			{
				// Invoked before the event is processed by the widget. 
				// They let you perform actions based on the event before the widget sees it. 
				// They also give you the opportunity to decide if the event should be ignored, discarded, or allowed to be processed by the widget. 
				PtAddFilterCallback(_rwidget->widget(), _arg, callback, data);
			}

			inline 
			void addLinkAfter(int(*callback)(PtWidget_t *, void *, PtCallbackInfo_t *), void *data = nullptr)
			{
				// invoked after the widget has processed the event, even if the widget's class methods consume it
				PtAddEventHandler(_rwidget->widget(), _arg, callback, data); 
			}

			inline 
			void addLink(int(*callback)(PtWidget_t *, void *, PtCallbackInfo_t *), KeyModes::eKeyModes keymode = KeyModes::none, bool chained = false, void *data = nullptr)
			{
				PtAddHotkeyHandler(_rwidget->widget(), _arg, keymode, chained ? Pt_HOTKEY_CHAINED : 0, data, callback);
			}

			template<std::size_t count>
			inline 
			void removeLink(PtCallback_t const (&callbacks)[count])
			{
				PtRemoveCallbacks(_rwidget->widget(), _arg, callbacks, count);
			}

			inline 
			void removeLink(PtCallback_t callback)
			{
				PtCallback_t callbacks [] = { callback };

				removeLink(callbacks);
			}

			inline 
			void removeLink(int(*callback)(PtWidget_t *, void *, PtCallbackInfo_t *), void *data = nullptr)
			{
				PtRemoveCallback(_rwidget->widget(), _arg, callback, data);
			}

			template<std::size_t count>
			inline 
			void removeLinkBefore(PtRawCallback_t const (&callbacks)[count])
			{
				PtRemoveFilterHandlers(_rwidget->widget(), callbacks, count);
			}

			template<std::size_t count>
			inline 
			void removeLinkAfter(PtRawCallback_t const (&callbacks)[count])
			{
				PtRemoveEventHandlers(_rwidget->widget(), callbacks, count);
			}

			inline 
			void removeLinkBefore(PtRawCallback_t callback)
			{
				PtRawCallback_t callbacks [] = { callback };

				removeLinkBefore(callbacks);
			}

			inline 
			void removeLinkAfter(PtRawCallback_t callback)
			{
				PtRawCallback_t callbacks[] = { callback };

				removeLinkAfter(callbacks);
			}

			inline 
			void removeLinkBefore(int(*callback)(PtWidget_t *, void *, PtCallbackInfo_t *), void *data = nullptr)
			{
				PtRemoveFilterCallback(_rwidget->widget(), _arg, callback, data);
			}

			inline 
			void removeLinkAfter(int(*callback)(PtWidget_t *, void *, PtCallbackInfo_t *), void *data = nullptr)
			{
				PtRemoveEventHandler(_rwidget->widget(), _arg, callback, data);
			}

			inline 
			void removeLink(int(*callback)(PtWidget_t *, void *, PtCallbackInfo_t *), KeyModes::eKeyModes keymode = KeyModes::none, bool chained = false, void *data = nullptr)
			{
				PtRemoveHotkeyHandler(_rwidget->widget(), _arg, keymode, chained ? Pt_HOTKEY_CHAINED : 0, data, callback);
			}

			// The value argument to PtSetArg() is the address of a pointer of the appropriate C type.
			// len isn't used.
			// When PtGetResources() is called, 
			// the pointer specified is set to point to the same data as the widget's internal pointer. 
			// The data is external(!) to the widget; 
			// you might be able to modify it, depending on the resource. 
			template<class T>
			inline
			typename stdex::enable_if<
				stdex::is_pointer<T>::value, 
				T
			>::type getPointer() const
			{
				T value = nullptr;
				PtArg_t args[1];

				PtSetArg(&args[0], _arg, &value, 0);
				PtGetResources(_rwidget->widget(), 1, args);

				return value;
			}

			// When using the pointer method to get a scalar, array, or flag resource, 
			// the widget always gives a pointer to an internal widget data structure. 
			// In the argument list element you set up using PtSetArg(), 
			// you must provide the address of a variable to which the internal data pointer can be assigned. 
			template<class T>
			inline
			typename stdex::enable_if<
				stdex::is_pointer<T>::value == false, 
				typename stdex::remove_cv<T>::type const &
			>::type getScalar() const
			{
				return *getPointer<const T*>();
			}
 
			inline
			const char* getString() const
			{
				return getPointer<const char*>();
			}

			// If you set the value and len arguments to PtSetArg() to zero, 
			// PtGetResources() returns the resource's value (converted to long) as 0 (false) or 1 (true)
			inline 
			bool getBoolean() const
			{
				PtArg_t arg;

				PtSetArg(&arg, _arg, 0, 0);
				PtGetResources(_rwidget->widget(), 1, &arg);

				return (arg.value != 0);
			}

			// If you set the value and len arguments to PtSetArg() to zero, 
			// PtGetResources() returns the resource's value (converted to long) as Address of the data 
			template<class T>
			inline
			typename stdex::enable_if<
				stdex::is_pointer<T>::value == false, 
				const T*
			>::type getStruct() const
			{
				return getPointer<const T*>();
			}

			// The value argument to PtSetArg() is the address of a pointer of the appropriate type 
			// (the type is determined by the data given to the widget when this resource is set). 
			// The len isn't used.
			// When PtGetResources() is called, the pointer specified is set to point to the widget's internal data. 
			template<class T>
			inline
			typename stdex::enable_if<
				stdex::is_pointer<T>::value == true, 
				typename stdex::remove_cv<T>::type const
			>::type getAlloc() const
			{
				typedef typename stdex::remove_cv<T>::type type;
				return getPointer<const type>();
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

				if (!cl)
					return;

				PtWidget_t *w = _rwidget->widget();

				PtInvokeCallbackList(cl, w, info);
			}


		public:

			~WidgetResourceBase()
			{}
		};

		template<class ArgT, class ResourceGroupT, class ResourceT>
		struct WidgetArgument;

		template<class ArgT, class ResourceT> // pointer always
		struct WidgetArgument<
			ArgT, 
			typename stdex::enable_if<
				(
					stdex::is_pointer<ResourceT>::value ||
					stdex::is_void<ResourceT>::value 
				),
				WidgetResourceGroupType::alloc_type
			>::type,
			ResourceT
		> :
			private WidgetResourceBase<ArgT>
		{
			typedef WidgetResourceGroupType::WidgetArgumentGroupType::alloc_type resource_group_type;
			typedef 
			typename stdex::conditional< 
				stdex::is_void<ResourceT>::value,
				const void *,
				typename stdex::remove_cv<ResourceT>::type const // const pointer
			>::type resource_type;

			WidgetArgument(IPtWidget *widget, ArgT arg) :
				WidgetResourceBase<ArgT>(widget, arg)
			{}

			~WidgetArgument()
			{}


			inline 
			int set(resource_type pdata, std::size_t size)
			{
				return this->setAlloc(&pdata, size);
			}

			inline 
			typename stdex::enable_if<
				stdex::is_same<resource_type, const void*>::value,
				int
			>::type set(resource_type pdata)
			{
				typedef typename stdex::remove_pointer<resource_type>::type type;
				return this->setAlloc(pdata, sizeof(type));
			}

			inline 
			resource_type get() const
			{
				return WidgetResourceBase<ArgT>::template getAlloc<resource_type>();
			}

		};

		class NotImplemented
		{
			NotImplemented();
			~NotImplemented();
		};

		template<class ArgT, class ResourceT>
		struct WidgetArgument<ArgT, WidgetResourceGroupType::WidgetArgumentGroupType::array_type, ResourceT> :
			private NotImplemented//WidgetResourceBase<ArgT>
		{
			typedef WidgetResourceGroupType::WidgetArgumentGroupType::array_type resource_group_type;
			typedef ResourceT resource_type;

			// not impelemented
		};

		template<class ArgT, class ResourceT>
		struct WidgetArgument<ArgT, WidgetResourceGroupType::boolean_type, ResourceT> :
			private WidgetResourceBase<ArgT>
		{
			typedef WidgetResourceGroupType::boolean_type resource_group_type;
			typedef ResourceT resource_type;

			WidgetArgument(IPtWidget *widget, ArgT arg) :
				WidgetResourceBase<ArgT>(widget, arg)
			{}

			~WidgetArgument()
			{}

			inline
			int set(resource_type value)
			{
				return this->setBoolean(value);
			}

			inline
			resource_type get() const
			{
				return this->getBoolean();
			}
		};

		template<class ArgT, class ResourceT>
		struct WidgetArgument<ArgT, WidgetResourceGroupType::WidgetArgumentGroupType::color_type, ResourceT> :
			private WidgetResourceBase<ArgT>
		{
			typedef WidgetResourceGroupType::color_type resource_group_type;
			typedef
			typename stdex::conditional< 
				stdex::is_void<ResourceT>::value,
				PgColor_t,
				ResourceT
			>::type resource_type;

			WidgetArgument(IPtWidget *widget, ArgT arg) :
				WidgetResourceBase<ArgT>(widget, arg)
			{}

			~WidgetArgument()
			{}

			inline 
			int set(resource_type color)
			{
				return setColor(color);
			}

			inline 
			resource_type get() const
			{
				return WidgetResourceBase<ArgT>::template getScalar<PgColor_t>();
			}
		};

		template<class ArgT, class ResourceT>
		struct WidgetArgument<ArgT, WidgetResourceGroupType::WidgetArgumentGroupType::complex_type, ResourceT> :
			private NotImplemented//WidgetResourceBase<ArgT>
		{
			typedef WidgetResourceGroupType::WidgetArgumentGroupType::complex_type resource_group_type;
			typedef ResourceT resource_type;

			// not impelemented
		};

		namespace flag_detail
		{
			template<class T> struct mask_type { typedef long type; };
			template<> struct mask_type<bool> { typedef bool type; };
		}

		template<class ArgT, class ResourceT>
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


			template<class A1, typename A2>
			inline int set(A1 flag, A2 mask)
			{
				return this->setFlag(flag, static_cast<typename flag_detail::mask_type<A2>::type>(mask));
			}
			
			template<class A1>
			inline int set(A1 bitmask)
			{
				int err = this->setFlag(bitmask, true);
				if(0 != err)
					return err;
				return this->setFlag(~bitmask, false);
			}

			inline resource_type get() const
			{
				return WidgetResourceBase<ArgT>::template getScalar<resource_type>();
			}

			template<class A1>
			inline bool get(A1 flag) const
			{
				return ((get() & flag) == flag);
			}

		};

		template<class ArgT, class ResourceT>
		struct WidgetArgument<ArgT, WidgetResourceGroupType::WidgetArgumentGroupType::function_type, ResourceT> :
			private NotImplemented//WidgetResourceBase<ArgT>
		{
			typedef WidgetResourceGroupType::WidgetArgumentGroupType::function_type resource_group_type;
			typedef ResourceT resource_type;

			// not impelemented
		};

		template<class ArgT, class ResourceT>
		struct WidgetArgument<ArgT, WidgetResourceGroupType::WidgetArgumentGroupType::image_type, ResourceT> :
			private NotImplemented//WidgetResourceBase<ArgT>
		{
			typedef WidgetResourceGroupType::WidgetArgumentGroupType::image_type resource_group_type;
			typedef ResourceT resource_type;

			// not impelemented
		};

		template<class ArgT, class ResourceT>
		struct WidgetArgument<
			ArgT, 
			typename
			stdex::enable_if<
				(
					stdex::is_pointer<ResourceT>::value ||
					stdex::is_void<ResourceT>::value
				),
				WidgetResourceGroupType::pointer_type
			>::type,
			ResourceT
		> :
			private WidgetResourceBase<ArgT>
		{
			typedef WidgetResourceGroupType::pointer_type resource_group_type;
			typedef
			typename stdex::conditional< 
				stdex::is_void<ResourceT>::value,
				void *,
				ResourceT
			>::type resource_type;

			WidgetArgument(IPtWidget *widget, ArgT arg) :
				WidgetResourceBase<ArgT>(widget, arg)
			{}

			~WidgetArgument()
			{}

			inline
			int set(resource_type value)
			{
				return this->setPointer(value);
			}

			inline
			resource_type get() const
			{
				return WidgetResourceBase<ArgT>::template getPointer<resource_type>();
			}
		};

		template<class ArgT, class ResourceT>
		struct WidgetArgument<
				ArgT, 
				typename stdex::enable_if<
					sizeof(ResourceT) <= sizeof(long), // make shure that Resource type fits in long or goto basic WidgetArgument
					 WidgetResourceGroupType::scalar_type
				>::type,
				ResourceT
		> :
			private WidgetResourceBase<ArgT>
		{
			typedef WidgetResourceGroupType::WidgetArgumentGroupType::scalar_type resource_group_type;
			typedef ResourceT resource_type;

			WidgetArgument(IPtWidget *widget, ArgT arg) :
				WidgetResourceBase<ArgT>(widget, arg)
			{}

			~WidgetArgument()
			{}

			inline
			int set(resource_type value)
			{
				return this->setScalar(value);
			}

			inline
			resource_type get() const
			{
				return WidgetResourceBase<ArgT>::template getScalar<resource_type>();
			}
		};

		template<class ArgT, class ResourceT>//const char * always
		struct WidgetArgument<
				ArgT, 
				typename stdex::enable_if<
					(
						stdex::is_same<typename stdex::remove_cv<ResourceT>::type, char*>::value ||// make shure that Resource type is const char*
						stdex::is_void<ResourceT>::value // or void; if not goto basic WidgetArgument
					),
					WidgetResourceGroupType::string_type
				>::type,
				ResourceT
		> :
			private WidgetResourceBase<ArgT>
		{
			typedef WidgetResourceGroupType::string_type resource_group_type;
			typedef const char * resource_type;

			WidgetArgument(IPtWidget *widget, ArgT arg) :
				WidgetResourceBase<ArgT>(widget, arg)
			{}

			~WidgetArgument()
			{}

			inline 
			int set(resource_type str)
			{
				return this->setString(str);
			}

			inline 
			resource_type get() const
			{
				return this->getString();
			}

		};

		template<class ArgT, class ResourceT>
		struct WidgetArgument<
			ArgT, 
			typename stdex::enable_if<
				stdex::is_pointer<ResourceT>::value == false,
				WidgetResourceGroupType::struct_type
			>::type,
			ResourceT
		> :
			private WidgetResourceBase<ArgT>
		{
		public:
			typedef WidgetResourceGroupType::struct_type resource_group_type;
			typedef ResourceT resource_type;

			WidgetArgument(IPtWidget *widget, ArgT arg) :
				WidgetResourceBase<ArgT>(widget, arg)
			{}

			~WidgetArgument()
			{}


			inline 
			int set(resource_type value)
			{
				return this->setStruct(&value);
			}

			template<class T>
			inline 
			int set(const T &value)
			{
				return this->setStruct(&static_cast<const resource_type&>(value));
			}

			inline 
			const resource_type& get() const
			{
				return *WidgetResourceBase<ArgT>::template getStruct<resource_type>();
			}
		};

		struct WidgetArgumentsBase
		{
			//friend class WidgetResourcesSingleton;			

			/*template<class ArgT>
			static std::map<ArgT, WidgetArgument <ArgT> >  &_resources()
			{
				static std::map<ArgT, WidgetArgument <ArgT> >  resources;

				return resources;
			}*/

		protected:

			/*
			template<class ArgT>
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

			/*template<class ArgT>
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

		template<class LinkT, class ResourceT = PtCallback_t*>
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
		template<class LinkT>
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

		template<class LinkT>
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

		template<class EventT = Events::eEvents, class ResourceT = PtRawCallback_t*>
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

		template<class EventT = Events::eEvents, class ResourceT = PtRawCallback_t*>
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

			template<class PrevT, class LinkT, class ResourceT = void>
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

				template<class ArgT, class ResourceT = void>
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