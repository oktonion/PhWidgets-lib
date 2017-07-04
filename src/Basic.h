#ifndef PT_BASIC_H
#define PT_BASIC_H

#include <photon/PtBasic.h>

#include "./Widget.h"


namespace PhWidgets
{
		
	class Basic:
		public Widget
	{
	public:

		struct ThisArgs
		{
			struct ArgUnsignedShort
			{
				enum eArgUnsignedShort
				{
					margin_height = Pt_ARG_MARGIN_HEIGHT,
					margin_width = Pt_ARG_MARGIN_WIDTH
				};
			};
			
			struct ArgUnsignedLong
			{
				enum eArgUnsignedLong
				{
					bandwidth_threshold = Pt_ARG_BANDWIDTH_THRESHOLD,
					basic_flags = Pt_ARG_BASIC_FLAGS
				};
			};

			struct ArgColor
			{
				enum eArgColor
				{
					bevel_color = Pt_ARG_BEVEL_COLOR,
					color = Pt_ARG_COLOR,
					dark_bevel_color = Pt_ARG_DARK_BEVEL_COLOR,
					dark_fill_color = Pt_ARG_DARK_FILL_COLOR,
					fill_color = Pt_ARG_FILL_COLOR,
					inline_color = Pt_ARG_INLINE_COLOR,
					light_bevel_color = Pt_ARG_LIGHT_BEVEL_COLOR,
					light_fill_color = Pt_ARG_LIGHT_FILL_COLOR,
					outline_color = Pt_ARG_OUTLINE_COLOR
				};
			};

			struct ArgChar
			{		
				enum eArgChar
				{
					bevel_contrast = Pt_ARG_BEVEL_CONTRAST,
					contrast = Pt_ARG_CONTRAST
				};
			};
			
			struct ArgPattern
			{
				enum eArgPattern
				{
					fill_pattern = Pt_ARG_FILL_PATTERN,
					trans_pattern = Pt_ARG_TRANS_PATTERN
				};
			};
			
			struct ArgUnsignedChar
			{
				enum eArgUnsignedChar
				{
					highlihgt_roundness = Pt_ARG_HIGHLIGHT_ROUNDNESS
				};
			};
			
			struct ArgPChar
			{
				enum eArgPChar
				{
					style = Pt_ARG_STYLE
				};
			};	
		};

		struct ThisCallbacks
		{
			struct Callback
			{
				enum eCallback
				{
					activate = Pt_CB_ACTIVATE,
					arm = Pt_CB_ARM,
					disarm = Pt_CB_DISARM,
					got_focus = Pt_CB_GOT_FOCUS,
					lost_focus = Pt_CB_LOST_FOCUS,
					menu = Pt_CB_MENU,
					repeat = Pt_CB_REPEAT
				};
			};
		};

		struct ArgUnsignedShort:
			public ArgumentsEx<Widget::ArgUnsignedShort>,
			public ThisArgs::ArgUnsignedShort
		{
			using Widget::ArgUnsignedShort::eArgUnsignedShort;
			using ThisArgs::ArgUnsignedShort::eArgUnsignedShort;
		};
			
		struct ArgUnsignedLong:
			public ArgumentsEx<Widget::ArgUnsignedLong>,
			public ThisArgs::ArgUnsignedLong
		{
			using Widget::ArgUnsignedLong::eArgUnsignedLong;
			using ThisArgs::ArgUnsignedLong::eArgUnsignedLong;
		};

		struct ArgColor:
			public ArgumentsEx<Widget::ArgColor>,
			public ThisArgs::ArgColor
		{
			using Widget::ArgColor::eArgColor;
			using ThisArgs::ArgColor::eArgColor;
		};

		struct ArgChar:
			public ThisArgs::ArgChar
		{
		};
			
		struct ArgPattern:
			public ThisArgs::ArgPattern
		{
		};
			
		struct ArgUnsignedChar:
			public ThisArgs::ArgUnsignedChar
		{
		};

		struct ArgPChar:
			public ArgumentsEx<Widget::ArgPChar>,
			public ThisArgs::ArgPChar
		{
			using Widget::ArgPChar::eArgPChar;
			using ThisArgs::ArgPChar::eArgPChar;
		};	

		struct Callback:
			public ArgumentsEx<ThisCallbacks::Callback>,
			public Widget::Callback
		{
		};

		struct Arguments:
			public ArgUnsignedShort,
			public ArgUnsignedLong,
			public ArgColor,
			public ArgChar,
			public ArgPattern,
			public ArgUnsignedChar,
			public ArgPChar,
			public Widget::Arguments
		{
		};

		struct Callbacks :
			public Callback,
			public Widget::Callbacks
		{
		};

	protected:
		virtual void check();

		void setColor(PgColor_t);
		PgColor_t getColor() const;

		void setFillColor(PgColor_t);
		PgColor_t getFillColor() const;

		void addActivateCallback(callback_t callback);
		void addArmCallback(callback_t callback);
		void addDisarmCallback(callback_t callback);
		void addGotFocusCallback(callback_t callback);
		void addLostFocusCallback(callback_t callback);
		void addMenuCallback(callback_t callback);
		void addRepeatCallback(callback_t callback);
						
	public:
		Basic(int abn);
		Basic(PtWidget_t *wdg);
		
		Basic(const Basic &rhs);
		
		property<PgColor_t>::bind<Basic, &Basic::getColor, &Basic::setColor> Color;
		property<PgColor_t>::bind<Basic, &Basic::getFillColor, &Basic::setFillColor> FillColor;

		event<int, PtWidget_t *, void *, PtCallbackInfo_t *>::bind<Basic, &Basic::addActivateCallback>		Activate;
		event<int, PtWidget_t *, void *, PtCallbackInfo_t *>::bind<Basic, &Basic::addArmCallback>			Arm;
		event<int, PtWidget_t *, void *, PtCallbackInfo_t *>::bind<Basic, &Basic::addDisarmCallback>		Disarm;
		event<int, PtWidget_t *, void *, PtCallbackInfo_t *>::bind<Basic, &Basic::addGotFocusCallback>		GotFocus;
		event<int, PtWidget_t *, void *, PtCallbackInfo_t *>::bind<Basic, &Basic::addLostFocusCallback>		LostFocus;
		event<int, PtWidget_t *, void *, PtCallbackInfo_t *>::bind<Basic, &Basic::addMenuCallback>			Menu;
		event<int, PtWidget_t *, void *, PtCallbackInfo_t *>::bind<Basic, &Basic::addRepeatCallback>		Repeat;

		void OnActivated(PtCallbackInfo_t *info);
		void OnArmed(PtCallbackInfo_t *info);
		void OnDisarmed(PtCallbackInfo_t *info);
		void OnGotFocused(PtCallbackInfo_t *info);
		void OnLostFocus(PtCallbackInfo_t *info);
		void OnMenu(PtCallbackInfo_t *info);
		void OnRepeat(PtCallbackInfo_t *info);
	};		  
		
	
	INIT_WIDGET_RESOURCE0(Basic::ThisArgs::ArgPChar::eArgPChar, String);
	//INIT_WIDGET_RESOURCE0(Basic::ThisArgs::ArgPVoid::eArgPVoid, Alloc);

	INIT_WIDGET_RESOURCE1(Basic::ThisArgs::ArgColor::eArgColor, PgColor_t, Color);
	INIT_WIDGET_RESOURCE1(Basic::ThisArgs::ArgUnsignedShort::eArgUnsignedShort, unsigned short, Scalar);
	INIT_WIDGET_RESOURCE1(Basic::ThisArgs::ArgChar::eArgChar, char, Scalar);
	INIT_WIDGET_RESOURCE1(Basic::ThisCallbacks::Callback::eCallback, PtCallback_t, Link);

	INIT_WIDGET_RESOURCE2(Basic::ThisArgs::ArgUnsignedLong::eArgUnsignedLong, unsigned long, unsigned long, Flag);


	
}


#endif
