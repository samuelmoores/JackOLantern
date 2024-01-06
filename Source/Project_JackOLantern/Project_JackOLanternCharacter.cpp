// Copyright Epic Games, Inc. All Rights Reserved.

#include "Project_JackOLanternCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Pot.h"
#include "Throwable.h"
#include "DSP/AudioDebuggingUtilities.h"
#include "Kismet/GameplayStatics.h"

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

	//Set Particle System
	static ConstructorHelpers::FObjectFinder<UParticleSystem> SparksFinder(TEXT("/Game/StarterContent/Particles/P_Explosion"));
	if(SparksFinder.Succeeded())
	{
		HitParticles = SparksFinder.Object;
	}

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
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

void AProject_JackOLanternCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Movement
	runSpeed = 500.0f;
	sprintSpeed = 700.0f;
	crouchSpeed = 75.0f;
	isSprinting = false;
	isCrouching = false;
	isDodging = false;

	//Attacking
	isAttacking = false;
	isReloading = false;
	isShooting = false;
	isAiming = false;
	hasGun = false;
	hasPistol = false;
	hasRifle = false;
	selectedWeapon = 0;
	hasPot = false;

	//States
	PlayerStateMovement = IDLE;
	PlayerStateAttacking = NOTATTACKING;
	PlayerStateWeapon = UNARMED;
	
	
	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AProject_JackOLanternCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(GetCharacterMovement()->Velocity.IsZero())
	{
		SetIdleState();
	}

	 /*switch (PlayerStateMovement)
	 {
	 case IDLE:
	 	Print("idle");
	 	break;
	 case RUNNING:
	 	Print("run");
	 	break;
	 case JUMPING:
	 	Print("jump");
	 	break;
	 case SPRINTING:
	 	Print("sprint");
	 	break;
	 case CROUCHING:
	 	Print("crouch");
	 	break;
	 case DODGING:
	 	Print("dodge");
	 	break;
	 default:
	 	Print("no state");
	 }*/

	/*switch(PlayerStateAttacking)
	{
	case MELEE:
		Print("Melee");
		break;
	case AIMING_PISTOL:
		Print("Aiming Pistol");
		break;
	case RELOADING_PISTOL:
		Print("Reloading Pistol");
		break;
	case SHOOOTING_PISTOL:
		Print("Shooting Pistol");
		break;
	case NOTATTACKING:
		Print("Not Attacking");
		break;
	default:
		Print("no attack state");
	}*/

	/*switch(PlayerStateWeapon)
	{
	case HAS_PISTOL:
		Print("Has Pistol");
		break;
	case HAS_RIFLE:
		Print("Has Rifle");
		break;
	case HAS_MELEEWEAPON:
		Print("Has Melee Weapon");
		break;
	default:
		Print("no weapon state");
	}*/
	
}

void AProject_JackOLanternCharacter::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if(OtherActor->ActorHasTag("Pot"))
	{
		Pot = Cast<APot>(OtherActor);
	}
}

void AProject_JackOLanternCharacter::Print(FString message)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, message, true);
}

void AProject_JackOLanternCharacter::SetState()
{
	float velMag = GetCharacterMovement()->Velocity.Length();
	
	if(GetCharacterMovement()->Velocity.IsZero())
	{
		PlayerStateMovement = IDLE;
	}
	else if(velMag > crouchSpeed && velMag < sprintSpeed)
	{
		PlayerStateMovement = RUNNING;
	}
	else if(GetCharacterMovement()->IsFalling())
	{
		PlayerStateMovement = JUMPING;
	}
	else if(isSprinting)
	{
		PlayerStateMovement = SPRINTING;
	}
	else if(isCrouching)
	{
		PlayerStateMovement = CROUCHING;
	}
	else if(isDodging)
	{
		PlayerStateMovement = DODGING;
	}
}

