// Fill out your copyright notice in the Description page of Project Settings.

#include "RockElementAbility2.h"
#include "Tori.h"
#include "Engine/BlockingVolume.h"


// Sets default values
ARockElementAbility2::ARockElementAbility2()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	boxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	boxCollider->SetupAttachment(RootComponent);

	Cast<UShapeComponent>(boxCollider)->SetGenerateOverlapEvents(true);
	boxCollider->OnComponentBeginOverlap.AddDynamic(this, &ARockElementAbility2::OnOverlapBegin);

}

// Called when the game starts or when spawned
void ARockElementAbility2::BeginPlay()
{
	Super::BeginPlay();
	myElement = Cast<ARockElement>(GetOwner());
	myPlayer = myElement->myOwner;
	//SetActorScale3D(scale);
	SetLifeSpan(myElement->ability2Lifespan);
	speed = myElement->ability2Speed;
	damageDivision = speed;
	playerKnockback = myElement->ability2KnockbackMulti;
	damage = myElement->ability2Damage;
}

// Called every frame
void ARockElementAbility2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (movingTime > 0)
	{
		FVector NewLocation = GetActorLocation();
		NewLocation += GetActorForwardVector() * speed * DeltaTime;
		SetActorLocation(NewLocation);
		movingTime -= DeltaTime;
	}
}

void ARockElementAbility2::setupAttack(ATori * newOwner, FVector scale, float lifeSpan, float wallSpeed, float knockbackMultiplier)
{
	//myPlayer = newOwner;
	//SetActorScale3D(scale);
	//SetLifeSpan(lifeSpan);
	//speed = wallSpeed;
	//playerKnockback = knockbackMultiplier;
}

void ARockElementAbility2::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor,
	UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (movingTime > 0)
	{
		if (OtherActor->IsA(ATori::StaticClass()))
		{
			ATori* player = Cast<ATori>(OtherActor);
			UE_LOG(LogTemp, Warning, TEXT("PLAYER IS TOUCHING ME!"));
			player->recieveDamage(damage * (speed / damageDivision), playerKnockback * speed, GetActorLocation());
		}
		else if(OtherActor->IsA(ABlockingVolume::StaticClass()) || OtherActor->IsA(ARockElementAbility2::StaticClass()))
		{
			movingTime = 0;
		}
	}

}

void ARockElementAbility2::moveWall(FRotator playerRot, float punchSpeed)
{
	/// Can update this function to "slowly" turn the wall towards the correct rotation
	//punchPos = playerLoc;
	//wallPos = this->GetActorLocation();
	//FRotator temp = (wallPos - punchPos).Rotation();
	FRotator temp = playerRot;
	this->SetActorRotation(temp);
	movingTime = maxMovingTime;
	speed *= punchSpeed;
}
