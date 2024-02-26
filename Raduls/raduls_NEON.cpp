#include "defs.h"

#ifdef COMPILE_FOR_NEON

#define RunWrapper RunWrapperNEON

#include "raduls_impl.h"

namespace raduls
{
	void CInstrSetNEON::Run(const SortParams& p)
	{
		RunWrapperNEON(p);
	}
}

#endif