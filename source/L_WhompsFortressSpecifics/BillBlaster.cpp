#include "BillBlaster.h"
#include "BulletBill.h"
#include "Particle.h"

SharedFilePtr BillBlaster::bulletModel1;
SharedFilePtr BillBlaster::bulletModel2;
SharedFilePtr BillBlaster::modelFile;
SharedFilePtr BillBlaster::clsnFile;

SpawnInfo BillBlaster::spawnData = // 0x02127f94
{
	[]() -> ActorBase* { return new BillBlaster; },
	0x002B,
	0x00C4,
	0x00000002,
	0x00200000_f,
	0x01000000_f,
	0x00000000_f,
	0x00000000_f
};

CLPS_Block BillBlaster::clps = // 0x02127e7c
{
    // TODO!!!
};

int BillBlaster::InitResources()
{
    Model::LoadFile(bulletModel1);
    Model::LoadFile(bulletModel2);
    model.SetFile(Model::LoadFile(modelFile), 1, -1);
    UpdateModelPosAndRotY();
    UpdateClsnPosAndRot();
    clsn.SetFile(MovingMeshCollider::LoadFile(clsnFile), clsnNextMat, 0x199_f, ang.y, clps);
    bulletID = 0;
    // TODO: REST OF INIT!
    return 1;
}

int BillBlaster::CleanupResources()
{
    if (clsn.IsEnabled())
    {
        clsn.Disable();
    }
    modelFile.Release();
    clsnFile.Release();
    bulletModel1.Release();
    bulletModel2.Release();
    return 1;
}

int BillBlaster::Behavior()
{
    if (!UpdateKillByMegaChar(0x2000, 0, 0, 0xC8000_f))
    {
        if (!Actor::FindWithID(bulletID))
        {
            Actor* player = ClosestPlayer();
            Fix12i horzDist = Vec3_HorzDist(&pos, &player->pos);
            short horzAngle = Vec3_HorzAngle(&pos, &player->pos);
            short playerAngleDiff = AngleDiff(horzAngle, ang.y);
            if (playerAngleDiff < 0x2000 && 0x320000_f < horzDist && horzDist < 0x5dc000_f)
            {
                Vector3 spawnPos = pos;
                spawnPos.y += 0x96000_f;
                BulletBill* bullet = (BulletBill*)Actor::Spawn(0xde, 0, &spawnPos, ang, areaID, -1);
                bulletID = bullet->uniqueID;
                bullet->billBlaster = this;
            }
        }
        IsClsnInRange(0, 0);
    }
    return 1;
}

int BillBlaster::Render()
{
    model.Render();
    return 1;
}

void BillBlaster::OnHitByMegaChar(Player& megaChar)
{
    megaChar.IncMegaKillCount();
    KillByMegaChar(megaChar);
    ang.y = motionAng.y;
}

void BillBlaster::Kill()
{
    Particle::System::NewSimple(PTS_TRIANGLES_BIG_GRAY_2, pos.x, pos.y, pos.z);
    PoofDustAt(pos);
    Sound::PlayBank3(0xF, &camSpacePos);
    Destroy();
}