// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_FindPathPoint.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "TurnBasedPuzzle/AI/EnemyController.h"
#include "TurnBasedPuzzle/Characters/EnemyCharacter.h"

UBTT_FindPathPoint::UBTT_FindPathPoint()
{
	NodeName = TEXT("Find Patrol Path Point");
}

EBTNodeResult::Type UBTT_FindPathPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (AEnemyController* EnemyController = Cast<AEnemyController>(OwnerComp.GetAIOwner()))
	{
		if (const AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn()))
		{
			if (EnemyCharacter->PatrolPath != nullptr)
			{
				const int32 Index = EnemyController->GetBlackboardComponent()->GetValueAsInt(BB_PatrolIndex.SelectedKeyName);
				const FVector PathLocation = UKismetMathLibrary::TransformLocation(EnemyCharacter->PatrolPath->GetActorTransform(),
					EnemyCharacter->PatrolPath->PathPoints[Index]);
				EnemyController->GetBlackboardComponent()->SetValueAsVector(BB_PathLocation.SelectedKeyName,PathLocation);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