void AProject_JackOLanternCharacter::SetIdleState()
{
	if(isCrouching)
	{
		PlayerStateMovement = CROUCHING;
		if(isDodging)
		{
			PlayerStateMovement = DODGING;
		}
	}
	else if(isDodging)
	{
		PlayerStateMovement = DODGING;
	}
	else if(isAttacking)
	{
	}
	else
	{
		PlayerStateMovement = IDLE;
	}
	
}

void AProject_JackOLanternCharacter::SetMoveState()
{
	if(!isSprinting && !isCrouching)
	{
		if(GetCharacterMovement()->IsFalling())
		{
			PlayerStateMovement = JUMPING;
		}
		else if(isDodging)
		{
			PlayerStateMovement = DODGING;
		}
		else if(isAttacking)
		{
		}
		else
		{
			PlayerStateMovement = RUNNING;
		}
	}
	else if(isDodging)
	{
		PlayerStateMovement = DODGING;
	}
	else if(isAttacking)
	{
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

		//Sprinting
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &AProject_JackOLanternCharacter::SprintStart);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AProject_JackOLanternCharacter::SprintStop);

		//Crouching
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Started, this, &AProject_JackOLanternCharacter::CrouchStart);
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed, this, &AProject_JackOLanternCharacter::CrouchStop);

		//Dodging
		EnhancedInputComponent->BindAction(DodgeAction, ETriggerEvent::Started, this, &AProject_JackOLanternCharacter::Dodge);

		//Attacking
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &AProject_JackOLanternCharacter::Attack);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Completed, this, &AProject_JackOLanternCharacter::EndAttack);

		//Crouching
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Started, this, &AProject_JackOLanternCharacter::AimStart);
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Completed, this, &AProject_JackOLanternCharacter::AimStop);

		//Changing Weapon
		EnhancedInputComponent->BindAction(ChangeWeaponAction, ETriggerEvent::Started, this, &AProject_JackOLanternCharacter::ChangeWeapon);

		//Shooting
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started, this, &AProject_JackOLanternCharacter::ShootStart);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Completed, this, &AProject_JackOLanternCharacter::ShootStop);

		//Reloading
		EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Started, this, &AProject_JackOLanternCharacter::ReloadStart);

		//Interacting
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AProject_JackOLanternCharacter::InteractStart);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Completed, this, &AProject_JackOLanternCharacter::InteractStop);

		
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

	SetMoveState();
	
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

void AProject_JackOLanternCharacter::Jump()
{
	Super::Jump();
	PlayerStateMovement = JUMPING;
	PlayerStateAttacking = NOTATTACKING;
	GetCharacterMovement()->MaxWalkSpeed = runSpeed;
	isCrouching = false;
	isSprinting = false;
	isDodging = false;
	isAiming = false;
}

void AProject_JackOLanternCharacter::SprintStart(const FInputActionValue& Value)
{
	if(!isCrouching && !GetCharacterMovement()->IsFalling() && PlayerStateMovement == RUNNING)
	{
		PlayerStateMovement = SPRINTING;
		isSprinting = true;
		GetCharacterMovement()->MaxWalkSpeed = sprintSpeed;
	}
}

void AProject_JackOLanternCharacter::SprintStop(const FInputActionValue& Value)
{
	if(!isCrouching && !GetCharacterMovement()->IsFalling() && isSprinting)
	{
		isSprinting = false;
		GetCharacterMovement()->MaxWalkSpeed = runSpeed;
		PlayerStateMovement = IDLE;
	}
}

void AProject_JackOLanternCharacter::CrouchStart(const FInputActionValue& Value)
{
	if(!isSprinting && !GetCharacterMovement()->IsFalling() && !isReloading)
	{
		PlayerStateMovement = CROUCHING;
		isCrouching = true;
		GetCharacterMovement()->MaxWalkSpeed = crouchSpeed;
	}
}

void AProject_JackOLanternCharacter::CrouchStop(const FInputActionValue& Value)
{
	if(!isSprinting && !GetCharacterMovement()->IsFalling())
	{
		isCrouching = false;
		GetCharacterMovement()->MaxWalkSpeed = runSpeed;
		PlayerStateMovement = IDLE;
	}
}

