#ifndef BILL_BLASTER_INCLUDED
#define BILL_BLASTER_INCLUDED

#include "../SM64DS_2.h"

// vtable at 0x02127fb8, size is 0x324, actor id is 0x2B
struct BillBlaster : Platform
{
    uint32_t bulletID;

    virtual int InitResources() override;		            // 0x02127090
	virtual int CleanupResources() override;	            // 0x02126f04
    virtual int Behavior() override;			            // 0x02126f8c
    virtual int Render() override;				            // 0x02126f64
	//virtual void ~BillBlaster() override;	                // 0x02126dbc
	//virtual void ~BillBlaster() override;	                // 0x02126e00
    virtual void OnHitByMegaChar(Player& megaChar) override;// 0x02126ecc
    virtual void Kill() override;                           // 0x02126e58

    //BillBlaster();                                        // 0x021271b4

    static SharedFilePtr bulletModel1;
    static SharedFilePtr bulletModel2;
    static SharedFilePtr modelFile;
    static SharedFilePtr clsnFile;
    static SpawnInfo spawnData;
};

static_assert(sizeof(BillBlaster) == 0x324, "Bill blaster is wrong size");

#endif BILL_BLASTER_INCLUDED