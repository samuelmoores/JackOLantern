// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

UCLASS()
class PROJECT_JACKOLANTERN_API APickup : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* ParticleSystem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;
	
public:	
	// Sets default values for this actor's properties
	APickup();

	float rotation;
	float rotationSpeed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
