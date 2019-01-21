// Fill out your copyright notice in the Description page of Project Settings.

#include "pickUp.h"
#include "Tori.h"
#include "Engine/Classes/Components/PrimitiveComponent.h"

// Sets default values
ApickUp::ApickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	collider = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = collider;
	Cast<UShapeComponent>(RootComponent)->SetGenerateOverlapEvents(true);
	Cast<UShapeComponent>(RootComponent)->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	collider->OnComponentBeginOverlap.AddDynamic(this, &ApickUp::OnOverlapBegin);

}

// Called when the game starts or when spawned
void ApickUp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ApickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ApickUp::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("PickUp Getting hit"));
	if (OtherActor->IsA(ATori::StaticClass()))
	{
		ATori* player = Cast<ATori>(OtherActor);
		ABaseElement* temp = GetWorld()->SpawnActor<ABaseElement>(ElementBlueprint);
		if (player->pickUpElement(temp))
		{
			temp->myOwner = player;
			Destroy();
		}
		else
		{
			temp->Destroy();
		}
	}
}

