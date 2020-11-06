// Fill out your copyright notice in the Description page of Project Settings.


#include "NTProj_Charge.h"

ANTProj_Charge::ANTProj_Charge()
{
	LifeSpan = 5.f;
}

void ANTProj_Charge::SetupArrow()
{
	CreateDefaultArrow(FColor::Red, 3.f);
}