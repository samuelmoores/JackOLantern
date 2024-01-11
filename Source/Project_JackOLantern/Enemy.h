// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "NiagaraComponent.h"
#include "Enemy.generated.h"

UCLASS()
class PROJECT_JACKOLANTERN_API AEnemy : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	USphereComponent* HitBox;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UNiagaraSystem* DeathParticles;

protected:
	// Called when the game starts or when spawned
	AEnemy();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:
	//-------------------------------------- Blueprint --------------------------------
	UPROPERTY(BlueprintReadWrite)
	bool attack;

	UPROPERTY(BlueprintReadOnly)
	bool returningToStart;
	
	UFUNCTION(BlueprintCallable)
	bool GetAttacking() {return attacking;};

	UFUNCTION(BlueprintCallable)
	void SetAttacking(bool attackingUpdate) {attacking = attackingUpdate;};

	//-----------------------------------Variables---------------------------------------------------
	class AProject_JackOLanternCharacter* Player;
	FTimerHandle Timer;
	FVector StartingPosition;
	FRotator StartingRotation;
	FVector DirectionToMovement;
	float health;
	float distanceFromPlayer;
	float distanceFromStart;
	bool playerFound;
	bool attacking;
	float timeStopPursue;
	float timeSinceStopPursue;
	bool playerOnFirstFloor;
	bool pursuePlayer;

	//--------------------------------Functions------------------------------------------------------
	void Print(FString message);
	void SetPlayer(AProject_JackOLanternCharacter* RespawnedPlayer);
	void Move();
	void ReturnToStart();
	void PursuePlayer();

};
