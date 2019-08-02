#ifndef PHWIDGETS_WIDGET_H
#define PHWIDGETS_WIDGET_H

#include <photon/PhT.h>
#include <photon/PtWidget.h>
#include <photon/PtContainer.h>
#include <photon/PtGridLayout.h>
#include <photon/PtRowLayout.h>

#include <map>
#include <string>
#include <list>

#include "./service/stdex/stdex.h"
#include "./service/phproperty.hpp"
#include "./service/phevent.hpp"
#include "./service/phbitmask.hpp"
#include "./service/tag_property.hpp"
#include "./service/WidgetResource.hpp"

#include "./Cursor.h"
#include "./Color.h"


//typedef Ph_rect `PhRect_t`;

#ifndef __QNXNTO__
	typedef struct Ph_rect   PhRect_t;
#endif

// @defgroup Widgets PhWidgets library widgets
// @defgroup Values PhWidgets library flags and predefined values
// @defgroup Classes PhWidgets library helper classes
// @defgroup Resources PhWidgets library resource ID's and raw widgets flags

//! The main namespace for all widgets
namespace PhWidgets
{
	using namespace cppproperties;
	using namespace phevents;
	using namespace cppbitmasks;

	//! Specifies how a widget anchors to the edges of its container.
	/*! 
		Apply to Widget::Anchor property
		Is the alias for Widget::Flags::Anchor

		@see
    	- Widget::Anchor
		- Widget::Flags::Anchor::eAnchorStyles

		@ingroup Values
	*/
	struct AnchorStyles
	{
		//! Anchor flags for Widget resource Widget::Arguments::anchor_flags.
		/*!
			Anchor flags specify how the widget is anchored to its parent.

			### Aliases ###
			
			PhWidgets::Widget::Flags::Anchor::eAnchorStyles,
			PhWidgets::Widget::ThisFlags::Anchor::eAnchorStyles
		*/
		enum eAnchorStyles
		{
			LeftAnchoredRight = Pt_LEFT_ANCHORED_RIGHT, //!< Anchors the widget's left extent to the right edge of its parent's canvas. 
			RightAnchoredRight = Pt_RIGHT_ANCHORED_RIGHT, //!< Anchors the widget's right extent to the right edge of its parent's canvas.
			TopAnchoredBottom = Pt_TOP_ANCHORED_BOTTOM, //!< Anchors the widget's top extent to the bottom edge of its parent's canvas. 
			BottomAnchoredBottom = Pt_BOTTOM_ANCHORED_BOTTOM, //!< Anchors the widget's bottom extent to the bottom edge of its parent's canvas. 
			LeftAnchoredLeft = Pt_LEFT_ANCHORED_LEFT, //!< Anchors the widget's left extent to the left edge of its parent's canvas. 
			RightAnchoredLeft = Pt_RIGHT_ANCHORED_LEFT, //!< Anchors the widget's right extent to the left edge of its parent's canvas. 
			TopAnchoredTop = Pt_TOP_ANCHORED_TOP, //!< Anchors the widget's top extent to the top edge of its parent's canvas. 
			BottomAnchoredTop = Pt_BOTTOM_ANCHORED_TOP, //!< Anchors the widget's bottom extent to the top edge of its parent's canvas. 
			BalloonsOn = Pt_BALLOONS_ON, //!< If a child widget has been assigned a balloon, pop up the balloon as soon as the pointer passes over the child widget; otherwise delay the pop up for 1.25 seconds. 

			// Visual Studio like styles:

			Bottom = BottomAnchoredBottom, //!< The widget is anchored to the bottom edge of its container.
			Left = LeftAnchoredLeft, //!<The widget is anchored to the left edge of its container.
			None = 0, //!<The widget is not anchored to any edges of its container.
			Right = RightAnchoredRight, //!<The widget is anchored to the right edge of its container.
			Top = TopAnchoredTop, //!<The widget is anchored to the top edge of its container.

			All = 	LeftAnchoredRight | RightAnchoredRight | 
					TopAnchoredBottom | BottomAnchoredBottom |
					LeftAnchoredLeft | RightAnchoredLeft |
					TopAnchoredTop | BottomAnchoredTop |
					BalloonsOn
		};
	};

	/*!
		@struct PhWidgets::Widget
		@ingroup Widgets
	*/

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

		
		typedef phevent::ph_callback_t callback_t;//!< An event handler that is raised when an [event](@ref Widget::phwidgets_event) occur.
		
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

		//! Contains resource IDs for Widget arguments. @ingroup Resources
		struct ThisArgs
		{
			//! Contains resource IDs for Widget arguments of type `PhArea_t`.
			struct ArgArea
			{
				//! Resource IDs for Widget arguments of type `PhArea_t`.

				/*!
					### Aliases ###
					
					PhWidgets::Widget::Arguments::eArgArea,
					PhWidgets::Widget::ArgArea::eArgArea

					See Widget::resource for usage description.
				*/
				enum eArgArea
				{			
					area = Pt_ARG_AREA //!< A `PhArea_t` structure (see the Photon Library Reference) that contains the x, y, height, and width values for the widget. 
				};
			};
			
			//! Contains resource IDs for Widget arguments of type **unsigned**.
			struct ArgUnsigned
			{
				//! Resource IDs for Widget arguments of type **unsigned**.

				/*!
					### Aliases ###
					
					PhWidgets::Widget::Arguments::eArgUnsigned,
					PhWidgets::Widget::ArgUnsigned::eArgUnsigned

					See Widget::resource for usage description.
				*/
				enum eArgUnsigned
				{
					anchor_flags = Pt_ARG_ANCHOR_FLAGS //!< This resource specifies how the widget is anchored to its parent.
				};
			};
			
			//! Contains resource IDs for Widget arguments of type **unsigned short**.
			struct ArgUnsignedShort
			{
				//! Resource IDs for Widget arguments of type **unsigned short**.

				/*!
					### Aliases ###
					
					PhWidgets::Widget::Arguments::eArgUnsignedShort,
					PhWidgets::Widget::ArgUnsignedShort::eArgUnsignedShort

					See Widget::resource for usage description.
				*/
				enum eArgUnsignedShort
				{
					bevel_width = Pt_ARG_BEVEL_WIDTH, //!< The width of the widget's bevel if the widget is highlighted and is to draw a bevel.
					cursor_type = Pt_ARG_CURSOR_TYPE, //!< The type of cursor. See Widget::Flags::Cursor::eCursorFlags for possible values.
					height = Pt_ARG_HEIGHT, //!< The height of the widget.
					width = Pt_ARG_WIDTH //!< The width of the widget.
				};
			};
			
			//! Contains resource IDs for Widget arguments of type **unsigned long**.
			struct ArgUnsignedLong
			{
				//! Resource IDs for Widget arguments of type **unsigned long**.

				/*!
					### Aliases ###
					
					PhWidgets::Widget::Arguments::eArgUnsignedLong,
					PhWidgets::Widget::ArgUnsignedLong::eArgUnsignedLong

					See Widget::resource for usage description.
				*/
				enum eArgUnsignedLong
				{
					eflags = Pt_ARG_EFLAGS //!< Extended [flags](@ref Widget::Flags::eFlags) inherited by all widgets.
				};
			};
			
			//! Contains resource IDs for Widget arguments of type **long**.
			struct ArgLong
			{
				//! Resource IDs for Widget arguments of type **long**.

				/*!
					### Aliases ###
					
					PhWidgets::Widget::Arguments::eArgLong,
					PhWidgets::Widget::ArgLong::eArgLong

					See Widget::resource for usage description.
				*/
				enum eArgLong
				{
					flags = Pt_ARG_FLAGS, //!< Common [flags](@ref Widget::Flags::eFlags) used by all widgets. Except for those indicated as read-only, these flags are all read/write. 
					resize_flags = Pt_ARG_RESIZE_FLAGS //!< Controls a widget's resize policy in both the x and y directions.
													   //!< Documentation in progress...
				};
			};

			//! Contains resource IDs for Widget arguments of type <b>char*</b>.
			struct ArgPChar
			{
				//! Resource IDs for Widget arguments of type <b>char*</b>.

