#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PatrolPath.generated.h"

UCLASS()
class TURNBASEDPUZZLE_API APatrolPath : public AActor
{
	GENERATED_BODY()
public:	
	APatrolPath();
	UPROPERTY(EditInstanceOnly,BlueprintReadWrite,Category="Path Points",meta=(MakeEditWidget))
	TArray<FVector> PathPoints;

};
