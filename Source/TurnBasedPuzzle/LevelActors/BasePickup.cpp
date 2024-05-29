// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePickup.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TurnBasedPuzzle/Characters/HeroCharacter.h"

// Sets default values
ABasePickup::ABasePickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pickup Mesh"));
	PickupMesh->SetupAttachment(RootComponent);
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	BoxCollider->SetupAttachment(RootComponent);
	RotatingMovementComp = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("Rotation Movment Comp"));
	PickupMesh->SetCanEverAffectNavigation(false);//
	BoxCollider->SetCanEverAffectNavigation(false);//
	
}

// Called when the game starts or when spawned
void ABasePickup::BeginPlay()
{
	Super::BeginPlay();
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this,&ABasePickup::OnBoxColliderBeginOverlap);
}

// Called every frame
void ABasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasePickup::OnBoxColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AHeroCharacter* HeroCharacter = Cast<AHeroCharacter>(OtherActor))
	{
		switch (PickupType)
		{
		case EPickupType::EPT_Stone:
			HeroCharacter->SpawnStone();
			HeroCharacter->bCanThrowStone = true;
			if (Cue_Pickup)
			{
				UGameplayStatics::PlaySound2D(GetWorld(),Cue_Pickup);
			}
			Destroy();
			break;
		case EPickupType::EPT_Pistol:
			HeroCharacter->bCanShoot = true;
			HeroCharacter->PistolAmmo = AmmoAmount;
			if (Cue_Pickup)
			{
				UGameplayStatics::PlaySound2D(GetWorld(),Cue_Pickup);
			}
			Destroy();
			break;
		}
	}
}