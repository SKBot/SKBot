#include "SciencevesselManager.h"
#include "UnitUtil.h"

using namespace UAlbertaBot;

SciencevesselManager::SciencevesselManager()
{
}

void SciencevesselManager::executeMicro(const BWAPI::Unitset & targets)
{
	const BWAPI::Unitset & scienceVessels = getUnits();

	//create a set of all scienceVessel targets
	BWAPI::Unitset scienceVesslTargets;
	for (auto & unit : BWAPI::Broodwar->self()->getUnits())
	{
		if (!unit->getType().isBuilding() && unit->isUnderAttack())
		{
			scienceVesslTargets.insert(unit);
		}
	}

	BWAPI::Unitset availableScienceVessel(scienceVessels);

	//for each ScienceVessel, send it to closet target
	for (auto & scienceVessel : availableScienceVessel)
	{

		double closetTargetDist = std::numeric_limits<double>::infinity();
		BWAPI::Unit closetTarget = nullptr;

		for (auto & target : scienceVesslTargets)
		{
			//shelled the unshelled one
			if (target->isDefenseMatrixed())
			{
				continue;
			}
			double dist = scienceVessel->getDistance(target);

			if (!closetTarget || (dist < closetTargetDist))
			{
				closetTarget = target;
				closetTargetDist = dist;
			}
		}
		if (closetTarget)
		{
			scienceVessel->useTech(BWAPI::TechTypes::Defensive_Matrix, closetTarget);

			scienceVesslTargets.erase(closetTarget);
		}

		else
		{
			break;
		}
	}

	for (auto & scienceVessel : availableScienceVessel)
	{
		Micro::SmartMove(scienceVessel, order.getPosition());
	}
	
}