// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseAbility.h"
#include "Engine/Classes/Components/SphereComponent.h"
#include "WaterElement.h"
#include "GameFramework/Actor.h"
#include "WaterElementAbility2.generated.h"

class AWaterElement;

UCLASS()
class UN_EZ_API AWaterElementAbility2 : public ABaseAbility
{
	GENERATED_BODY()
	
public:
	AWaterElementAbility2();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	float currBuffDur;
	float dashDist;
	float ccDur;
	float slow;
	float damage;


	// Blueprint functions
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "WaterAbility2 collision")
		void stopCollision();

	UFUNCTION(BlueprintCallable, Category = "Output Log WaterAbility 2")
		void outputLog();

	UPROPERTY(EditAnywhere, Category = "Ability2", BlueprintReadWrite)
		class AWaterElement* myElement;

	USphereComponent* collider;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
