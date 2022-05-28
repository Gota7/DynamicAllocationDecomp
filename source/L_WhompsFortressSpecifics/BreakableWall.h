#ifndef BREAKABLE_WALL_INCLUDED
#define BREAKABLE_WALL_INCLUDED

#include "../SM64DS_2.h"

const uint16_t NORMAL_BREAKABLE_WALL_OBJECT_ID = 0xC9;
const uint16_t NORMAL_BREAKABLE_WALL_ACTOR_ID = 0x2F;
const uint16_t STAR_BREAKABLE_WALL_OBJECT_ID = 0xCA;
const uint16_t STAR_BREAKABLE_WALL_ACTOR_ID = 0x30;

// vtable at 0x021280b0, size is 0x324, actor ids are 0x2f and 0x30
struct BreakableWall : Platform
{
    char unk_300 = 0;
    bool wallDestroyed = false;
    short secretJingleTimer = 0;

    virtual int InitResources() override;		// 0x02127494
    virtual int CleanupResources() override;	// 0x02127300
    virtual int Behavior() override;            // 0x021273a4
    virtual int Render() override;				// 0x02127364
    //virtual void ~BreakableWall() override;	// 0x021271e4
    //virtual void ~BreakableWall() override;	// 0x02127228
    virtual void OnHitByCannonBlastedChar(Actor& blaster) override; // 0x021272e0
    virtual void Kill() override;               // 0x02127280

    //BreakableWall();                          // 0x021275ac

    static SharedFilePtr modelFiles[2]; // With star, then normal.
    static SharedFilePtr clsnFiles[2]; // With star, then normal.
    static SpawnInfo spawnDataStar;
    static SpawnInfo spawnDataNormal;
};

struct StarBreakableWall : BreakableWall {};

static_assert(sizeof(BreakableWall) == 0x324, "Breakable wall is wrong size");

#endif BREAKABLE_WALL_INCLUDED