				/*!
					### Aliases ###
					
					PhWidgets::Widget::Arguments::eArgPChar,
					PhWidgets::Widget::ArgPChar::eArgPChar

					See Widget::resource for usage description.
				*/
				enum eArgPChar
				{
					help_topic = Pt_ARG_HELP_TOPIC //!< The meaning of this resource depends on the bits set in Widget::Flags::eflags:
												   //!< If Widget::Flags::Extended::internal_help isn't set, Widget::Flags::help_topic is used to set the topic position within the HTML help file.
												   //!< If Widget::Flags::Extended::internal_help is set, Widget::Flags::help_topic is the help information to be displayed.

				};
			};
			
			//! Contains resource IDs for Widget arguments of type <b>void*</b>.
			struct ArgPVoid
			{
				//! Resource IDs for Widget arguments of type <b>void*</b> that are stored in widget.

				/*!
					@note 
					This resource is data that is internally stored in widget as a copy.

					### Aliases ###
					
					PhWidgets::Widget::Arguments::eArgPVoidData,
					PhWidgets::Widget::ArgPVoid::eArgPVoidData

					See Widget::resource for usage description.
				*/
				enum eArgPVoidData
				{
					layout_data = Pt_ARG_LAYOUT_DATA, //!< This resource provides a convenient method to get or set either of the Pt_ARG_*_LAYOUT_DATA resources.
													  //!< Documentation in progress...
					data = Pt_ARG_DATA, //!< This resource is used internally by PhAB applications as well as by compound widgets.
					user_data = Pt_ARG_USER_DATA //!< Data that you want to store in the widget's internal memory.
				};

				//! Resource IDs for Widget arguments of type <b>void*</b> that are stored externally.

				/*!
					@note 
					This resource is data that is externally stored in widget as just a pointer. 
					The widget doesn't make a copy of the memory referenced by the pointer; 
					don't free the memory while the widget is still referencing it.

					### Aliases ###
					
					PhWidgets::Widget::Arguments::eArgPVoid,
					PhWidgets::Widget::ArgPVoid::eArgPVoid

					See Widget::resource for usage description.
				*/
				enum eArgPVoid
				{
					pointer = Pt_ARG_POINTER //!< A pointer to any data that you want to associate with the widget.
				};
			};

			//! Contains resource IDs for Widget arguments of type `PhRect_t`.
			struct ArgRect
			{
				//! Resource IDs for Widget arguments of type `PhRect_t`.

				/*!
					### Aliases ###
					
					PhWidgets::Widget::Arguments::eArgRect,
					PhWidgets::Widget::ArgRect::eArgRect

					See Widget::resource for usage description.
				*/
				enum eArgRect
				{
					enchor_offsets = Pt_ARG_ANCHOR_OFFSETS, //!< The four values in this `PhRect_t` structure (see the Photon Library Reference) determine the anchor offsets of each of the widget's sides. 
															//!< (An anchor offset is the distance between the anchoring side of the parent and corresponding side of the child.) 
					
					extent = Pt_ARG_EXTENT //!< A `PhRect_t` structure that contains the extent of the widget, a rectangle that specifies the upper-left and lower-right corners of the widget.
				};
			};
			
			//! Contains resource IDs for Widget arguments of type `PgColor_t`.
			struct ArgColor
			{
				//! Resource IDs for Widget arguments of type `PgColor_t`.

				/*!
					### Aliases ###
					
					PhWidgets::Widget::Arguments::eArgColor,
					PhWidgets::Widget::ArgColor::eArgColor

					See Widget::resource for usage description.
				*/
				enum eArgColor
				{
					cursor_color = Pt_ARG_CURSOR_COLOR //!< The color of the pointer when it's inside the widget.
				};	
			};
			
			//! Contains resource IDs for Widget arguments of type `PhCursorDef_t`.
			struct ArgPCursorDef
			{
				//! Resource IDs for Widget arguments of type `PhCursorDef_t`.

				/*!
					### Aliases ###
					
					PhWidgets::Widget::Arguments::eArgPCursorDef,
					PhWidgets::Widget::ArgPCursorDef::eArgPCursorDef

					See Widget::resource for usage description.
				*/
				enum eArgPCursorDef
				{
					bitmap_cursor = Pt_ARG_BITMAP_CURSOR //!< Defines bitmaps for the cursor when the [cursor type](@ref Widget::Arguments::cursor_type) is set to Widget::Flags::Cursor::bitmap. 
				};
			};
			
			//! Contains resource IDs for Widget arguments of type `PtGridLayoutData_t`.
			struct ArgPGridLayoutData
			{
				//! Resource IDs for Widget arguments of type `PtGridLayoutData_t`.
				/*!
					### Aliases ###
					
					PhWidgets::Widget::Arguments::eArgPGridLayoutData,
					PhWidgets::Widget::ArgPGridLayoutData::eArgPGridLayoutData

					See Widget::resource for usage description.
				*/
				enum eArgPGridLayoutData
				{
					grid_layout_data = Pt_ARG_GRID_LAYOUT_DATA //!< A `PtGridLayoutData_t` structure that defines additional layout data for the widget when its container widget uses a PtGridLayout type layout. 
															   //!< Documentation in progress...
				};
			};
			
			//! Contains resource IDs for Widget arguments of type `PhPoint_t`.
			struct ArgPoint
			{
				//! Resource IDs for Widget arguments of type `PhPoint_t`.
				/*!
					### Aliases ###
					
					PhWidgets::Widget::Arguments::eArgPoint,
					PhWidgets::Widget::ArgPoint::eArgPoint

					See Widget::resource for usage description.
				*/
				enum eArgPoint
				{
					pos = Pt_ARG_POS //!< A `PhPoint_t` structure that stores the x and y coordinates for the widget.
				};
			};

			//! Contains resource IDs for Widget arguments of type `PtRowLayoutData_t`.
			struct ArgPRowLayoutData
			{
				//! Resource IDs for Widget arguments of type `PtRowLayoutData_t`.
				/*!
					### Aliases ###
					
					PhWidgets::Widget::Arguments::eArgPRowLayoutData,
					PhWidgets::Widget::ArgPRowLayoutData::eArgPRowLayoutData

					See Widget::resource for usage description.
				*/
				enum eArgPRowLayoutData
				{
					row_layout_data = Pt_ARG_ROW_LAYOUT_DATA //!< A `PtRowLayoutData_t` structure that defines additional layout data for the widget when its container widget uses a PtRowLayout type layout. 
				};
			};

			//! Contains resource IDs for Widget arguments of type `PhDim_t`.
			struct ArgDim
			{
				//! Resource IDs for Widget arguments of type `PhDim_t`.
				/*!
					### Aliases ###
					
					PhWidgets::Widget::Arguments::eArgDim,
					PhWidgets::Widget::ArgDim::eArgDim

					See Widget::resource for usage description.
				*/
				enum eArgDim
				{
					dim = Pt_ARG_DIM, //!< A `PhDim_t` structure (see the Photon Library Reference) that defines the height and width values for the widget.
					max_dim = Pt_ARG_MAXIMUM_DIM, //!< A `PhDim_t` structure (see the Photon Library Reference) that defines the maximum size that a widget can be.
					min_dim = Pt_ARG_MINIMUM_DIM //!< A `PhDim_t` structure (see the Photon Library Reference) that defines the minimum size that a widget can be.
				};
			};
		};

		//! Contains resource IDs for Widget callbacks.
		struct ThisCallbacks
		{
			//! Contains resource IDs for Widget callbacks of type `PtRawCallback_t`.
			struct RawCallback
			{
				//! Resource IDs for Widget arguments of type `PtRawCallback_t`.
				/*!
					### Aliases ###
					
					PhWidgets::Widget::Callbacks::eRawCallback,
					PhWidgets::Widget::RawCallback::eRawCallback

					See Widget::resource for usage description.
				*/
				enum eRawCallback
				{
					filter = Pt_CB_FILTER, //!< A list of raw callbacks invoked when an event that matches the provided event mask is to be passed to the widget. 
										   //!< These callbacks are invoked before the event is processed by the widget. Contrast this resource with Widget::Callbacks::raw.
										   //!< Documentation in progress...

