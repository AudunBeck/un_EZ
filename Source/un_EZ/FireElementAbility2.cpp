// Fill out your copyright notice in the Description page of Project Settings.

#include "FireElementAbility2.h"
#include "GameFramework/CharacterMovementComponent.h"

AFireElementAbility2::AFireElementAbility2()
{
	PrimaryActorTick.bCanEverTick = true;
	collider = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent")); // Can change USphereComponent to Mesh
	RootComponent = collider;
	Cast<UShapeComponent>(RootComponent)->SetGenerateOverlapEvents(true);
	Cast<UShapeComponent>(RootComponent)->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	collider->OnComponentBeginOverlap.AddDynamic(this, &AFireElementAbility2::OnOverlapBegin);
}

void AFireElementAbility2::BeginPlay()
{
	Super::BeginPlay();
	myElement = Cast<AFireElement>(GetOwner());
	myPlayer = myElement->myOwner;
	SetLifeSpan(myElement->ability2Lifespan);
	attackRange = myElement->ability2Range;
	damage = myElement->ability2Damage;
	//myPlayer->GetCharacterMovement()->GravityScale = 0.f;
}

void AFireElementAbility2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector forward = myPlayer->GetActorForwardVector();
	NewLocation = myPlayer->GetActorLocation();
	NewLocation += (forward * speed * DeltaTime);
	myPlayer->SetActorLocation(NewLocation);

	// Sets the hitbox ahead of the player while flying forward
	SetActorLocation(myPlayer->GetActorForwardVector() * attackRange + myPlayer->GetActorLocation());
	SetActorRotation(myPlayer->GetActorRotation());
}

void AFireElementAbility2::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	Super::OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if (OtherActor != myPlayer)
	{
		if (OtherActor->IsA(ATori::StaticClass()))
		{
			myPlayer->setRotationRate(myPlayer->rotationRate);
			myPlayer->setMoveSpeed(myPlayer->moveSpeed);
			Cast<ATori>(OtherActor)->recieveDamage(myPlayer, damage);
			myPlayer->stopAllVelocity();
			myElement->fireChi = 2;
			myPlayer->freezeFrame(0.3, true);
			myPlayer->locked = 0;		
			myElement->abilityHit = true;
			Destroy();
		}
	}
}