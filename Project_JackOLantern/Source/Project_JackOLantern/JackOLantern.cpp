// Fill out your copyright notice in the Description page of Project Settings.


#include "JackOLantern.h"

// Sets default values
AJackOLantern::AJackOLantern()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AJackOLantern::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AJackOLantern::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UStaticMeshComponent* AJackOLantern::GetMesh()
{
	return Mesh;
}

