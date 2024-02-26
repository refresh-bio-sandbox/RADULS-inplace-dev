#pragma once
#include "instr_set_detect.h"
#include "defs.h"
#include "raduls.h"

namespace raduls
{
	struct SortParams;

	class CInstrSetBase
	{
	public:
		virtual void Run(const SortParams& p) = 0;
	};

#ifdef COMPILE_FOR_AVX
	class CInstrSetAVX : public CInstrSetBase
	{
	public:
		void Run(const SortParams& p) override;
	};
#endif

#ifdef COMPILE_FOR_AVX2
	class CInstrSetAVX2 : public CInstrSetBase
	{
	public:
		void Run(const SortParams& p) override;
	};
#endif

#ifdef COMPILE_FOR_NEON
	class CInstrSetNEON : public CInstrSetBase
	{
	public:
		void Run(const SortParams& p) override;
	};
#endif

	class CInstrSetSSE2 : public CInstrSetBase
	{
	public:
		void Run(const SortParams& p) override;
	};

	class CInstrSetDispatcher
	{
		CInstrSetBase* runner = nullptr;
		CInstrSetDispatcher()
		{
#ifdef COMPILE_FOR_AVX
			static CInstrSetAVX avx;
#endif
#ifdef COMPILE_FOR_AVX2
			static CInstrSetAVX2 avx2;
#endif
			static CInstrSetSSE2 sse2;

			auto instr_set = InstrSetDetect::GetInstr();

			if(instr_set== InstrSetDetect::Instr::NotSet)
				throw exceptions::UndetectedHardware();
			if (instr_set >= InstrSetDetect::Instr::SSE2)
				runner = &sse2;
			else
				throw exceptions::UnsupportedHardware();
#ifdef COMPILE_FOR_AVX
			if(instr_set >= InstrSetDetect::Instr::AVX)
				runner = &avx;
#endif
#ifdef COMPILE_FOR_AVX2
			if (instr_set >= InstrSetDetect::Instr::AVX2)
				runner = &avx2;
#endif		
		}
	public:
		static CInstrSetDispatcher& GetInst()
		{
			static CInstrSetDispatcher d;
			return d;
		}

		void Run(const SortParams& p)
		{
			runner->Run(p);
		}
	};

}
