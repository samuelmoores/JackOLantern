// Fill out your copyright notice in the Description page of Project Settings.
#include "Pot.h"
#include "Project_JackOLanternCharacter.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values
APot::APot()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);

	BoxCollider = CreateDefaultSubobject<UBoxComponent>("BoxCollider");
	BoxCollider->SetupAttachment(Mesh);

}

// Called when the game starts or when spawned
void APot::BeginPlay()
{
	Super::BeginPlay();

	playerFound = false;
	BoxCollider->AttachToComponent(Mesh, FAttachmentTransformRules::KeepRelativeTransform);
	hasBeenThrown = false;

}

// Called every frame
void APot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APot::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if(OtherActor->ActorHasTag("Player") && !freakout)
	{
		Player  = Cast<AProject_JackOLanternCharacter>(OtherActor);
		
		if(!Player->hasPot && OtherActor->ActorHasTag("Player"))
		{
			Mesh->SetSimulatePhysics(false);
			playerFound = true;
			Player->hasPot = true;
			Mesh->SetWorldTransform(Player->GetMesh()->GetSocketTransform("clavicle_r_SOC"));
			Mesh->AttachToComponent(Player->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale , "clavicle_r_SOC");
		}
	}

	if(OtherActor->ActorHasTag("Enemy"))
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),Explosion, Mesh->GetComponentLocation(),FRotator::ZeroRotator, FVector::One(), true);
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
	if(Other->ActorHasTag("Level") && !shattered)
	{
		Shatter();
	}
}

void APot::Throw()
{
	Mesh->SetSimulatePhysics(true);
	playerFound = false;
	Mesh->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);

	FVector ImpulseVector = Player->GetActorForwardVector();

	ImpulseVector *= 200.0f;

	if(Player->GetVelocity().Length() != 0.0f)
	{
		ImpulseVector += Player->GetVelocity()/3;
	}
	
	Mesh->AddImpulse(ImpulseVector, NAME_None, true);
	Player->isAttacking = false;

}

void APot::Shatter()
{
	shattered = true;
	FActorSpawnParameters spawnParams;
	Mesh->SetVisibility(false);
	BoxCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Meshes_Broken_Spawned = GetWorld()->SpawnActor<AActor>(Meshes_Broken, GetActorLocation(), GetActorRotation(), spawnParams);
	Destroy();
}

void APot::Print(FString message)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, message, true);

}


