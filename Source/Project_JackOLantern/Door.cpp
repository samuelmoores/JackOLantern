// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "Project_JackOLanternCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxCollider->SetupAttachment(Mesh);
	

	isOpen = false;
	playerFound = false;
	openStartTime = 0.0f;
	rotateSpeed = 50.0f;
	player = nullptr;
}

void ADoor::Open()
{
	isOpen = true;
	openStartTime = GetWorld()->GetTimeSeconds(); 
	GetWorldTimerManager().SetTimer(Timer,this, &ADoor::Rotate, GetWorld()->DeltaTimeSeconds, true);
}

void ADoor::Rotate()
{
	if(Mesh->GetComponentRotation().Yaw < -85.0f && Mesh->GetComponentRotation().Yaw > -180.0f)
	{
		float newYaw = Mesh->GetComponentRotation().Yaw - 2;
		Mesh->SetWorldRotation(FRotator(0.0f, newYaw, 0.0f));
	}

	if(Mesh->GetComponentRotation().Yaw < 180.0f && Mesh->GetComponentRotation().Yaw > 120.0f)
	{
		float newYaw = Mesh->GetComponentRotation().Yaw - 2;
		Mesh->SetWorldRotation(FRotator(0.0f, newYaw, 0.0f));
	}
	
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADoor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if(OtherActor->ActorHasTag("Player"))
	{
		player = Cast<AProject_JackOLanternCharacter>(OtherActor);
		if(player)
		{
			playerFound = true;
		}
	}
}

void ADoor::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	if(playerFound)
	{
		playerFound = false;
	}
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(playerFound)
	{
		if(player)
		{
			if(player->isInteracting && !isOpen)
			{
				Open();
			}
		}
	}

}

void ADoor::Print(FString message)
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, message, true);
}

