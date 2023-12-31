// Fill out your copyright notice in the Description page of Project Settings.


#include "Pot.h"
#include "Project_JackOLanternCharacter.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values
APot::APot()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<UStaticMeshComponent>("Root");
	Root->SetupAttachment(RootComponent);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(Root);

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

void APot::Print(FString message)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, message, true);

}

// Called every frame
void APot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(freakout)
	{
		FVector newScale = Mesh->GetComponentScale();
		Mesh->SetWorldScale3D(newScale + FVector(0.2f, 0.2f, 0.2f));
	}

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

	if(OtherActor->ActorHasTag("Enemy") && !freakout)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),Explosion, Mesh->GetComponentLocation(),FRotator::ZeroRotator, FVector::One(), false);
		Mesh->SetSimulatePhysics(false);
		Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		freakout = true;
	}

}

void APot::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

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

