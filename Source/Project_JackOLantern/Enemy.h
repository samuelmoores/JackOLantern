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

public:
	class AProject_JackOLanternCharacter* Player;
	float health;
	float distanceFromPlayer;
	UAnimationAsset* Animator;

	//-------------------------------------- BlueprintVariables --------------------------------
	UPROPERTY(BlueprintReadWrite)
	bool canAttack;

	UPROPERTY(BlueprintReadWrite)
	bool attack;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void Move(float DeltaTime);

public:
	AEnemy();
	virtual void Tick(float DeltaTime) override;
	void Print(FString message);
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	void SetPlayer(AProject_JackOLanternCharacter* RespawnedPlayer);
};
