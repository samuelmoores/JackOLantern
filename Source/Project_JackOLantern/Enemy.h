// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Project_JackOLanternCharacter.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class PROJECT_JACKOLANTERN_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

	AProject_JackOLanternCharacter* Player;

	float health;

	float distanceFromPlayer;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void Move(float DeltaTime);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Print(FString message);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
