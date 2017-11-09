#pragma once

#include "Common.h"
#include "BWTA.h"

#include "UnitData.h"

#include "..\..\SparCraft\source\SparCraft.h"

namespace UAlbertaBot
{
struct BaseInfo;
typedef std::vector<BaseInfo> BaseInfoVector;

class InformationManager 
{
    InformationManager();
    
    BWAPI::Player       _self;
    BWAPI::Player       _enemy;

    std::map<BWAPI::Player, UnitData>                   _unitData;
    std::map<BWAPI::Player, BWTA::BaseLocation *>       _mainBaseLocations;
    std::map<BWAPI::Player, std::set<BWTA::Region *> >  _occupiedRegions;

    int                     getIndex(BWAPI::Player player) const;

    void                    updateUnit(BWAPI::Unit unit);
    void                    initializeRegionInformation();
    void                    initializeBaseInfoVector();
    void                    updateUnitInfo();
    void                    updateBaseLocationInfo();
    void                    updateOccupiedRegions(BWTA::Region * region,BWAPI::Player player);
    bool                    isValidUnit(BWAPI::Unit unit);
	void							countEnemyWorkers(); //new added
	void							assignEnemyWorkers(); //new added
	int								getEnemyWorkers(); //new added
	int								_enemyWorkersNumber; //new added
	std::vector<int>				_enemyWorkersArray; //new added
	int								getEnemyMainBase(); //new added
	//void							countEnemyBase(); //new added
	//void							assignEnemyMainBase(); //new added
	std::vector<int>				_enemyBaseArray; //new added
	int								_enemyBaseNumber; //new added
	bool							detectEnemyWorker(); //new added
	int								_currentEnemyBaseId; //new added
	//bool							detectEnemyRush(); //new added
	std::string						_rushDetected; //new added

public:

    // yay for singletons!
    static InformationManager & Instance();

	bool detectEnemyRush(); //new added
	bool detectEnemySecondBase(); //new addded

    void                    update();

    // event driven stuff
    void					onUnitShow(BWAPI::Unit unit)        { updateUnit(unit); }
    void					onUnitHide(BWAPI::Unit unit)        { updateUnit(unit); }
    void					onUnitCreate(BWAPI::Unit unit)		{ updateUnit(unit); }
    void					onUnitComplete(BWAPI::Unit unit)    { updateUnit(unit); }
    void					onUnitMorph(BWAPI::Unit unit)       { updateUnit(unit); }
    void					onUnitRenegade(BWAPI::Unit unit)    { updateUnit(unit); }
    void					onUnitDestroy(BWAPI::Unit unit);

    bool					isEnemyBuildingInRegion(BWTA::Region * region);
    int						getNumUnits(BWAPI::UnitType type,BWAPI::Player player);
    bool					nearbyForceHasCloaked(BWAPI::Position p,BWAPI::Player player,int radius);
    bool					isCombatUnit(BWAPI::UnitType type) const;

    void                    getNearbyForce(std::vector<UnitInfo> & unitInfo,BWAPI::Position p,BWAPI::Player player,int radius);

    const UIMap &           getUnitInfo(BWAPI::Player player) const;

    std::set<BWTA::Region *> &  getOccupiedRegions(BWAPI::Player player);
    BWTA::BaseLocation *    getMainBaseLocation(BWAPI::Player player);

    bool                    enemyHasCloakedUnits();

	bool					enemyHasMutaHydra(); //newly added
	bool					enemyHasDefenceBuilding(); //newly added
	bool					enemyHasSiegeTankFirebat(); //newly added
	bool					enemyHasDragoon(); //newly added
	bool					enemyHasArmoryMech(); //newly added

    void                    drawExtendedInterface();
    void                    drawUnitInformation(int x,int y);
    void                    drawMapInformation();

    const UnitData &        getUnitData(BWAPI::Player player) const;
};
}
