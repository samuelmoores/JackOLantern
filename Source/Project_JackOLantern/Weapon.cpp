// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add("Weapon");

}

void AWeapon::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(!pickedUp)
	{
		Mesh->SetRelativeRotation(FRotator(Mesh->GetComponentRotation().Pitch, Mesh->GetComponentRotation().Yaw + (DeltaSeconds * 100.0f), Mesh->GetComponentRotation().Roll));
	
	}
}

void AWeapon::Attack()
{
}

