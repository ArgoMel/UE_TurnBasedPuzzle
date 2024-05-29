#include "HeroAnimInstance.h"

void UHeroAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	HeroCharacter = Cast<AHeroCharacter>(TryGetPawnOwner());
}

void UHeroAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (HeroCharacter)
	{
		bIsAlive = HeroCharacter->bIsAlive;
		bIsMoving = !HeroCharacter->GetVelocity().IsZero();
	}
}
