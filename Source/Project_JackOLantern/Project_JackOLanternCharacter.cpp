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
#include "Pickup.h"
#include "Pot.h"
#include "Door.h"
#include "Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "Project_JackOLanternGameMode.h"

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

	HitBox = CreateDefaultSubobject<USphereComponent>(TEXT("Hitbox"));
	HitBox->SetupAttachment(GetMesh(), "middle_r_01_BIND");

	//Set Particle System
	static ConstructorHelpers::FObjectFinder<UParticleSystem> SparksFinder(TEXT("/Game/StarterContent/Particles/P_Explosion"));
	if(SparksFinder.Succeeded())
	{
		HitParticles = SparksFinder.Object;
	}

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemy::StaticClass(), AEnemies);

	for (AActor* Actor : AEnemies)
	{
		AEnemy* Enemy = Cast<AEnemy>(Actor);
		if(Enemy)
		{
			Enemy->SetPlayer(this);
		}
	}

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void AProject_JackOLanternCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	health = 1.0f;

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
	isDead = false;

	//Interacting
	hasKey = false;
	foundDoor = false;
	foundPot = false;
	underTable = false;


	//States
	PlayerStateMovement = IDLE;
	PlayerStateAttacking = NOTATTACKING;
	PlayerStateWeapon = UNARMED;

	//Death
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
	
	/*if(hasPot)
	{
		Print("hasPot");
	}
	else
	{
		Print("not hasPot");
	}*/

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

	if(OtherActor->ActorHasTag("Pot") && !hasPot)
	{
		foundPot = true;
		Pot = Cast<APot>(OtherActor);
	}

	if(OtherActor->ActorHasTag("Key"))
	{
		foundKey = true;
		Key = Cast<APickup>(OtherActor);
	}

	if(OtherActor->ActorHasTag("Enemy") && isAttacking )
	{
		EnemyToDamage = Cast<AEnemy>(OtherActor);
		if(EnemyToDamage)
		{
			overlappedEnemy = true;
		}
	}

	if(OtherActor->ActorHasTag("Door"))
	{
		Door = Cast<ADoor>(OtherActor);
		foundDoor = true;
	}

	if(OtherActor->ActorHasTag("Table"))
	{
		underTable = true;
	}
	
}

void AProject_JackOLanternCharacter::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	if(OtherActor->ActorHasTag("Key"))
	{
		foundKey = false;
	}

	if(OtherActor->ActorHasTag("Enemy"))
	{
		overlappedEnemy = false;
		if(EnemyToDamage)
		{
			//EnemyToDamage->damaged = false;
			overlappedEnemy = true;
		}
	}

	if(OtherActor->ActorHasTag("Door"))
	{
		Door = nullptr;
		foundDoor = false;
	}

	if(OtherActor->ActorHasTag("Pot") && !hasPot)
	{
		foundPot = false;
		Pot = nullptr;
	}

	if(OtherActor->ActorHasTag("Table"))
	{
		underTable = false;
	}
	
}

void AProject_JackOLanternCharacter::Print(FString message)
{
	GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow, message, true);
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
	if(!isSprinting && !GetCharacterMovement()->IsFalling() && !isReloading)
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
	
	if(foundKey)
	{
		hasKey = true;
		foundKey = false;
		if(Key)
		{
			Key->Collect();
		}
	}

	if(foundDoor && Door && hasKey)
	{
		Door->Open();
	}

	if(foundPot && Pot)
	{
		Pot->Pickup();
		foundPot = false;
	}
}

void AProject_JackOLanternCharacter::InteractStop(const FInputActionValue& Value)
{
	isInteracting = false;
}

//----------------------------------- attacking input ---------------------------------------------------------------------------

void AProject_JackOLanternCharacter::Attack(const FInputActionValue& Value)
{
	if(!isAttacking && GetCharacterMovement()->Velocity.Z == 0.0f && !hasPot)
	{
		isAttacking = true;
		playAttackAnim = true;
		if(GetVelocity().Length() < 500.0f)
		{
			//GetCharacterMovement()->DisableMovement();
		}
	}else if(hasPot)
	{
		hasPot = false;
		PlayerStateAttacking = THROWING_POT;
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
		isAiming = false;
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

//----------------------------------------------------------------------- attacking ---------------------------------------------------------------------------------------------------

void AProject_JackOLanternCharacter::ThrowPot()
{
	Pot->Throw();
}

void AProject_JackOLanternCharacter::EndThrowPot()
{
	hasPot = false;
	Pot = nullptr;
	PlayerStateAttacking = NOTATTACKING;
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

void AProject_JackOLanternCharacter::EndAttackAnim()
{
	isAttacking = false;
	playAttackAnim = false;

	GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	
}

void AProject_JackOLanternCharacter::DoDamage(float DamageAmount)
{
	if(EnemyToDamage && overlappedEnemy)
	{
		EnemyToDamage->Damage(DamageAmount);
	}
}

void AProject_JackOLanternCharacter::Death()
{
	isDead = true;
	GetCharacterMovement()->DisableMovement();
	timeOfDeath = GetWorld()->GetTimeSeconds();
	GetWorldTimerManager().SetTimer(Timer,this, &AProject_JackOLanternCharacter::Respawn, GetWorld()->DeltaTimeSeconds, true);
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
