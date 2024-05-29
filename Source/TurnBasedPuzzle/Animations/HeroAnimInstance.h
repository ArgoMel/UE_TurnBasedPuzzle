#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "TurnBasedPuzzle/Characters/HeroCharacter.h"
#include "HeroAnimInstance.generated.h"

UCLASS()
class TURNBASEDPUZZLE_API UHeroAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Hero")
	bool bIsAlive = true;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Hero")
	bool bIsMoving = false;

	UPROPERTY()
	TObjectPtr<AHeroCharacter> HeroCharacter ;
	
};
