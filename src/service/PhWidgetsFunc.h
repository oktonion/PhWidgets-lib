#ifndef PHWIDGETS_PH_WIDGETS_FUNC_H
#define PHWIDGETS_PH_WIDGETS_FUNC_H

#include <photon/PtWidget.h>

#include <vector>

namespace PhWidgets
{
	PtWidget_t* GetABW(int n);
	std::vector<PtWidget_t*> GetABW();
	size_t GetABWCount();
}

#undef AbGetABW
#define AbGetABW( n ) PhWidgets::GetABW( n )
#define AbGetABWS() PhWidgets::GetABW()

#endif
