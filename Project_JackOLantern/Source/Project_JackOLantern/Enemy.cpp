// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

#include "Kismet/GameplayStatics.h"
#include "Project_JackOLanternCharacter.h"
#include "Engine/DamageEvents.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<AProject_JackOLanternCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	distanceFromPlayer = 0.0f;
	health = 1.0f;
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	distanceFromPlayer = FVector::Distance(GetActorLocation(), Player->GetActorLocation());
	FDamageEvent damg;

	if(distanceFromPlayer < 90.0f)
	{
		Player->TakeDamage(0.001f, damg, Player->GetController(), this);
	}

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	health -= 0.01f;
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

