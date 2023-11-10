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
	openStartTime = 0.0f;
	rotateSpeed = 50.0f;
}

void ADoor::Open()
{
	if(!isOpen)
	{
		openStartTime = GetWorld()->GetTimeSeconds();
		GetWorldTimerManager().SetTimer(Timer,this, &ADoor::Rotate, GetWorld()->GetDeltaSeconds()/rotateSpeed, true);
	}
}

void ADoor::Rotate()
{
	float elapsedTime = GetWorld()->GetTimeSeconds() - openStartTime;
	if(GetActorRotation().Yaw > -90.0f)
	{
		SetActorRelativeRotation(FRotator(0.0f, elapsedTime*(-1) * rotateSpeed, 0.0f));
	}
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