					raw = Pt_CB_RAW //!< A list of `PtRawCallback_t` structures that defines the raw callbacks that the widget invokes if the event it receives matches the event mask provided in the `PtRawCallback_t` structure.
									//!< Documentation in progress...

				};
			};

			//! Contains resource IDs for Widget callbacks of type `PtCallback_t`.
			struct Callback
			{
				//! Resource IDs for Widget arguments of type `PtCallback_t`.
				/*!
					### Aliases ###
					
					PhWidgets::Widget::Callbacks::eCallback,
					PhWidgets::Widget::Callback::eCallback

					See Widget::resource for usage description.
				*/
				enum eCallback
				{
					blocked = Pt_CB_BLOCKED, //!< A list of `PtCallback_t` structures that define the callbacks that the widget invokes whenever it must ignore an event due to being blocked.
											 //!< Documentation in progress...

					destroyed = Pt_CB_DESTROYED, //!< A list of `PtCallback_t` structures that define the callbacks invoked when the widget is marked for destruction and is no longer visible. 
												 //!< You can use these callbacks, for example, to adjust the appearance of the widgets around the one being destroyed.
												 //!< In contrast, the Widget::Callbacks::is_destroyed callbacks are invoked when the widget's resources are actually being released.
												 //!< Documentation in progress...

					dnd = Pt_CB_DND, //!< A list of `PtCallback_t` structures that define the callbacks called when a drag-and-drop (Events::dndrop) event is received.
									 //!< Documentation in progress...

					is_destroyed = Pt_CB_IS_DESTROYED, //!< A list of `PtCallback_t` structures that define the callbacks invoked when the widget's resources are being released. 
													   //!< You'll find this resource useful for cleaning up variables or memory associated with the widget. 
													   //!< Documentation in progress...

					outbound = Pt_CB_OUTBOUND, //!< A list of `PtCallback_t` structures that define the callbacks invoked when you press the pointer button on the widget and then move out of the "hot spot" with the button still depressed. 
											   //!< This callback is particularly useful for initiating drag or drag-and-drop operations.
											   //!< Documentation in progress...

					realized = Pt_CB_REALIZED, //!< A list of `PtCallback_t` structures that define the callbacks that the widget invokes whenever it is realized. 
											   //!< Documentation in progress...

					unrealized = Pt_CB_UNREALIZED //!< A list of `PtCallback_t` structures that define the callbacks that the widget invokes whenever it's unrealized. 
												  //!< Documentation in progress...
				};
			};
			
			//! Contains resource IDs for Widget callbacks of type `PtHotkeyCallback_t`.
			struct HotkeyCallback
			{
				//! Resource IDs for Widget arguments of type `PtHotkeyCallback_t`.
				/*!
					### Aliases ###
					
					PhWidgets::Widget::Callbacks::eHotkeyCallback,
					PhWidgets::Widget::HotkeyCallback::eHotkeyCallback

					See Widget::resource for usage description.
				*/
				enum eHotkeyCallback
				{
					//! A list of `PtHotkeyCallback_t` structures. 
					
					//! If the widget receives a key event that matches a structure's key cap and key modifiers, the widget calls the function specified in that structure. 
					//! If a function isn't specified, the widget invokes its Basic::Callbacks::activate callback list with a reason_subtype of Widget::Callbacks::hotkey. 
					//! @remark A hotkey isn't invoked if any ancestor of the widget that owns it is blocked.
					//! Documentation in progress...
					hotkey = Pt_CB_HOTKEY
				};
			};
		};

		//! Contains flags for Widget resources.
		struct ThisFlags
		{
			//! Contains flags for Widget resource Widget::Arguments::cursor_type.
			struct Cursor
			{
				//! Cursor flags for Widget resource Widget::Arguments::cursor_type.
				/*!
					### Aliases ###
					
					PhWidgets::Widget::Flags::Cursor::eCursorFlags
				*/
				enum eCursorFlags
				{
					inherit = Ph_CURSOR_INHERIT, //!< Inherit the cursor, not from the class hierarchy, but from the family hierarchy; 
												 //!< that is, from the way your application nests the widgets. 
												 //!< The cursor might even be inherited from the Photon server itself.

					bitmap_no_inherit = Ph_CURSOR_BITMAP,	//!< Use the bitmap stored in Arguments::bitmap_cursor for the cursor.
															//!< By default, bitmap cursors aren't inherited by a widget's child regions.
															//!< Use Widget::Flags::Cursor::bitmap_inherit instead to inherit bitmap cursor.

					bitmap_inherit = Ph_CURSOR_BITMAP & ~Ph_CURSOR_NO_INHERIT,	//!< Use the bitmap stored in Arguments::bitmap_cursor for the cursor.
																				//!< By default, bitmap cursors aren't inherited by a widget's child regions.
																				//!< Use this flag to inherit bitmap cursor.

					bitmap = bitmap_no_inherit //!< Same as Cursor::bitmap_no_inherit

				};
			};

			//! Contains flags for Widget resource Widget::Arguments::eflags.
			struct Extended
			{
				//! Extended flags for Widget resource Widget::Arguments::eflags.
				/*!
					### Aliases ###
					
					PhWidgets::Widget::Flags::Extended::eExFlags
				*/
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
			
			//! Contains flags for Widget resource Widget::Arguments::anchor_flags.
			struct Anchor:
				public AnchorStyles
			{};

			//! Contains flags for Widget resource Widget::Arguments::resize_flags.
			struct Resize
			{
				//! Resize flags for Widget resource Widget::Arguments::resize_flags.
				/*!
					Resize flags to control a widget's resize policy in both the x and y directions.

					@note
					Each ..._bits flag is a mask that represents all the bits of that type.
					The default setting of this resource is 0; that is, no resize policy is in effect.
					A widget's resize policy deals solely with the widget's renderable data. 
					For a button, the data is its text; for a container, the data is its children. 
					@par
					Any rendered data that doesn't fit within the widget's canvas is clipped.
					If no resize policy is in effect, the widget's size is unbounded; 
					it may be made as large or small as specified via Widget::Arguments::dim or Widget::Arguments::area.
					@par
					If a resize policy is in effect, the widget grows or shrinks to honor that policy:
					- If the policy is ..._always, the widget resizes itself to fit its data 
					the dimensions specified via Widget::Arguments::dim or Widget::Arguments::area don't apply. 
					- If the policy is ..._as_requred, the widget resizes itself to fit its data only if its current canvas size is inadequate to contain that data. 
					In other words, it grows, but doesn't shrink, to fit its data.
					- If the widget has the ..._initial bit set, the resize policy is applied only once each time the widget is realized. 
					This bit is meaningful only in concert with ..._always or ..._as_requred.

					### Aliases ###
					
					PhWidgets::Widget::Flags::Resize::eResizeFlags
				*/
				enum eResizeFlags
				{
					None = 0,
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

			//! Common flags for Widget resource Widget::Arguments::flags.
			/*! 
				Common flags used by all widgets. Except for those indicated as read-only, these flags are all read/write.

				### Aliases ###
					
				PhWidgets::Widget::Flags::eFlags
			*/
			enum eFlags
			{
				AllButtons = Pt_ALL_BUTTONS, //!< Any pointer button can activate the widget. Default is the left button only. 
				Autohighlight = Pt_AUTOHIGHLIGHT, //!< Highlight and give focus to the widget when the cursor enters its extent, and unhighlight and remove focus when the cursor leaves. 
				Blocked = Pt_BLOCKED, //!< Prevent the widget and all its non-window-class children from interacting with Photon events. 

				/*!
					If certain widgets have this bit set, and your application sets their resources, the relevant callbacks are invoked. 
					Otherwise callbacks aren't invoked when your application sets resources. 
					@note
					If a callback refers to this flag, its description says so explicitly.
					For example, if this bit is set for a Divider and you use Divider::Undefined to change the size of one of its children, 
					the Divider::DeviderDraged event is invoked. 
				*/
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
				Selectable = Pt_SELECTABLE, //!< You can select ([repeat](@ref Basic::Repeat), [arm](@ref Basic::Arm), [disarm](@ref Basic::Disarm) and [activate](@ref Basic::Activate)) the widget. Widgets usually provide visual feedback when selected. 
				SelectNoredraw = Pt_SELECT_NOREDRAW, //!< The widget doesn't change its appearance when set or unset. This is meaningful only when the widget is Selectable. 
				Set = Pt_SET, //!< The widget is in a set state. Generally, this indicates that the widget has been selected. 

