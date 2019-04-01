// Fill out your copyright notice in the Description page of Project Settings.

#include "pickUp.h"
#include "Tori.h"
#include "Engine/Classes/Components/PrimitiveComponent.h"
#include "pickUpSpawner.h"

ApickUp::ApickUp()
{
	PrimaryActorTick.bCanEverTick = true;
	collider = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = collider;
	Cast<UShapeComponent>(RootComponent)->SetGenerateOverlapEvents(true);
	Cast<UShapeComponent>(RootComponent)->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	collider->OnComponentBeginOverlap.AddDynamic(this, &ApickUp::OnOverlapBegin);
	collider->OnComponentEndOverlap.AddDynamic(this, &ApickUp::OnOverlapEnd);

}

void ApickUp::BeginPlay()
{
	Super::BeginPlay();
}

void ApickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ApickUp::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ATori::StaticClass()))
	{
		if (ElementBlueprint != nullptr)
		{
			ATori* player = Cast<ATori>(OtherActor);
			player->currentPickUp = this;
		}
		else
			UE_LOG(LogTemp, Error, TEXT("You forgot to add a element to this pickup, IDIOT!"));
	}
}

void ApickUp::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Error, TEXT("Object walking away"));
	if (OtherActor->IsA(ATori::StaticClass()))
	{
		ATori* player = Cast<ATori>(OtherActor);
		player->currentPickUp = nullptr;
		UE_LOG(LogTemp, Error, TEXT("Player Walking away"));

	}
}

void ApickUp::giveElement(ATori * player)
{
	FActorSpawnParameters tempParam;
	tempParam.Owner = player;
	ABaseElement* temp = GetWorld()->SpawnActor<ABaseElement>(ElementBlueprint, tempParam);
	if (player->pickUpElement(temp))
	{
		if (mySpawner != nullptr)
			mySpawner->elementPickedUp();
		StartDestroy();
	}
	else
	{
		temp->Destroy();
	}
}
