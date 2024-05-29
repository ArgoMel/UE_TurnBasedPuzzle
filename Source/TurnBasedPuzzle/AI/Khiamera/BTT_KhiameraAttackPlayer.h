// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_KhiameraAttackPlayer.generated.h"


UCLASS()
class TURNBASEDPUZZLE_API UBTT_KhiameraAttackPlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTT_KhiameraAttackPlayer();
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Khiamera")
	FBlackboardKeySelector BB_CanSeePlayer;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
