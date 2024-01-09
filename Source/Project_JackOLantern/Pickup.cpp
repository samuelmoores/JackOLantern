// Fill out your copyright notice in the Description page of Project Settings.

#include "Pickup.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "Components/AudioComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/BoxComponent.h"

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
	rotation = 1.0f;
	rotationSpeed = 100.0f;
	moveSpeed = 1.0f;

	startLocation = GetActorLocation();
	endLocation = GetActorLocation() + FVector(0.0f, 0.0f, 125.0f);

	keyFound = false;
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	rotation += DeltaTime;
	
	SetActorRelativeRotation(FRotator(GetActorRotation().Pitch, GetActorRotation().Yaw + (DeltaTime * rotationSpeed), GetActorRotation().Roll));

}

void APickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	
}

void APickup::Collect()
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Explosion, Mesh->GetComponentLocation(), Mesh->GetComponentRotation(), FVector::One(), true);
	BoxCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	keyFound = true;
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
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Explosion, Mesh->GetComponentLocation(), Mesh->GetComponentRotation(), FVector::One(), true);
		Mesh->SetVisibility(false);
		GetWorldTimerManager().ClearTimer(Timer);
	}

	if(GetActorLocation().Z < endLocation.Z)
	{
		SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z+ moveSpeed));
	}
	
}

void APickup::Print(FString message)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, message, true);
}


