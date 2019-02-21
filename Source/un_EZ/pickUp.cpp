// Fill out your copyright notice in the Description page of Project Settings.

#include "pickUp.h"
#include "Tori.h"
#include "Engine/Classes/Components/PrimitiveComponent.h"

ApickUp::ApickUp()
{
	PrimaryActorTick.bCanEverTick = true;
	collider = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = collider;
	Cast<UShapeComponent>(RootComponent)->SetGenerateOverlapEvents(true);
	Cast<UShapeComponent>(RootComponent)->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	collider->OnComponentBeginOverlap.AddDynamic(this, &ApickUp::OnOverlapBegin);

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
			FActorSpawnParameters tempParam;
			tempParam.Owner = player;
			ABaseElement* temp = GetWorld()->SpawnActor<ABaseElement>(ElementBlueprint, tempParam);
			if (player->pickUpElement(temp))
			{
				StartDestroy();
			}
			else
			{
				temp->Destroy();
			}
		}
		else
			UE_LOG(LogTemp, Error, TEXT("You forgot to add a element to this pickup, IDIOT!"));
	}
}