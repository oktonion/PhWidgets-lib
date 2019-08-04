#include "PhWidgetsFunc.h"

#include <Pt.h>
#include <Ap.h>
extern PtWidgetClassRef_t *PtOSContainer;
extern PtWidgetClassRef_t *PtClient;
/*extern*/ PtWidgetClassRef_t *PtMtrend;
/*extern*/ PtWidgetClassRef_t *PtMultitext;
/*extern*/ PtWidgetClassRef_t *PtScrollBar;
extern PtWidgetClassRef_t *PtServer;
/*extern*/ PtWidgetClassRef_t *PtWebClient;

using namespace PhWidgets;

#define STRINGIZE_NX(A) #A
#define STRINGIZE(A) STRINGIZE_NX(A)
#define RETURN_PHWIDGETS_CLASS_NAME(wdg, xxx) if(PtWidgetClass(wdg) == xxx) return STRINGIZE_NX(xxx);

namespace PhWidgets
{
    const char * WidgetClassName(PtWidget_t *wdg)
    {
        if(wdg)
        {
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtArc);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtBarGraph);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtBasic);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtBezier);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtBkgd);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtButton);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtCalendar);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtClient);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtClock);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtColorPanel);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtColorPatch);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtColorSel);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtColorSelGroup);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtColorWell);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtComboBox);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtCompound);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtContainer);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtDisjoint);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtDivider);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtEllipse);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtFileSel);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtFontSel);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtGauge);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtGenList);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtGenTree);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtGraphic);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtGrid);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtGroup);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtImageArea);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtLabel);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtLine);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtList);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtMenu);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtMenuBar);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtMenuButton);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtMeter);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtMtrend);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtMultitext);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtNumeric);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtNumericFloat);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtNumericInteger);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtOnOffButton);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtOSContainer);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtPane);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtPanelGroup);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtPixel);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtPolygon);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtPrintSel);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtProgress);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtRaw);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtRawList);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtRawTree);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtRect);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtRegion);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtScrollArea);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtScrollBar);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtScrollContainer);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtSeparator);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtServer);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtSlider);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtTab);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtTerminal);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtText);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtTimer);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtToggleButton);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtToolbar);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtToolbarGroup);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtTree);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtTrend);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtTty);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtUpDown);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtWebClient);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtWidget);
            RETURN_PHWIDGETS_CLASS_NAME(wdg, PtWindow);
        }

        return "Unknown";
    }

    const char * WidgetName(PtWidget_t *wdg)
    {
        const char *name = ApInstanceName(wdg);

        if(NULL == name)
            name = WidgetClassName(wdg);
        
        return name;
    }
}