				//! Pressing the pointer button on this widget causes it to toggle between being set and unset. 
				//! @remark Normally, selectable widgets act as push buttons they become set when you press the pointer button, and unset when you release the button. 
				Toggle = Pt_TOGGLE, 
	
				WidgetRebuild = Pt_WIDGET_REBUILD, //!< (read-only) The widget will be rebuilt(rerealized) when the widget engine is finished applying resource changes.
				WidgetResize = Pt_WIDGET_RESIZE //!< (read-only) The widget will be resized when the widget engine is finished applying resource changes. 
			};

		};

		//! Contains resource IDs for Widget arguments of type `PhArea_t`. @ingroup Resources
		struct ArgArea:
			public ThisArgs::ArgArea
        { };
		
		//! Contains resource IDs for Widget arguments of type **unsigned**. @ingroup Resources
		struct ArgUnsigned:
			public ThisArgs::ArgUnsigned
        { };
		
		//! Contains resource IDs for Widget arguments of type **unsigned short**. @ingroup Resources
		struct ArgUnsignedShort:
			public ThisArgs::ArgUnsignedShort
        { };
		
		//! Contains resource IDs for Widget arguments of type **unsigned long**. @ingroup Resources
		struct ArgUnsignedLong:
			public ThisArgs::ArgUnsignedLong
        { };
		
		//! Contains resource IDs for Widget arguments of type **long**. @ingroup Resources
		struct ArgLong:
			public ThisArgs::ArgLong
        { };

		//! Contains resource IDs for Widget arguments of type <b>char*</b>. @ingroup Resources
		struct ArgPChar:
			public ThisArgs::ArgPChar
        { };
		
		//! Contains resource IDs for Widget arguments of type <b>void*</b>. @ingroup Resources
		struct ArgPVoid:
			public ThisArgs::ArgPVoid
        { };

		//! Contains resource IDs for Widget arguments of type `PhRect_t`. @ingroup Resources
		struct ArgRect:
			public ThisArgs::ArgRect
        { };
		
		//! Contains resource IDs for Widget arguments of type `PgColor_t`. @ingroup Resources
		struct ArgColor:
			public ThisArgs::ArgColor
        { };
		
		//! Contains resource IDs for Widget arguments of type `PhCursorDef_t`. @ingroup Resources
		struct ArgPCursorDef:
			public ThisArgs::ArgPCursorDef
        { };
		
		//! Contains resource IDs for Widget arguments of type `PtGridLayoutData_t`. @ingroup Resources
		struct ArgPGridLayoutData:
			public ThisArgs::ArgPGridLayoutData
        { };
		
		//! Contains resource IDs for Widget arguments of type `PhPoint_t`. @ingroup Resources
		struct ArgPoint:
			public ThisArgs::ArgPoint
        { };

		//! Contains resource IDs for Widget arguments of type `PtRowLayoutData_t`. @ingroup Resources
		struct ArgPRowLayoutData:
			public ThisArgs::ArgPRowLayoutData
        { };

		//! Contains resource IDs for Widget arguments of type `PhDim_t`. @ingroup Resources
		struct ArgDim:
			public ThisArgs::ArgDim
		{ };

		//! Contains resource IDs for Widget callbacks of type `PtRawCallback_t`. @ingroup Resources
		struct RawCallback:
			public ThisCallbacks::RawCallback
		{ };

		//! Contains resource IDs for Widget callbacks of type `PtCallback_t`. @ingroup Resources
		struct Callback:
			public ThisCallbacks::Callback
		{ };

		//! Contains resource IDs for Widget callbacks of type `PtHotkeyCallback_t`. @ingroup Resources
		struct HotkeyCallback:
			public ThisCallbacks::HotkeyCallback
		{ };

		//! Contains resource IDs for all Widget arguments. @ingroup Resources
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
		{ };

		//! Contains resource IDs for all Widget callbacks. @ingroup Resources
		struct Callbacks:
			public RawCallback,
			public Callback,
			public HotkeyCallback
		{ };

		//! Contains flags for all Widget resources. @ingroup Resources
		struct Flags:
			public ThisFlags
		{ };


				
	private:
	
		int _abn;
		mutable PtWidget_t *_widget;
		
		using IPhWidgetsProperty::setArgument;
		using IPhWidgetsProperty::getArgument;
		
	protected:

		template<class ParentArgs>
		struct ArgumentsEx:
			public ParentArgs
        { };

		typedef ResourceFrom<>::
			Define::String<ArgPChar::eArgPChar>::
			Define::Alloc<ArgPVoid::eArgPVoidData>::
			Define::Pointer<ArgPVoid::eArgPVoid>::
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
			//Define::Link<RawCallback::eRawCallback, `PtRawCallback_t`*>::
			//Define::Link<HotkeyCallback::eHotkeyCallback, `PtHotkeyCallback_t`*>::

		resource_type WidgetResourcesSingleton;
	
		virtual PtWidget_t *widget() const;
		virtual void check();
		
		//for properties:
		
		void setAllowDrop(bool);
		bool getAllowDrop() const;

		void setEnabled(bool);
		bool getEnabled() const;

		void setHelpTopic(std::string);
		std::string getHelpTopic() const;

		void setLocation(PhPoint_t);
		PhPoint_t getLocation() const;

		void setBounds(PhArea_t);
		PhArea_t getBounds() const;

		short getBottom() const;

		void setCursor(PhWidgets::Cursor);
		PhWidgets::Cursor getCursor() const;

		bool getCanFocus() const;

		bool getCanSelect() const;

		bool getContainsFocus() const;

		bool getFocused() const;

		bool hasChildren() const;

		void setLeft(short);
		short getLeft() const;

		void setTag(const void*, std::size_t);
		const void * getTag() const;

		void setTop(short);
		short getTop() const;

		short getRight() const;

		void setVisible(bool);
		bool getVisible() const;

		bool getIsRealized() const;

		void setParent(PtWidget_t*);
		PtWidget_t* getParent() const;
						
	public:
		//! (constructor) 
		/*!
			Constructs a Widget by ID.
			@param[in] abn ID given by PhAB to widget (like 'ABN_WIDGET_NAME').
		*/
		Widget(int abn);

		//! (constructor) 
		/*!
			Constructs a Widget by pointer to widget.
			@param[in] wdg pointer to Photon widget.
		*/
		Widget(PtWidget_t *wdg);

		//! (copy constructor) 
		/*!
			Constructs a Widget by copy.
			@param[in] other another Widget to be used as source to initialize the elements of the container with.
		*/
		Widget(const Widget &other);

		//! Exchanges the contents of <b>*this</b> and other
		/*!
			@param[in] other widget to exchange the contents with.
		*/
		void swap(Widget &other);
		
		//! Assigns value in Widget 
		/*!
			Replaces the contents of the Widget.
			@param[in] other another Widget to use as data source.
		*/
		Widget &operator=(const Widget &other);

		//! Compares Widgets
		/*!
			Compares the Widgets by their Photon widget pointers.
			@param[in] other Widget whose contents to compare.
		*/
		bool operator==(const Widget &other) const;

		//! Compares Widgets
		/*!
			Compares the Widgets by their Photon widget pointers.
			@param[in] other Widget whose contents to compare.
		*/
		bool operator!=(const Widget &other) const;

		//! Compares Widgets
		/*!
			Compares the Widgets by their Photon widget pointers.
			@param[in] other Widget whose contents to compare.
		*/
		bool operator<(const Widget &other) const;

		//! Compares Widgets
		/*!
			Compares the Widgets by their Photon widget pointers.
			@param[in] other Widget whose contents to compare.
		*/
		bool operator<=(const Widget &other) const;

		//! Compares Widgets
		/*!
			Compares the Widgets by their Photon widget pointers.
			@param[in] other Widget whose contents to compare.
		*/
		bool operator>(const Widget &other) const;

