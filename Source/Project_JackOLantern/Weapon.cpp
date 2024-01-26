// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	Mesh->SetWorldScale3D(FVector(2.0f, 2.0f, 2.0f));

}

void AWeapon::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(!pickedUp)
	{
		Mesh->SetRelativeRotation(FRotator(Mesh->GetComponentRotation().Pitch, Mesh->GetComponentRotation().Yaw + (DeltaSeconds * 100.0f), Mesh->GetComponentRotation().Roll));
	
	}
	else
	{
		Mesh->SetWorldScale3D(FVector::One());

	}
}

void AWeapon::Attack()
{
}

