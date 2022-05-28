#ifndef POLE_BILLBOARD_INCLUDED
#define POLE_BILLBOARD_INCLUDED

#include "../SM64DS_2.h"

const uint16_t POLE_BILLBOARD_OBJECT_ID = 0xC4;
const uint16_t POLE_BILLBOARD_ACTOR_ID = 0x2A;

// vtable at 0x02114360, size is 0x124, actor id is 0x2A
struct PoleBillboard : Actor
{
    Model model;

    virtual int InitResources() override;		// 0x021112a0
	virtual int CleanupResources() override;	// 0x02111254
    virtual int Render() override;				// 0x02111278
	//virtual void ~PoleBillboard() override;	// 0x021111a0
	//virtual void ~PoleBillboard() override;	// 0x021111d0

    //PoleBillboard();                          // 0x021112dc
    void UpdateModelTransform();                // 0x02111214

    static SharedFilePtr modelFile;
    static SpawnInfo spawnData;
};

static_assert(sizeof(PoleBillboard) == 0x124, "Pole billboard is wrong size");

#endif POLE_BILLBOARD_INCLUDED