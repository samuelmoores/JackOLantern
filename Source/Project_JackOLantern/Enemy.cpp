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

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	distanceFromPlayer = 0.0f;
	health = 1.0f;
	canAttack = false;
	attack = false;
	
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

	if(Player)
	{
		distanceFromPlayer = FVector::Distance(GetActorLocation(), Player->GetActorLocation());
	
		if(!Player->isDead)
		{
			if(distanceFromPlayer < 90.0f)
			{
				canAttack = true;

			}
			else
			{

				if(!canAttack)
				{
					Move(DeltaTime);
				}
			}
		
		}
		else
		{
			canAttack = false;
		}
	}
}

void AEnemy::Print(FString message)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, message, true);
}

void AEnemy::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if(OtherActor->ActorHasTag("Player") && attack)
	{
		if(Player)
		{
			Player->health -= 1.0f;
			if(Player->health <= 0.0f)
			{
				Player->Death();
				canAttack = false;
				UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), DeathParticles, GetMesh()->GetComponentLocation(), GetMesh()->GetComponentRotation(), FVector::One(), true);

			}
		}
	}
}

void AEnemy::SetPlayer(AProject_JackOLanternCharacter* RespawnedPlayer)
{
	Player = RespawnedPlayer;
}



