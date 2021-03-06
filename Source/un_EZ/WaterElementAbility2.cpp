#include "WaterElementAbility2.h"
#include "WaterElement.h"

AWaterElementAbility2::AWaterElementAbility2()
{
	PrimaryActorTick.bCanEverTick = true;
	collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("RootComponent"));
	RootComponent = collider;
	Cast<UShapeComponent>(RootComponent)->SetGenerateOverlapEvents(true);
	Cast<UShapeComponent>(RootComponent)->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
}

void AWaterElementAbility2::BeginPlay()
{
	myElement = Cast<AWaterElement>(GetOwner());
	myPlayer = myElement->myOwner;
	SetLifeSpan(myElement->ability2lifeSpan);
	ccDur = myElement->ability2CcDur;
	slow = myElement->ability2Slow;
	damage = myElement->ability2Damage;
	myPlayer->damageMultiplier = 0.f;

	Super::BeginPlay();
	collider->OnComponentBeginOverlap.AddDynamic(this, &AWaterElementAbility2::OnOverlapBegin);
}

void AWaterElementAbility2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (myPlayer)
	{
		myPlayer->damageMultiplier = 0.f;
		myPlayer->hitAnimImmune = true;
	}
}

void AWaterElementAbility2::outputLog()
{
	UE_LOG(LogTemp, Warning, TEXT("Collision off"));
}

void AWaterElementAbility2::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor,
	UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	Super::OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if (OtherActor->IsA(ABaseAbility::StaticClass()))
	{
		if (OtherActor != this)
		{
			if (Cast<ABaseAbility>(OtherActor)->myPlayer != myPlayer)
			{
				if (myElement != nullptr)
				{
					if (myPlayer != nullptr)
					{
						ATori* enemy = Cast<ABaseAbility>(OtherActor)->getMyOwner();
						enemy->recieveDamage(myPlayer, damage);
						myPlayer->setMoveSpeed(myPlayer->moveSpeed);
						myPlayer->hitAnimImmune = false;
						UE_LOG(LogTemp, Warning, TEXT("Balls"));
						myElement->dashTime = myElement->maxDashTime;
						myElement->ability2CounterAnim();
						this->Destroy();
					}
				}
			}
		}
	}
}

