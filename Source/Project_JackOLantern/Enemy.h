// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "NiagaraComponent.h"
#include "GameFramework/DefaultPawn.h"
#include "Enemy.generated.h"

UCLASS()
class PROJECT_JACKOLANTERN_API AEnemy : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attacking, meta = (AllowPrivateAccess = "true"))
	UNiagaraSystem* DeathParticles;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool AI_controlled;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool isGhost;

protected:
	// Called when the game starts or when spawned
	AEnemy();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
public:
	//-------------------------------------- Blueprint Variables --------------------------------
	UPROPERTY(BlueprintReadOnly)
	bool returningToStart;
	UPROPERTY(BlueprintReadWrite)
	bool dead;
	UPROPERTY(BlueprintReadWrite)
	bool damaged;
	UPROPERTY(BlueprintReadWrite)
	bool wasPunched;
	UPROPERTY(BlueprintReadWrite)
	bool attacking;
	
	//-------------------------------------- Blueprint Functions --------------------------------

	//-----------------------------------Variables---------------------------------------------------
	class AProject_JackOLanternCharacter* Player;
	FTimerHandle Timer;
	FVector StartingPosition;
	FRotator StartingRotation;
	FVector DirectionToMovement;

	//--------------- movement -----------------------------
	float distanceFromPlayer;
	float distanceFromStart;
	float timeStopPursue;
	float timeSinceStopPursue;
	
	bool playerFound;
	bool playerOnFirstFloor;
	bool pursuePlayer;

	//-------------- attacking -----------------------------------------
	float health;
	
	//--------------------------------Functions------------------------------------------------------
	void Print(FString message);
	void SetPlayer(AProject_JackOLanternCharacter* RespawnedPlayer);
	void Move();
	void ReturnToStart();
	void PursuePlayer();

	UFUNCTION(BlueprintCallable)
	float TakeDamage(float DamageAmount);

	void LocatePlayer();

};
