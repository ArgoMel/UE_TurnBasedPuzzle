// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NodeBase.generated.h"

UCLASS()
class TURNBASEDPUZZLE_API ANodeBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANodeBase();
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Node Base")
	ANodeBase* TeleportNode;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Node Base")
	bool bIsTeleport = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Node Base")
	bool bIsEndNode = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Node Base")
	bool bShowPanel1 = false;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Node Base")
    bool bShowPanel2 = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Node Base")
	bool bShowPanel3 = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Node Base")
	bool bShowPanel4 = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Node Base")
	bool bShowDecoMesh = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Node Base")
	bool bShowFX_Teleport = false;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Node Base")
	class UBoxComponent* BoxCollider;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Node Base")
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Node Base")
	UStaticMeshComponent* DecoFinishMesh;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Node Base")
	UStaticMeshComponent* NodeCollider;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Node Base")
	UStaticMeshComponent* Panel1;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Node Base")
	UStaticMeshComponent* Panel2;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Node Base")
	UStaticMeshComponent* Panel3;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Node Base")
	UStaticMeshComponent* Panel4;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Node Base")
	class UNiagaraComponent* FX_Teleport;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Node Base")
	FName LevelName;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Node Base")
	TSubclassOf<UUserWidget> VictoryWidget;
 	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnBoxColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};
