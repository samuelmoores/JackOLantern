// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include  "Interactable.h"
#include "GameFramework/Actor.h"
#include "Project_JackOLanternCharacter.h"
#include "Door.generated.h"

class UBoxComponent;

UCLASS()
class PROJECT_JACKOLANTERN_API ADoor : public AInteractable
{
	GENERATED_BODY()
	
	bool isOpen;
	bool playerFound;
	float openStartTime;
	float rotateSpeed;
	FTimerHandle Timer;
	AProject_JackOLanternCharacter* player;
	
public:	
	// Sets default values for this actor's properties
	ADoor();
	
	void Open();
	void Rotate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Interact() override;


};
