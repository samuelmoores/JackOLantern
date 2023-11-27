// Copyright Epic Games, Inc. All Rights Reserved.

#include "Project_JackOLanternCharacter.h"

#include "Door.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Throwable.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AProject_JackOLanternCharacter

AProject_JackOLanternCharacter::AProject_JackOLanternCharacter() 
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	Door = nullptr;
}

void AProject_JackOLanternCharacter::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if(OtherActor->IsA(ADoor::StaticClass()))
	{
		Door = Cast<ADoor>(OtherActor);
	}
}

void AProject_JackOLanternCharacter::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
	if(Door)
	{
		Door = nullptr;
	}
}

float AProject_JackOLanternCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
                                                 AController* EventInstigator, AActor* DamageCauser)
{
	health -= DamageAmount;

	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void AProject_JackOLanternCharacter::Throw()
{
	FActorSpawnParameters spawnParams;
	spawnParams.Owner = this;
	spawnParams.Instigator = GetInstigator();
	
	FVector Start = GetActorLocation() + GetActorForwardVector()* 100.0f;
	FVector End = Start;
	FCollisionQueryParams Params;
	FCollisionObjectQueryParams ObjectParams;
	ObjectParams.AddObjectTypesToQuery(ECollisionChannel::ECC_GameTraceChannel1);
	Params.AddIgnoredActor(this);
    FHitResult Hit;
	bool bhit = GetWorld()->SweepSingleByChannel(Hit,Start,End,FQuat::Identity, ECC_Visibility,FCollisionShape::MakeSphere(200.0f),Params);
	AActor* HitActor = Hit.GetActor();

	// if(throwable)
	// {
	// 	DrawDebugSphere(GetWorld(), Start, 200.0f, 32, FColor::Green, false, 1.0, 0, 1.0);
	//
	// 	FVector Location(0.0f, 0.0f, 0.0f);
	// 	FRotator Rotation(0.0f, 0.0f, 0.0f);
	// 	FActorSpawnParameters SpawnInfo;
	// 	GetWorld()->SpawnActor<AThrowable>(throwable, GetActorLocation() + GetActorForwardVector() * 200.0f, GetActorRotation(), SpawnInfo);
	//
	// }

	if(bhit)
	{
		if(HitActor != nullptr && HitActor->IsA(AThrowable::StaticClass()))
		{
			
			AActor* Spawned = GetWorld()->SpawnActor<AActor>(HitActor->GetClass(), GetActorLocation() + GetActorForwardVector()*200, GetActorRotation(), spawnParams);
			HitActor->Destroy();
			UPrimitiveComponent* spawnedPrimitive = Cast<UPrimitiveComponent>(Spawned->GetRootComponent());
			if (Spawned)
			{
				AThrowable* ThrowableActor = Cast<AThrowable>(Spawned);
				if(ThrowableActor)
				{
					ThrowableActor->isThrown = true;
				}
				if (spawnedPrimitive)
				{
					
					FVector ThrowDirection = GetActorForwardVector();
					float ThrowStrength = 90000.0f;
					spawnedPrimitive->AddImpulse(ThrowDirection * ThrowStrength);
				}
			}
		}
	}
	
	
}

void AProject_JackOLanternCharacter::AddCandy()
{
	numCandy++;
}

int AProject_JackOLanternCharacter::GetCandy()
{
	return numCandy;
}

void AProject_JackOLanternCharacter::startInteracting()
{
	if(Door)
	{
		Door->Open();
	}
}

void AProject_JackOLanternCharacter::stopInteracting()
{
	interacting = false;
}

void AProject_JackOLanternCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	health = 1.0f;
	numCandy = 0;

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void AProject_JackOLanternCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AProject_JackOLanternCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AProject_JackOLanternCharacter::Look);

		//Throwing
		EnhancedInputComponent->BindAction(ThrowAction, ETriggerEvent::Started, this, &AProject_JackOLanternCharacter::Throw);

		//Interacting
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AProject_JackOLanternCharacter::startInteracting);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Completed, this, &AProject_JackOLanternCharacter::stopInteracting);

		//Another New Event

		
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AProject_JackOLanternCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AProject_JackOLanternCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}



