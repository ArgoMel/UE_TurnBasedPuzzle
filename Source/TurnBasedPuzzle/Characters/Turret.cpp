// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"

#include "HeroCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ATurret::ATurret()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	TurretMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void ATurret::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(TH_TracePlayer,this,&ATurret::TracePlayer,1.0f,true,.2f);
}

// Called every frame
void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATurret::TracePlayer()
{
	const FVector StartTrace = TurretMesh->GetSocketLocation(TurretSocket);
	const FVector EndTrace = StartTrace + (GetActorForwardVector() * Distance);
	FHitResult HitResult;
	const TArray<AActor*> ActorsToIgnore;
	const bool bHit = UKismetSystemLibrary::BoxTraceSingleForObjects(GetWorld(),StartTrace,EndTrace,FVector(8.0f),FRotator::ZeroRotator,
		TraceObjectQuery,true,ActorsToIgnore,EDrawDebugTrace::ForDuration,HitResult,true);
	if (bHit)
	{
		if (AHeroCharacter* HeroCharacter = Cast<AHeroCharacter>(HitResult.GetActor()))
		{
			HeroCharacter->PlayerKilled();
			GetWorldTimerManager().PauseTimer(TH_TracePlayer);
			if (Cue_BlastLaser)
			{
				UGameplayStatics::PlaySound2D(GetWorld(),Cue_BlastLaser);
			}
			if (Anim_Fire)
			{
				TurretMesh->PlayAnimation(Anim_Fire,false);
			}
		}
	}
	
}

