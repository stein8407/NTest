// Fill out your copyright notice in the Description page of Project Settings.

/*
źü�� �߻� ���� ���� �� �߻絿�� ó�� 
NTLauncherState�� �����ϰ� ���� ��ü, ĳ���ͷκ��� ���� ��ǲ�� ���� ���¿� �������ִ� ����

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
	UPROPERTY(EditDefaultsOnly)	// źü�߻���ġ ĸ�� ���� ������
	float FireOffset_Forward;

	UPROPERTY(EditDefaultsOnly) // źü�߻���ġ �������κ��� ������
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
