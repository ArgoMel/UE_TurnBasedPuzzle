#include "EnemyCharacter.h"
#include "../TurnedBasedMacro.h"
#include "HeroCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TurnBasedPuzzle/AI/EnemyController.h"

AEnemyCharacter::AEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	AttackCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Attack Coolider"));
	AttackCollider->SetupAttachment(GetMesh());

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("Pawn Sensing Comp"));
	PawnSensingComp->HearingThreshold = 1000.0f;
	PawnSensingComp->LOSHearingThreshold = 1200.0f;
	PawnSensingComp->SightRadius = 400.0f;
	PawnSensingComp->SetPeripheralVisionAngle(20.0f);
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	AttackCollider->OnComponentBeginOverlap.AddDynamic(this,&AEnemyCharacter::OnAttackColliderBeginOverlap);
	PawnSensingComp->OnSeePawn.AddDynamic(this,&AEnemyCharacter::OnSeenPawn);
	PawnSensingComp->OnHearNoise.AddDynamic(this,&AEnemyCharacter::OnHearingNoise);
	AHeroCharacter* HeroCharacter = 
		Cast<AHeroCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (HeroCharacter&&
		EnemyType == EEnemyType::EET_Revenant)
	{
		HeroCharacter->OnPlayerMoved.AddDynamic(this, &AEnemyCharacter::Flip);
	}
}

void AEnemyCharacter::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	AttackCollider->AttachToComponent(
		GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);
}

void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemyCharacter::AttackPlayer()
{
	if (UAnimInstance* AnimInstance = Cast<UAnimInstance>(GetMesh()->GetAnimInstance()))
	{
		if (Montage_Attack)
		{
			AnimInstance->Montage_Play(Montage_Attack,1.0f);
			if (Cue_AttackSound)
			{
				UGameplayStatics::PlaySound2D(GetWorld(),Cue_AttackSound);
			}
		}
	}
}

void AEnemyCharacter::Flip()
{
	const float Yaw = GetActorRotation().Yaw;
	if (Yaw == 0.0f)
	{
		SetActorRotation(FRotator(0.0f,180.0f,0.0f));
	}
	else if(Yaw == 180.0f)
	{
		SetActorRotation(FRotator(0.0f,0.0f,0.0f));
	}
	else
	{
		SetActorRotation(FRotator(0.0f,Yaw * -1,0.0f));
	}
}

void AEnemyCharacter::EnemyKilled()
{
	bIsAlive = false;
	SetLifeSpan(1.0f);
}

void AEnemyCharacter::OnAttackColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor,	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
	bool bFromSweep, const FHitResult& SweepResult)
{
	if (AHeroCharacter* HeroCharacter = Cast<AHeroCharacter>(OtherActor))
	{
		HeroCharacter->PlayerKilled();
		if (Cue_AttackSound)
		{
			UGameplayStatics::PlaySound2D(GetWorld(),Cue_AttackSound);
		}
	}
}

void AEnemyCharacter::OnSeenPawn(APawn* InPawn)
{
	if (AHeroCharacter* HeroCharacter = Cast<AHeroCharacter>(InPawn))
	{
		HeroCharacter->bIsMoving = false;
		HeroCharacter->bCanClickNode = false;
		if (AEnemyController* EnemyController = Cast<AEnemyController>(GetController()))
		{
			switch (EnemyType)
			{
			case EEnemyType::EET_Khiamera:
				EnemyController->GetBlackboardComponent()->SetValueAsBool(BB_CanSeePlayer,true);
				EnemyController->GetBlackboardComponent()->SetValueAsVector(
					BB_PlayerLocation,HeroCharacter->GetActorLocation());
				break;
			case EEnemyType::EET_Revenant:
				if (HeroCharacter->bIsAlive)
				{
					bCanShoot = true;
					HeroCharacter->PlayerKilled();
					if (Cue_AttackSound)
					{
						UGameplayStatics::PlaySound2D(GetWorld(),Cue_AttackSound);
					}
					if (Cue_PistolShoot)
					{
						UGameplayStatics::PlaySound2D(GetWorld(),Cue_PistolShoot);
					}
				}		
				break;
			case EEnemyType::EET_Grux:
				EnemyController->GetBlackboardComponent()->SetValueAsBool(
					BB_GruxCanSeePlayer,true);
				EnemyController->GetBlackboardComponent()->SetValueAsVector(
					BB_GPlayerLocation,HeroCharacter->GetActorLocation());
				EnemyController->GetBlackboardComponent()->SetValueAsBool(
					BB_GruxCanMove,false);
				EnemyController->GetBlackboardComponent()->SetValueAsBool(
					BB_GruxHearNoise,false);
				break;
			default: ;
			}
		}
		
	}
}

void AEnemyCharacter::OnHearingNoise(APawn* _Instigator, const FVector& Location, 
	float Volume)
{
	if (EnemyType == EEnemyType::EET_Grux)
	{
		if (AEnemyController* EnemyController = Cast<AEnemyController>(GetController()))
		{
			EnemyController->GetBlackboardComponent()->SetValueAsBool(
				BB_GruxHearNoise,true);
			EnemyController->GetBlackboardComponent()->SetValueAsVector(
				BB_NoiseLocation,Location);
		}
	}
}
