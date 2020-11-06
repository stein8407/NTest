// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../NTCommon.h"
#include "GameFramework/Actor.h"
#include "NTProjectileBase.generated.h"

UCLASS()
class NTEST_API ANTProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditDefaultsOnly)
	class USphereComponent* RootSphere;

	UPROPERTY(EditDefaultsOnly)
	class UProjectileMovementComponent* MoveComponent;

	UPROPERTY(EditDefaultsOnly)
	float SphereRadius;

	UPROPERTY(EditDefaultsOnly)
	float InitialSpeed;

	UPROPERTY(EditDefaultsOnly)
	float LifeSpan;

private:
	bool bCountLifeSpan = false;
	float RemainLifeSpan;

public:	
	// Sets default values for this actor's properties
	ANTProjectileBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void SetupArrow() {}
	virtual void OnLaunch() {}
	virtual void OnBlockedMovement() {}
	virtual void OnLifeSpanExpired() {}

	class UArrowComponent* CreateDefaultArrow(FColor InColor = FColor::Red, float InSize = 1.f);

private:
	void UpdateLifeSpan(float DeltaTime);
	void ExpireLifeSpan();
	void InitCommonMovementProperties();

	UFUNCTION()
	void OnStop(const FHitResult& ImpactResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Launch();
	
};
