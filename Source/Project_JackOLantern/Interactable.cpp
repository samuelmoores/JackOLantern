// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"



// Sets default values
AInteractable::AInteractable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	


}

void AInteractable::Print(FString message)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, message, true);
}

void AInteractable::Interact()
{
}

