#pragma once;

#include <Common.h>
#include "MicroManager.h"

namespace UAlbertaBot
{
	class SciencevesselManager : public MicroManager
	{
	public:

		SciencevesselManager();
		void executeMicro(const BWAPI::Unitset & targets);
	};
}