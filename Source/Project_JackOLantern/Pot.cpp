// Fill out your copyright notice in the Description page of Project Settings.
#include "Pot.h"
#include "Enemy.h"
#include "Project_JackOLanternCharacter.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values
APot::APot()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


}

// Called when the game starts or when spawned
void APot::BeginPlay()
{
	Super::BeginPlay();

	playerFound = false;
	BoxCollider->AttachToComponent(Mesh, FAttachmentTransformRules::KeepRelativeTransform);
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
	const bool bHitLevel = Other->ActorHasTag("Level");
	const bool bHitEnemy = Other->ActorHasTag("Enemy"); 
	
	if((bHitLevel || bHitEnemy) && !shattered && hasBeenThrown)
	{
		hasBeenThrown = false;
		if(bHitEnemy)
		{
			AEnemy* Enemy = Cast<AEnemy>(Other);
			Enemy->dead = true;
			killedEnemy = true;
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
	Mesh->SetSimulatePhysics(true);
	playerFound = false;
	Mesh->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);

	FVector ImpulseVector = Mesh->GetComponentTransform().GetUnitAxis(EAxis::Z);
	
	ImpulseVector *= 400.0f;

	if(Player->GetVelocity().Length() != 0.0f)
	{
		ImpulseVector += Player->GetVelocity()/3;
	}
	
	Mesh->AddImpulse(ImpulseVector, NAME_None, true);
	Player->isAttacking = false;
}

void APot::Pickup()
{
	if(Player->GetJackStateWeapon() != HAS_POT)
	{
		Print("Pot Pickup");
		Player->SetWeaponState(HAS_POT);
		Mesh->SetSimulatePhysics(false);
		Mesh->SetWorldTransform(Player->GetMesh()->GetSocketTransform("clavicle_r_SOC"));
		Mesh->AttachToComponent(Player->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale , "clavicle_r_SOC");
	}
}

void APot::Shatter()
{
	shattered = true;
	FActorSpawnParameters spawnParams;
	Mesh->SetVisibility(false);
	BoxCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetSimulatePhysics(false);

	if(!killedEnemy)
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
	if(timeSinceShatter > 3.0f)
	{
		Mesh->SetVisibility(true);
		BoxCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		shattered = false;
		playerFound = false;
		Meshes_Broken_Spawned->Destroy();
		GetWorldTimerManager().ClearTimer(Timer);
	}
}


