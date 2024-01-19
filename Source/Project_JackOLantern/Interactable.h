// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/AudioComponent.h"
#include "Interactable.generated.h"

UCLASS()
class PROJECT_JACKOLANTERN_API AInteractable : public AActor
{
	GENERATED_BODY()
public:
	AInteractable();
	virtual void Interact();

protected:
	//----------------------------------------------- variables-----------------------------------------------------
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* BoxCollider;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UAudioComponent* Sound;

	//----------------------------------------------functions--------------------------------------------------------------------
	void Print(FString message);

};
