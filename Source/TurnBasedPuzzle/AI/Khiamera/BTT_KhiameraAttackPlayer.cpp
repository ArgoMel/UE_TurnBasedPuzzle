#include "BTT_KhiameraAttackPlayer.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TurnBasedPuzzle/AI/EnemyController.h"
#include "TurnBasedPuzzle/Characters/EnemyCharacter.h"

UBTT_KhiameraAttackPlayer::UBTT_KhiameraAttackPlayer()
{
	NodeName = TEXT("Khiamera Attack Player");
}

EBTNodeResult::Type UBTT_KhiameraAttackPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn()))
	{
		EnemyCharacter->AttackPlayer();
		if (AEnemyController* EnemyController = Cast<AEnemyController>(OwnerComp.GetAIOwner()))
		{
			EnemyController->GetBlackboardComponent()->SetValueAsBool(BB_CanSeePlayer.SelectedKeyName,false);
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
