#include "defs.h"

#ifdef COMPILE_FOR_AVX2

#define RunWrapper RunWrapperAVX2

#include "raduls_impl.h"

namespace raduls
{
	void CInstrSetAVX2::Run(const SortParams& p)
	{		
		RunWrapperAVX2(p);
	}
}

#endif