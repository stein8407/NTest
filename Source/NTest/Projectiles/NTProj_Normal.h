// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NTProjectileBase.h"
#include "NTProj_Normal.generated.h"

/**
 * 
 */
UCLASS()
class NTEST_API ANTProj_Normal : public ANTProjectileBase
{
	GENERATED_BODY()

public:	
	ANTProj_Normal();

protected:
	virtual void SetupArrow() override;
};
