// Fill out your copyright notice in the Description page of Project Settings.

#include "Pickup.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);

	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>("ParticleSystem");
	ParticleSystem->SetupAttachment(RootComponent);

	Sound = CreateDefaultSubobject<UAudioComponent>("Sound");
	ParticleSystem->SetupAttachment(Mesh);

}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	rotation = 0.0f;
	rotationSpeed = 75.0f;
	moveSpeed = 50.0f;

	startLocation = GetActorLocation();
	endLocation = GetActorLocation() + FVector(0.0f, 0.0f, 100.0f);

	keyFound = false;
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	rotation += DeltaTime;
	SetActorRelativeRotation(FRotator(0.0f, rotation * rotationSpeed, 0.0f));

}

void APickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if(OtherActor->ActorHasTag("Player") && !keyFound)
	{
		keyFound = true;
		ParticleSystem->Activate();
		rotationSpeed = 1000.0f;
		Sound->Play();
		startTime = GetWorld()->GetTimeSeconds();
		GetWorldTimerManager().SetTimer(Timer, this, &APickup::HideMesh, GetWorld()->GetDeltaSeconds(), true);
	}
	
}

void APickup::HideMesh()
{
	float elapsedTime = GetWorld()->GetTimeSeconds() - startTime;

	// Check if the Mesh is valid before attempting to hide it
	if(Mesh && elapsedTime > 2.0f)
	{
		ParticleSystem->Deactivate();
		ParticleSystem->Activate();
		Mesh->SetVisibility(false);
		GetWorldTimerManager().ClearTimer(Timer);
		
	}
	else
	{
		float Alpha = FMath::Clamp(elapsedTime, 0.0f, 2.0f);
		Mesh->SetWorldLocation(FMath::Lerp(startLocation, endLocation, Alpha));
	}
}

void APickup::Print(FString message)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, message, true);
}


