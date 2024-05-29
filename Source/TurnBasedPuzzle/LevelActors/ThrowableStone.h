// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ThrowableStone.generated.h"

UCLASS()
class TURNBASEDPUZZLE_API AThrowableStone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AThrowableStone();

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Throwable Stone")
	UStaticMeshComponent* StoneMesh;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Throwable Stone")
	class USphereComponent* SphereCollider;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Throwable Stone")
	class UProjectileMovementComponent* ProjectileMovementComp;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Throwable Stone")
	USoundBase* Cue_Impact;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable,Category="Throwable")
	void ThrowStone(AActor* Actor , FVector InVelocity);

	UFUNCTION()
	void OnSphereColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
};
