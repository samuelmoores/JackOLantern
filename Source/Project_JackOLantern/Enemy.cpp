// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Project_JackOLanternCharacter.h" 
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
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	//if player respawns get a new ref
	if(!Player)
	{
		Player = Cast<AProject_JackOLanternCharacter>( UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	}

	
	if(Player && !dead && !AI_controlled)
	{
		LocatePlayer();

		if(!damaged && !Player->isDead && playerOnFirstFloor && !Player->underTable)
		{
			PursuePlayer();
		}
		else if(pursuePlayer )
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

	if(Player->GetActorLocation().Z > 300.0f)
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
	
	if(distanceFromPlayer < 90.0f)
	{
	}
	else
	{
		Move();
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
		if(!Player->isDead && playerOnFirstFloor)
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

void AEnemy::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

}

void AEnemy::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
	
}

float AEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	if(!dead)
	{
		wasPunched = true;
		health -= DamageAmount;
		damaged = true;
		wasPunched = true;
		if(health <= 0.0f)
		{
			dead = true;
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




