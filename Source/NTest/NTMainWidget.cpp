// Fill out your copyright notice in the Description page of Project Settings.


#include "NTMainWidget.h"
#include "Components/Border.h"
#include "Components/Button.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "NTLauncherComponent.h"
#include "NTestCharacter.h"

void UNTMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ResetWidget();
	BT_Reset->OnClicked.AddDynamic(this, &UNTMainWidget::ResetBoard);
}

void UNTMainWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if(!ProjLauncherPtr.IsValid())
		return;

	UpdateProgress();
	UpdateFireCount();
}

void UNTMainWidget::Init(ANTestCharacter* InOwnerChar)
{
	ensure(InOwnerChar != nullptr);
	ProjLauncherPtr = InOwnerChar->LauncherComponent;
}

void UNTMainWidget::ResetBoard()
{
	if(ProjLauncherPtr.IsValid())
		ProjLauncherPtr->ResetFireCounts();
}

void UNTMainWidget::ResetWidget()
{
	ResetBoard();
	BD_Charge->SetVisibility(ESlateVisibility::Hidden);
	PB_Charge->SetPercent(0.f);
}

void UNTMainWidget::UpdateProgress()
{
	float ChargingProgress = ProjLauncherPtr->GetChargingProgress();
	BD_Charge->SetVisibility(ChargingProgress > 0.f ? ESlateVisibility::SelfHitTestInvisible : ESlateVisibility::Hidden);
	PB_Charge->SetPercent(ChargingProgress);
}

void UNTMainWidget::UpdateFireCount()
{
	TXT_A->SetText(FText::FromString(FString::FromInt(ProjLauncherPtr->GetFireCount(EProjectileType::Normal))));
	TXT_B->SetText(FText::FromString(FString::FromInt(ProjLauncherPtr->GetFireCount(EProjectileType::Charge))));
	TXT_C->SetText(FText::FromString(FString::FromInt(ProjLauncherPtr->GetFireCount(EProjectileType::Cluster))));
	TXT_D->SetText(FText::FromString(FString::FromInt(ProjLauncherPtr->GetFireCount(EProjectileType::Bounce))));
}