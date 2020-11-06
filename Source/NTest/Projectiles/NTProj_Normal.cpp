// Fill out your copyright notice in the Description page of Project Settings.


#include "NTProj_Normal.h"
#include "Components/ArrowComponent.h"

ANTProj_Normal::ANTProj_Normal()
{
	LifeSpan = 3.f;
}

void ANTProj_Normal::SetupArrow()
{
	CreateDefaultArrow();
}