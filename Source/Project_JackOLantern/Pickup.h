// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "NiagaraComponent.h"
#include "Pickup.generated.h"

UCLASS()
class PROJECT_JACKOLANTERN_API APickup : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* BoxCollider;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UAudioComponent* Sound;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UNiagaraSystem* Explosion;
	
public:	
	// Sets default values for this actor's properties
	APickup();
	void Collect();

	float rotation;
	float rotationSpeed;
	FTimerHandle Timer;
	float startTime;
	float moveSpeed;
	FVector startLocation;
	FVector endLocation;
	bool keyFound;

protected:
	virtual void BeginPlay() override;
	void HideMesh();

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	void Print(FString message);


};
