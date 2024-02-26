#include "defs.h"

#define RunWrapper RunWrapperSSE2

#include "raduls_impl.h"

namespace raduls
{
	void CInstrSetSSE2::Run(const SortParams& p)
	{
		RunWrapperSSE2(p);
	}
}