		//! Compares Widgets
		/*!
			Compares the Widgets by their Photon widget pointers.
			@param[in] other Widget whose contents to compare.
		*/
		bool operator>=(const Widget &other) const;

		//! Returns the stored pointer.
		PtWidget_t* get() const;
		
		//! Converts Widget to Photon widget pointer
		operator PtWidget_t*();

		//! Converts Widget to constant Photon widget pointer
		operator const PtWidget_t*() const;

		//! Sets input focus to the widget.
		/*!
			@return `true` if the input focus request was successful; otherwise, `false`.
		*/
		bool Focus();

		//@{
		//! Sets the bounds of the widget to the specified location and size.
		/*!
			@param[in] x The new Widget::Left property value of the widget.
			@param[in] y The new Widget::Top property value of the widget.
			@param[in] width The new Widget::Width property value of the widget.
			@param[in] height The new Widget::Height property value of the widget.
		*/
		void SetBounds(short x, short y, unsigned short width, unsigned short height);

		//! Sets the bounds of the widget to the specified location.
		/*!
			@param[in] x The new Widget::Left property value of the widget.
			@param[in] y The new Widget::Top property value of the widget.
		*/
		void SetBounds(short x, short y);
		//@}

		//! Activates the widget.
		/*!
			The Select method activates the widget if the widget's Widget::Flags::Selectable flag of Widget::Arguments::flags is set true, 
			it is contained in another widget, and all its parent widget are both visible and enabled.
		*/
		void Select();

		//! Make the widget and its children visible and possibly interactive.
		/*!
			Make a widget and its children visible to the user and possibly interactive. 

			@note
			Some widgets (for example, menus) have Widget::Flags::DelayRealize set in their Widget::Arguments::flags.
			Such delay-realized widgets aren't visibly rendered when their ancestors are realized. 
			Although they're present in the hierarchy, 
			delay-realized widgets become visible only when the application realizes them specifically with a call to Realize(). 
			An application might do this, for example, if the user requested it to activate a menu.

			@return `true` if the realize request was successful; otherwise, `false`.
		*/
		bool Realize();

		//! Unrealizes the widget and all its children.
		/*!
			The widgets are removed from the display, and the widget engine will no longer invoke their callbacks.
			Unrealized widgets still exist in the widget hierarchy and can be realized again. 

			@note
			Unrealizing and realizing a widget can take some time. 
			If you want to hide a widget quickly, you can set its Widget::Visible property to `false`.

			@return `true` if the unrealize request was successful; otherwise, `false`.
		*/
		bool Unrealize();

		//! Conceals the widget from the user.
		/*!
			@remark
			Hiding the widget is equivalent to setting the Widget::Visible property to `false`. 
			After the Widget::Hide method is called, the Widget::Visible property returns a value of `false` until the Widget::Show method is called.

			@see
			- Show()
			- Visible
		*/
		void Hide();

		//! Displays the widget to the user.
		/*!
			@remark
			Showing the widget is equivalent to setting the Widget::Visible property to `true`. 
			After the Widget::Show method is called, the Widget::Visible property returns a value of `true` until the Widget::Hide method is called.
			
			@see
			- Hide()
			- Visible
		*/
		void Show();

		//! Resources of the Widget
		/*!
			All resources of the Widget could be accessed by using PhWidgets::Widget::resource.
			As an example:

			- Widget resources could be accessed using Widget::resource with Widget::Arguments and Widget::Callbacks.
			- Basic (which is the child of Widget) and Widget resources could be accessed by Basic::resource with Basic::Arguments and Basic::Callbacks
			or you can specify resources only for one class (Basic::ThisArgs and Basic::ThisCallbacks, Widget::ThisArgs and Widget::ThisCallbacks).
			- Label (which is the child of Basic), Widget and Basic resources could be all accessed by Label::resource
			or, again, you can specify resources only for one class 
			(Basic::ThisArgs and Basic::ThisCallbacks, Widget::ThisArgs and Widget::ThisCallbacks, Label::ThisArgs).

			and so on...

			There are two types of resources:
			- argument
			- callback

			Each resource could be obtained using Widget::Arguments::$argument_tag$ or Widget::Callbacks::$callback_tag$ respectively.

			### Examples ###

			@code
				// You have somewhere:
				PtWidget_t *ptwidget; // pointer to widget
				int ptwidget_realized_callback( PtWidget_t *, void *, PtCallbackInfo_t *); // callback

				// constructing Widget
				PhWidgets::Widget widget(ptwidget);
				
				// get/set of widget width
				unsigned short widget_width = widget.resource.argument[Widget::Arguments::width].get();
				widget.resource.argument[Widget::Arguments::width].set(100);

				// add/remove callback
				widget.resource.callback[Widget::Callbacks::realized].add(ptwidget_realized_callback);
				widget.resource.callback[Widget::Callbacks::realized].remove(ptwidget_realized_callback);
			@endcode

			For convenient use of resources each widget has properties and events. 
			So the code snippet above could shrink to:
			@code
				// You have somewhere:
				PtWidget_t *ptwidget; // pointer to widget
				int ptwidget_realized_callback( PtWidget_t *, void *, PtCallbackInfo_t *); // callback

				// constructing Widget
				PhWidgets::Widget widget(ptwidget);
				
				// get/set of widget width
				unsigned short widget_width = widget.Width;
				widget.Width = 100;

				// add/remove callback
				widget.Realized += ptwidget_realized_callback;
				widget.Realized -= ptwidget_realized_callback;
			@endcode
		*/
		WidgetResourcesSingleton resource;

		//! @name Properties
		//! Properties are used to simplify use of widget resources.
		//@{
		//! Gets or sets a value indicating whether the widget can accept data that the user drags onto it.
		/*!
			### Property Value ### 
			
			> **bool**

			`true` if drag-and-drop operations are allowed in the widget; otherwise, `false`. The default is `false`.

			@see
			- DragEventArgs
			- DragOver
			- DragDrop
			- DragEnter
			- DragLeave
			- DoDragDrop
		*/
		property<bool>::bind<Widget, &Widget::getAllowDrop, &Widget::setAllowDrop> AllowDrop;
		
		//! Gets or sets flags specifying how the widget is anchored to its parent.
		/*!
			### Property Value ### 
			
			> [AnchorStyles::eAnchorStyles](@ref Flags::Anchor::eAnchorStyles) 

			A bitwise combination of the Flags::Anchor::eAnchorStyles values.

			### Examples ###

			@code
				// You have somewhere:
				PtWidget_t *ptwidget; // pointer to widget

				// constructing Widget
				PhWidgets::Widget widget(ptwidget);
				
				// anchor the widget to the bottom right corner of the parent
   				widget.Anchor = (PhWidgets::AnchorStyles::Bottom | PhWidgets::AnchorStyles::Right);
			@endcode

			@remark
			Use the Widget::Anchor property to define how a widget is automatically resized as its parent widget is resized. 
			Anchoring a widget to its parent widget ensures that the anchored edges remain in the same position relative to the edges of the parent widget when the parent widget is resized.
			You can anchor a widget to one or more edges of its container. 
			For example, if you have a Container with a Button whose Button::Anchor property value is set to [AnchorStyles::Top](@ref Flags::Anchor::Top) and [AnchorStyles::Bottom](@ref Flags::Anchor::Bottom), 
			the Button is stretched to maintain the anchored distance to the top and bottom edges of the Container as the [Height](@ref Container::Height) of the Container is increased. 

			@see
			- AnchorStyles
			- Dock
			- Layout
		*/
		phbitmask<unsigned, Flags::Anchor::eAnchorStyles, Flags::Anchor::All>::
			bind<Widget, ArgUnsigned::eArgUnsigned, ArgUnsigned::anchor_flags> Anchor;

		//! Gets or sets the bevel width of the widget.
		/*!
			### Property Value ### 
			
			> **unsigned short**

			The bevel width of the widget in pixels.

			@remark
			The width of the widget's bevel if the widget is highlighted and is to draw a bevel.

			@see 
			- Widget::ThisFlags::Highlighted
			- Basic::ThisFlags::Basic::eBasic
		*/
		phproperty<unsigned short>::bind<Widget, Arguments::eArgUnsignedShort, Arguments::bevel_width>	BevelWidth; 
		
