#ifndef BULLET_BILL_INCLUDED
#define BULLET_BILL_INCLUDED

#include "../SM64DS_2.h"

struct BillBlaster;

// vtable at 0x, size is 0x3E0, actor id is 0xDE
struct BulletBill : Enemy
{
    CylinderClsnWithPos cylinderClsn;
    WithMeshClsn withMeshClsn;
    Model model1;
    Model model2;
    ShadowModel shadow;
    void* unk[2];
    BillBlaster* billBlaster;

    virtual int InitResources() override;		// 0x
	virtual int CleanupResources() override;	// 0x
    virtual int Behavior() override;			// 0x
    virtual int Render() override;				// 0x
	//virtual void ~BulletBill() override;	// 0x
	//virtual void ~BulletBill() override;	// 0x
    virtual Fix12i OnAimedAtWithEgg() override;				// 0x

    //BillBlaster();                          // 0x

    static SharedFilePtr modelFile;
    static SharedFilePtr animFile;
    static SpawnInfo spawnData;
};

static_assert(sizeof(BulletBill) == 0x3E0, "Bullet bill is wrong size");

#endif BULLET_BILL_INCLUDED