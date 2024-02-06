// Fill out your copyright notice in the Description page of Project Settings.

#include "Pickup.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);
	
	BoxCollider = CreateDefaultSubobject<UBoxComponent>("BoxCollider");
	BoxCollider->SetupAttachment(Mesh);

	Sound = CreateDefaultSubobject<UAudioComponent>("Sound");
	
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	pickedUp = false;

	rotation = 1.0f;
	rotationSpeed = 100.0f;
	moveSpeed = 1.0f;

	startLocation = GetActorLocation();
	endLocation = GetActorLocation() + FVector(0.0f, 0.0f, 125.0f);

}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Mesh->SetRelativeRotation(FRotator(Mesh->GetComponentRotation().Pitch, Mesh->GetComponentRotation().Yaw + (DeltaTime * rotationSpeed), Mesh->GetComponentRotation().Roll));
	
}

void APickup::Interact_With_Pickup()
{
	Mesh->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), InteractParticles, Mesh->GetComponentLocation(), Mesh->GetComponentRotation(), FVector::One(), true);
	Sound->Play();
	startTime = GetWorld()->GetTimeSeconds();
	GetWorldTimerManager().SetTimer(Timer, this, &APickup::HideMesh, GetWorld()->GetDeltaSeconds(), true);
}

void APickup::HideMesh()
{
	float elapsedTime = GetWorld()->GetTimeSeconds() - startTime;

	rotationSpeed += 10.0f;

	if(elapsedTime < 0.05)
	{
		if( moveSpeed > 0.0f)
		{
			moveSpeed += 1.0f;
			moveSpeed *= -1;
		}
		else
		{
			moveSpeed -= 1.0f;
		}
	}
	else
	{
		moveSpeed += 1.0f;
	}

	if(Mesh && elapsedTime > 2.0f)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), InteractParticles, Mesh->GetComponentLocation(), Mesh->GetComponentRotation(), FVector::One(), true);
		GetWorldTimerManager().ClearTimer(Timer);
		Mesh->SetVisibility(false);
	}

	if(Mesh->GetComponentLocation().Z < endLocation.Z)
	{
		Mesh->SetWorldLocation(FVector(Mesh->GetComponentLocation().X, Mesh->GetComponentLocation().Y, Mesh->GetComponentLocation().Z+ moveSpeed));
	}
	
}

