#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HeroCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerDeath);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerMoved);

class UInputMappingContext;
class UInputAction;
class ANodeBase;
class AThrowableStone;

UCLASS()
class TURNBASEDPUZZLE_API AHeroCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	AHeroCharacter();
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY()
	FTimerHandle TH_ResetPlayerMovment;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Hero|Component")
	TObjectPtr<UPawnNoiseEmitterComponent> PawnNoiseEmitterComp;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Hero|Input")
	TObjectPtr<UInputMappingContext> HeroMappingContext;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Hero|Input")
	TObjectPtr<UInputAction> ActionMove;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Hero|Input")
	TObjectPtr<UInputAction> ActionFire;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Hero|Input")
	TObjectPtr<UInputAction> ActionTeleport;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Hero|Input")
	TObjectPtr<UInputAction> ActionThrowStone;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero|Ability")
	int32 PistolAmmo = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero|Ability")
	float AcceptDistance = 400.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hero|Ability")
	float MoveSpeed = 2.0f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Hero|Ability")
	bool bIsAlive = true;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Hero|Ability")
	bool bIsMoving = false;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Hero|Ability")
	bool bCanClickNode = false;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Hero|Ability")
	bool bCanShoot = false;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Hero|Ability")
	bool bCanThrowStone = false;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Hero|Ability")
	bool bCanTeleport = false;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Hero|Locations")
	FVector NodeLocation;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Hero|Locations")
	FVector StoneLocation;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Hero|Node")
	TObjectPtr<ANodeBase> TargetNode;

	UPROPERTY(BlueprintReadOnly,Category="Hero|Stone")
	TObjectPtr<AThrowableStone> StoneInstance;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Hero|Montage")
	TObjectPtr<UAnimMontage> Montage_Fire;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Hero|Montage")
	TObjectPtr<UAnimMontage> Montage_Intro;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Hero|Trace Object Types")
	TArray<TEnumAsByte<EObjectTypeQuery>> ShootObjectsQuery;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Hero|Trace Object Types")
	TArray<TEnumAsByte<EObjectTypeQuery>> StoneObjectsQuery;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Hero|Trace Object Types")
	TArray<TEnumAsByte<EObjectTypeQuery>> ClickObjectsQuery;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Hero|Sound FX")
	TObjectPtr<USoundBase> Cue_Teleport;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Hero|Sound FX")
	TObjectPtr<USoundBase> Cue_PistolShoot;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Hero|Sound FX")
	TObjectPtr<USoundBase> Cue_DeathSound;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Hero|VFX")
	TObjectPtr<UParticleSystem> FX_Pistol;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Hero|VFX")
	TObjectPtr<UParticleSystem> FX_Teleport;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Hero|Projectile")
	TSubclassOf<AThrowableStone> StoneClass;

	UPROPERTY(BlueprintAssignable,Category="Hero")
	FOnPlayerDeath OnPlayerDeath;
	UPROPERTY(BlueprintAssignable,Category="Hero")
	FOnPlayerMoved OnPlayerMoved;

public:
	UFUNCTION(BlueprintCallable,Category="Hero")
	void SpawnStone();
	UFUNCTION(BlueprintCallable,Category="Hero")
	void ReportNoise();
	UFUNCTION(BlueprintCallable,Category="Hero")
	void PlayerKilled();
	UFUNCTION(BlueprintCallable,Category="Hero")
	void PistolShoot();
	UFUNCTION(BlueprintCallable,Category="Hero")
	void ThrowStone();
	UFUNCTION(BlueprintCallable,Category="Hero")
	void TeleportPlayer();
	UFUNCTION(BlueprintCallable,Category="Hero")
	void StartClickNode();
	UFUNCTION(BlueprintCallable,Category="Hero")
	void MovePlayerToNodeLocation();	
	UFUNCTION(BlueprintCallable,Category="Hero")
	void InsertMappingContext();
	UFUNCTION(BlueprintCallable,BlueprintPure,Category="Hero")
	bool CanPlayerShoot()const;
	UFUNCTION(BlueprintCallable,Category="Hero")
	void ResetPlayerMovment();
	UFUNCTION(BlueprintCallable,Category="Hero")
	void AddOffsetToPlayer(float DeltaTime);
};
