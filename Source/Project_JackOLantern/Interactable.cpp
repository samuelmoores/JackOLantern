// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable.h"
#include "Components/BoxComponent.h"
#include "Components/AudioComponent.h"


// Sets default values
AInteractable::AInteractable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);
	
	BoxCollider = CreateDefaultSubobject<UBoxComponent>("BoxCollider");
	BoxCollider->SetupAttachment(Mesh);

	Sound = CreateDefaultSubobject<UAudioComponent>("Sound");

}

void AInteractable::Print(FString message)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, message, true);
}

void AInteractable::Interact()
{
}