		//! Gets the distance, in pixels, between the bottom edge of the widget and the top edge of its container's client area.
		/*!
			### Property Value ### 
			
			> **short**

			An `short` representing the distance, in pixels, between the bottom edge of the widget and the top edge of its container's client area.

			@remark
			The value of this property is equal to the sum of the Widget::Top property value, and the Widget::Height property value.
			@par
			The Widget::Bottom property is a read-only property. 
			You can manipulate this property value by changing the value of the Widget::Top or Widget::Height properties 
			or calling the Widget::SetBounds methods.

			@see
			- Top
			- Height
		*/
		property<short, property<>::ro>::bind<Widget, &Widget::getBottom> Bottom;
		
		//! Gets or sets the size and location of the widget including its nonclient elements, in pixels, relative to the parent widget.
		/*!
			### Property Value ### 
			
			@code
				typedef struct Ph_area { 
					PhPoint_t pos;
					PhDim_t size; 
				} PhArea_t;
			@endcode

			A `PhArea_t` in pixels relative to the parent widget that represents the size and location of the widget including its nonclient elements.

			### Examples ###

			@code
				// You have somewhere:
				PtWidget_t *ptwidget; // pointer to widget

				// constructing Widget
				PhWidgets::Widget widget(ptwidget);
				
				// set the widget size and location using the Bounds property.
				PhArea_t bounds;

				PhPoint_t pos = {20, 48};
    			PhDim_t size = {12, 20};

				bounds.pos = pos; // location
				bounds.size = size; // size
   				widget.Bounds = bounds;
			@endcode

			@see
			- Top
			- Left
			- Height
			- Width
		*/
		property<PhArea_t>::bind<Widget, &Widget::getBounds, &Widget::setBounds> Bounds;

		//! Gets a value indicating whether the widget can receive focus.
		/*!
			### Property Value ### 
			
			> **bool**

			`true` if the widget can receive focus; otherwise, `false`.

			@remark
			In order for a widget to receive input focus, the Widget must have a PtWidget_t pointer assigned to it, 
			and the Widget::Visible and Widget::Enabled properties must both be set to `true` for both the widget and all its parent widgets, 
			and the widget must be a PhWidgets::Window or the widget's outermost parent must be a PhWidgets::Window.

			@see
			- Enabled
			- Visible
			- Focus
			- Focused
			- CanSelect
		*/
		property<bool, property<>::ro>::bind<Widget, &Widget::getCanFocus> CanFocus;

		//! Gets a value indicating whether the widget can be selected.
		/*!
			### Property Value ### 
			
			> **bool**

			`true` if the widget can be selected; otherwise, `false`.

			@remark
			This property returns `true` if the Widget::Flags::Selectable flag of Widget::Arguments::flags is set, 
			is contained in another widget, the widget itself is visible and enabled, and all its parent widget are visible and enabled.

			@see
			- Select
			- Enabled
			- Visible
			- Focus
			- CanFocus
		*/
		property<bool, property<>::ro>::bind<Widget, &Widget::getCanSelect> CanSelect;

		//! Gets a value indicating whether the widget, or one of its child widgets, currently has the input focus.
		/*!
			### Property Value ### 
			
			> **bool**

			`true` if the widget or one of its child widgets currently has the input focus; otherwise, `false`.

			@remark
			You can use this property to determine whether a widget or any of the widgets contained within it has the input focus. 
			To determine whether the widget has focus, regardless of whether any of its child widgets have focus, use the Widget::Focused property. 
			To give a widget the input focus, use the Widget::Focus or Widget::Select methods.

			@see
			- CanFocus
			- Focus
			- Focused
			- CanSelect
		*/
		property<bool, property<>::ro>::bind<Widget, &Widget::getContainsFocus> ContainsFocus;

		//! Gets or sets the cursor that is displayed when the mouse pointer is over the widget.
		/*!
			### Property Value ### 
			
			> PhWidgets::Cursor

			A Cursor that represents the cursor to display when the mouse pointer is over the widget.

			### Examples ###

			@code
				// You have somewhere:
				PtWidget_t *ptwidget; // pointer to widget

				// constructing Widget
				PhWidgets::Widget widget(ptwidget);
				
				widget.Cursor = PhWidgets::Cursors::Hand;
			@endcode

			@note
			Cursor could also be constructed from PhCursorDef_t 
			so you can assign your own defined PhCursorDef_t structure to this property.

			@code
				PhCursorDef_t curdef;
				
				curdef.size1.x = curdef.size2.x = BMP_WIDTH;
				curdef.size1.y = curdef.size2.y = BMP_HEIGHT;
				...
				// fill 'curdef' with your own cursor info
				...

				widget.Cursor = curdef; // assign custom cursor
			@endcode

			@remark
			Assign a PhWidgets::Cursor to the Widget::Cursor property of the widget to change the cursor displayed when the mouse pointer is over the widget.

			@see
			- PhWidgets::Cursor
			- Cursors
		*/
		property<PhWidgets::Cursor>::bind<Widget, &Widget::getCursor, &Widget::setCursor> Cursor;

		//! Gets or sets the color of the cursor pointer when it's inside the widget.
		/*!
			### Property Value ### 
			
			> Drawing::Color

			A Drawing::Color that represents the color of the cursor pointer when it's inside the widget.

			### Examples ###

			@code
				// You have somewhere:
				PtWidget_t *ptwidget; // pointer to widget

				// constructing Widget
				PhWidgets::Widget widget(ptwidget);
				
				widget.CursorColor = PhWidgets::Drawing::Colors::AliceBlue;
			@endcode

			@see
			- Drawing::Color
			- Drawing::Colors::eColors
			- Drawing::Color::FromARGB
			- Cursors
		*/
		phproperty<Drawing::Color>::bind<Widget, Arguments::eArgColor, Arguments::cursor_color> CursorColor;

		//! Gets or sets a value indicating whether the widget can respond to user interaction.
		/*!
			### Property Value ### 
			
			> **bool**

			`true` if the widget can respond to user interaction; otherwise, `false`. The default is `true`.

			@remark
			With the Enabled property, you can enable or disable widgets at run time. 
			For example, you can disable widgets that do not apply to the current state of the application. 
			You can also disable a widget to restrict its use. 
			For example, a button can be disabled to prevent the user from clicking it. 
			If a widget is disabled, it cannot be selected.  
			@par
			When a container widget has its enabled property set to `false`, 
			all its contained widgets are disabled, as well. 
			For example, 
			if the user clicks on any of the widgets contained in a disabled Container widget, no events are raised. 

			@note
			Setting the Enabled property to `false` does not disable the application's widget box or prevent the application window from receiving the focus.

			@see 
			- Container
		*/
		property<bool>::bind<Widget, &Widget::getEnabled, &Widget::setEnabled> Enabled;

		//! Gets a value indicating whether the widget has input focus.
		/*!
			### Property Value ### 
			
			> **bool**

			`true` if the widget has focus; otherwise, `false`.

			@see 
			- CanFocus
			- Focus
			- CanSelect
			- ContainsFocus
		*/
		property<bool, property<>::ro>::bind<Widget, &Widget::getFocused> Focused;

		//! Gets a value indicating whether the widget contains one or more child widgets.
		/*!
			### Property Value ### 
			
			> **bool**

			`true` if the widget contains one or more child widgets; otherwise, `false`.

			@see 
			- Widgets
		*/
		property<bool, property<>::ro>::bind<Widget, &Widget::hasChildren> HasChildren;

		//! Gets or sets the height of the widget.
		/*!
			### Property Value ### 
			
			> **unsigned short**

			The height of the widget in pixels.

			@remark
			Changes made to the Widget::Height and Widget::Top property values cause the Widget::Bottom property value of the widget to change.

			@see 
			- Top
			- Bottom
		*/
		phproperty<unsigned short>::bind<Widget, Arguments::eArgUnsignedShort, Arguments::height> Height;

		
		property<std::string>::bind<Widget, &Widget::getHelpTopic, &Widget::setHelpTopic> HelpTopic; //!< Gets or sets the help topic of the widget.

