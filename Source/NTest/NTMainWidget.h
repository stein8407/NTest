// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NTCommon.h"
#include "Blueprint/UserWidget.h"
#include "NTMainWidget.generated.h"


class UProgressBar;
class UTextBlock;
class UButton;
class UBorder;
class ANTestCharacter;
class UNTLauncherComponent;

UCLASS()
class NTEST_API UNTMainWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UBorder* BD_Charge;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UProgressBar* PB_Charge;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UTextBlock* TXT_A;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UTextBlock* TXT_B;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UTextBlock* TXT_C;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UTextBlock* TXT_D;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	UButton* BT_Reset;

	
private:
	TWeakObjectPtr<UNTLauncherComponent> ProjLauncherPtr;

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void Init(ANTestCharacter* InOwnerChar);
private:
	
	UFUNCTION()
	void ResetBoard();
	void ResetWidget();

	void UpdateProgress();
	void UpdateFireCount();
};
