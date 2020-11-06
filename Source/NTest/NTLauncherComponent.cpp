// Fill out your copyright notice in the Description page of Project Settings.


#include "NTLauncherComponent.h"
#include "NTLauncherState.h"
#include "NTestCharacter.h"
#include "Projectiles/NTProjectileBase.h"
#include "Components/CapsuleComponent.h"

// Sets default values for this component's properties
UNTLauncherComponent::UNTLauncherComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	FireOffset_Forward = 20.f;
	FireOffset_Ground  = 50.f;
}


// Called when the game starts
void UNTLauncherComponent::BeginPlay()
{
	Super::BeginPlay();
	
	InitStateMap();
}

void UNTLauncherComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	
	DestroyStateMap();
}


// Called every frame
void UNTLauncherComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	GetState()->TickState(DeltaTime);
}


void UNTLauncherComponent::ChangeState(ELauncherState NextState)
{
	DEBUG_MSG("ChangeState : %s", FColor::Red, *GETENUMSTRING("ELauncherState", NextState));

	CurrentState = StateMap[NextState];
	CurrentState->OnEnter();
}

FNTLauncherState* const UNTLauncherComponent::GetState() const
{
	return CurrentState;
}

void UNTLauncherComponent::InitStateMap()
{
	StateMap.Add(ELauncherState::Default, new FLS_Default(this));
	StateMap.Add(ELauncherState::PrimaryCharging, new FLS_PrimaryCharging(this));
	StateMap.Add(ELauncherState::PrimaryCharged, new FLS_PrimaryCharged(this));
	StateMap.Add(ELauncherState::SecondaryCharging, new FLS_SecondaryCharging(this));
	CurrentState = StateMap[ELauncherState::Default];
}

void UNTLauncherComponent::DestroyStateMap()
{
	CurrentState = nullptr;
	for (auto& it : StateMap)
	{
		delete it.Value;
	}
}

void UNTLauncherComponent::FireProjectile(EProjectileType FireType)
{
	DEBUG_MSG("Fire : %s", FColor::Green, *GETENUMSTRING("EProjectileType", FireType));

	ChangeState(ELauncherState::Default);
}

float UNTLauncherComponent::GetChargingProgress() const
{
	return GetState()->GetChargingProgress();
}

void UNTLauncherComponent::OnPrimaryPress()
{
	GetState()->OnPrimary_Press();
}

void UNTLauncherComponent::OnPrimaryRelease()
{
	GetState()->OnPrimary_Release();
}

void UNTLauncherComponent::OnSecondaryPress()
{
	GetState()->OnSecondary_Press();
}

void UNTLauncherComponent::OnSecondaryRelease()
{
	GetState()->OnSecondary_Release();
}
