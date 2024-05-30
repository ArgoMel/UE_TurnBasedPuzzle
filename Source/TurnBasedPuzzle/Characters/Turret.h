#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Turret.generated.h"

UCLASS()
class TURNBASEDPUZZLE_API ATurret : public AActor
{
	GENERATED_BODY()
public:	
	ATurret();
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY()
	FTimerHandle TH_TracePlayer;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Turret")
	TObjectPtr<USkeletalMeshComponent> TurretMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret")
	TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjectQuery;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Turret")
	TObjectPtr<USoundBase> Cue_BlastLaser;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret")
	TObjectPtr<UAnimationAsset> Anim_Fire;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret")
	FName TurretSocket = FName("Muzzle_01");
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Turret")
	float Distance = 1500.0f;
	
public:
	UFUNCTION(BlueprintCallable,Category="Turret")
	void TracePlayer();
};
