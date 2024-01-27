// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Project_JackOLanternCharacter.h" 
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	distanceFromPlayer = 0.0f;
	health = 1.0f;
	damaged = false;

	returningToStart = false;
	playerOnFirstFloor = true;
	pursuePlayer = false;

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	StartingPosition = GetActorLocation();
	StartingRotation = GetActorRotation();
	dead = false;

	//Don't chase the player until they go near the ghost
	playerFound = false;

	//set the reference so the enemy can find the player
	Player = Cast<AProject_JackOLanternCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if(!dead && !AI_controlled)
	{
		LocatePlayer();

		if(!damaged && !attacking && !Player->isDead && playerOnFirstFloor && !Player->underTable)
		{
			PursuePlayer();
		}
		else if(pursuePlayer && !attacking )
		{
			pursuePlayer = false;
			timeStopPursue = GetWorld()->GetTimeSeconds();
			GetWorldTimerManager().SetTimer(Timer, this, &AEnemy::ReturnToStart, GetWorld()->DeltaTimeSeconds, true);
		}
	}
}

void AEnemy::LocatePlayer()
{
	distanceFromPlayer = FVector::Distance(GetActorLocation(), Player->GetActorLocation());
	distanceFromStart = FVector::Distance(GetActorLocation(), StartingPosition);

	if(Player->GetActorLocation().Z > 1000.0f)
	{
		playerOnFirstFloor = false;
	}
	else
	{
		playerOnFirstFloor = true;
	}
}

void AEnemy::PursuePlayer()
{
	pursuePlayer = true;
	returningToStart = false;

	// --------------------------------------------- Ghost Movement ---------------------------------------------------------------
	if(isGhost)
	{
		//don't start chasing player until the player is near the ghost for the first time
		if(distanceFromPlayer < 1350.0f && !playerFound)
		{
			playerFound = true;
		}

		//once the player is near the ghost, don't stop chasing the player
		//make sure the ghost if facing the player while it attacks
		if(distanceFromPlayer < 400.0f && playerFound)
		{
			GetCharacterMovement()->DisableMovement();
			DirectionToMovement = Player->GetActorLocation() - GetActorLocation();
			DirectionToMovement.Normalize();
			FVector MovementVector = DirectionToMovement ;
			FRotator TargetRotation = MovementVector.ToOrientationRotator();
			FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), TargetRotation, GetWorld()->DeltaTimeSeconds, 3.0f);
			SetActorRotation(NewRotation);
		}
		else if(playerFound)
		{
			GetCharacterMovement()->SetMovementMode(MOVE_Walking);
			Move();
		}
	}
	else //------------------------------ Regular Zombie Movement ---------------------------------------------------------------
	{
		if(distanceFromPlayer < 90.0f)
		{
			attacking = true;
		}
		else
		{
			attacking = false;
			Move();
		}
	}
	
}

void AEnemy::ReturnToStart()
{
	timeSinceStopPursue = GetWorld()->GetTimeSeconds() - timeStopPursue;

	if(timeSinceStopPursue > 3.0f )
	{
		returningToStart = true;

		Move();
		
		if(distanceFromStart < 10.0f)
		{
			GetWorldTimerManager().ClearTimer(Timer);
			SetActorRotation(StartingRotation);
		}
		if(!Player->isDead && playerOnFirstFloor) //if player goes up stairs stop chasing
		{
			GetWorldTimerManager().ClearTimer(Timer);
		}
	}
}

void AEnemy::Move()
{
	if(!returningToStart)
	{
		DirectionToMovement = Player->GetActorLocation() - GetActorLocation();
	}
	else
	{
		DirectionToMovement = StartingPosition - GetActorLocation();
	}
	
	DirectionToMovement.Normalize();

	FVector MovementVector = DirectionToMovement ;
	
	FRotator TargetRotation = MovementVector.ToOrientationRotator();

	FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), TargetRotation, GetWorld()->DeltaTimeSeconds, 3.0f);
	
	SetActorRotation(NewRotation);

	GetCharacterMovement()->AddInputVector(MovementVector);
	
}

float AEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	if(!dead)
	{
		attacking = false;
		wasPunched = true;
		health -= DamageAmount;
		damaged = true;
		wasPunched = true;
		if(health <= 0.0f)
		{
			dead = true;
			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}
	return DamageAmount;
}

void AEnemy::SetPlayer(AProject_JackOLanternCharacter* RespawnedPlayer)
{
	Player = RespawnedPlayer;
}

void AEnemy::Print(FString message)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, message, true);
}




