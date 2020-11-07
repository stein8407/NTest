// Fill out your copyright notice in the Description page of Project Settings.

#include "NTLauncherState.h"
#include "NTLauncherComponent.h"

FNTLauncherState::FNTLauncherState(UNTLauncherComponent* InOwner): Owner(InOwner) {}

void FLS_Default::OnPrimary_Press()
{
	Owner->ChangeState(ELauncherState::PrimaryCharging);
}

void FLS_Default::OnSecondary_Press()
{
	Owner->ChangeState(ELauncherState::SecondaryCharging);
}

void FLS_PrimaryCharging::OnEnter()
{
	RemainClusterTime = DefaultClusterTime;
	RemainLifeTime = DefaultLifeTime;
}

void FLS_PrimaryCharging::OnPrimary_Release()
{
	Owner->FireProjectile(EProjectileType::Normal);
}

void FLS_PrimaryCharging::OnSecondary_Press()
{
	if (CanFireCluster())
	{
		Owner->FireProjectile(EProjectileType::Cluster);
	}
	else
	{
		Owner->ChangeState(ELauncherState::SecondaryCharging);
	}
}

void FLS_PrimaryCharging::TickState(float DeltaTime)
{
	RemainClusterTime -= DeltaTime;
	RemainLifeTime -= DeltaTime;

	if (RemainLifeTime <= 0.f)
	{
		Owner->ChangeState(ELauncherState::PrimaryCharged);
	}
}

float FLS_PrimaryCharging::GetChargingProgress() const
{
	return 1.f - RemainLifeTime / DefaultLifeTime;
}

bool FLS_PrimaryCharging::CanFireCluster() const
{
	return RemainClusterTime > 0.f;
}

void FLS_PrimaryCharged::OnPrimary_Release()
{
	Owner->FireProjectile(EProjectileType::Charge);
}

void FLS_PrimaryCharged::OnSecondary_Press()
{
	Owner->ChangeState(ELauncherState::SecondaryCharging);
}

float FLS_PrimaryCharged::GetChargingProgress() const
{
	return 1.f;
}

void FLS_SecondaryCharging::OnPrimary_Press()
{
	Owner->ChangeState(ELauncherState::PrimaryCharging);
}

void FLS_SecondaryCharging::OnSecondary_Release()
{
	Owner->FireProjectile(EProjectileType::Bounce);
}
