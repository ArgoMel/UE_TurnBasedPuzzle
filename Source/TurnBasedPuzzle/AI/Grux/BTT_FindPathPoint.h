#pragma once
#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_FindPathPoint.generated.h"

UCLASS()
class TURNBASEDPUZZLE_API UBTT_FindPathPoint : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTT_FindPathPoint();
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Grux")
	FBlackboardKeySelector BB_PatrolIndex;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Grux")
	FBlackboardKeySelector BB_PathLocation;
};
