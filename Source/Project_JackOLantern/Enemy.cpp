// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

#include "Kismet/GameplayStatics.h"
#include "Project_JackOLanternCharacter.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/CharacterMovementComponent.h"

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

void AEnemy::Move(float DeltaTime)
{
	FVector DirectionToPlayer = Player->GetActorLocation() - GetActorLocation();
	DirectionToPlayer.Normalize();

	FVector MovementVector = DirectionToPlayer ;

	FRotator NewRotation = MovementVector.ToOrientationRotator();
	SetActorRotation(NewRotation);

	GetCharacterMovement()->AddInputVector(MovementVector);
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	distanceFromPlayer = FVector::Distance(GetActorLocation(), Player->GetActorLocation());
	FDamageEvent damg;


	if(distanceFromPlayer < 90.0f)
	{
	}
	else
	{
		Move(DeltaTime);
	}
}

void AEnemy::Print(FString message)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, message, true);
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


