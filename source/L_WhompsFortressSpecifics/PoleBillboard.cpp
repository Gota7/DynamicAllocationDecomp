#include "PoleBillboard.h"

SharedFilePtr PoleBillboard::modelFile;

SpawnInfo PoleBillboard::spawnData = // 0x0211433c
{
	[]() -> ActorBase* { return new PoleBillboard; },
	POLE_BILLBOARD_ACTOR_ID,
	POLE_BILLBOARD_OBJECT_ID - 1,
	0x00000000,
	0x00000000_f,
	0x00010000_f,
	0x00000000_f,
	0x00000000_f
};

int PoleBillboard::InitResources()
{
    char* file = Model::LoadFile(modelFile);
    model.SetFile(file, 1, -1);
    UpdateModelTransform();
    return 1;
}

int PoleBillboard::CleanupResources()
{
    modelFile.Release();
    return 1;
}

int PoleBillboard::Render()
{
    model.Render();
    return 1;
}

void PoleBillboard::UpdateModelTransform()
{
    Matrix4x3_FromRotationY(model.mat4x3, ang.y);
	model.mat4x3.c3 = pos >> 3;
}