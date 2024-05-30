#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_IncrementIndex.generated.h"

UCLASS()
class TURNBASEDPUZZLE_API UBTT_IncrementIndex : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTT_IncrementIndex();
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Grux")
	FBlackboardKeySelector BB_PatrolIndex;
};
