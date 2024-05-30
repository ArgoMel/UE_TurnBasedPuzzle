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
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Grux")
	FBlackboardKeySelector BB_GruxCanSeePlayer;
};
