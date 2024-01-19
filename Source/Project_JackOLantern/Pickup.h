// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "NiagaraComponent.h"
#include "Pickup.generated.h"

UCLASS()
class PROJECT_JACKOLANTERN_API APickup : public AInteractable
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UNiagaraSystem* InteractParticles;
	
public:	
	// Sets default values for this actor's properties
	APickup();

	//--------------------------- variables -------------------------------------------------------------------
	bool pickedUp;

	//animations
	FTimerHandle Timer;
	FVector startLocation;
	FVector endLocation;
	float rotation;
	float rotationSpeed;
	float startTime;
	float moveSpeed;

protected:
	virtual void BeginPlay() override;
	void HideMesh();

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void Interact() override;

};
