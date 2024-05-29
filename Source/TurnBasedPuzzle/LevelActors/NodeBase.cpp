// Fill out your copyright notice in the Description page of Project Settings.


#include "NodeBase.h"
#include "Components/BoxComponent.h"
#include "NiagaraComponent.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "TurnBasedPuzzle/Characters/HeroCharacter.h"
#include "TurnBasedPuzzle/Misc/TurnBasedMode.h"

// Sets default values
ANodeBase::ANodeBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	NodeCollider = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Node Collider"));
	NodeCollider->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn,ECollisionResponse::ECR_Ignore);
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);
	BoxCollider->SetBoxExtent(FVector(1.0f,1.0f,70.0f));
	BoxCollider->SetupAttachment(BaseMesh);
	NodeCollider->SetupAttachment(BaseMesh);
	DecoFinishMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Deco Finish Mesh"));
	DecoFinishMesh->SetupAttachment(BaseMesh);
	Panel1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Panel 1 Mesh"));
	Panel1->SetupAttachment(BaseMesh);
	Panel2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Panel 2 Mesh"));
	Panel2->SetupAttachment(BaseMesh);
	Panel3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Panel 3 Mesh"));
	Panel3->SetupAttachment(BaseMesh);
	Panel4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Panel 4 Mesh"));
	Panel4->SetupAttachment(BaseMesh);
	FX_Teleport = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Teleport VFX"));
	FX_Teleport->SetVisibility(false);
	FX_Teleport->SetupAttachment(BaseMesh);
	BaseMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Panel1->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Panel2->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Panel3->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Panel4->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	NodeCollider->SetGenerateOverlapEvents(true);
	Panel1->SetVisibility(false);
	Panel2->SetVisibility(false);
	Panel3->SetVisibility(false);
	Panel4->SetVisibility(false);
	DecoFinishMesh->SetVisibility(false);
}

// Called when the game starts or when spawned
void ANodeBase::BeginPlay()
{
	Super::BeginPlay();
	
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

// Called every frame
void ANodeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this,&ANodeBase::OnBoxColliderBeginOverlap);
}

void ANodeBase::OnBoxColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AHeroCharacter* HeroCharacter = Cast<AHeroCharacter>(OtherActor))
	{
		HeroCharacter->bIsMoving = false;
		if (bIsEndNode)
		{
			if (VictoryWidget)
			{
				CreateWidget<UUserWidget>(GetWorld(),VictoryWidget)->AddToViewport(0);
				if (ATurnBasedMode* TurnBasedMode = Cast<ATurnBasedMode>(UGameplayStatics::GetGameMode(GetWorld())))
				{
					TurnBasedMode->SetNextLevel(LevelName);
				}
			}
			
		}
	}
}

