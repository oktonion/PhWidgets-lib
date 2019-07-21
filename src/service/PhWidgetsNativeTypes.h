//! @addtogroup native Photon native functions and types
//! All members of this group are located at global namespace
//!@{

/*!
    @struct PtWidget_t

    Native widget handle of Photon microGUI library.

    @note
    Do not use directly. You can gain access to all widget functionality with corresponding PhWidgets class.

    ### Examples ###

    @code
        // You have somewhere:
        PtWidget_t *ptwidget; // pointer to widget
        int ptwidget_realized_callback( PtWidget_t *, void *, PtCallbackInfo_t *); // callback

        // constructing Widget
        PhWidgets::Widget widget(ptwidget);
        
        // set of widget width
        widget.Width = 10;

        // add callback
        widget.Realized += ptwidget_realized_callback;
    @endcode

    @see
    - PhWidgets::Widget
*/

/*!
    @struct PhPoint_t
    
    Coordinates of a single point.

    The PhPoint_t structure describes the coordinates of a single point. 
    It contains at least the following members: 

    ### Members ###

    > short x
        X-axis coordinate. 
    > short y 
        Y-axis coordinate.
    
    @see
    - PhWidgets::Widget::Location
    - PhWidgets::Widget::Position
*/

/*!
    @struct PhDim_t
    
    Dimensions of an area.

    The PhDim_t structure defines the dimensions of an area. 
    It contains at least the following members: 
    
    ### Members ###

    > unsigned short w
        Width of the area. 
    > unsigned short h 
        Height of the area.

    @see
    - PhWidgets::Widget::Size
*/

/*!
    @struct PhArea_t
    
    Position and dimensions of a rectangular area.

    The PhArea_t structure describes the position and dimensions of a rectangular area. 
    It's used extensively by the PhWidgets::Widget.
    This structure contains at least the following members:
    
    ### Members ###

    > PhPoint_t pos
        Upper-left corner of the area. 
    > PhDim_t size 
        Size of the area. 

    @see
    - PhWidgets::Widget::Bounds
*/

/*!
    @struct PhRegionDataHdr_t
    
    Data that's attached to a region.

    The PhRegionDataHdr_t structure describes data that's attached to a region. 
    It includes at least the following members: 
    
    ### Members ###

    > unsigned short len
        The length of the data, in bytes. The data immediately follows the PhRegionDataHdr_t structure in the region's block of data. 
    > unsigned short type
        The type of data, which indicates the data structure used.
    
    @remark
    Use PhWidgets::Cursor to manipulate widget cursor.
*/

/*!
    @struct PhCursorDef_t
    
    Bitmap for the cursor.

    The PhCursorDef_t structure is used to define bitmaps to be used as the cursor. 
    The members include at least: 
    
    ### Members ###
    
    > PhRegionDataHdr_t hdr
        A pointer to a PhRegionDataHdr_t structure that defines the region data header. 
    > PhPoint_t size1
        The dimensions of the first bitmap plane, in pixels. 
    > PhPoint_t offset1
        The position of the upper-left corner of the first plane of the bitmap, relative to the hot spot. 
    > PgColor_t color1
        The color of the first bitmap plane. 
    > char bytesperline1
        The number of bytes per line for the first bitmap plane. 
    > PhPoint_t size2
        The dimensions of the second bitmap plane, in pixels. 
    > PhPoint_t offset2
        The position of the upper-left corner of the second plane of the bitmap, relative to the hot spot. 
    > PgColor_t color2
        The color of the second bitplane. You can't have more than two bitplanes. 
    > char bytesperline2
        The number of bytes per line for the second bitmap plane. 
    > char images
        The bitmap image data, as a series of 1-bit-per-pixel planes. 
    
    @remark
    Use PhWidgets::Cursor to manipulate widget cursor.
*/

/*!
    @struct PgColor_t

    > `typedef unsigned long PgColor_t;`

    Composite color value.

    The PgColor_t type definition describes a composite color value. 
    The interpretation of the color depends on the current color model.

    @remark
    Use PhWidgets::Drawing::Color and PhWidgets::Drawing::Colors to manipulate colors of the widget.
*/

/*!
    @struct PtGridLayoutData_t
    
    Defines additional layout data for the widget when its container widget uses a PtGridLayout type layout.
 
    The members include at least: 
    
    ### Members ###
    
    > short flags
        Flags used by PtGridLayoutData_t.
    
    @see
    - PhWidgets::Widget::Arguments::grid_layout_data
*/

/*!
    @struct PtRowLayoutData_t
    
    Defines additional layout data for the widget when its container widget uses a PtRowLayout type layout.
 
    The members include at least: 
    
    ### Members ###
    
    > PhDim_t hint
        Contains w (width) and h (height) hints for this child widget. 
        Think of these hints as a user defined minimum size, even if the widget could be smaller. 
        Set w and h to 0 if you just want to apply flags to this child.
    > short flags
        Flags used by PtRowLayoutData_t.
    
    @see
    - PhWidgets::Widget::Arguments::row_layout_data
*/

/*!
    @struct PhRect_t
    
    Coordinates of a rectangle.
 
    The PhRect_t structure describes the coordinates of a rectangle. 
    It contains at least the following members: 
    
    ### Members ###
    
    > PhPoint_t ul
        Upper-left corner. 
    > PhPoint_t lr
        Lower-right corner.
    
    @see
    - PhWidgets::Widget::Arguments::extent
*/

