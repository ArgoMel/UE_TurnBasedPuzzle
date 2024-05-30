#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TurnBasedMode.generated.h"

UCLASS()
class TURNBASEDPUZZLE_API ATurnBasedMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	ATurnBasedMode();
protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Turn Based Mode")
	TSubclassOf<UUserWidget> GameOverWidget;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turn Based Mode")
	TObjectPtr<UUserWidget> GameOverScreen;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Turn Based Mode")
	FName LevelToLoad;

	UPROPERTY()
	FTimerHandle TH_GameOverScreen;

public:
	UFUNCTION(BlueprintCallable,Category="Turn Based Mode")
	void SetNextLevel(FName LevelName);
	UFUNCTION(BlueprintCallable,Category="Turn Based Mode")
	void OpenNextLevel();
	UFUNCTION(BlueprintCallable,Category="Turn Based Mode")
	void RestartLevel();
	UFUNCTION(BlueprintCallable,Category="Turn Based Mode")
	void ShowGameOverScreen();

	UFUNCTION()
	void ActivateGameOverScreen();
};
