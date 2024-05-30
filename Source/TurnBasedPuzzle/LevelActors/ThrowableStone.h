#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ThrowableStone.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class TURNBASEDPUZZLE_API AThrowableStone : public AActor
{
	GENERATED_BODY()
public:	
	AThrowableStone();
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Throwable Stone")
	TObjectPtr<UStaticMeshComponent> StoneMesh;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Throwable Stone")
	TObjectPtr<USphereComponent> SphereCollider;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Throwable Stone")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComp;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Throwable Stone")
	TObjectPtr<USoundBase> Cue_Impact;
	

public:
	UFUNCTION(BlueprintCallable,Category="Throwable")
	void ThrowStone(AActor* Actor , FVector InVelocity);

	UFUNCTION()
	void OnSphereColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor,	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
		bool bFromSweep, const FHitResult & SweepResult);
	
};
