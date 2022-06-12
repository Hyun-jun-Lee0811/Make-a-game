/*--------------------------------------------------------------
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Assignment: CS230 Final Project
File Name: ParticleEmitter.cpp
Project: CS230
Author: Hyunjun Lee, Geumbi Yeo
Creation date: 2022/6/2
-----------------------------------------------------------------*/
#include "ParticleEmitter.h"
#include "Engine.h"
#include "GameObjectManager.h"

CS230::ParticleEmitter::Particle::Particle(const std::filesystem::path& spriteFile) : GameObject({ 0,0 }), life(0)
{
	AddGOComponent(new Sprite(spriteFile, this));
}

void CS230::ParticleEmitter::Particle::Revive(math::vec2 positions, math::vec2 velocitys, double lifes)
{
	SetPosition(positions);
	SetVelocity(velocitys);
	life = lifes;
	GetGOComponent<CS230::Sprite>()->PlayAnimation(0);
}

void CS230::ParticleEmitter::Particle::Update(double dt)
{
	if (IsAlive() == true)
	{
		GameObject::Update(dt);
		life -= dt;
	}
}

void CS230::ParticleEmitter::Particle::Draw(math::TransformMatrix matrix)
{
	if (IsAlive() == true)
	{
		GameObject::Draw(matrix);
	}
}

CS230::ParticleEmitter::ParticleEmitter(double lifetime) : lifetime(lifetime), particleIndexToUse(0) {}

CS230::ParticleEmitter::~ParticleEmitter()
{
	particleMemoryPool.clear();
}

void CS230::ParticleEmitter::AddParticle(Particle* particleData)
{
	particleMemoryPool.push_back(particleData);
	Engine::GetGSComponent<CS230::GameObjectManager>()->Add(particleData);
}

void CS230::ParticleEmitter::Emit(int number, math::vec2 position, math::vec2 emitterVelocity, math::vec2 emitVector, double spread)
{
	for (int t = 0; t < number; t++)
	{
		if (this != nullptr)
		{
			if (particleMemoryPool[particleIndexToUse]->IsAlive() == true)
			{
				Engine::GetLogger().LogError("Particle Overwrite");
			}
		}
	}
	if (this != nullptr)
	{
		particleMemoryPool[particleIndexToUse++]->Revive(position, emitterVelocity, lifetime);
	}
	double A_random = rand() % static_cast<int>(spread / 2.0 - (-spread / 2.0) + 1.0) + static_cast<int>(-spread / 2.0);
	math::vec2 V_random = emitterVelocity + math::RotateMatrix(A_random) * emitVector * (((rand() % 1024) / 2048.0) + 0.5);
	if (this != nullptr)
	{
	particleMemoryPool[particleIndexToUse++]->Revive(position, V_random, lifetime);
	if (particleIndexToUse >= particleMemoryPool.size())
	{
		particleIndexToUse = 0;
	}
	}
}