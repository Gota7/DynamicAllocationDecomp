#include "BreakableWall.h"

SharedFilePtr BreakableWall::modelFiles[2];
SharedFilePtr BreakableWall::clsnFiles[2];

SpawnInfo BreakableWall::spawnDataStar = // 0x02128070
{
	[]() -> ActorBase* { return new StarBreakableWall; },
	STAR_BREAKABLE_WALL_ACTOR_ID,
	STAR_BREAKABLE_WALL_OBJECT_ID - 1,
	0x00000000,
	0x00000000_f,
	0x00001000_f,
	0x00000000_f,
	0x00000000_f
};

SpawnInfo BreakableWall::spawnDataNormal = // 0x0212808c
{
	[]() -> ActorBase* { return new BreakableWall; },
	NORMAL_BREAKABLE_WALL_ACTOR_ID,
	NORMAL_BREAKABLE_WALL_OBJECT_ID - 1,
	0x00000000,
	0x00000000_f,
	0x00001000_f,
	0x00000000_f,
	0x00000000_f
};

// First with start then without.
FixedSizeCLPS_Block<1> clpsBlocks[2] = //0x021136d4
{
    {
        {'C', 'L', 'P', 'S'},
        8,
        1,
        {
            // low: 0x00000FC4, high: 0x000000ff
            CLPS(
                CLPS::_TextureID::TX_ROCK,
                0,
                0x3f,
                CLPS::_TractionID::TR_NORMAL,
                CLPS::_CamBehavID::CA_NORMAL,
                CLPS::_BehaviorID::BH_NORMAL,
                0,
                0,
                0,
                0xff
            )
        }
    },
    {
        {'C', 'L', 'P', 'S'},
        8,
        1,
        {
            // low: 0x00000FC0, high: 0x000000ff
            CLPS(
                CLPS::_TextureID::TX_NONE,
                0,
                0x3f,
                CLPS::_TractionID::TR_NORMAL,
                CLPS::_CamBehavID::CA_NORMAL,
                CLPS::_BehaviorID::BH_NORMAL,
                0,
                0,
                0,
                0xff
            )
        }
    }
};

int BreakableWall::InitResources()
{
    if (actorID == STAR_BREAKABLE_WALL_ACTOR_ID) // Breakable wall with star.
    {
        platformType = 0;
        platformSpriteData = (uint8_t)param1;
        if (platformSpriteData == 0xFF) platformSpriteData = 0;
    }
    else
    {
        platformType = 1; // Normal breakable wall.
    }
    model.SetFile(Model::LoadFile(modelFiles[platformType]), 1, -1);
    UpdateModelPosAndRotY();
    UpdateClsnPosAndRot();
    clsn.SetFile(MovingMeshCollider::LoadFile(clsnFiles[platformType]), clsnNextMat, 0x199_f, ang.y, (CLPS_Block&)clpsBlocks[platformType]);
    return 1;
}

int BreakableWall::CleanupResources()
{
    if (clsn.IsEnabled())
    {
        clsn.Disable();
    }
    modelFiles[platformType].Release();
    clsnFiles[platformType].Release();
    return 1;
}

int BreakableWall::Behavior()
{
    if (actorID == STAR_BREAKABLE_WALL_ACTOR_ID && wallDestroyed)
    {
        if (clsn.IsEnabled())
        {
            clsn.Disable();
        }
        if (PlaySecretJingle(secretJingleTimer)) // Play secret jingle until done.
        {
            Vector3 spawnPos = pos;
            spawnPos.y += 0xc8000_f;
            Actor::Spawn(0xB2, platformSpriteData | 0x40, spawnPos, nullptr, areaID, -1); // Spawn correct star ID.
            Destroy();
        }
    }
    else
    {
        clsn.range = 0x240000_f;
        IsClsnInRange(0x240000_f, 0); // This enables collision if in range side effect.
    }
    return 1;
}

int BreakableWall::Render()
{
    if (!wallDestroyed) model.Render();
    return 1;
}

void BreakableWall::OnHitByCannonBlastedChar(Actor& blaster)
{
    Kill();
}

void BreakableWall::Kill()
{
    Sound::PlayBank3(0xf, camSpacePos);
    Particle::System::NewSimple(Particle::PTS_ROCKS_BROWN, pos.x, pos.y, pos.z);
    if (actorID != STAR_BREAKABLE_WALL_ACTOR_ID) Destroy(); // Simply just destroy wall if it doesn't spawn a star.
    wallDestroyed = true;
}