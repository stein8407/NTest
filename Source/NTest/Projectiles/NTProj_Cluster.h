// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NTProjectileBase.h"
#include "NTProj_Cluster.generated.h"

/**
 * 
 */
UCLASS()
class NTEST_API ANTProj_Cluster : public ANTProjectileBase
{
	GENERATED_BODY()
public:
	ANTProj_Cluster();

protected:
	virtual void SetupArrow() override;
	virtual void OnLifeSpanExpired() override;

private:
	static FQuat RelRotationL;
	static FQuat RelRotationR;
};
