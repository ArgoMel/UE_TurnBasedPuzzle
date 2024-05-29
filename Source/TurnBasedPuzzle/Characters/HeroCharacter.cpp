// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroCharacter.h"
#include "EnemyCharacter.h"
#include "TurnBasedPuzzle/LevelActors/ThrowableStone.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "HeroController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/PawnNoiseEmitterComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "TurnBasedPuzzle/LevelActors/BasePickup.h"
#include "TurnBasedPuzzle/LevelActors/NodeBase.h"

// Sets default values
AHeroCharacter::AHeroCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PawnNoiseEmitterComp = CreateDefaultSubobject<UPawnNoiseEmitterComponent>(TEXT("Pawn Noise Emitter Comp"));
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

// Called when the game starts or when spawned
void AHeroCharacter::BeginPlay()
{
	Super::BeginPlay();
	bUseControllerRotationPitch = false;//
	bUseControllerRotationRoll = false;//
	bUseControllerRotationYaw = false;//
	InsertMappingContext();
	if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
	{
		if (Montage_Intro)
		{
			AnimInstance->Montage_Play(Montage_Intro,1.0f);
			GetWorldTimerManager().SetTimer(TH_ResetPlayerMovment,this,&AHeroCharacter::ResetPlayerMovment,1.0f,false,1.5f);
		}
	}
}

// Called every frame
void AHeroCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddOffsetToPlayer(DeltaTime);
}

// Called to bind functionality to input
void AHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// handle pistol shoot
		EnhancedInputComponent->BindAction(ActionFire,ETriggerEvent::Started,this,&AHeroCharacter::PistolShoot);

		// handle player movement
		EnhancedInputComponent->BindAction(ActionMove,ETriggerEvent::Started,this,&AHeroCharacter::StartClickNode);
		EnhancedInputComponent->BindAction(ActionMove,ETriggerEvent::Completed,this,&AHeroCharacter::MovePlayerToNodeLocation);

		// handle teleport 
		EnhancedInputComponent->BindAction(ActionTeleport,ETriggerEvent::Started,this,&AHeroCharacter::TeleportPlayer);

		// handel throwing a stone 
		EnhancedInputComponent->BindAction(ActionThrowStone,ETriggerEvent::Started,this,&AHeroCharacter::ThrowStone);
	}
}

void AHeroCharacter::SpawnStone()
{
	if (StoneClass)
	{
		const FVector SpawnLocation = GetActorLocation();
		FActorSpawnParameters SpawnParams;
		SpawnParams.Instigator = this;
		SpawnParams.Owner = this;
		StoneInstance = GetWorld()->SpawnActor<AThrowableStone>(StoneClass,SpawnLocation,FRotator::ZeroRotator,SpawnParams);
		const FName StoneSocket = FName("StoneSocket");
		StoneInstance->AttachToComponent(GetMesh(),FAttachmentTransformRules::SnapToTargetNotIncludingScale,StoneSocket);
		StoneInstance->SetActorScale3D(FVector(.7f));
	}
}

void AHeroCharacter::ReportNoise()
{
	if (PawnNoiseEmitterComp)
	{
		if (TargetNode)
		{
			PawnNoiseEmitterComp->MakeNoise(TargetNode,1000.0f,StoneLocation);
		}
	}
}

void AHeroCharacter::PlayerKilled()
{
	bIsAlive = false;
	bCanClickNode = false;
	bCanShoot = false;
	if (Cue_DeathSound)
	{
		UGameplayStatics::PlaySound2D(GetWorld(),Cue_DeathSound);
	}
	if (OnPlayerDeath.IsBound())
	{
		OnPlayerDeath.Broadcast();
	}
}

void AHeroCharacter::PistolShoot()
{
	if (CanPlayerShoot())
	{
		bCanClickNode = false;
		if (const AHeroController* HeroController = Cast<AHeroController>(GetController()))
		{
			FHitResult HitResult;
			if (HeroController->GetHitResultUnderCursorForObjects(ShootObjectsQuery,true,HitResult))
			{
				if (AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(HitResult.GetActor()))
				{
					--PistolAmmo;
					EnemyCharacter->EnemyKilled();
					const FRotator YawRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(),EnemyCharacter->GetActorLocation());
					SetActorRotation(FRotator(0.0f,YawRotation.Yaw,0.0f));
					if (Cue_PistolShoot)
					{
						UGameplayStatics::PlaySound2D(GetWorld(),Cue_PistolShoot);
						if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
						{
							if (Montage_Fire != nullptr)
							{
								AnimInstance->Montage_Play(Montage_Fire,1.0f);
								if (FX_Pistol)
								{
									const FName SpawnSocket = FName("Muzzle_01");
									const FVector SpawnLocation = GetMesh()->GetSocketLocation(SpawnSocket);
									UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),FX_Pistol,SpawnLocation,FRotator::ZeroRotator);
									GetWorldTimerManager().SetTimer(TH_ResetPlayerMovment,this,&AHeroCharacter::ResetPlayerMovment,1.0f,false,2.0f);
								}
							}
						}
					}
				}
				
				
			}
		}
	}
}

