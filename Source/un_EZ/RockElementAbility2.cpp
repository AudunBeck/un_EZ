// Fill out your copyright notice in the Description page of Project Settings.

#include "RockElementAbility2.h"
#include "Tori.h"


// Sets default values
ARockElementAbility2::ARockElementAbility2()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	boxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	RootComponent = boxCollider;

	Cast<UShapeComponent>(RootComponent)->SetGenerateOverlapEvents(true);

	boxCollider->OnComponentBeginOverlap.AddDynamic(this, &ARockElementAbility2::OnOverlapBegin);

}

// Called when the game starts or when spawned
void ARockElementAbility2::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ARockElementAbility2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	

}

void ARockElementAbility2::setupAttack(FVector scale, float lifeSpan)
{
	SetActorScale3D(scale);
	SetLifeSpan(lifeSpan);
}

void ARockElementAbility2::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (moving)
	{
		if (OtherActor->IsA(ATori::StaticClass()))
		{
			ATori* player = Cast<ATori>(OtherActor);
			UE_LOG(LogTemp, Warning, TEXT("PLAYER IS TOUCHING ME!"));

		}
	}
}

