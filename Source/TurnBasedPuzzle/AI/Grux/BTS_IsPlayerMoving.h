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
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Grux")
	FBlackboardKeySelector BB_GruxCanMove;
};
