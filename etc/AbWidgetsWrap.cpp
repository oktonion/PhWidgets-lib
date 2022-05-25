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
#include <cstddef>

#include "ablibs.h"
#include "abimport.h"

namespace PhWidgets
{
	namespace internal
	{
		template<typename T, std::size_t N>
		inline PtWidget_t* GetABW(std::size_t n, T (&AbWidgets)[N])
		{
			PtWidget_t *widget = n < N ? AbGetABW(n) : 0;
			
			return widget;
		}

		template<typename T, std::size_t N>
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

		struct enable_ABW;

		template<class> PtWidget_t* GetABW(int);
		template<class> std::vector<PtWidget_t*> GetABW();
		template<class> std::size_t GetABWCount();

		template<>
		PtWidget_t* GetABW<internal::enable_ABW>(int n)
		{
			if(n < 0)
				return 0;
				
			return internal::GetABW(std::size_t(n), AbWidgets);
		}

		template<>
		std::vector<PtWidget_t*> GetABW<internal::enable_ABW>()
		{
			return internal::GetABW(AbWidgets);
		}

		template<>
		std::size_t GetABWCount<internal::enable_ABW>()
		{
			return sizeof(AbWidgets) / sizeof(AbWidgets[0]);
		}
	} // namespace internal
}
