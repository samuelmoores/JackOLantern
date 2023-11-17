// Fill out your copyright notice in the Description page of Project Settings.


#include "Throwable.h"
#include "Components/SphereComponent.h"
#include "Engine/World.h"


// Sets default values
AThrowable::AThrowable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create and attach a sphere collision component
	ThrowableCollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("BallCollisionComponent"));
	ThrowableCollisionComponent->OnComponentHit.AddDynamic(this, &AThrowable::OnHit);
	isThrown = false;
	ThrowableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ThrowableMesh"));;
	RootComponent = ThrowableCollisionComponent;
	ThrowableMesh->SetupAttachment(ThrowableCollisionComponent);
	ThrowableCollisionComponent->SetCollisionProfileName(TEXT("BlockAll"));
	ThrowableCollisionComponent->SetSimulatePhysics(true);
	ThrowableCollisionComponent->SetNotifyRigidBodyCollision(true);
	ThrowableMesh->SetSimulatePhysics(false);
	ThrowableMesh->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	
	
}
void AThrowable::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if(isThrown)
	{
		// Destroy the ball
		Destroy();

		// Spawn fragmented ball pieces at the location of the collision
		for (auto mesh : meshArray)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			GetWorld()->SpawnActor<AActor>(mesh, Hit.Location, FRotator::ZeroRotator, SpawnParams);
		}
	}
}

// Called when the game starts or when spawned
void AThrowable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AThrowable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

