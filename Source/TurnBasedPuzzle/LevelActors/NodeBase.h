#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NodeBase.generated.h"

class UNiagaraComponent;

UCLASS()
class TURNBASEDPUZZLE_API ANodeBase : public AActor
{
	GENERATED_BODY()
public:	
	ANodeBase();
protected:
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Node Base")
	TObjectPtr<UBoxComponent> BoxCollider;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Node Base")
	TObjectPtr<UStaticMeshComponent> BaseMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Node Base")
	TObjectPtr<UStaticMeshComponent> DecoFinishMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Node Base")
	TObjectPtr<UStaticMeshComponent> NodeCollider;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Node Base")
	TObjectPtr<UStaticMeshComponent> Panel1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Node Base")
	TObjectPtr<UStaticMeshComponent> Panel2;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Node Base")
	TObjectPtr<UStaticMeshComponent> Panel3;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Node Base")
	TObjectPtr<UStaticMeshComponent> Panel4;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Node Base")
	TObjectPtr<UNiagaraComponent> FX_Teleport;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node Base")
	TSubclassOf<UUserWidget> VictoryWidget;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Node Base")
	TObjectPtr<ANodeBase> TeleportNode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node Base")
	FName LevelName;
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
 	
public:
	UFUNCTION()
	void OnBoxColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
		bool bFromSweep, const FHitResult & SweepResult);
};
