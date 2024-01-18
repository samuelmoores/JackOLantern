// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Pot.h"
#include "Project_JackOLanternCharacter.h" 
#include "NiagaraFunctionLibrary.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HitBox = CreateDefaultSubobject<USphereComponent>("HitBox");
	HitBox->SetupAttachment(GetMesh(), "index_l_02");

	distanceFromPlayer = 0.0f;
	health = 1.0f;
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

	if(Player && !dead && !AI_controlled)
	{
		LocatePlayer();

		if(!Player->isDead && playerOnFirstFloor && !Player->underTable)
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
		health -= DamageAmount;
		if(health <= 0.0f)
		{
			dead = true;
			GetCharacterMovement()->DisableMovement();
			GetCapsuleComponent()->SetCollisionEnabled((ECollisionEnabled::NoCollision));
		}
	}
	return DamageAmount;
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

void AEnemy::SetPlayer(AProject_JackOLanternCharacter* RespawnedPlayer)
{
	Player = RespawnedPlayer;
}

void AEnemy::Print(FString message)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, message, true);
}