		//! Gets or sets a value indicating whether the widget is realized.
		/*!
			### Property Value ### 
			
			> **bool**

			`true` if the widget is realized; otherwise, `false`.

			@see 
			- Enabled
			- CanFocus
			- Hide()
			- Show()
		*/
		property<bool, property<>::ro>::bind<Widget, &Widget::getIsRealized> IsRealized;

		//! Gets or sets the distance, in pixels, between the left edge of the widget and the left edge of its container's client area.
		/*!
			### Property Value ### 
			
			> **short**

			An `short` representing the distance, in pixels, between the left edge of the widget and the left edge of its container's client area.

			@remark
			The value of this property is equivalent to the 'x' value of the Widget::Location property value of the widget.
			@par
			Changes made to the Widget::Width and Widget::Left property values cause the Widget::Right property value of the widget to change.

			@see
			- Right
			- Width
		*/
		property<short>::bind<Widget, &Widget::getLeft, &Widget::setLeft> Left;

		//! Gets or sets the coordinates of the upper-left corner of the widget relative to the upper-left corner of its container.
		/*!
			### Property Value ### 
			
			> PhPoint_t

			The `PhPoint_t` that represents the upper-left corner of the widget relative to the upper-left corner of its container.

			@remark
			Because the `PhPoint_t` struct is a value type, it is returned by value, 
			meaning accessing the property returns a copy of the upper-left point of the widget. 
			So, adjusting the x or y values of the `PhPoint_t` returned from this property will not affect the 
			Widget::Left, Widget::Right, Widget::Top, or Widget::Bottom property values of the widget. 
			To adjust these properties set each property value individually, or set the Widget::Location property with a new `PhPoint_t`. 
			@par
			If the Widget is a PhWidgets::Window, the Widget::Location property value represents the upper-left corner of the PhWidgets::Window in screen coordinates.

			@see
			- Window
		*/		
		property<PhPoint_t>::bind<Widget, &Widget::getLocation, &Widget::setLocation> Location;

		//! Gets or sets the parent container of the widget.
		/*!
			### Property Value ### 
			
			> PtWidget_t*

			The `PtWidget_t*` that represents the parent or container widget of the widget.

			@remark
			Setting the Parent property value to **nullptr** removes the widget from the Widget.WidgetCollection of its current parent widget.

			@note
			This property may and will return **nullptr** if current widget has no parent.
			Always check `widget.Parent != nullptr` before assingning this property to Widget class
			if you are unsure that widget have parent at first place.
			In case of empty parent (**nullptr** returned) code like `Widget parent = other_widget.Parent;`
			will throw the `std::invalid_argument` exception.

			### Examples ###

			@code
				PhWidgets::Button button(ptwidget);
				PhWidgets::Window main_window(ABN_MAIN_WINDOW);

				if(nullptr == button.Parent) // check if button have parent
					button.Parent = main_window; // setting parent

			@endcode

			@see
			- Window
			- Container
		*/
		property<PtWidget_t*>::bind<Widget, &Widget::getParent, &Widget::setParent> Parent;

		//! Gets or sets the absolute coordinates of the upper-left corner of the widget.
		/*!
			### Property Value ### 
			
			> PhPoint_t

			The `PhPoint_t` that represents the absolute coordinates of the upper-left corner of the widget.

			@remark
			Because the `PhPoint_t` struct is a value type, it is returned by value, 
			meaning accessing the property returns a copy of the upper-left point of the widget. 
			So, adjusting the x or y values of the `PhPoint_t` returned from this property will not affect the 
			Widget::Left, Widget::Right, Widget::Top, or Widget::Bottom property values of the widget. 
			To adjust these properties set each property value individually, or set the Widget::Position property with a new `PhPoint_t`. 
			@par
			If the Widget is a PhWidgets::Window, the Widget::Position property value represents the upper-left corner of the PhWidgets::Window in screen coordinates.

			@see
			- Window
		*/
		phproperty<PhPoint_t>::bind<Widget, Arguments::eArgPoint, Arguments::pos> Position;


		//! Gets the distance, in pixels, between the right edge of the widget and the left edge of its container's client area.
		/*!
			### Property Value ### 
			
			> **short**

			An `short` representing the distance, in pixels, between the right edge of the widget and the left edge of its container's client area.

			@remark
			The value of this property is equal to the sum of the Widget::Left property value, and the Widget::Width property value.
			@par
			The Widget::Right property is a read-only property. 
			You can manipulate this property value by changing the value of the Widget::Left or Widget::Width properties 
			or calling the Widget::SetBounds methods.

			@see
			- Left
			- Width
		*/
		property<short, property<>::ro>::bind<Widget, &Widget::getRight> Right;

		//! Gets or sets the size of the widget.
		/*!
			### Property Value ### 
			
			> PhDim_t

			The `PhDim_t` that represents the height and width of the widget in pixels.

			@remark
			Because the `PhDim_t` struct is a value type, it is returned by value, 
			meaning accessing the property returns a copy of the size of the widget. 
			So, adjusting the 'w' or 'h' values of the `PhDim_t` returned from this property will not affect the 
			Widget::Width or Widget::Height property values of the widget. 
			To adjust these properties set each property value individually, or set the Widget::Size property with a new `PhDim_t`. 

			@see
			- SetBounds(short x, short y, unsigned short width, unsigned short height)
		*/
		phproperty<PhDim_t>::bind<Widget, Arguments::eArgDim, Arguments::dim> Size;
		
		//! Gets or sets the resource that contains data about the widget.
		/*!
			### Property Value ### 
			
			> <b>const void*</b> 

			An `const void *` that contains data about the widget. The default is `nullptr`.

			### Examples ###

			@code
				// You have somewhere:
				PtWidget_t *ptwidget; // pointer to widget
			@endcode



			@code
				// constructing Widget
				PhWidgets::Widget widget(ptwidget);
				
				widget.Tag = PhWidgets::Colors::Red;
				PgColor_t color = Tag;
			@endcode

			@note
			Widget::Tag could accept any pointer and copies data from it in widget Widget::Arguments::user_data resource.
			If you want to pass data by 'raw pointer to data' then use `widget.Tag(ptr, size)` method.

			@code
				// constructing Widget
				PhWidgets::Widget widget(ptwidget);
				
				void *ptr = new char[100];

				// set resource:
				widget.Tag(ptr, 100 * sizeof(char));
				// or like this:
				widget.Tag.set(ptr, 100 * sizeof(char));
			@endcode

			@attention
			Do not provide just pointer for the Widget::Tag property to `set` if your intentions are to copy dynamic array! 
			Use `widget.Tag(ptr, size)` method instead. See example below:

			@code
				// constructing Widget
				PhWidgets::Widget widget(ptwidget);
				
				int *ptr = new int[42];
				float fvalue;
				double arr[20];

				// right use to copy to Widget::Arguments::user_data:
				widget.Tag(ptr, 42 * sizeof(int)); // copy 42 ints
				widget.Tag = fvalue; // copy 1 float
				widget.Tag = arr; // copy 20 double

				// exotic but valid use of storing just pointer in widget not the data it points to
				// copy 1 int* - only pointer! 
				widget.Tag = ptr; 
				// Note that property will return const int**.
				const int **ptr_get = widget.Tag;
				// where (*ptr_get) is the ptr passed
				ptr == (*ptr_get); // true
			@endcode

			@attention
			This property returns just raw `const void*` that is casted to user-provided type
			so be really carefull with all casts!
			Make shure that you know the exact type hiding beneath the pointer or 
			the behaviour is undefined.
			@par
			Although the property will cover you in some cases with `nullptr` as a result 
			if you will try to do some really unapropriate cast - do not rely on it much! 

			@code
				// constructing Widget
				PhWidgets::Widget widget(ptwidget);
				
				void *dptr = new double[42];

				widget.Tag(dptr, 42 * sizeof(double)); // set to 42 doubles

				// right:
				const double *dptr_get = widget.Tag; // get
				const void *vptr_get = widget.Tag; // get - always safe!

				// undefined behaviour:
				// const float *fptr_get = widget.Tag; // Wrong type! Do not do this!
				// const MyCustomClass *obj_ptr_get = Widget.Tag; // UB get! Do not do this!
			@endcode


			@remark
			Any pointer can be assigned to this property. 
			A common use for the Tag property is to store data that is closely associated with the widget. 
			@par
			For example, if you have a widget that displays different colors, 
			you might store a pointer to struct that contains the set of defined colors in that widget's Widget::Tag property 
			so the colors can be accessed quickly.

			@see
			- Widget::Arguments::user_data
		*/
		tag_property<Widget, &Widget::getTag, &Widget::setTag> Tag;

