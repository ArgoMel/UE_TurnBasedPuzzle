// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "BasePickup.generated.h"

UENUM()
enum class EPickupType
{
	EPT_Stone	UMETA(DisplayName = "Stone"),
	EPT_Pistol	UMETA(DisplayName = "Pistol")
};
UCLASS()
class TURNBASEDPUZZLE_API ABasePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasePickup();

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Pickup")
	UStaticMeshComponent* PickupMesh;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Pickup")
	class UBoxComponent* BoxCollider;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Pickup")
	class URotatingMovementComponent* RotatingMovementComp;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Pickup")
	EPickupType PickupType;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Pickup")
	int32 AmmoAmount = 1;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Pickup")
	USoundBase* Cue_Pickup;
	
	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	void OnBoxColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};
