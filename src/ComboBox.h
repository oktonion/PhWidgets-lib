#ifndef PHWIDGETS_COMBO_BOX_H
#define PHWIDGETS_COMBO_BOX_H

#include <photon/PtComboBox.h>

#include "./Compound.h"


namespace PhWidgets
{
	/*!
		@struct PhWidgets::ComboBox
		@ingroup Widgets
	*/

	//! A text field with a list of choices
	/*!
		The ComboBox class provides a widget that's built from two exported subordinate widgets: 
        [List](@ref PhWidgets::List) and [Text](@ref PhWidgets::TextWidget).

        A ComboBox widget provides a text-entry area and a list of choices.
        @par
        You can type in the text field or choose a predefined entry from the list. 
        The list can be either:
        @par
        - Static: Always present above or below the text field.
        - Dropping: You must click a button to see the list.
        @par
        The widget behaves like a List or Text widget, depending on which part has focus.

        @note
        You can't specify the selection mode for the list.

        To select an item using the pointer, either click on an item or drag the pointer down the list 
        and release the button when the correct item is highlighted. 
        You can select only one item. 
        If you drag the pointer, the list can scroll.
        @par
        A blocking mechanism lets ComboBox block the inheritance of certain resources from its subordinate widgets. 
        This prevents any actions that would negatively affect the look and behavior of a ComboBox widget. 
	*/		
	class ComboBox:
		public Compound
	{
	public:

		//! Contains resource IDs for ComboBox arguments. @ingroup Resources
		struct ThisArgs
		{
    		//! Contains resource IDs for ComboBox arguments of type **unsigned short**.
			struct ArgUnsignedShort
			{
				//! Resource IDs for ComboBox arguments of type **unsigned short**.

				/*!
					### Aliases ###
					
					PhWidgets::ComboBox::Arguments::eArgUnsignedShort,
					PhWidgets::ComboBox::ArgUnsignedShort::eArgUnsignedShort

					See Widget::resource for usage description.
				*/
				enum eArgUnsignedShort
				{
					button_width = Pt_ARG_CBOX_BUTTON_WIDTH, //!< The width of the drop button, in pixels. Default is 13.
					max_visible_count = Pt_ARG_CBOX_MAX_VISIBLE_COUNT,  //!< The maximum number of list items that may be visible before scrollbars appear.
                                                                        //!< If this is 0, the entire list is displayed without scrollbars.
                    selected_item = Pt_ARG_CBOX_SEL_ITEM  //!< An index into List::Arguments::items that indicates which list item is currently selected.
				};
			};

            //! Contains resource IDs for ComboBox arguments of type **unsigned long**.
			struct ArgUnsignedLong
			{
				//! Resource IDs for ComboBox arguments of type **unsigned long**.

				/*!
					### Aliases ###
					
					PhWidgets::ComboBox::Arguments::eArgUnsignedLong,
					PhWidgets::ComboBox::ArgUnsignedLong::eArgUnsignedLong

					See Widget::resource for usage description.
				*/
				enum eArgUnsignedLong
				{
                    //! The fill color of the text area.

				    /*!
                        Default value is Pg_LGRAY.
                        
                        @note 
                        This resource should be `PgColor_t` type but for some reason documentation says **unsigned long**.
                    */
					text_fill_color = Pt_ARG_CBOX_TEXT_FILL_COLOR
				};

                //! Resource IDs for ComboBox flags of type **unsigned long**.

				/*!
					### Aliases ###
					
					PhWidgets::ComboBox::Arguments::eArgUnsignedLongFlag,
					PhWidgets::ComboBox::ArgUnsignedLong::eArgUnsignedLongFlag

					See Widget::resource for usage description.
				*/
				enum eArgUnsignedLongFlag
                {
                    cbox_flags = Pt_ARG_CBOX_FLAGS //!< [Flags](@ref ComboBox::Flags::eComboBoxFlags) of ComboBox widget.
                };
			};
		};

        //! Contains resource IDs for ComboBox callbacks. @ingroup Resources
		struct ThisCallbacks
		{
            //! Contains resource IDs for ComboBox callbacks of type `PtCallback_t`.
			struct Callback
			{
                //! Resource IDs for ComboBox arguments of type `PtCallback_t`.
				/*!
					### Aliases ###
					
					PhWidgets::ComboBox::Callbacks::eCallback,
					PhWidgets::ComboBox::Callback::eCallback

					See Widget::resource for usage description.
				*/
				enum eCallback
				{
					list_activate = Pt_CB_CBOX_ACTIVATE, //!< A list of `PtCallback_t` structures that define the callbacks that the widget invokes when the list is activated (i.e opened). 
					list_close = Pt_CB_CBOX_CLOSE //!< A list of `PtCallback_t` structures that define the callbacks that are invoked when you close the combobox's list. 
				};
			};
		};

        //! Contains flags for ComboBox resources. @ingroup Resources
		struct ThisFlags
		{
			//! ComboBox flags for ComboBox resource ComboBox::Arguments::cbox_flags.
			/*!
				The default setting of ComboBox::Arguments::cbox_flags resource is 0; that is, no flags have been set. 

				### Aliases ###
				
				PhWidgets::ComboBox::Flags::eComboBoxFlags
			*/
			enum eComboBoxFlags
			{
				AltDown = Pt_COMBOBOX_ALT_DOWN, //!< Enable the Alt-↓ keychord, which displays the list and highlights the item corresponding to the current text.
				MaxWidth = Pt_COMBOBOX_MAX_WIDTH, //!< Make the combo box size itself to fit the longest list item. 
				IsOpen = Pt_COMBOBOX_OPEN,  //!< (read-only) If this bit is set, the list is currently open. 
                StaticList = Pt_COMBOBOX_STATIC,  //!< Make the list field static and remove the drop button. 
                                                  //!< If this bit is off, the list field is visible only when the drop button is pressed. 
                ListAbove = Pt_COMBOBOX_TOP  //!< Place the list field above the text field. 
                                             //!< If this bit is off, the list field is placed below the text field. 
                                             //!< If there isn't enough space between the text field and the edge of the screen, 
                                             //!< the list may appear on the opposite side of the text field. 
			};
		};

		//! Contains resource IDs for arguments of type **unsigned short**. @ingroup Resources
		struct ArgUnsignedShort:
			public ArgumentsEx<Compound::ArgUnsignedShort>,
			public ThisArgs::ArgUnsignedShort
		{
			typedef ThisArgs::ArgUnsignedShort::eArgUnsignedShort eArgUnsignedShort;
		};

		//! Contains resource IDs for arguments of type **unsigned long**. @ingroup Resources
		struct ArgUnsignedLong:
			public ArgumentsEx<Compound::ArgUnsignedLong>,
			public ThisArgs::ArgUnsignedLong
		{
			typedef ThisArgs::ArgUnsignedLong::eArgUnsignedLong eArgUnsignedLong;
            typedef ThisArgs::ArgUnsignedLong::eArgUnsignedLongFlag eArgUnsignedLongFlag;
		};	

		//! Contains resource IDs for all ComboBox arguments. @ingroup Resources
		struct Arguments:
			public ArgUnsignedShort,
			public ArgUnsignedLong,
			public Compound::Arguments
        { };

		//! Contains resource IDs for all ComboBox callbacks. @ingroup Resources
		struct Callbacks:
			public Callback,
			public Compound::Callbacks
		{ };

		//! Contains flags for all ComboBox resources. @ingroup Resources
		struct Flags:
			public ThisFlags,
			public Compound::Flags
        { };

		typedef ResourceFrom<Compound::WidgetResourcesSingleton>::
			Define::Scalar<ThisArgs::ArgUnsignedShort::eArgUnsignedShort, unsigned short>::
			Define::Color<ThisArgs::ArgUnsignedLong::eArgUnsignedLong, unsigned long>:: // that's right - color of unsigned long
            Define::Flag<ThisArgs::ArgUnsignedLong::eArgUnsignedLongFlag, unsigned long>::
            
            Define::Link<ThisCallbacks::Callback::eCallback, PtCallback_t*>::

		resource_type WidgetResourcesSingleton;

	protected:
		virtual void check();
						
	public:
		//! Resources of the ComboBox
		/*!
			@see
			- Widget::resource
		*/
		WidgetResourcesSingleton resource;

		//! (constructor) 
		/*!
			Constructs a ComboBox widget by ID.
			@param[in] abn ID given by PhAB to widget (like 'ABN_WIDGET_NAME').
		*/
		explicit ComboBox(int abn);

		//! (constructor) 
		/*!
			Constructs a ComboBox widget by pointer to widget.
			@param[in] wdg pointer to Photon widget.
		*/
		explicit ComboBox(PtWidget_t *wdg);
		
		//! (copy constructor) 
		/*!
			Constructs a ComboBox widget by copy.
			@param[in] other another ComboBox widget to be used as source to initialize the elements of the container with.
		*/
		ComboBox(const ComboBox &other);

		//! Assigns value in ComboBox widget 
		/*!
			Replaces the contents of the ComboBox widget.
			@param[in] other another ComboBox widget to use as data source.
		*/
		ComboBox &operator=(const ComboBox &other);

		//! @name Properties
		//! Properties are used to simplify use of widget resources.
		//@{

		//@}
		
	};
	
} // namespace PhWidgets

cppbitmasks::bitmask<unsigned short, PhWidgets::ComboBox::Flags::eComboBoxFlags> operator|(const PhWidgets::ComboBox::Flags::eComboBoxFlags &flag1, const PhWidgets::ComboBox::Flags::eComboBoxFlags &flag2);
cppbitmasks::bitmask<unsigned short, PhWidgets::ComboBox::Flags::eComboBoxFlags> operator&(const PhWidgets::ComboBox::Flags::eComboBoxFlags &flag1, const PhWidgets::ComboBox::Flags::eComboBoxFlags &flag2);
cppbitmasks::bitmask<unsigned short, PhWidgets::ComboBox::Flags::eComboBoxFlags> operator^(const PhWidgets::ComboBox::Flags::eComboBoxFlags &flag1, const PhWidgets::ComboBox::Flags::eComboBoxFlags &flag2);

#endif // PHWIDGETS_COMBO_BOX_H