/*!
    @struct PtCallback_t
    
    Regular callback structure.
 
    The PtCallback_t structure lets you specify a widget's callbacks.
    This structure contains at least: 
    
    ### Members ###
    
    > int (*event_f)( PtWidget_t *, void *, PtCallbackInfo_t * )
        A pointer to the callback function. 
    > void *data
        A pointer to data that you want to pass as the second parameter to the callback function when it's invoked.

    ### Callback functions ###

    A callback function takes the following arguments:

    > PtWidget_t *widget
        A pointer to the widget instance that invoked the callback. 

    > void *client_data
        The data from the PtCallback_t structure.
        @note
        A PhAB callback takes as its second argument a pointer to an ApInfo_t structure. For more information, see the Photon Library Reference.

    > PtCallbackInfo_t *cbinfo
        A pointer to a common Photon callback structure. 
        The structure provides information related to the widget callback being invoked, the Photon event, and some widget-specific callback data. 
        The format of the data varies with the widget class and callback type. 
        For more information, see PtCallbackInfo_t. 

    Callback functions should return `Pt_CONTINUE` unless the description of the widget's callback resource tells you to return something else. 
    
    @see
    - PhWidgets::Widget::Realized
    - PhWidgets::Widget::Unrealized
*/

/*!
    @struct PtRawCallback_t
    
    Event handler structure.
 
    The PtRawCallback_t structure lets you specify event handlers (raw and filter callbacks) for your application's widgets.
    This structure contains at least: 
    
    ### Members ###
    
    > event_mask
        A bitmap that specifies which events trigger the function specified in `event_f`. See PhEvent_t.
    > int (*event_f)( PtWidget_t *, void *, PtCallbackInfo_t * )
        A pointer to the callback function. 
    > void *data
        A pointer to data that you want to pass as the second parameter to the callback function when it's invoked.
    
    @see
    - PhWidgets::Widget::Realized
    - PhWidgets::Widget::Unrealized
*/

/*!
    @struct PtHotkeyCallback_t
    
    Hotkey handler structure.
 
    The PtHotkeyCallback_t structure lets you specify hotkeys or hotkey handlers, or both, for various widgets.
    This structure contains at least: 
    
    ### Members ###
 
    > unsigned short key_sym_cap
        Depending on the specified flags, this member contains either the symbol or cap of the key to be interpreted as a hotkey. For valid key_sym_cap values, see <photon/PkKeyDef.h>. 
    > short flags
        Determines how key_sym_cap is interpreted and whether or not key_mods is used.
    > unsigned long key_mods
        Key modifiers that must be active for the key to be considered a hotkey.
    > PtWidget_t *widget
        If `event_f` is NULL, the widget member's activate callback is invoked with a reason_subtype of `Pt_CB_HOTKEY`. 
        If the `widget` member is NULL when the hotkey is attached, it's set to the widget that the hotkey is attached to. 
    > void *data
        A pointer to any data that you want to pass as the second argument to the callback function. 
    > int (*event_f)( PtWidget_t *, void *, PtCallbackInfo_t * )
        A pointer to the hotkey function. 
        If `event_f` is NULL when the hotkey is activated, 
        the widget that the hotkey is attached to has its PhWidgets::Basic::Activate invoked with a reason_subtype of `Pt_CB_HOTKEY`. 
        

    @see
    - PhWidgets::Basic::Activate
    - PhWidgets::Widget::Realized
    - PhWidgets::Widget::Unrealized
*/

/*!
    @struct PtCallbackInfo_t
    
    Specific callback information.
 
    The PtCallbackInfo_t structure is the third argument passed to all callback functions. 
    You can use this structure to determine why callbacks occurred and to get the specific callback information. 
    This structure contains at least: 
    
    ### Members ###
    
    > unsigned long reason
        The reason why this callback was invoked. 
    > unsigned long reason_subtype
        If there are different ways to invoke the callback, this member indicates which one. 
    > PhEvent_t *event
        A pointer to a PhEvent_t structure that describes the event that caused this callback to be invoked.
    > void *cbdata
        A pointer to callback-specific data. 

    @remark
    For more information see events of PhWidgets.

    @see
    - PhWidgets::Widget::Realized
    - PhWidgets::Widget::Unrealized
*/

/*!
    @struct PhEvent_t
    
    Data structure describing an event.

    The PhEvent_t structure describes an event. 
    It contains at least the following members: 
    
    ### Members ###
    
    > unsigned long type
        A predefined event type. 
    > unsigned short subtype
        Further information about the event. 
    > unsigned short processing_flags
        Flags used or set in processing the event. These flags are ignored when you emit an event, and always zero in a received event. 
    > PhEventRegion_t emitter
        A PhEventRegion_t structure identifying the region that emitted the event. 
    > PhEventRegion_t collector
        A PhEventRegion_t structure identifying the region that collected the event. 
        When your process has many regions open, collector lets you distinguish which of its regions was involved. 
    > unsigned short input_group
        The number of the input group. A value of 0 means there's no input group. 
    > unsigned short flags
        Event-modifier flags.
    > unsigned long timestamp
        When the event was emitted, in milliseconds. The Photon Manager generates this member. 
    > PhPoint_t translation
        A PhPoint_t structure that specifies the translation between the emitting region's origin and the collecting region's origin. 
        An application uses this member to convert coordinates that are relative to the emitter's region to coordinates that are relative to the collector's region. 
    > unsigned short num_rects
        The number of rectangles associated with the event.
    > unsigned short data_len
        The length of the data associated with the event. Since event data is optional, you can set data_len to 0 when there's no data.
    
    @remark
    For more information see events of PhWidgets.

    @see
    - PhWidgets::Widget::Realized
    - PhWidgets::Widget::OnDestroyed
    - PhWidgets::Widget::Unrealized
*/

//!@}
