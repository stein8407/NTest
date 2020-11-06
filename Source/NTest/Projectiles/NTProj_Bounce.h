// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NTProjectileBase.h"
#include "NTProj_Bounce.generated.h"

/**
 * 
 */
UCLASS()
class NTEST_API ANTProj_Bounce : public ANTProjectileBase
{
	GENERATED_BODY()

public:
	ANTProj_Bounce();

protected:
	virtual void SetupArrow() override;
};
