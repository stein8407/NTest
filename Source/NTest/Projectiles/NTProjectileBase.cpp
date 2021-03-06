// Fill out your copyright notice in the Description page of Project Settings.


#include "NTProjectileBase.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/ArrowComponent.h"

// Sets default values
ANTProjectileBase::ANTProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereRadius = 15.f;
	InitialSpeed = 100.f;
	LifeSpan = 3.f;
	bDestroyOnHit = true;

	RootSphere = CreateDefaultSubobject<USphereComponent>(TEXT("RootSphere"));
	RootSphere->SetCollisionProfileName(TEXT("Projectile"));
	RootSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootSphere->SetSphereRadius(SphereRadius);
	RootSphere->SetHiddenInGame(false);
	SetRootComponent(RootSphere);

	MoveComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MoveComp"));
	InitCommonMovementProperties();
}

// Called when the game starts or when spawned
void ANTProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	SetupArrow();
}

// Called every frame
void ANTProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateLifeSpan(DeltaTime);
}

void ANTProjectileBase::UpdateLifeSpan(float DeltaTime)
{
	if (!bCountLifeSpan)
		return;
	
	RemainLifeSpan -= DeltaTime;
	if (RemainLifeSpan <= 0.f)
	{
		ExpireLifeSpan();
	}
}

void ANTProjectileBase::Launch()
{	
	RootSphere->OnComponentHit.AddDynamic(this, &ANTProjectileBase::OnHit);
	RootSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	
	RemainLifeSpan = LifeSpan;
	bCountLifeSpan = RemainLifeSpan > 0.f;

	MoveComponent->Activate();
	OnLaunch();
}

void ANTProjectileBase::ExpireLifeSpan()
{
	bCountLifeSpan = false;
	OnLifeSpanExpired();
	Destroy();
}

void ANTProjectileBase::InitCommonMovementProperties()
{
	ensure(MoveComponent != nullptr);

	MoveComponent->SetUpdatedComponent(RootSphere);
	MoveComponent->SetAutoActivate(false);
	MoveComponent->InitialSpeed = InitialSpeed;
	MoveComponent->MaxSpeed = InitialSpeed;

	MoveComponent->bRotationFollowsVelocity = true;
	MoveComponent->ProjectileGravityScale = 0.f;
	MoveComponent->BounceVelocityStopSimulatingThreshold = 0.f;
}

UArrowComponent* ANTProjectileBase::CreateDefaultArrow(FColor InColor, float InSize)
{
	static const float DefaultArrowSize = 1.f;
	auto Arrow = NewObject<UArrowComponent>(this);
	Arrow->SetHiddenInGame(false);
	Arrow->ArrowColor = InColor;
	Arrow->ArrowSize = DefaultArrowSize * InSize;
	Arrow->SetUsingAbsoluteScale(true);
	Arrow->RegisterComponent();
	Arrow->AttachToComponent(GetRootComponent(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false));
	return Arrow;
}

void ANTProjectileBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// DEBUG_MSG("Hit !!", FColor::Cyan);

	if (bDestroyOnHit)
	{
		Destroy();
	}
}