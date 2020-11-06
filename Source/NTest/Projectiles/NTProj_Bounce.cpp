// Fill out your copyright notice in the Description page of Project Settings.


#include "NTProj_Bounce.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/ArrowComponent.h"

ANTProj_Bounce::ANTProj_Bounce()
{
	LifeSpan = 5.f;

	MoveComponent->bShouldBounce = true;
	MoveComponent->Bounciness = 1.f;
	MoveComponent->Friction = 0.f;
}

void ANTProj_Bounce::SetupArrow()
{
	CreateDefaultArrow(FColor::Blue);
}