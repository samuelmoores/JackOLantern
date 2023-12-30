// Fill out your copyright notice in the Description page of Project Settings.

#include "Pickup.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"

#include "Project_JackOLanternCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);
	
	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>("ParticleSystem");
	ParticleSystem->SetupAttachment(Mesh);

}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	rotation = 0.0f;
	rotationSpeed = 75.0f;

	ParticleSystem->Deactivate();
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	rotation += DeltaTime;
	SetActorRelativeRotation(FRotator(0.0f, rotation * 75.0f, 0.0f));

}

void APickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if(OtherActor->ActorHasTag("Player"))
	{
		ParticleSystem->Activate();
		Mesh->SetVisibility(false);
	}
	
}

