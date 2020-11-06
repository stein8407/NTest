// Fill out your copyright notice in the Description page of Project Settings.

/*
탄체의 발사 상태 관리 및 발사동작 처리 
NTLauncherState를 관리하고 상태 교체, 캐릭터로부터 받은 인풋을 현재 상태와 연결해주는 역할

*/

#pragma once

#include "NTCommon.h"
#include "Components/ActorComponent.h"
#include "NTLauncherComponent.generated.h"

class FNTLauncherState;
class ANTProjectileBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NTEST_API UNTLauncherComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)	// 탄체발사위치 캡슐 전방 오프셋
	float FireOffset_Forward;

	UPROPERTY(EditDefaultsOnly) // 탄체발사위치 지면으로부터 오프셋
	float FireOffset_Ground;

private:
	FNTLauncherState* CurrentState;
	TMap<ELauncherState, FNTLauncherState*> StateMap;


public:	
	// Sets default values for this component's properties
	UNTLauncherComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ChangeState(ELauncherState NextState);
	FNTLauncherState* const GetState() const;

	void FireProjectile(EProjectileType FireType);
	float GetChargingProgress() const;

	void OnPrimaryPress();
	void OnPrimaryRelease();
	void OnSecondaryPress();
	void OnSecondaryRelease();

	static TSubclassOf<ANTProjectileBase> ProjClassByType(EProjectileType InType);

private:
	void InitStateMap();
	void DestroyStateMap();

	FTransform CalcFireTransform() const;
};
