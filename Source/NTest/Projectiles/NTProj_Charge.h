// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NTProjectileBase.h"
#include "NTProj_Charge.generated.h"

/**
 * 
 */
UCLASS()
class NTEST_API ANTProj_Charge : public ANTProjectileBase
{
	GENERATED_BODY()

public:
	ANTProj_Charge();

protected:
	virtual void SetupArrow() override;
};
