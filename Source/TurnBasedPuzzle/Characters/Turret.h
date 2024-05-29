// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Turret.generated.h"

UCLASS()
class TURNBASEDPUZZLE_API ATurret : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurret();
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Turret")
	USkeletalMeshComponent* TurretMesh;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Turret")
	USoundBase* Cue_BlastLaser;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Turret")
	float Distance = 1500.0f;

	UPROPERTY()
	FTimerHandle TH_TracePlayer;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Turret")
	TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjectQuery;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Turret")
	UAnimationAsset* Anim_Fire;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Turret")
	FName TurretSocket = FName("Muzzle_01");
	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable,Category="Turret")
	void TracePlayer();
};
