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
#include "./service/phbitmask.hpp"

#include "./WidgetResource.hpp"

//typedef Ph_rect PhRect_t;

#ifndef __QNXNTO__
	typedef struct Ph_rect   PhRect_t;
#endif

namespace PhWidgets
{
	using namespace cppproperties;
	using namespace phevents;
	using namespace cppbitmasks;

	//! Superclass for all widgets
	/*!
		Widget is the fundamental superclass. 
		All widgets belong to a subclass of Widget. 
	*/	
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
					eflags = Pt_ARG_EFLAGS //!< Extended \link Widget::ExtendedFlags flags\endlink inherited by all widgets.
				};
			};
			
			struct ArgLong
			{
				enum eArgLong
				{
					flags = Pt_ARG_FLAGS, //!< Common \link Widget::WidgetFlags flags\endlink used by all widgets. Except for those indicated as read-only, these flags are all read/write. 
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

		struct ThisFlags
		{
			struct Extended
			{
				//! Extended flags inherited by all widgets
				enum eExFlags
				{
					//! Consume any event encountered, whether or not an action was performed as a result of that event. 
					//! (When a widget has processed an event and prevents another widget from interacting with the event, the first widget is said to have consumed the event.) 
					ConsumeEvents = Pt_CONSUME_EVENTS,

					InternalHelp = Pt_INTERNAL_HELP, //!< Display help information for the widget in a balloon, not in the Helpviewer.
					//damage_parent = Pt_DAMAGE_PARENT, //!< If the widget is damaged for any reason, damage its parent instead (internal use only). 
					SkipLayout = Pt_SKIP_LAYOUT //!< Skip this widget when performing a layout. 
				};
			};

			struct Anchor
			{
				//! Anchor flags specify how the widget is anchored to its parent.
				enum eAnchorFlags
				{
					LeftAnchoredRight = Pt_LEFT_ANCHORED_RIGHT, //!< Anchor the widget's left extent to the right edge of its parent's canvas. 
					RightAnchoredRight = Pt_RIGHT_ANCHORED_RIGHT, //!< Anchor the widget's right extent to the right edge of its parent's canvas.
					TopAnchoredBottom = Pt_TOP_ANCHORED_BOTTOM, //!< Anchor the widget's top extent to the bottom edge of its parent's canvas. 
					BottomAnchoredBottom = Pt_BOTTOM_ANCHORED_BOTTOM, //!< Anchor the widget's bottom extent to the bottom edge of its parent's canvas. 
					LeftAnchoredLeft = Pt_LEFT_ANCHORED_LEFT, //!< Anchor the widget's left extent to the left edge of its parent's canvas. 
					RightAnchoredLeft = Pt_RIGHT_ANCHORED_LEFT, //!< Anchor the widget's right extent to the left edge of its parent's canvas. 
					TopAnchoredTop = Pt_TOP_ANCHORED_TOP, //!< Anchor the widget's top extent to the top edge of its parent's canvas. 
					BottomAnchoredTop = Pt_BOTTOM_ANCHORED_TOP, //!< Anchor the widget's bottom extent to the top edge of its parent's canvas. 
					BalloonsOn = Pt_BALLOONS_ON, //!< If a child widget has been assigned a balloon, pop up the balloon as soon as the pointer passes over the child widget; otherwise delay the pop up for 1.25 seconds. 

					// Visual Studio like styles:

					Bottom = BottomAnchoredBottom, //!< The widget is anchored to the bottom edge of its container.
					Left = LeftAnchoredLeft, //!<The widget is anchored to the left edge of its container.
					None = 0, //!<The widget is not anchored to any edges of its container.
					Right = RightAnchoredRight, //!<The widget is anchored to the right edge of its container.
					Top = TopAnchoredTop //!<The widget is anchored to the top edge of its container.
				};
			};

			struct Resize
			{
				//! Resize flags to control a widget's resize policy in both the x and y directions.

				//! Note that each ..._bits flag is a mask that represents all the bits of that type.
				//! The default setting of this resource is 0; that is, no resize policy is in effect.
				//! A widget's resize policy deals solely with the widget's renderable data. For a button, the data is its text; for a container, the data is its children. Any rendered data that doesn't fit within the widget's canvas is clipped.
				//! If no resize policy is in effect, the widget's size is unbounded; it may be made as large or small as specified via Pt_ARG_DIM or Pt_ARG_AREA.
				//! If a resize policy is in effect, the widget grows or shrinks to honor that policy.If the policy is ..._always, the widget resizes itself to fit its data�the dimensions specified via Pt_ARG_DIM or Pt_ARG_AREA don't apply. 
				//! If the policy is ..._as_requred, the widget resizes itself to fit its data only if its current canvas size is inadequate to contain that data. In other words, it grows, but doesn't shrink, to fit its data.
				//! If the widget has the ..._initial bit set, the resize policy is applied only once each time the widget is realized. This bit is meaningful only in concert with ..._always or ..._as_requred.
				enum eResizeFlags
				{

					ResizeX_asRequired = Pt_RESIZE_X_AS_REQUIRED,
					ResizeX_always = Pt_RESIZE_X_ALWAYS,
					ResizeX_initial = Pt_RESIZE_X_INITIAL,
					ResizeX_bits = Pt_RESIZE_X_BITS,
					ResizeY_asRequired = Pt_RESIZE_Y_AS_REQUIRED,
					ResizeY_always = Pt_RESIZE_Y_ALWAYS,
					ResizeY_initial = Pt_RESIZE_Y_INITIAL,
					ResizeY_bits = Pt_RESIZE_Y_BITS,
					ResizeXY_asRequired = Pt_RESIZE_XY_ALWAYS,
					ResizeXY_always = Pt_RESIZE_XY_AS_REQUIRED,
					ResizeXY_initial = Pt_RESIZE_XY_INITIAL,
					ResizeXY_bits = Pt_RESIZE_XY_BITS

				};
			};

			//! Common flags used by all widgets. Except for those indicated as read-only, these flags are all read/write.
			enum eFlags
			{
				
				AllButtons = Pt_ALL_BUTTONS, //!< Any pointer button can activate the widget. Default is the left button only. 
				Autohighlight = Pt_AUTOHIGHLIGHT, //!< Highlight and give focus to the widget when the cursor enters its extent, and unhighlight and remove focus when the cursor leaves. 
				Blocked = Pt_BLOCKED, //!< Prevent the widget and all its non-window-class children from interacting with Photon events. 

				//! If certain widgets have this bit set, and your application sets their resources, the relevant callbacks are invoked. 
				//! Otherwise callbacks aren't invoked when your application sets resources. If a callback refers to this flag, its description says so explicitly.
				//! For example, if this bit is set for a Divider and you use Divider::Undefined to change the size of one of its children, the Divider::DeviderDraged event is invoked. 
				CallbacksActive = Pt_CALLBACKS_ACTIVE,

				Clear = Pt_CLEAR, //!< (read-only) The widget's brothers-in-front don't intersect with its extent. 
				ClipHighlight = Pt_CLIP_HIGHLIGHT, //!< Clip the corners of the highlighting rectangle.
				Damaged = Pt_DAMAGED, //!< (read-only) The Widget requires repair. 
				DamageFamily = Pt_DAMAGE_FAMILY, //!< (read-only) The widget and all its children need to be repaired. 
				DelayRealize = Pt_DELAY_REALIZE, //!< Prevent the widget from becoming realized unless it's explicitly realized with Widget::Realized event. 
				Destroyed = Pt_DESTROYED, //!< (read-only) The widget has been marked for destruction. 
				FocusRender = Pt_FOCUS_RENDER, //!< Render a focus indicator when the widget when it gets focus. 
				GetsFocus = Pt_GETS_FOCUS, //!< Allow the widget to be granted focus. The widget needs to have this bit set if it's to receive key events. 
				Ghost = Pt_GHOST, //!< Dim the widget. Setting this flag doesn't affect the widget's behavior, just its appearance. The simplest way to disable the widget is to set the Blocked flag in this resource. 
				Highlighted = Pt_HIGHLIGHTED, //!< Allow the widget to be highlighted as defined by the Widget::BevelWidth, and the Basic::BasicFlags. 
				InFlux = Pt_IN_FLUX, //!< (read-only) A call to PtContainerHold() has been made on the widget. 
				Menuable = Pt_MENUABLE, //!< Respond to clicks on the pointer's right button (i.e. enable the Basic::MenuActivate event). 
				MenuButton = Pt_MENU_BUTTON, //!< The widget is a menu item. 
				Obscured = Pt_OBSCURED, //!< (read-only) The widget is completely covered by one other widget, or it's completely outside its parent container's canvas. 
				Opaque = Pt_OPAQUE, //!< (read-only) This widget obscures everything directly behind it (i.e. it isn't transparent). 
				Procreated = Pt_PROCREATED, //!< (read-only) The widget was created by another widget (as opposed to an application), such as the List and Text created by a ComboBox. 
				Realized = Pt_REALIZED, //!< (read-only) The widget is realized. 
				Realizing = Pt_REALIZING, //!< (read-only) The widget is in the process of being realized. 
				Region = Pt_REGION, //!< Force the widget to have a region. 
				Selectable = Pt_SELECTABLE, //!< You can select (\link Basic::Repeat repeat \endlink, \link Basic::Arm arm \endlink, \link Basic::Disarm disarm \endlink and \link Basic::Activate activate \endlink) the widget. Widgets usually provide visual feedback when selected. 
				SelectNoredraw = Pt_SELECT_NOREDRAW, //!< The widget doesn't change its appearance when set or unset. This is meaningful only when the widget is Selectable. 
				Set = Pt_SET, //!< The widget is in a �set� state. Generally, this indicates that the widget has been selected. 

				//! Pressing the pointer button on this widget causes it to toggle between being set and unset. 
				//! Normally, selectable widgets act as push buttons � they become set when you press the pointer button, and unset when you release the button. 
				Toggle = Pt_TOGGLE, 
	
				WidgetRebuild = Pt_WIDGET_REBUILD, //!< (read-only) The widget will be rebuilt(rerealized) when the widget engine is finished applying resource changes.
				WidgetResize = Pt_WIDGET_RESIZE, //!< (read-only) The widget will be resized when the widget engine is finished applying resource changes. 
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

		struct Flags:
			public ThisFlags
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
			//Define::Link<RawCallback::eRawCallback, PtRawCallback_t*>::
			//Define::Link<HotkeyCallback::eHotkeyCallback, PtHotkeyCallback_t*>::

		resource_type WidgetResourcesSingleton;
	
		PtWidget_t *widget() const;
		virtual void check();
		
		//for properties:

		void setEnabled(bool);
		bool getEnabled() const;

		void setHelpTopic(std::string);
		std::string getHelpTopic() const;

		void setLocation(PhPoint_t);
		PhPoint_t getLocation() const;

		void setBounds(PhArea_t);
		PhArea_t getBounds() const;

		short getBottom() const;

		void setLeft(short);
		short getLeft() const;

		void setTop(short);
		short getTop() const;
						
	public:
		//! (constructor) 
		/*!
			Constructs a Widget by ID.
			\param[in] abn ID given by PhAB to widget (like 'ABN_WIDGET_NAME').
		*/
		Widget(int abn);

		//! (constructor) 
		/*!
			Constructs a Widget by pointer to widget.
			\param[in] wdg pointer to Photon widget.
		*/
		Widget(PtWidget_t *wdg);

		//! (copy constructor) 
		/*!
			Constructs a Widget by copy.
			\param[in] other another Widget to be used as source to initialize the elements of the container with.
		*/
		Widget(const Widget &other);
		
		//! Assigns value in Widget 
		/*!
			Replaces the contents of the Widget.
			\param[in] other another Widget to use as data source.
		*/
		Widget &operator=(const Widget &other);

		//! Compares Widgets
		/*!
			Compares the Widgets by their Photon widget pointers.
			\param[in] other Widgets whose contents to compare.
		*/
		bool operator==(const Widget &other) const;

		//! Compares Widgets
		/*!
			Compares the Widgets by their Photon widget pointers.
			\param[in] other Widgets whose contents to compare.
		*/
		bool operator<(const Widget &other) const;

		
		//! Converts Widget to Photon widget pointer
		operator PtWidget_t*();

		//! Converts Widget to constant Photon widget pointer
		operator const PtWidget_t*() const;

		//! Resources of the Widget
		WidgetResourcesSingleton resource;
	
		//! @name Properties
		//! @{ 
		phbitmask<unsigned, Flags::Anchor::eAnchorFlags>::bind<Widget, ArgUnsigned::eArgUnsigned, ArgUnsigned::anchor_flags>			Anchor; //!< Gets or sets flags specifying how the widget is anchored to its parent. See Flags::Anchor::eAnchorFlags.
		property<short, property<>::ro>::bind<Widget, &Widget::getBottom> Bottom; //!< Gets the distance, in pixels, between the bottom edge of the widget and the top edge of its container's client area.
		property<PhArea_t>::bind<Widget, &Widget::getBounds, &Widget::setBounds> Bounds; //!< Gets or sets the size and location of the widget including its nonclient elements, in pixels, relative to the parent widget.

		property<bool>::bind<Widget, &Widget::getEnabled, &Widget::setEnabled>							Enabled; //!< Gets or sets a value indicating whether the widget can respond to user interaction.
		property<std::string>::bind<Widget, &Widget::getHelpTopic, &Widget::setHelpTopic>				HelpTopic; //!< Gets or sets the help topic of the widget.
		property<short>::bind<Widget, &Widget::getLeft, &Widget::setLeft>								Left; //!< Gets or sets the distance, in pixels, between the left edge of the widget and the left edge of its parent widget.
		property<short>::bind<Widget, &Widget::getTop, &Widget::setTop>									Top; //!< Gets or sets the distance, in pixels, between the top edge of the widget and the top edge of its parent widget.
		property<PhPoint_t>::bind<Widget, &Widget::getLocation, &Widget::setLocation>					Location; //!< Gets or sets the coordinates of the upper-left corner of the widget relative to the upper-left corner of its parent widget.

		phproperty<unsigned short>::bind<Widget, Arguments::eArgUnsignedShort, Arguments::width>		Width; //!< Gets or sets the width of the widget.
		phproperty<unsigned short>::bind<Widget, Arguments::eArgUnsignedShort, Arguments::height>		Height; //!< Gets or sets the height of the widget.
		phproperty<unsigned short>::bind<Widget, Arguments::eArgUnsignedShort, Arguments::bevel_width>	BevelWidth; //!< Gets or sets the bevel width of the widget.
		phproperty<PhDim_t>::bind<Widget, Arguments::eArgDim, Arguments::dim>							Size; //!< Gets or sets the size of the widget.
		phproperty<PhPoint_t>::bind<Widget, Arguments::eArgPoint, Arguments::pos>						Position; //!< Gets or sets the absolute coordinates of the upper-left corner of the widget.

		phbitmask<unsigned long, Flags::Extended::eExFlags>::bind<Widget, ArgUnsignedLong::eArgUnsignedLong, ArgUnsignedLong::eflags>	ExtendedFlags; //!< Gets or sets extended flags inherited by all widgets. See Flags::Extended::eExFlags.
		phbitmask<long, Flags::eFlags>::bind<Widget, ArgLong::eArgLong, ArgLong::flags>													WidgetFlags; //!< Gets or sets flags inherited by all widgets. See Flags::eFlags.
		phbitmask<long, Flags::Resize::eResizeFlags>::bind<Widget, ArgLong::eArgLong, ArgLong::resize_flags>							ResizeFlags; //!< Gets or sets flags to control a widget's resize policy. See Flags::Resize::eResizeFlags.
		
		//! @}

		//! @name Events
		//! @{ 
		phwidgets_event<Widget, Widget::Callbacks::destroyed>		Destroyed; //!< Occurs when the widget is destroyed.
		phwidgets_event<Widget, Widget::Callbacks::blocked>			Blocked; //!< Occurs when the widget is blocked.
		phwidgets_event<Widget, Widget::Callbacks::dnd>				DragDrop; //!< Occurs when a drag-and-drop operation is completed.
		phwidgets_event<Widget, Widget::Callbacks::is_destroyed>	IsDestroyed; //!< Occurs when the widget's resources are being released.
		phwidgets_event<Widget, Widget::Callbacks::outbound>		Outbound; //!< Occurs when you press the pointer button on the widget and then move out of the "hot spot" with the button still depressed.
		phwidgets_event<Widget, Widget::Callbacks::realized>		Realized; //!<  Occurs when the widget is realized.
		phwidgets_event<Widget, Widget::Callbacks::unrealized>		Unrealized; //!<  Occurs when the widget is unrealized.

		//! @}

		//! @name Event raisers
		//! @{ 
		void OnDestroyed(PtCallbackInfo_t *info); //!< Raises the Widget::Destroyed event.
		void OnBlocked(PtCallbackInfo_t *info); //!< Raises the Widget::Blocked event.
		void OnDragDrop(PtCallbackInfo_t *info); //!< Raises the Widget::DragDrop event.
		void OnOutbound(PtCallbackInfo_t *info); //!< Raises the Widget::Outbound event.
		void OnRealized(PtCallbackInfo_t *info); //!< Raises the Widget::Realized event.
		void OnUnrealized(PtCallbackInfo_t *info); //!< Raises the Widget::Unrealized event.

		//! @}

		

	};

	//! Specifies how a widget anchors to the edges of its container.

	//! Apply to Widget::Anchor property
	struct AnchorStyles:
		public Widget::Flags::Anchor
	{};

}//namespace PhWidgets

cppbitmasks::bitmask<unsigned long, PhWidgets::Widget::Flags::Extended::eExFlags> operator|(const PhWidgets::Widget::Flags::Extended::eExFlags &flag1, const PhWidgets::Widget::Flags::Extended::eExFlags &flag2);
cppbitmasks::bitmask<unsigned long, PhWidgets::Widget::Flags::Extended::eExFlags> operator&(const PhWidgets::Widget::Flags::Extended::eExFlags &flag1, const PhWidgets::Widget::Flags::Extended::eExFlags &flag2);
cppbitmasks::bitmask<unsigned long, PhWidgets::Widget::Flags::Extended::eExFlags> operator^(const PhWidgets::Widget::Flags::Extended::eExFlags &flag1, const PhWidgets::Widget::Flags::Extended::eExFlags &flag2);

cppbitmasks::bitmask<long, PhWidgets::Widget::Flags::eFlags> operator|(const PhWidgets::Widget::Flags::eFlags &flag1, const PhWidgets::Widget::Flags::eFlags &flag2);
cppbitmasks::bitmask<long, PhWidgets::Widget::Flags::eFlags> operator&(const PhWidgets::Widget::Flags::eFlags &flag1, const PhWidgets::Widget::Flags::eFlags &flag2);
cppbitmasks::bitmask<long, PhWidgets::Widget::Flags::eFlags> operator^(const PhWidgets::Widget::Flags::eFlags &flag1, const PhWidgets::Widget::Flags::eFlags &flag2);

cppbitmasks::bitmask<long, PhWidgets::Widget::Flags::Resize::eResizeFlags> operator|(const PhWidgets::Widget::Flags::Resize::eResizeFlags &flag1, const PhWidgets::Widget::Flags::Resize::eResizeFlags &flag2);
cppbitmasks::bitmask<long, PhWidgets::Widget::Flags::Resize::eResizeFlags> operator&(const PhWidgets::Widget::Flags::Resize::eResizeFlags &flag1, const PhWidgets::Widget::Flags::Resize::eResizeFlags &flag2);
cppbitmasks::bitmask<long, PhWidgets::Widget::Flags::Resize::eResizeFlags> operator^(const PhWidgets::Widget::Flags::Resize::eResizeFlags &flag1, const PhWidgets::Widget::Flags::Resize::eResizeFlags &flag2);

cppbitmasks::bitmask<unsigned, PhWidgets::Widget::Flags::Anchor::eAnchorFlags> operator|(const PhWidgets::Widget::Flags::Anchor::eAnchorFlags &flag1, const PhWidgets::Widget::Flags::Anchor::eAnchorFlags &flag2);
cppbitmasks::bitmask<unsigned, PhWidgets::Widget::Flags::Anchor::eAnchorFlags> operator&(const PhWidgets::Widget::Flags::Anchor::eAnchorFlags &flag1, const PhWidgets::Widget::Flags::Anchor::eAnchorFlags &flag2);
cppbitmasks::bitmask<unsigned, PhWidgets::Widget::Flags::Anchor::eAnchorFlags> operator^(const PhWidgets::Widget::Flags::Anchor::eAnchorFlags &flag1, const PhWidgets::Widget::Flags::Anchor::eAnchorFlags &flag2);


#endif