void AProject_JackOLanternCharacter::Dodge(const FInputActionValue& Value)
{
	isDodging = true;
}

void AProject_JackOLanternCharacter::Attack(const FInputActionValue& Value)
{
	if(hasPot)
	{
		isAttacking = true;
		PlayerStateAttacking = MELEE;
	}
}

void AProject_JackOLanternCharacter::AimStart(const FInputActionValue& Value)
{
	if(hasGun)
	{
		if(!isShooting && !isReloading && !isDodging)
		{
			if(hasPistol)
			{
				isAiming = true;
				PlayerStateAttacking = AIMING_PISTOL;
			}
			else if(hasRifle)
			{
				isAiming = true;
				PlayerStateAttacking = AIMING_RIFLE;
			}
		}
	}
}

void AProject_JackOLanternCharacter::AimStop(const FInputActionValue& Value)
{
	if(hasGun && isAiming)
	{
		isAiming = false;
		PlayerStateAttacking = NOTATTACKING;
	}

}

void AProject_JackOLanternCharacter::ChangeWeapon(const FInputActionValue& Value)
{
	switch(selectedWeapon)
	{
	case 0:
		PlayerStateWeapon = UNARMED;
	case 1:
		PlayerStateWeapon = HAS_MELEEWEAPON;
		break;
	case 2:
		//PlayerStateWeapon = HAS_PISTOL;
		break;
	case 3:
		//PlayerStateWeapon = HAS_RIFLE;
		break;
	default:
		PlayerStateWeapon = UNARMED;
	}
}

void AProject_JackOLanternCharacter::ShootStart(const FInputActionValue& Value)
{
	if(isAiming && !isShooting)
	{
		isShooting = true;
		FHitResult Hit;
		FVector Start =  GetFollowCamera()->GetComponentLocation();
		FVector End = Start + GetFollowCamera()->GetForwardVector() * 10000;
		bool hit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_WorldDynamic, FCollisionQueryParams::DefaultQueryParam, FCollisionResponseParams::DefaultResponseParam);
		if(hit)
		{
			FTransform SpawnTransform(Hit.ImpactNormal.Rotation(), Hit.ImpactPoint);
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticles, SpawnTransform);
		}
		else
		{
			Print("Not hit");
		}
	}
}

void AProject_JackOLanternCharacter::ReloadStart(const FInputActionValue& Value)
{
	if(hasGun && !isReloading)
	{
		if(hasPistol)
		{
			isReloading = true;
			PlayerStateAttacking = RELOADING_PISTOL;
			
		}
		else if(hasRifle)
		{
			isReloading = true;
			PlayerStateAttacking = RELOADING_PISTOL;
			
		}
	}
}

void AProject_JackOLanternCharacter::InteractStart(const FInputActionValue& Value)
{
	isInteracting = true;
}

void AProject_JackOLanternCharacter::InteractStop(const FInputActionValue& Value)
{
	isInteracting = false;
}

void AProject_JackOLanternCharacter::ShootStop()
{
	isShooting = false;

	if(isAiming)
	{
		PlayerStateAttacking = AIMING_PISTOL;
	}
	else
	{
		PlayerStateAttacking = NOTATTACKING;
	}
}

void AProject_JackOLanternCharacter::ReloadStop()
{
	isReloading = false;
	PlayerStateAttacking = NOTATTACKING;
}

void AProject_JackOLanternCharacter::ThrowPot()
{
	if(Pot && isAttacking)
	{
		Pot->Throw();
	}
}

void AProject_JackOLanternCharacter::EndThrowPot()
{
	hasPot = false;
	PlayerStateAttacking = NOTATTACKING;

}

void AProject_JackOLanternCharacter::EndDodge()
{
	isDodging = false;
	if(isCrouching)
	{
		PlayerStateMovement = CROUCHING;
	}
	else if(isSprinting)
	{
		PlayerStateMovement = SPRINTING;
	}
	else
	{
		PlayerStateMovement = IDLE;
	}
}

void AProject_JackOLanternCharacter::EndAttack(const FInputActionValue& Value)
{
}

