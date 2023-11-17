// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Throwable.generated.h"

UCLASS()
class PROJECT_JACKOLANTERN_API AThrowable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AThrowable();
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Destruct")
	TArray<TSubclassOf<AActor>> meshArray;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ThrowableMesh;

	// The ball's collision component
	UPROPERTY(VisibleAnywhere)
	USphereComponent* ThrowableCollisionComponent;

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	bool isThrown;
};
