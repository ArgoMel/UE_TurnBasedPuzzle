#include "NodeBase.h"
#include "Components/BoxComponent.h"
#include "NiagaraComponent.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "TurnBasedPuzzle/Characters/HeroCharacter.h"
#include "TurnBasedPuzzle/Misc/TurnBasedMode.h"

ANodeBase::ANodeBase()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);
	BaseMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxCollider->SetBoxExtent(FVector(1.0f, 1.0f, 70.0f));
	BoxCollider->SetupAttachment(BaseMesh);

	NodeCollider = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Node Collider"));
	NodeCollider->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn,ECollisionResponse::ECR_Ignore);
	NodeCollider->SetupAttachment(BaseMesh);
	NodeCollider->SetGenerateOverlapEvents(true);

	DecoFinishMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Deco Finish Mesh"));
	DecoFinishMesh->SetupAttachment(BaseMesh);
	DecoFinishMesh->SetVisibility(false);

	Panel1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Panel1"));
	Panel1->SetupAttachment(BaseMesh);
	Panel1->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Panel1->SetVisibility(false);

	Panel2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Panel2"));
	Panel2->SetupAttachment(BaseMesh);
	Panel2->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Panel2->SetVisibility(false);

	Panel3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Panel3"));
	Panel3->SetupAttachment(BaseMesh);
	Panel3->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Panel3->SetVisibility(false);

	Panel4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Panel4"));
	Panel4->SetupAttachment(BaseMesh);
	Panel4->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Panel4->SetVisibility(false);

	FX_Teleport = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Teleport VFX"));
	FX_Teleport->SetVisibility(false);
	FX_Teleport->SetupAttachment(BaseMesh);
}

void ANodeBase::BeginPlay()
{
	Super::BeginPlay();
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &ANodeBase::OnBoxColliderBeginOverlap);
}

void ANodeBase::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	Panel1->SetVisibility(bShowPanel1);
	Panel2->SetVisibility(bShowPanel2);
	Panel3->SetVisibility(bShowPanel3);
	Panel4->SetVisibility(bShowPanel4);
	DecoFinishMesh->SetVisibility(bShowDecoMesh);
	FX_Teleport->SetVisibility(bShowFX_Teleport);
}

void ANodeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANodeBase::OnBoxColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
	bool bFromSweep, const FHitResult& SweepResult)
{
	if (AHeroCharacter* HeroCharacter = Cast<AHeroCharacter>(OtherActor))
	{
		HeroCharacter->bIsMoving = false;
		if (bIsEndNode&&
			VictoryWidget)
		{
			CreateWidget<UUserWidget>(GetWorld(), VictoryWidget)->AddToViewport(0);
			if (ATurnBasedMode* TurnBasedMode = 
				Cast<ATurnBasedMode>(UGameplayStatics::GetGameMode(GetWorld())))
			{
				TurnBasedMode->SetNextLevel(LevelName);
			}
		}
	}
}

