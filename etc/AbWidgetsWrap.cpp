/****************************************************************************/
/*																			*/
/*	This source file is used to link 'AbWidgets' array to 'PhWidgets' lib.	*/
/*	It should be placed in 'src' folder of PhAB project with 'ablibs.h' and	*/
/*	'abimport.h' so it will be compiled with other project source files to	*/
/*	link global variables of PhAB project with the library.					*/
/*																			*/
/*	Note that library folder 'PhWidgets' itself should be located also in	*/
/*	'src' directory of the project. If not- correct the include path below 	*/
/*	to match the location of 'PhWidgets' library includes.					*/
/*																			*/
/****************************************************************************/


#include <photon/PtWidget.h>
#include <vector>

#include "ablibs.h"
#include "abimport.h"

//$PROJ/src/PhWidgets/include/service/header.h

#include "./PhWidgets/include/service/PhWidgetsFunc.h"
#include "./PhWidgets/include/service/PhWidgetsTypes.h"
#include "./PhWidgets/include/service/code_extensions.h"

namespace PhWidgets
{
	namespace internal
	{
		template<typename T, size_t N>
		inline PtWidget_t* GetABW(size_t n, T (&AbWidgets)[N])
		{
			PtWidget_t *widget = n < N ? AbWidgets[n].wgt : nullptr;
			
			return widget;
		}

		template<typename T, size_t N>
		inline std::vector<PtWidget_t*> GetABW(T (&AbWidgets)[N])
		{
			std::vector<PtWidget_t*> widgets;
			
			widgets.reserve(N);
			
			for(size_t i = 0; i < N; ++i)
			{
				widgets.push_back(internal::GetABW(i, AbWidgets));
			}
					
			return widgets;
		}
	}

	PtWidget_t* GetABW(int n)
	{
		if(n < 0)
			return nullptr;
			
		return internal::GetABW(size_t(n), AbWidgets);
	}

	std::vector<PtWidget_t*> GetABW()
	{
		return internal::GetABW(AbWidgets);
	}

	size_t GetABWCount()
	{
		return countof(AbWidgets);
	}
}
