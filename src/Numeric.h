#ifndef PHWIDGETS_NUMERIC_H
#define PHWIDGETS_NUMERIC_H

#include <photon/PtNumeric.h>

#include "./Compound.h"


namespace PhWidgets
{
	/*!
		@struct PhWidgets::Numeric
		@ingroup Widgets
	*/

	//! A superclass for numeric widgets
	/*!
		Numeric is a parent class for all numeric widgets. 
		It creates a Text widget and arrows to let you interact with the widget. 
		It also creates some of the base functionality of numeric widgets.

		@see
		- NumericFloat
		- NumericInteger
	*/		
	class Numeric:
		public Compound
	{
	public:

		//! Contains resource IDs for Numeric arguments. @ingroup Resources
		struct ThisArgs
		{
			//! Contains resource IDs for Numeric arguments of type <b>char*</b>.
			struct ArgPChar
			{
				//! Resource IDs for Numeric arguments of type <b>char*</b>.

				/*!
					### Aliases ###
					
					PhWidgets::Numeric::Arguments::eArgPChar,
					PhWidgets::Numeric::ArgPChar::eArgPChar

					See Widget::resource for usage description.
				*/
				enum eArgPChar
				{
					numeric_prefix = Pt_ARG_NUMERIC_PREFIX,
					numeric_suffix = Pt_ARG_NUMERIC_SUFFIX
				};
			};	
			
			//! Contains resource IDs for Numeric arguments of type **unsigned short**.
			struct ArgUnsignedShort
			{
				//! Resource IDs for Numeric arguments of type **unsigned short**.

				/*!
					### Aliases ###
					
					PhWidgets::Numeric::Arguments::eArgUnsignedShort,
					PhWidgets::Numeric::ArgUnsignedShort::eArgUnsignedShort

					See Widget::resource for usage description.
				*/
				enum eArgUnsignedShort
				{
					numeric_spacing = Pt_ARG_NUMERIC_SPACING,
					numeric_updown_width = Pt_ARG_NUMERIC_UPDOWN_WIDTH
				};

				//! Resource IDs for Numeric flags of type **unsigned short**.

				/*!
					### Aliases ###
					
					PhWidgets::Numeric::Arguments::eArgUnsignedShortFlag,
					PhWidgets::Numeric::ArgUnsignedShort::eArgUnsignedShortFlag

					See Widget::resource for usage description.
				*/
				enum eArgUnsignedShortFlag
				{
					numeric_flags = Pt_ARG_NUMERIC_FLAGS
				};
			};
		};

        //! Contains flags for Numeric resources. @ingroup Resources
		struct ThisFlags
		{
			//! Numeric flags for Numeric resource Numeric::Arguments::cbox_flags.
			/*!
				The default setting of Numeric::Arguments::numeric_flags resource is 0; that is, no flags have been set. 

				### Aliases ###
				
				PhWidgets::Numeric::Flags::eNumericFlags
			*/
			enum eNumericFlags
			{
				AutoHighlight = Pt_NUMERIC_AUTO_HIGHLIGHT, //!< Autohighlight text when selected. 
				EnableUpDown = Pt_NUMERIC_ENABLE_UPDOWN, //!< Display the up/down buttons. 
				Hexadecimal = Pt_NUMERIC_HEXADECIMAL,  //!< Display the value as a hexadecimal number (applies only to NumericInteger). 
                UseSeparators = Pt_NUMERIC_USE_SEPARATORS,  //!< Insert comma separators in values (e.g. 1,000).
                Wrap = Pt_NUMERIC_WRAP  //!< Wrap numbers from minimum to maximum and from maximum to minimum.
			};
		};

		//! Contains resource IDs for arguments of type **unsigned short**. @ingroup Resources
		struct ArgUnsignedShort:
			public ArgumentsEx<Compound::ArgUnsignedShort>,
			public ThisArgs::ArgUnsignedShort
		{
			typedef ThisArgs::ArgUnsignedShort::eArgUnsignedShort eArgUnsignedShort;
			typedef ThisArgs::ArgUnsignedShort::eArgUnsignedShortFlag eArgUnsignedShortFlag;
		};

		//! Contains resource IDs for arguments of type <b>char*</b>. @ingroup Resources
		struct ArgPChar:
			public ArgumentsEx<Compound::ArgPChar>,
			public ThisArgs::ArgPChar
		{
			typedef ThisArgs::ArgPChar::eArgPChar eArgPChar;
		};	

		//! Contains resource IDs for all Numeric arguments. @ingroup Resources
		struct Arguments:
			public ArgUnsignedShort,
			public ArgPChar,
			public Compound::Arguments
        { };

		//! Contains flags for all Numeric resources. @ingroup Resources
		struct Flags:
			public ThisFlags,
			public Compound::Flags
        { };

		typedef ResourceFrom<Compound::WidgetResourcesSingleton>::
			Define::String<ThisArgs::ArgPChar::eArgPChar>::
			Define::Scalar<ThisArgs::ArgUnsignedShort::eArgUnsignedShort, unsigned short>::
			Define::Flag<ThisArgs::ArgUnsignedShort::eArgUnsignedShortFlag, unsigned short>::

		resource_type WidgetResourcesSingleton;

	protected:
		virtual void check();
						
	public:
		//! Resources of the Numeric
		/*!
			@see
			- Widget::resource
		*/
		WidgetResourcesSingleton resource;

		//! (constructor) 
		/*!
			Constructs a Numeric widget by ID.
			@param[in] abn ID given by PhAB to widget (like 'ABN_WIDGET_NAME').
		*/
		explicit Numeric(int abn);

		//! (constructor) 
		/*!
			Constructs a Numeric widget by pointer to widget.
			@param[in] wdg pointer to Photon widget.
		*/
		explicit Numeric(PtWidget_t *wdg);
		
		//! (copy constructor) 
		/*!
			Constructs a Numeric widget by copy.
			@param[in] other another Numeric widget to be used as source to initialize the elements of the container with.
		*/
		Numeric(const Numeric &other);

		//! Assigns value in Numeric widget 
		/*!
			Replaces the contents of the Numeric widget.
			@param[in] other another Numeric widget to use as data source.
		*/
		Numeric &operator=(const Numeric &other);

		//! @name Properties
		//! Properties are used to simplify use of widget resources.
		//@{

		//@}
		
	};
	
} // namespace PhWidgets

cppbitmasks::bitmask<unsigned short, PhWidgets::Numeric::Flags::eNumericFlags> operator|(const PhWidgets::Numeric::Flags::eNumericFlags &flag1, const PhWidgets::Numeric::Flags::eNumericFlags &flag2);
cppbitmasks::bitmask<unsigned short, PhWidgets::Numeric::Flags::eNumericFlags> operator&(const PhWidgets::Numeric::Flags::eNumericFlags &flag1, const PhWidgets::Numeric::Flags::eNumericFlags &flag2);
cppbitmasks::bitmask<unsigned short, PhWidgets::Numeric::Flags::eNumericFlags> operator^(const PhWidgets::Numeric::Flags::eNumericFlags &flag1, const PhWidgets::Numeric::Flags::eNumericFlags &flag2);


#endif // PHWIDGETS_NUMERIC_H
