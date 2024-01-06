// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Project_JackOLanternCharacter.h"
#include "Components/BoxComponent.h"
#include "NiagaraComponent.h"
#include "Pot.generated.h"

UCLASS()
class PROJECT_JACKOLANTERN_API APot : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Root;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* BoxCollider;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UNiagaraSystem* Explosion;	

public:
	// Sets default values for this character's properties
	APot();
	AProject_JackOLanternCharacter* Player;

	UStaticMeshComponent* GetMesh() {return Mesh;}

	FVector OriginalLoc;

	bool playerFound;
	bool hasBeenThrown;
	bool freakout;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Print(FString message);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
	
	void Throw();

};
