/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Assignment: CS230 Final Project
File Name: GameParticles.cpp
Project: CS230
Author: Hyunjun Lee, Geumbi Yeo
Creation date: 2022/6/2
-----------------------------------------------------------------*/
#include "GameParticles.h"
#include "../Engine/GameObject.h"
#include "../Engine/Sprite.h"

SmokeEmitter::SmokeEmitter() : ParticleEmitter(1.0)
{
	for (int i = 0; i < NumParticles; i++)
	{
		AddParticle(new SmokeParticle("Assets/smoke.spt"));
	}
}

HitEmitter::HitEmitter() : ParticleEmitter(1.0)
{
	for (int i = 0; i < NumParticles; i++)
	{
		AddParticle(new HitParticle("Assets/hit.spt"));
	}
}

MeteorBitEmitter::MeteorBitEmitter() : ParticleEmitter(1.5)
{
	for (int i = 0; i < NumParticles; i++)
	{
		AddParticle(new MeteorBit("Assets/MeteorBit.spt"));
	}
}

CrushEmitter::CrushEmitter() : ParticleEmitter(1.0)
{
	for (int i = 0; i < NumParticles; i++)
	{
		AddParticle(new Crush("Assets/crush.spt"));
	}
}
