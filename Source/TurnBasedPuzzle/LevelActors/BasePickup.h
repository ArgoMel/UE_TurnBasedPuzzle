#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePickup.generated.h"

class URotatingMovementComponent;

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
	ABasePickup();
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Pickup")
	TObjectPtr<UStaticMeshComponent> PickupMesh;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Pickup")
	TObjectPtr<UBoxComponent> BoxCollider;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Pickup")
	TObjectPtr<URotatingMovementComponent> RotatingMovementComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
	TObjectPtr<USoundBase> Cue_Pickup;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Pickup")
	EPickupType PickupType;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Pickup")
	int32 AmmoAmount = 1;

public:
	UFUNCTION()
	void OnBoxColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor,	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
		bool bFromSweep, const FHitResult & SweepResult);
};
