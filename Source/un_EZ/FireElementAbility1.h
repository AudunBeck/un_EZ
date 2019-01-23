// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/Classes/Components/SphereComponent.h"
#include "RockElementAbility2.h"
#include "Tori.h"
#include "FireElementAbility1.generated.h"

UCLASS()
class UN_EZ_API AFireElementAbility1 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFireElementAbility1();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Owner of the attack
	void setupAttack(ATori* newOwner, float lifeSpan, float range);

	UPROPERTY(EditAnywhere, Category = "Ability1")
		class ATori* myOwner;

	UPROPERTY(EditAnywhere, Category = "Ability1")
		USphereComponent* collider;


	// Add a description here
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	bool buffed = false;
	float attackRange = 100;

};