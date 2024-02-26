#include "defs.h"
#ifdef COMPILE_FOR_AVX

#define RunWrapper RunWrapperAVX

#include "raduls_impl.h"

namespace raduls
{
	void CInstrSetAVX::Run(const SortParams& p)
	{		
		RunWrapperAVX(p);
	}
}
#endif