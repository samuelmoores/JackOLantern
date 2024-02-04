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
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* BoxCollider;
	
	bool isOpen;
	bool playerFound;
	float openStartTime;
	float rotateSpeed;
	FTimerHandle Timer;
	AProject_JackOLanternCharacter* player;
	
public:	
	// Sets default values for this actor's properties
	ADoor();
	
	UFUNCTION(BlueprintCallable)
	void Open();

	void Rotate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:	
	virtual void Interact() override;

};
