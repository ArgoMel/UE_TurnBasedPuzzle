#include "TurnBasedMode.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "TurnBasedPuzzle/Characters/HeroCharacter.h"

ATurnBasedMode::ATurnBasedMode()
{
	
}

void ATurnBasedMode::BeginPlay()
{
	Super::BeginPlay();
	GameOverScreen = CreateWidget(GetWorld(),GameOverWidget);
	GameOverScreen->AddToViewport(0);
	GameOverScreen->SetVisibility(ESlateVisibility::Hidden);
	AHeroCharacter* HeroCharacter =
		Cast<AHeroCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (HeroCharacter)
	{
		HeroCharacter->OnPlayerDeath.AddDynamic(this,&ATurnBasedMode::ActivateGameOverScreen);
	}
}


void ATurnBasedMode::SetNextLevel(FName LevelName)
{
	LevelToLoad = LevelName;
}

void ATurnBasedMode::OpenNextLevel()
{
	if (!LevelToLoad.IsNone())
	{
		UGameplayStatics::OpenLevel(GetWorld(),LevelToLoad,true);
	}
}

void ATurnBasedMode::RestartLevel()
{
	const FName CurrentLevel = *UGameplayStatics::GetCurrentLevelName(GetWorld(),true);
	UGameplayStatics::OpenLevel(GetWorld(),CurrentLevel,true);
}

void ATurnBasedMode::ShowGameOverScreen()
{
	if (GameOverScreen)
	{
		GameOverScreen->SetVisibility(ESlateVisibility::Visible);
	}
}

void ATurnBasedMode::ActivateGameOverScreen()
{
	if (!GetWorldTimerManager().IsTimerActive(TH_GameOverScreen))
	{
		GetWorldTimerManager().SetTimer(
			TH_GameOverScreen,this,&ATurnBasedMode::ShowGameOverScreen,1.0f,false,2.0f);
	}
}

