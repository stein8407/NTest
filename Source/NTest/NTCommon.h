// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"


#define GETENUMSTRING(etype, evalue) (FindObject<UEnum>(ANY_PACKAGE, TEXT(etype), true)->GetNameStringByIndex((int32)evalue))
#define DEBUG_MSG(x, Color, ...) GEngine->AddOnScreenDebugMessage(-1, 5.0f, Color, FString::Printf(TEXT(x), ##__VA_ARGS__));


UENUM()
enum class ELauncherState : uint8
{
	Default, 
	PrimaryCharging,
	PrimaryCharged,
	SecondaryCharging
};

UENUM()
enum class EProjectileType : uint8
{
	Normal,
	Charge,
	Cluster,
	Bounce
};