void AHeroCharacter::ThrowStone()
{
	if (bCanThrowStone)
	{
		bCanThrowStone = false;
		bCanClickNode = false;
		if (const AHeroController* HeroController = Cast<AHeroController>(GetController()))
		{
			FHitResult HitResult;
			if (HeroController->GetHitResultUnderCursorForObjects(StoneObjectsQuery,true,HitResult))
			{
				if (ANodeBase* NodeBase = Cast<ANodeBase>(HitResult.GetActor()))
				{
					TargetNode = NodeBase;
					StoneLocation = HitResult.Location;
					const FRotator YawRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(),StoneLocation);
					SetActorRotation(FRotator(0.0f,YawRotation.Yaw,0.0f));

					if (TargetNode)
					{
						if (!TargetNode->BoxCollider->IsOverlappingActor(this))
						{
							if (StoneInstance)
							{
								StoneInstance->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
								const FVector VecDistance = NodeLocation - GetActorLocation();
								const FVector Velocity = UKismetMathLibrary::MakeVector(VecDistance.X,VecDistance.Y,VecDistance.Z + 600.0f); //
								StoneInstance->ThrowStone(TargetNode,Velocity);
							}
						}
					}
				}
			}
		}
	}
}

void AHeroCharacter::TeleportPlayer()
{
	if (bCanTeleport)
	{
		TArray<AActor*> OverlapActors;
		GetCapsuleComponent()->GetOverlappingActors(OverlapActors,ANodeBase::StaticClass());
		if (const ANodeBase* NodeBase = Cast<ANodeBase>(OverlapActors[0]))
		{
			if (NodeBase->TeleportNode != nullptr)
			{
				if (Cue_Teleport)
				{
					UGameplayStatics::PlaySound2D(GetWorld(),Cue_Teleport);
					if (FX_Teleport)
					{
						UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),FX_Teleport,NodeBase->TeleportNode->GetActorLocation());
						const FRotator YawRotation = UKismetMathLibrary::FindLookAtRotation(NodeBase->GetActorLocation(),GetActorLocation());
						const FVector TeleportLocation = NodeBase->TeleportNode->GetActorLocation();
						TArray<AActor*> OverlapPickups;
						UGameplayStatics::GetAllActorsOfClass(GetWorld(),ABasePickup::StaticClass(),OverlapPickups);
						if (const ABasePickup* BasePickup = Cast<ABasePickup>(OverlapPickups[0]))
						{
							if (NodeBase->TeleportNode->BoxCollider->IsOverlappingActor(BasePickup))
							{
								TeleportTo(TeleportLocation,FRotator(0.0f,YawRotation.Yaw,0.0f));
							}
							else
							{
								TeleportTo(TeleportLocation,FRotator(0.0f,YawRotation.Yaw,0.0f));
							}
						}
						
						
					}
				}
			}
		}
	}
}

void AHeroCharacter::StartClickNode()
{
	if (bCanClickNode)
	{
		if (const AHeroController* HeroController = Cast<AHeroController>(GetController()))
		{
			FHitResult HitResult;
			
			if (HeroController->GetHitResultUnderCursorForObjects(ClickObjectsQuery,true,HitResult))
			{
				if (const ANodeBase* NodeBase = Cast<ANodeBase>(HitResult.GetActor()))
				{
					if (!GetCapsuleComponent()->IsOverlappingActor(NodeBase))
					{
						const float Distance = FVector::Distance(GetActorLocation(),HitResult.Location);
						if (Distance <= AcceptDistance)
						{
							TArray<AActor*> OverlapActors;
							NodeBase->BoxCollider->GetOverlappingActors(OverlapActors,AEnemyCharacter::StaticClass());
							if (!OverlapActors.IsEmpty())
							{
								if (const AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(OverlapActors[0]))
								{
									if (!NodeBase->BoxCollider->IsOverlappingActor(EnemyCharacter))
									{
										NodeLocation = HitResult.Location;
										bIsMoving = true;
										//bCanClickNode = false;
										bCanTeleport = NodeBase->bIsTeleport;
										if (OnPlayerMoved.IsBound())
										{
											OnPlayerMoved.Broadcast();
										}
									}
								}
							}
							else
							{
								NodeLocation = HitResult.Location;
								bIsMoving = true;
								//bCanClickNode = false;
								bCanTeleport = NodeBase->bIsTeleport;
								if (OnPlayerMoved.IsBound())
								{
									OnPlayerMoved.Broadcast();
								}
							}
							
						}
					}
				}
			}
		}
	}
}

void AHeroCharacter::MovePlayerToNodeLocation()
{
	if (bIsMoving)
	{
		if (AHeroController* HeroController = Cast<AHeroController>(GetController()))
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(HeroController,NodeLocation);
		}
	}
}

void AHeroCharacter::InsertMappingContext()
{
	if (const AHeroController* HeroController = Cast<AHeroController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(HeroController->GetLocalPlayer()))
		{
			if (HeroMappingContext)
			{
				EnhancedInputSubsystem->AddMappingContext(HeroMappingContext,0);
			}
		}
	}
}

bool AHeroCharacter::CanPlayerShoot() const
{
	return PistolAmmo > 0 && bIsAlive && bCanShoot;
}

void AHeroCharacter::ResetPlayerMovment()
{
	bCanClickNode = true;
}

void AHeroCharacter::AddOffsetToPlayer(float DeltaTime)
{
	if (bIsMoving)
	{
		const FVector OffsetLocation = UKismetMathLibrary::VInterpTo(GetActorLocation(),NodeLocation,DeltaTime,MoveSpeed);
		SetActorLocation(OffsetLocation,false,nullptr);
		
	}
}

