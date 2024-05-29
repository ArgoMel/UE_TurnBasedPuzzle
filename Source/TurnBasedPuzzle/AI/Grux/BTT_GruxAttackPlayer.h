// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_GruxAttackPlayer.generated.h"

UCLASS()
class TURNBASEDPUZZLE_API UBTT_GruxAttackPlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTT_GruxAttackPlayer();

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Grux")
	FBlackboardKeySelector BB_GruxCanSeePlayer;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
