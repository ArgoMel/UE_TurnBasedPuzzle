// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTS_IsPlayerMoving.generated.h"


UCLASS()
class TURNBASEDPUZZLE_API UBTS_IsPlayerMoving : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTS_IsPlayerMoving();

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Grux")
	FBlackboardKeySelector BB_GruxCanMove;

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
