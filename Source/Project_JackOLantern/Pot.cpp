// Fill out your copyright notice in the Description page of Project Settings.
#include "Pot.h"
#include "Enemy.h"
#include "Project_JackOLanternCharacter.h"
#include "NiagaraFunctionLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
APot::APot()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);
	
	Sound = CreateDefaultSubobject<UAudioComponent>("Sound");
}

// Called when the game starts or when spawned
void APot::BeginPlay()
{
	Super::BeginPlay();
	
	playerFound = false;
	hasBeenThrown = false;
	killedEnemy = false;

}

void APot::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if(OtherActor->ActorHasTag("Player"))
	{
		if(!Player)
		{
			Player  = Cast<AProject_JackOLanternCharacter>(OtherActor);
		}
	}
}

void APot::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

}

void APot::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved,
	FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
	hitLevel = Other->ActorHasTag("Level");
	const bool bHitEnemy = Other->ActorHasTag("Enemy"); 
	
	if((hitLevel || bHitEnemy) && !shattered && hasBeenThrown)
	{
		hasBeenThrown = false;
		if(bHitEnemy)
		{
			AEnemy* Enemy = Cast<AEnemy>(Other);
			Enemy->TakeDamage(1.0f);
			Enemy->GetCharacterMovement()->DisableMovement();
			if(Enemy->health <= 0.0f)
			{
				Enemy->dead = true;
				Enemy->GetMesh()->SetSimulatePhysics(true);
				killedEnemy = true;
			}
		}
		Shatter();
	}
}

void APot::Interact()
{
	Super::Interact();
	if(Player)
	{
		Pickup();
	}
}

void APot::Throw()
{
	hasBeenThrown = true;
	playerFound = false;

	//setup the throw
	FVector ImpulseVector = Mesh->GetComponentTransform().GetUnitAxis(EAxis::Z);
	ImpulseVector *= 800.0f;
	Player->GetMesh()->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Ignore);

	//check if you have to add players velocity to the throw so it doesn't just fucking seep out of hand if running and throwing
	if(Player->GetVelocity().Length() != 0.0f)
	{
		ImpulseVector += Player->GetVelocity()/3;
	}

	//throw the damn pot
	Mesh->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	Mesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	Mesh->SetSimulatePhysics(true);
	Mesh->AddImpulse(ImpulseVector, NAME_None, true);
	Player->isAttacking = false;
}

void APot::Pickup()
{
	if(Player->GetJackStateWeapon() != HAS_POT && Player->GetJackStateWeapon() == UNARMED)
	{
		Player->SetWeaponState(HAS_POT);
		Mesh->SetSimulatePhysics(false);
		Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Mesh->SetWorldTransform(Player->GetMesh()->GetSocketTransform("clavicle_r_SOC"));
		Mesh->AttachToComponent(Player->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale , "clavicle_r_SOC");
	}
}

void APot::Shatter()
{
	shattered = true;
	Sound->Play();
	FActorSpawnParameters spawnParams;
	Mesh->SetVisibility(false);
	Mesh->SetSimulatePhysics(false);

	if(hitLevel)
	{
		Meshes_Broken_Spawned = GetWorld()->SpawnActor<AActor>(Meshes_Broken, GetActorLocation(), GetActorRotation(), spawnParams);

		timeOfShatter = GetWorld()->TimeSeconds;
		GetWorldTimerManager().SetTimer(Timer, this, &APot::UnShatter, GetWorld()->DeltaTimeSeconds, true);
	}
	else
	{

		Meshes_Broken_Spawned_ShatterOnly = GetWorld()->SpawnActor<AActor>(Meshes_Broken_ShatterOnly, GetActorLocation(), GetActorRotation(), spawnParams);
	}
}

void APot::UnShatter()
{
	timeSinceShatter = GetWorld()->TimeSeconds - timeOfShatter;
	if(timeSinceShatter > 10.0f)
	{
		Mesh->SetVisibility(true);
		//BoxCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		shattered = false;
		playerFound = false;
		Meshes_Broken_Spawned->Destroy();
		GetWorldTimerManager().ClearTimer(Timer);
	}
}


