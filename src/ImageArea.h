#ifndef PHWIDGETS_IMAGE_AREA_H
#define PHWIDGETS_IMAGE_AREA_H

#include <photon/PtImageArea.h>

#include "./Container.h"
#include "./Drawing/Image.h"

namespace PhWidgets
{
	/*!
		@struct PhWidgets::ImageArea
		@ingroup Widgets
	*/

	//! Represents an image area widget for displaying an image.
	/*!
		ImageArea is an area in which you can display an image. 
        You can select an area, zoom in and out, and scroll if the image is too large to fit in the area. 
        You can optionally display a grid when you've zoomed in past a specified amount.

		@note
		ImageArea can not handle alpha images.

		@see
		- Image
		- Container
	*/	
	class ImageArea:
		public Container
	{
	public:

		//! Contains resource IDs for ImageArea arguments. @ingroup Resources
		struct ThisArgs
		{
			//! Contains resource IDs for ImageArea arguments of type **long**.
			struct ArgLong
			{
				//! Resource IDs for ImageArea arguments of type **long**.

				/*!
					### Aliases ###
					
					PhWidgets::ImageArea::Arguments::eArgLong,
					PhWidgets::ImageArea::ArgLong::eArgLong

					See Widget::resource for usage description.
				*/
				enum eArgLong
				{
					grid_threshold = Pt_ARG_IMAGEAREA_GRID_THRESHOLD, //!< The grid threshold, expressed as a fixed-point 16.16 number. 
                                                                      //!< If the zooming factor (ThisArgs::zoom) is greater than this threshold, the grid is displayed. 
					zoom = Pt_ARG_IMAGEAREA_ZOOM //!< The zooming factor, expressed as a fixed-point 16.16 number.
				};
			};	

			//! Contains resource IDs for ImageArea arguments of type `PgColor_t`.
            struct ArgColor
			{
				//! Resource IDs for ImageArea arguments of type `PgColor_t`.

				/*!
					### Aliases ###
					
					PhWidgets::ImageArea::Arguments::eArgColor,
					PhWidgets::ImageArea::ArgColor::eArgColor

					See Widget::resource for usage description.
				*/
				enum eArgColor
                {
                    grid_color = Pt_ARG_IMAGEAREA_GRID_COLOR //!< The color of the grid, if displayed.
                };
            };

            //! Contains resource IDs for ImageArea arguments of type **short**.
			struct ArgShort
			{
                //! Resource IDs for ImageArea arguments of type **short**.

				/*!
					### Aliases ###
					
					PhWidgets::ImageArea::Arguments::eArgShort,
					PhWidgets::ImageArea::ArgShort::eArgShort

					See Widget::resource for usage description.
				*/
				enum eArgShort
				{
					top = Pt_ARG_IMAGEAREA_TOP, //!< The coordinate, in image pixels, of the top side of the image viewport. This only applies when the image is larger than the widget. 
					left = Pt_ARG_IMAGEAREA_LEFT //!< The coordinate, in image pixels, of the left side of the image viewport. This only applies when the image is larger than the widget. 
				};

				enum eArgShortFlag
				{
					imagearea_flags = Pt_ARG_IMAGEAREA_FLAGS //!< [Flags](@ref ImageArea::Flags::eImageAreaFlags) that control the behavior of the image area.
				};
			};

			//! Contains resource IDs for ImageArea arguments of type `PhImage_t`.
			struct ArgPImage
			{
				//! Resource IDs for ImageArea arguments of type `PhImage_t`.

				/*!
					### Aliases ###
					
					PhWidgets::ImageArea::Arguments::eArgPImage,
					PhWidgets::ImageArea::ArgPImage::eArgPImage

					See Widget::resource for usage description.
				*/
				enum eArgPImage
				{
					imagearea_image = Pt_ARG_IMAGEAREA_IMAGE  //!< A pointer to a `PhImage_t` structure
												    		  //!< that defines the image to be displayed in the image area.
				};
			};

			//! Contains resource IDs for ImageArea arguments of type `PhRect_t`.
			struct ArgRect
			{
				//! Resource IDs for ImageArea arguments of type `PhRect_t`.

				/*!
					### Aliases ###
					
					PhWidgets::ImageArea::Arguments::eArgRect,
					PhWidgets::ImageArea::ArgRect::eArgRect

					See Widget::resource for usage description.
				*/
				enum eArgRect
				{
					selection = Pt_ARG_IMAGEAREA_SELECTION  //!< A `PhRect_t` structure that contains the selected area of the image, in image coordinates (pixels).
				};
			};
			
		};

        //! Contains resource IDs for ImageArea callbacks. @ingroup Resources
		struct ThisCallbacks
		{
            //! Contains resource IDs for ImageArea callbacks of type `PtCallback_t`.
			struct Callback
			{
                //! Resource IDs for ImageArea arguments of type `PtCallback_t`.
				/*!
					### Aliases ###
					
					PhWidgets::ImageArea::Callbacks::eCallback,
					PhWidgets::ImageArea::Callback::eCallback

					See Widget::resource for usage description.
				*/
				enum eCallback
				{
					drag = Pt_CB_IMAGEAREA_DRAG, //!< A list of `PtCallback_t` structures that define the callbacks invoked when the image area is dragged.
					movement = Pt_CB_IMAGEAREA_MOVEMENT, //!< A list of `PtCallback_t` structures that define the callbacks that are invoked when the mouse cursor is moved over the image area. 
					scrolled = Pt_CB_IMAGEAREA_SCROLLED, //!< A list of `PtCallback_t` structures that define the callbacks that are invoked when the image area is scrolled. 
					selection = Pt_CB_IMAGEAREA_SELECTION //!< A list of `PtCallback_t` structures that define the callbacks invoked when the image area is selected. 
				};
			};
		};

		//! Contains flags for ImageArea resources. @ingroup Resources
		struct ThisFlags
		{
			//! ImageAreas flags for ImageArea resource ImageArea::Arguments::imagearea_flags.
			/*!
				The default setting of ImageArea::Arguments::imagearea_flags resource is 0; that is, no flags have been set. 

				### Aliases ###
				
				PhWidgets::ImageArea::Flags::eImageAreaFlags
			*/
			enum eImageAreaFlags
			{
				Autoscale = Pt_IMAGEAREA_AUTOSCALE, //!< Automatically scale the image to fit the size of the widget. 
				EnableSelection = Pt_IMAGEAREA_ENABLE_SELECTION, //!< Allow the user to select part of the image. 
				EditableSelection = Pt_IMAGEAREA_EDITABLE_SELECTION //!< Allow the user to modify a selection. 
			};
		};

		//! Contains resource IDs for arguments of type **long**. @ingroup Resources
		struct ArgLong:
			public ArgumentsEx<Container::ArgLong>,
			public ThisArgs::ArgLong
		{
			typedef ThisArgs::ArgLong::eArgLong eArgLong;
		};

		//! Contains resource IDs for arguments of type `PgColor_t`. @ingroup Resources
		struct ArgColor:
            public ArgumentsEx<Container::ArgColor>,
			public ThisArgs::ArgColor
		{
            typedef ThisArgs::ArgColor::eArgColor eArgColor;
		};	
		
		//! Contains resource IDs for arguments of type **short**. @ingroup Resources
		struct ArgShort:
			public ThisArgs::ArgShort
		{ };

		//! Contains resource IDs for arguments of type `PhImage_t`. @ingroup Resources
		struct ArgPImage:
			public ThisArgs::ArgPImage
		{ };

		//! Contains resource IDs for arguments of type `PhRect_t`. @ingroup Resources
		struct ArgRect:
			public ArgumentsEx<Container::ArgRect>,
			public ThisArgs::ArgRect
		{
            typedef ThisArgs::ArgRect::eArgRect eArgRect;
		};

		//! Contains resource IDs for callbacks of type `PtCallback_t`. @ingroup Resources
		struct Callback:
			public ArgumentsEx<Container::Callback>,
			public ThisCallbacks::Callback
		{
			typedef ThisCallbacks::Callback::eCallback eCallback;
		};

		//! Contains resource IDs for all ImageArea arguments. @ingroup Resources
		struct Arguments:
			public ArgLong,
			public ArgColor,
			public ArgShort,
			public ArgPImage,
			public ArgRect,
			public Container::Arguments
		{ };

		//! Contains resource IDs for all ImageArea callbacks. @ingroup Resources
		struct Callbacks:
			public Callback,
			public Container::Callbacks
		{ };

		//! Contains flags for all ImageArea resources. @ingroup Resources
		struct Flags:
			public ThisFlags,
			public Container::Flags
        { };

	protected:
		typedef ResourceFrom<Container::WidgetResourcesSingleton>::
			Define::Scalar<ThisArgs::ArgLong::eArgLong, long>::
			Define::Color<ThisArgs::ArgColor::eArgColor>::
			Define::Scalar<ThisArgs::ArgShort::eArgShort, short>::
			Define::Image<ArgPImage::eArgPImage>::
			Define::Struct<ThisArgs::ArgRect::eArgRect, PhRect_t>::
			Define::Flag<ThisArgs::ArgShort::eArgShortFlag, short>::

			Define::Link<ThisCallbacks::Callback::eCallback, PtCallback_t*>::

		resource_type WidgetResourcesSingleton;

		virtual void check();

		//for properties:
		
		void setAutoScale(bool);
		bool getAutoScale() const;

		Drawing::Image getImage() const;
		void setImage(Drawing::Image);
						
	public:
		//! (constructor) 
		/*!
			Constructs a ImageArea by ID.
			@param[in] abn ID given by PhAB to widget (like 'ABN_WIDGET_NAME').
		*/
		explicit ImageArea(int abn);

		//! (constructor) 
		/*!
			Constructs a ImageArea by pointer to widget.
			@param[in] wdg pointer to Photon widget.
		*/
		explicit ImageArea(PtWidget_t *wdg);

		//! (copy constructor) 
		/*!
			Constructs a ImageArea by copy.
			@param[in] other another ImageArea to be used as source to initialize the elements of the container with.
		*/
		ImageArea(const ImageArea &other);

		//! Assigns value in ImageArea 
		/*!
			Replaces the contents of the ImageArea.
			@param[in] other another ImageArea to use as data source.
		*/
		ImageArea &operator=(const ImageArea &other);

		//! Resources of the ImageArea
		/*!
			@see
			- Widget::resource
		*/
		WidgetResourcesSingleton resource;

		//! @name Properties
		//! Properties are used to simplify use of widget resources.
		//@{

		//! Determines whether or not to use automatically scale the image to fit the size of the widget. 
		/*!
			### Property Value ### 
			
			> **bool**

			`true` if the image within the ImageArea is stretched or shrunk to fit the size of the ImageArea; otherwise, `false`. The default is `false`.

			@see
			- Image
		*/
		property<bool>::bind<ImageArea, &ImageArea::getAutoScale, &ImageArea::setAutoScale> AutoScale;

		//! Gets or sets the color of the grid, if displayed.
		/*!
			### Property Value ### 
			
			> Drawing::Color

			A `Drawing::Color` that represents the color of the grid, if displayed.

			@see
			- Drawing::Colors
			- Drawing::Color
		*/
		phproperty<Drawing::Color>::bind<ImageArea, ArgColor::eArgColor, Arguments::grid_color> GridColor;
		
		//! Gets or sets the grid threshold.
		/*!
			### Property Value ### 
			
			> **long**

			A **long** that represents the grid threshold, expressed as a fixed-point 16.16 number.
			
			@remark
			If the zooming factor (ImageArea::ZoomingFactor) is greater than this threshold, the grid is displayed. 

			@see
			- ZoomingFactor
		*/
		phproperty<long>::bind<ImageArea, ArgLong::eArgLong, Arguments::grid_threshold> GridThreshold;

		//! Gets or sets the image that is displayed by ImageArea.
		/*!
			### Property Value ### 
			
			> Drawing::Image

			The `Drawing::Image` to display.

			### Examples ###

			@code
				void CreateBitmapAtRuntime( PtWidget_t *ptwidget, void *, PtCallbackInfo_t * )
				{
					using namespace PhWidgets;

					Widget this_widget(ptwidget);

					// constructing new ImageArea
					ImageArea imageArea1;

					imageArea1.Size = PhDim_t({210, 110});
					imageArea1.Parent = this_widget;

					Drawing::Image flag = Drawing::Image::FromFile("./flag_rus.jpg");
					imageArea1.Image = flag;
				}
			@endcode

			@remark
			The Image property is set to the `Drawing::Image` to display. You can do this either at design time or at run time.

			@note
			If you want to use the same image in multiple ImageArea widgets, create a clone of the image for each ImageArea. 
			Accessing the same image from multiple widgets causes an exception to occur.

			@see
			- ImageLocation
		*/
		property<Drawing::Image>::bind<ImageArea, &ImageArea::getImage, &ImageArea::setImage> Image;

		//! Gets or sets the zooming factor.
		/*!
			### Property Value ### 
			
			> **long**

			A **long** that represents the zooming factor, expressed as a fixed-point 16.16 number.

			@see
			- GridThreshold
		*/
		phproperty<long>::bind<ImageArea, ArgLong::eArgLong, Arguments::zoom> ZoomingFactor;

		//@}
		
		//! @name Events
		//@{
		phwidgets_event<ImageArea, ImageArea::Callbacks::drag>	Drag;
		phwidgets_event<ImageArea, ImageArea::Callbacks::movement>	Movement;
		phwidgets_event<ImageArea, ImageArea::Callbacks::scrolled>	Scrolled;
		phwidgets_event<ImageArea, ImageArea::Callbacks::selection>	Selection;
		//@}
	};
} // namespace PhWidgets


#endif // PHWIDGETS_IMAGE_AREA_H
