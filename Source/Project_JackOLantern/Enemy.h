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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attacking, meta = (AllowPrivateAccess = "true"))
	USphereComponent* HitBox;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attacking, meta = (AllowPrivateAccess = "true"))
	UNiagaraSystem* DeathParticles;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool AI_controlled;

protected:
	// Called when the game starts or when spawned
	AEnemy();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

public:
	//-------------------------------------- Blueprint Variables --------------------------------
	UPROPERTY(BlueprintReadWrite)
	bool doDamage;

	UPROPERTY(BlueprintReadWrite)
	bool damaged;

	UPROPERTY(BlueprintReadWrite)
	bool damagedAnimPlaying;

	UPROPERTY(BlueprintReadOnly)
	bool returningToStart;

	UPROPERTY(BlueprintReadWrite)
	bool dead;

	//-------------------------------------- Blueprint Functions --------------------------------
	UFUNCTION(BlueprintCallable)
	bool GetAttacking() {return attacking;};

	UFUNCTION(BlueprintCallable)
	void SetAttacking(bool attackingUpdate) {attacking = attackingUpdate; if(attacking){Print("attacking");}};

	UFUNCTION(BlueprintCallable)
	void DoDamage(float damageAmount);

	//-----------------------------------Variables---------------------------------------------------
	class AProject_JackOLanternCharacter* Player;
	FTimerHandle Timer;
	FVector StartingPosition;
	FRotator StartingRotation;
	FVector DirectionToMovement;
	
	float health;
	float distanceFromPlayer;
	float distanceFromStart;
	float timeStopPursue;
	float timeSinceStopPursue;
	
	bool playerFound;
	bool attacking;
	bool playerOnFirstFloor;
	bool pursuePlayer;
	bool playerOverlapped;

	//--------------------------------Functions------------------------------------------------------
	void Print(FString message);
	void SetPlayer(AProject_JackOLanternCharacter* RespawnedPlayer);
	void Move();
	void ReturnToStart();
	void PursuePlayer();
	void Damage(float damageAmount);
	void LocatePlayer();

};
