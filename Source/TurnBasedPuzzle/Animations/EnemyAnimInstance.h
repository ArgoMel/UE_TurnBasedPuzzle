#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "TurnBasedPuzzle/Characters/EnemyCharacter.h"
#include "EnemyAnimInstance.generated.h"

UCLASS()
class TURNBASEDPUZZLE_API UEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Enemy")
	bool bIsAlive = true;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Enemy")
	bool bIsMoving = false;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Enemy")
	bool bCanShoot = false;

	UPROPERTY()
	TObjectPtr<AEnemyCharacter> EnemyCharacter;
};
