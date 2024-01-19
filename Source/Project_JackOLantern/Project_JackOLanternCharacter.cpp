// Copyright Epic Games, Inc. All Rights Reserved.
#include "Project_JackOLanternCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Enemy.h"
#include "Project_JackOLanternGameMode.h"
#include "Weapon.h"

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
}

void AProject_JackOLanternCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	health = 1.0f;

	//-----------Movement------------------------------------------
	runSpeed = 500.0f;
	sprintSpeed = 700.0f;
	crouchSpeed = 75.0f;
	isSprinting = false;
	isCrouching = false;
	isDodging = false;
	underTable = false;

	//---------Attacking---------------------------------------------
	isDead = false;
	foundBat = false;
	selectedWeapon = 0;
	overlappingEnemy = false;

	//--------Interacting-------------------------------
	hasKey = false;
	foundDoor = false;
	
	//------------States------------------------------------
	PlayerStateMovement = IDLE;
	PlayerStateAttacking = NOTATTACKING;
	PlayerStateWeapon = UNARMED;

	//-------------Death----------------------------------
	timeOfDeath = 0.0f;
	timeSinceDeath = 0.0f;
	
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
	case PUNCHING:
		Print("Punching");
		break;
	case SWINGING_BAT:
		Print("SwingingBat");
		break;
	case THROWING_POT:
		Print("Throwing Pot");
		break;
	case NOTATTACKING:
		Print("Not Attacking");
		break;
	default:
		Print("no attack state");
	}*/

	/*
	switch(PlayerStateWeapon)
	{
	case HAS_POT:
		Print("Has Pot");
		break;
	default:
		Print("no weapon state");
	}
	*/

	/*if(isAttacking)
	{
		Print("is Attacking");
	}
	else
	{
		Print("not is Attacking");
	}*/
	
}

void AProject_JackOLanternCharacter::Print(FString message)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, message, true);
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
		
		//Changing Weapon
		EnhancedInputComponent->BindAction(ChangeWeaponAction, ETriggerEvent::Started, this, &AProject_JackOLanternCharacter::ChangeWeapon);
		
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

//-------------------------------- movement input -------------------------------------------------------------------------

void AProject_JackOLanternCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();
	
	if (Controller != nullptr && !isDead)
	{
		SetMoveState();

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
	if(!isSprinting && !GetCharacterMovement()->IsFalling())
	{
		PlayerStateMovement = CROUCHING;
		Crouch();
	}
}

void AProject_JackOLanternCharacter::CrouchStop(const FInputActionValue& Value)
{
	if(!isSprinting && !GetCharacterMovement()->IsFalling())
	{
		UnCrouch();
		PlayerStateMovement = IDLE;
		//GetCharacterMovement()->bWantsToCrouch = false;

	}
}

void AProject_JackOLanternCharacter::Dodge(const FInputActionValue& Value)
{
	isDodging = true;
}

//----------------------------------- interact input -------------------------------------------------------------------------

void AProject_JackOLanternCharacter::InteractStart(const FInputActionValue& Value)
{
	isInteracting = true;
	TArray<AActor*> OverlappedActors;
	
	GetOverlappingActors(OverlappedActors, AInteractable::StaticClass());
	
	for(int i = 0; i < OverlappedActors.Num(); i++)
	{
		AInteractable* OverlappedActor = Cast<AInteractable>(OverlappedActors[i]);
		OverlappedActor->Interact();
	}
}

void AProject_JackOLanternCharacter::InteractStop(const FInputActionValue& Value)
{
	isInteracting = false;
}

//----------------------------------- attacking input ---------------------------------------------------------------------------

void AProject_JackOLanternCharacter::Attack(const FInputActionValue& Value)
{
	if(!isAttacking && !GetCharacterMovement()->IsFalling() && !isDead)
	{
		isAttacking = true;
		
		//choose an attack animation to play
		switch(PlayerStateWeapon)
		{
		case UNARMED:
			PlayerStateAttacking = PUNCHING;
			break;
		case HAS_POT:
			PlayerStateAttacking = THROWING_POT;
			break;
		case HAS_BAT:
			PlayerStateAttacking = SWINGING_BAT;
			break;
		case HAS_PISTOL:
			break;
		case HAS_RIFLE:
			break;
		default:
			Print("No Attack State");
		}
	}
}

void AProject_JackOLanternCharacter::ChangeWeapon(const FInputActionValue& Value)
{
	//Print("Change Weapon");
	//Print(FString::SanitizeFloat(selectedWeapon));
	
	switch(selectedWeapon)
	{
	case 0:
		PlayerStateWeapon = UNARMED;
		break;
	case 1:
		PlayerStateWeapon = HAS_BAT;
		break;
	case 2:
		PlayerStateWeapon = HAS_PISTOL;
		break;
	case 3:
		PlayerStateWeapon = HAS_RIFLE;
		break;
	default:
		PlayerStateWeapon = UNARMED;
	}
}

//----------------------------------------------------------------------------- movement -------------------------------------------------------------------------------------------------------

void AProject_JackOLanternCharacter::Jump()
{
	if(!isDead)
	{
		Super::Jump();
		PlayerStateMovement = JUMPING;
		PlayerStateAttacking = NOTATTACKING;
		GetCharacterMovement()->MaxWalkSpeed = runSpeed;
		isCrouching = false;
		isSprinting = false;
		isDodging = false;
	}

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

//----------------------------------------------------------------------- attacking ---------------------------------------------------------------------------------------------------

void AProject_JackOLanternCharacter::Death()
{
	isDead = true;
	GetCharacterMovement()->DisableMovement();
	timeOfDeath = GetWorld()->GetTimeSeconds();
	GetWorldTimerManager().SetTimer(Timer,this, &AProject_JackOLanternCharacter::Respawn, GetWorld()->DeltaTimeSeconds, true);
}

void AProject_JackOLanternCharacter::SetWeaponState(WeaponState PlayerWeaponState)
{
	this->PlayerStateWeapon = PlayerWeaponState;
}

void AProject_JackOLanternCharacter::SetAttackState(AttackingState PlayerAttackState)
{
	PlayerStateAttacking = PlayerAttackState;

	//anti spam
	if(PlayerStateAttacking == NOTATTACKING)
	{
		isAttacking = false;
	}
}


// ------------------------------------------- respawning --------------------------------

void AProject_JackOLanternCharacter::CallRestartPlayer()
{
	AController* ControllerRef = GetController();

	Destroy();

	if(UWorld* World =  GetWorld())
	{
		if(AProject_JackOLanternGameMode* GameMode = Cast<AProject_JackOLanternGameMode>(World->GetAuthGameMode()))
		{
			GameMode->RestartPlayer(ControllerRef);
		}
	}
}

void AProject_JackOLanternCharacter::Respawn()
{
	timeSinceDeath = GetWorld()->TimeSeconds - timeOfDeath;

	if(timeSinceDeath > 7.0f)
	{
		isDead = false;
		CallRestartPlayer();
	}
}

void AProject_JackOLanternCharacter::Destroyed()
{
	Super::Destroyed();

	if(UWorld* World = GetWorld())
	{
		if(AProject_JackOLanternGameMode* GameMode = Cast<AProject_JackOLanternGameMode>(World->GetAuthGameMode()))
		{
			GameMode->GetOnPlayerDied().Broadcast(this);
		}
	}
}
