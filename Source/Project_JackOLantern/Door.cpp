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

	isOpen = false;
	playerFound = false;
	openStartTime = 0.0f;
	rotateSpeed = 100.0f;
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
	if(Mesh->GetComponentRotation().Yaw <= 0.0f && Mesh->GetComponentRotation().Yaw > -125)
	{
		float newYaw = Mesh->GetComponentRotation().Yaw - GetWorld()->DeltaTimeSeconds*(rotateSpeed);
		Mesh->SetWorldRotation(FRotator(0.0f, newYaw, 0.0f));
	}
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADoor::Interact()
{
	
}


