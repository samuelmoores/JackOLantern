// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "GameFramework/Character.h"
#include "Project_JackOLanternCharacter.h"
#include "Components/BoxComponent.h"

#include "Pot.generated.h"

UCLASS()
class PROJECT_JACKOLANTERN_API APot : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* BoxCollider;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UNiagaraSystem* Explosion;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> Meshes_Broken;

public:
	// Sets default values for this character's properties
	AProject_JackOLanternCharacter* Player;
	UStaticMeshComponent* GetMesh() {return Mesh;}
	FVector OriginalLoc;
	FTimerHandle Timer;
	AActor* Meshes_Broken_Spawned;
	bool playerFound;
	bool hasBeenThrown;
	bool freakout;
	bool shattered;
	float timeOfShatter;
	float timeSinceShatter;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void Print(FString message);

public:	
	APot();
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
	virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
	void Throw();
	void Shatter();

};
