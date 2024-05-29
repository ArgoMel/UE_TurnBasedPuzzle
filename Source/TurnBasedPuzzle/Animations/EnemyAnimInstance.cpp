#include "EnemyAnimInstance.h"

void UEnemyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	EnemyCharacter = Cast<AEnemyCharacter>(TryGetPawnOwner());
}

void UEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (EnemyCharacter)
	{
		bIsAlive = EnemyCharacter->bIsAlive;
		bIsMoving = !EnemyCharacter->GetVelocity().IsZero();
		bCanShoot = EnemyCharacter->bCanShoot;
	}
}
