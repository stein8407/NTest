// Copyright Epic Games, Inc. All Rights Reserved.

#include "NTestCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NTLauncherComponent.h"
#include "NTMainWidget.h"

ANTestCharacter::ANTestCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Rotation of the character should not affect rotation of boom
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->SocketOffset = FVector(0.f,0.f,75.f);
	CameraBoom->SetRelativeRotation(FRotator(0.f,180.f,0.f));

	// Create a camera and attach to boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	LauncherComponent = CreateDefaultSubobject<UNTLauncherComponent>(TEXT("LauncherComp"));

	ConstructorHelpers::FClassFinder<UUserWidget> WidgetClassFinder(TEXT("/Game/SideScrollerCPP/Blueprints/UW_Main"));
	MainWidgetClass = WidgetClassFinder.Class;
}


void ANTestCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	SetupWidget();
}

void ANTestCharacter::SetupWidget()
{
	auto PC = Cast<APlayerController>(GetController());
	if(PC == nullptr)
		return;

	PC->bShowMouseCursor = true;
	auto MainWidget = CreateWidget<UNTMainWidget>(PC, MainWidgetClass);
	MainWidget->Init(this);
	MainWidget->AddToViewport();
}

//////////////////////////////////////////////////////////////////////////
// Input

void ANTestCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAxis("MoveRight", this, &ANTestCharacter::MoveRight);

	PlayerInputComponent->BindTouch(IE_Pressed, this, &ANTestCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ANTestCharacter::TouchStopped);

	PlayerInputComponent->BindAction("Action1", IE_Pressed, this, &ANTestCharacter::Action1_Pressed);
	PlayerInputComponent->BindAction("Action1", IE_Released, this, &ANTestCharacter::Action1_Released);
	PlayerInputComponent->BindAction("Action2", IE_Pressed, this, &ANTestCharacter::Action2_Pressed);
	PlayerInputComponent->BindAction("Action2", IE_Released, this, &ANTestCharacter::Action2_Released);
}

void ANTestCharacter::MoveRight(float Value)
{
	// add movement in that direction
	AddMovementInput(FVector(0.f,-1.f,0.f), Value);
}

void ANTestCharacter::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// jump on any touch
	Jump();
}

void ANTestCharacter::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	StopJumping();
}

void ANTestCharacter::Action1_Pressed()
{
	LauncherComponent->OnPrimaryPress();
}

void ANTestCharacter::Action1_Released()
{
	LauncherComponent->OnPrimaryRelease();
}

void ANTestCharacter::Action2_Pressed()
{
	LauncherComponent->OnSecondaryPress();
}

void ANTestCharacter::Action2_Released()
{
	LauncherComponent->OnSecondaryRelease();
}