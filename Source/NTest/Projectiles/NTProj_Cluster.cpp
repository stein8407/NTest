// Fill out your copyright notice in the Description page of Project Settings.


#include "NTProj_Cluster.h"
#include "Components/ArrowComponent.h"
#include "NTProj_Normal.h"

FQuat ANTProj_Cluster::RelRotationL = FRotator(0.f, -45.f, 0.f).Quaternion();
FQuat ANTProj_Cluster::RelRotationR = FRotator(0.f, 45.f, 0.f).Quaternion();

ANTProj_Cluster::ANTProj_Cluster()
{
	LifeSpan = 3.f;
}

void ANTProj_Cluster::SetupArrow()
{
	CreateDefaultArrow();
	CreateDefaultArrow()->SetRelativeRotation(RelRotationL);
	CreateDefaultArrow()->SetRelativeRotation(RelRotationR);
}

void ANTProj_Cluster::OnLifeSpanExpired()
{
	auto SpawnLoc = GetActorLocation();
	auto Q = GetActorQuat();
	TArray<FQuat> Rotations { FQuat::Identity, RelRotationL, RelRotationR };
	for (auto& R : Rotations)
	{
		auto Proj = GetWorld()->SpawnActor<ANTProjectileBase>(ANTProj_Normal::StaticClass(), FTransform(Q * R, SpawnLoc));
		Proj->Launch();
	}
}