		//! Gets or sets the distance, in pixels, between the top edge of the widget and the top edge of its container's client area.
		/*!
			### Property Value ### 
			
			> **short**

			An `short` representing the distance, in pixels, between the top edge of the widget and the top edge of its container's client area.

			@remark
			The value of this property is equivalent to the 'y' value of the Widget::Location property value of the widget.
			@par
			Changes made to the Widget::Height and Widget::Top property values cause the Widget::Bottom property value of the widget to change.

			@see
			- Bottom
			- Height
		*/
		property<short>::bind<Widget, &Widget::getTop, &Widget::setTop> Top;

		//! Gets or sets a value indicating whether the widget and all its child widgets are displayed.
		/*!
			### Property Value ### 
			
			> **bool**

			`true` if the widget and all its child widgets are displayed; otherwise, `false`. The default is `true`.

			@remark
			Note that even if Widget::Visible is set to `true`, the widget might not be visible to the user if it is obscured behind other widgets.

			@see 
			- Enabled
			- CanFocus
			- Hide()
			- Show()
		*/
		property<bool>::bind<Widget, &Widget::getVisible, &Widget::setVisible> Visible;

		//! Gets or sets the width of the widget.
		/*!
			### Property Value ### 
			
			> **unsigned short**

			The width of the widget in pixels.

			@remark
			Changes made to the Widget::Width and Widget::Left property values cause the Widget::Right property value of the widget to change.

			@see 
			- Left
			- Right
		*/
		phproperty<unsigned short>::bind<Widget, Arguments::eArgUnsignedShort, Arguments::width> Width;

		phbitmask<unsigned long, Flags::Extended::eExFlags>::bind<Widget, ArgUnsignedLong::eArgUnsignedLong, ArgUnsignedLong::eflags>	ExtendedFlags; //!< Gets or sets extended flags inherited by all widgets. See Flags::Extended::eExFlags.
		phbitmask<long, Flags::eFlags>::bind<Widget, ArgLong::eArgLong, ArgLong::flags>													WidgetFlags; //!< Gets or sets flags inherited by all widgets. See Flags::eFlags.
		phbitmask<long, Flags::Resize::eResizeFlags>::bind<Widget, ArgLong::eArgLong, ArgLong::resize_flags>							ResizeFlags; //!< Gets or sets flags to control a widget's resize policy. See Flags::Resize::eResizeFlags.	
		//@}

		//! @name Events
		//@{ 
		phwidgets_event<Widget, Widget::Callbacks::destroyed>		Destroyed; //!< Occurs when the widget is destroyed.
		phwidgets_event<Widget, Widget::Callbacks::blocked>			Blocked; //!< Occurs when the widget is blocked.
		phwidgets_event<Widget, Widget::Callbacks::dnd>				DragDrop; //!< Occurs when a drag-and-drop operation is completed.
		phwidgets_event<Widget, Widget::Callbacks::is_destroyed>	IsDestroyed; //!< Occurs when the widget's resources are being released.
		phwidgets_event<Widget, Widget::Callbacks::outbound>		Outbound; //!< Occurs when you press the pointer button on the widget and then move out of the "hot spot" with the button still depressed.
		phwidgets_event<Widget, Widget::Callbacks::realized>		Realized; //!<  Occurs when the widget is realized.
		phwidgets_event<Widget, Widget::Callbacks::unrealized>		Unrealized; //!<  Occurs when the widget is unrealized.
		//@}

		//! @name Event raisers
		//@{ 
		void OnDestroyed(PtCallbackInfo_t *info); //!< Raises the Widget::Destroyed event.
		void OnBlocked(PtCallbackInfo_t *info); //!< Raises the Widget::Blocked event.
		void OnDragDrop(PtCallbackInfo_t *info); //!< Raises the Widget::DragDrop event.
		void OnOutbound(PtCallbackInfo_t *info); //!< Raises the Widget::Outbound event.
		void OnRealized(PtCallbackInfo_t *info); //!< Raises the Widget::Realized event.
		void OnUnrealized(PtCallbackInfo_t *info); //!< Raises the Widget::Unrealized event.
		//@}

		

	};

	namespace typedefs
	{
		typedef
		cppbitmasks::bitmask<
			unsigned, 
			PhWidgets::Widget::Flags::Anchor::eAnchorStyles,
			PhWidgets::Widget::Flags::Anchor::All
		>
		anchor_flags_bitmask;
	}
} // namespace PhWidgets

cppbitmasks::bitmask<unsigned long, PhWidgets::Widget::Flags::Extended::eExFlags> operator|(const PhWidgets::Widget::Flags::Extended::eExFlags &flag1, const PhWidgets::Widget::Flags::Extended::eExFlags &flag2);
cppbitmasks::bitmask<unsigned long, PhWidgets::Widget::Flags::Extended::eExFlags> operator&(const PhWidgets::Widget::Flags::Extended::eExFlags &flag1, const PhWidgets::Widget::Flags::Extended::eExFlags &flag2);
cppbitmasks::bitmask<unsigned long, PhWidgets::Widget::Flags::Extended::eExFlags> operator^(const PhWidgets::Widget::Flags::Extended::eExFlags &flag1, const PhWidgets::Widget::Flags::Extended::eExFlags &flag2);

cppbitmasks::bitmask<long, PhWidgets::Widget::Flags::eFlags> operator|(const PhWidgets::Widget::Flags::eFlags &flag1, const PhWidgets::Widget::Flags::eFlags &flag2);
cppbitmasks::bitmask<long, PhWidgets::Widget::Flags::eFlags> operator&(const PhWidgets::Widget::Flags::eFlags &flag1, const PhWidgets::Widget::Flags::eFlags &flag2);
cppbitmasks::bitmask<long, PhWidgets::Widget::Flags::eFlags> operator^(const PhWidgets::Widget::Flags::eFlags &flag1, const PhWidgets::Widget::Flags::eFlags &flag2);

cppbitmasks::bitmask<long, PhWidgets::Widget::Flags::Resize::eResizeFlags> operator|(const PhWidgets::Widget::Flags::Resize::eResizeFlags &flag1, const PhWidgets::Widget::Flags::Resize::eResizeFlags &flag2);
cppbitmasks::bitmask<long, PhWidgets::Widget::Flags::Resize::eResizeFlags> operator&(const PhWidgets::Widget::Flags::Resize::eResizeFlags &flag1, const PhWidgets::Widget::Flags::Resize::eResizeFlags &flag2);
cppbitmasks::bitmask<long, PhWidgets::Widget::Flags::Resize::eResizeFlags> operator^(const PhWidgets::Widget::Flags::Resize::eResizeFlags &flag1, const PhWidgets::Widget::Flags::Resize::eResizeFlags &flag2);

PhWidgets::typedefs::anchor_flags_bitmask operator|(const PhWidgets::Widget::Flags::Anchor::eAnchorStyles &flag1, const PhWidgets::Widget::Flags::Anchor::eAnchorStyles &flag2);
PhWidgets::typedefs::anchor_flags_bitmask operator&(const PhWidgets::Widget::Flags::Anchor::eAnchorStyles &flag1, const PhWidgets::Widget::Flags::Anchor::eAnchorStyles &flag2);
PhWidgets::typedefs::anchor_flags_bitmask operator^(const PhWidgets::Widget::Flags::Anchor::eAnchorStyles &flag1, const PhWidgets::Widget::Flags::Anchor::eAnchorStyles &flag2);

bool operator==(const PhArea_t &lhs, const PhArea_t &rhs);
bool operator!=(const PhArea_t &lhs, const PhArea_t &rhs);

#endif // PHWIDGETS_WIDGET_H
