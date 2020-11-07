// Fill out your copyright notice in the Description page of Project Settings.


#include "NTLauncherComponent.h"
#include "NTLauncherState.h"
#include "NTestCharacter.h"
#include "Projectiles/NTProjectileBase.h"
#include "Components/CapsuleComponent.h"
#include "Projectiles/NTProj_Normal.h"
#include "Projectiles/NTProj_Cluster.h"
#include "Projectiles/NTProj_Charge.h"
#include "Projectiles/NTProj_Bounce.h"

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
	// DEBUG_MSG("ChangeState : %s", FColor::Red, *GETENUMSTRING("ELauncherState", NextState));

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

TSubclassOf<ANTProjectileBase> UNTLauncherComponent::ProjClassByType(EProjectileType InType)
{
	UClass* ProjectileClass = nullptr;
	switch (InType)
	{
	case EProjectileType::Normal:	ProjectileClass = ANTProj_Normal::StaticClass();	break;
	case EProjectileType::Cluster:	ProjectileClass = ANTProj_Cluster::StaticClass();	break;
	case EProjectileType::Charge:	ProjectileClass = ANTProj_Charge::StaticClass();	break;
	case EProjectileType::Bounce:	ProjectileClass = ANTProj_Bounce::StaticClass();	break;
	}

	return ProjectileClass;
}

FTransform UNTLauncherComponent::CalcFireTransform() const
{
	auto OwnerChar = Cast<ANTestCharacter>(GetOwner());
	ensure(OwnerChar != nullptr);

	float CapRadius, CapHalfHeight;
	OwnerChar->GetCapsuleComponent()->GetScaledCapsuleSize(CapRadius, CapHalfHeight);
	FVector FwdVector = OwnerChar->GetActorForwardVector();

	FVector FireLocation = OwnerChar->GetActorLocation() + FwdVector * (CapRadius + FireOffset_Forward);
	FireLocation.Z += FireOffset_Ground - CapHalfHeight;

	return FTransform(OwnerChar->GetActorQuat(), FireLocation);
}


void UNTLauncherComponent::FireProjectile(EProjectileType FireType)
{
	// DEBUG_MSG("Fire : %s", FColor::Green, *GETENUMSTRING("EProjectileType", FireType));

	auto Proj = GetWorld()->SpawnActor<ANTProjectileBase>(ProjClassByType(FireType), CalcFireTransform());
	ensure(Proj != nullptr);
	Proj->Launch();
	
	// 발사 후에는 상태 초기화 
	ChangeState(ELauncherState::Default);
}