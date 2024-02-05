// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "Interactable.h"
#include "Project_JackOLanternCharacter.h"

#include "Pot.generated.h"

UCLASS()
class PROJECT_JACKOLANTERN_API APot : public AInteractable
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UAudioComponent* Sound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UNiagaraSystem* Explosion;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> Meshes_Broken;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> Meshes_Broken_ShatterOnly;

public:
	// Sets default values for this character's properties
	AProject_JackOLanternCharacter* Player;
	FVector OriginalLoc;
	FTimerHandle Timer;
	AActor* Meshes_Broken_Spawned;
	AActor* Meshes_Broken_Spawned_ShatterOnly;

	bool playerFound;
	bool hasBeenThrown;
	bool freakout;
	bool shattered;
	float timeOfShatter;
	float timeSinceShatter;
	bool killedEnemy;
	bool hitLevel;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	APot();
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
	virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
	virtual void Interact() override;
	
	UFUNCTION(BlueprintCallable)
	void Throw();
	
	void Pickup();
	void Shatter();
	void UnShatter();

};
