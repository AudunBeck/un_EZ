// Fill out your copyright notice in the Description page of Project Settings.

#include "FireElementAbility2.h"

// Sets default values
AFireElementAbility2::AFireElementAbility2()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFireElementAbility2::BeginPlay()
{
	Super::BeginPlay();
	myElement = Cast<AFireElement>(GetOwner());
	myPlayer = myElement->myOwner;
	SetLifeSpan(myElement->ability2Lifespan);
	attackRange = myElement->ability2Range;
}

// Called every frame
void AFireElementAbility2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Sets the hitbox ahead of the player while flying forward
	this->SetActorLocation(myPlayer->GetActorForwardVector() * attackRange + myPlayer->GetActorLocation());
	this->SetActorRotation(myPlayer->GetActorRotation());
}

