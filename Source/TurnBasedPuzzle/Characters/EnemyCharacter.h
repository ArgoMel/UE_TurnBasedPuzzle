#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TurnBasedPuzzle/LevelActors/PatrolPath.h"
#include "EnemyCharacter.generated.h"

class UPawnSensingComponent;
class UBoxComponent;

UENUM()
enum class EEnemyType
{
	EET_None		 UMETA(DisplayName = "None"),
	EET_Khiamera	 UMETA(DisplayName = "Khiamera"),
	EET_Revenant	 UMETA(DisplayName = "Revenant"),
	EET_Grux		 UMETA(DisplayName = "Grux")
	
};
UCLASS()
class TURNBASEDPUZZLE_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	AEnemyCharacter();
protected:
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
public:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Enemy")
	TObjectPtr<UPawnSensingComponent> PawnSensingComp;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Enemy")
	TObjectPtr<UBoxComponent> AttackCollider;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Enemy|Stats")
	bool bIsAlive = true;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Enemy|Stats")
	bool bIsMoving = false;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Enemy|Stats") // for revenant
	bool bCanShoot = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Enemy|Montage")
	TObjectPtr<UAnimMontage> Montage_Attack;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Enemy|Sound FX")
	TObjectPtr<USoundBase> Cue_AttackSound;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Enemy|Sound FX")
	TObjectPtr<USoundBase> Cue_PistolShoot;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Enemy|Socket")
	FName SocketName;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Enemy|Stats")
	EEnemyType EnemyType;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Enemy|Khiamera") // for Khiamera
	FName BB_CanSeePlayer = TEXT("CanSeePlayer");
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Enemy|Khiamera")// for Khiamera
	FName BB_PlayerLocation = TEXT("PlayerLocation");

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Enemy|Grux")// for Grux
	TObjectPtr<APatrolPath> PatrolPath;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Enemy|Grux") // for Grux
	FName BB_GruxCanSeePlayer = TEXT("GruxCanSeePlayer");
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Enemy|Grux") // for Grux
	FName BB_GPlayerLocation = TEXT("GPlayerLocation");	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Enemy|Grux")// for Grux
	FName BB_GruxCanMove = TEXT("GruxCanMove");
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Enemy|Grux")// for Grux
	FName BB_GruxHearNoise = TEXT("GruxHearNoise");
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Enemy|Grux")// for Grux
	FName  BB_NoiseLocation = TEXT("NoiseLocation");
	
public:
	UFUNCTION(BlueprintCallable,Category="Enemy")
	void EnemyKilled();
	UFUNCTION(BlueprintCallable,Category="Enemy")
	void AttackPlayer();

	/// ------ Revenant -------/////
	UFUNCTION(BlueprintCallable,Category="Enemy")
	void Flip();
	UFUNCTION()
	void OnAttackColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	void OnSeenPawn(APawn* InPawn);
	UFUNCTION()
	void OnHearingNoise(APawn* _Instigator, const FVector& Location, float Volume);
};
