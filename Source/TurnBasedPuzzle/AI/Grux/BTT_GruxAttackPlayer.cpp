#include "BTT_GruxAttackPlayer.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TurnBasedPuzzle/AI/EnemyController.h"
#include "TurnBasedPuzzle/Characters/EnemyCharacter.h"
#include "TurnBasedPuzzle/Characters/HeroCharacter.h"

UBTT_GruxAttackPlayer::UBTT_GruxAttackPlayer()
{
	NodeName = TEXT("Grux Attack Player");
}

EBTNodeResult::Type UBTT_GruxAttackPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (const AHeroCharacter* HeroCharacter = Cast<AHeroCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0)))
	{
		if (HeroCharacter->bIsAlive)
		{
			if (AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn()))
			{
				if (AEnemyController* EnemyController = Cast<AEnemyController>(OwnerComp.GetAIOwner()))
				{
					EnemyCharacter->AttackPlayer();
					EnemyController->GetBlackboardComponent()->SetValueAsBool(BB_GruxCanSeePlayer.SelectedKeyName,false);
					return EBTNodeResult::Succeeded;
				}
			}
		}
	}
	return EBTNodeResult::Failed;
}
