// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Project_JackOLanternCharacter.h" 
#include "NiagaraFunctionLibrary.h"
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
	attacking = false;
	attack = false;
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
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(Player)
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

		if(!Player->isDead && playerOnFirstFloor )
		{
			PursuePlayer();
		}
		else 
		{
			if(pursuePlayer)
			{
				pursuePlayer = false;
				timeStopPursue = GetWorld()->GetTimeSeconds();
				GetWorldTimerManager().SetTimer(Timer, this, &AEnemy::ReturnToStart, GetWorld()->DeltaTimeSeconds, true);
			}
		}
	}
}

void AEnemy::PursuePlayer()
{
	pursuePlayer = true;
	returningToStart = false;
	
	if(distanceFromPlayer < 90.0f)
	{
		attacking = true;
	}
	else
	{
		if(!attacking)
		{
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

	float NewRotationYaw = MovementVector.ToOrientationRotator().Yaw;
	SetActorRotation(FRotator(0.0f, NewRotationYaw, 0.0f));

	GetCharacterMovement()->AddInputVector(MovementVector);
	
}

void AEnemy::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if(OtherActor->ActorHasTag("Player") && attack)
	{
		if(Player)
		{
			Player->health -= 0.10f;
			if(Player->health <= 0.0f)
			{
				Player->Death();
				attacking = false;
				UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), DeathParticles, GetMesh()->GetComponentLocation(), GetMesh()->GetComponentRotation(), FVector::One(), true);

			}
		}
	}
}

void AEnemy::SetPlayer(AProject_JackOLanternCharacter* RespawnedPlayer)
{
	Player = RespawnedPlayer;
}

void AEnemy::Print(FString message)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, message, true);
}




