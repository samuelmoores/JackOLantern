// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Components/SphereComponent.h"
#include "Project_JackOLanternCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UENUM(BlueprintType)
enum MovementState { IDLE, RUNNING, JUMPING, DODGING, HURT, CROUCHING, SPRINTING };

UENUM(BlueprintType)
enum AttackingState { NOTATTACKING, PUNCHING, THROWING_POT, SWINGING_BAT, AIMING_PISTOL, AIMING_RIFLE, RELOADING_PISTOL, RELOADING_RIFLE};

UENUM(BlueprintType)
enum WeaponState { UNARMED, HAS_POT, HAS_BAT, HAS_PISTOL, HAS_RIFLE };

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AProject_JackOLanternCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Hand Sphere Collider for Punch */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	USphereComponent* HitBox;

	//--------------------------------- Input Actions --------------------------------------------------------
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ThrowAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SprintAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* CrouchAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* DodgeAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* AttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ChangeWeaponAction;
	
	// -------------------------------------- Variables ---------------------------------------------------------
	MovementState PlayerStateMovement;
	AttackingState PlayerStateAttacking;
	WeaponState PlayerStateWeapon;

	//movement
	float runSpeed;
	float sprintSpeed;
	float crouchSpeed;
	bool isSprinting;
	bool isCrouching;
	float dodgeSpeed;
	bool isDodging;

	//attacking
	bool foundBat;
	

	//*********************************************************************** *** ******************************************************************************
	//*********************************************************************** protected *****************************************************************************
	//*******************************************************************************************************************************************************
protected:
	// ------------------------------------ Actions -------------------------------------------------------------
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	virtual void Jump() override;
	void SprintStart(const FInputActionValue& Value);
	void SprintStop(const FInputActionValue& Value);
	void CrouchStart(const FInputActionValue& Value);
	void CrouchStop(const FInputActionValue& Value);
	void Dodge(const FInputActionValue& Value);
	void Attack(const FInputActionValue& Value);
	void ChangeWeapon(const FInputActionValue& Value);
	void InteractStart(const FInputActionValue& Value);
	void InteractStop(const FInputActionValue& Value);

	//--------------------------------------Respawning-----------------------------------------------------------
	virtual void Destroyed() override;
	void CallRestartPlayer();

	//--------------------------------- Anim Functions -----------------------------------------------------------
	UFUNCTION(BlueprintCallable)
	void EndDodge();
	
	UFUNCTION(BlueprintCallable)
	void ThrowPot();

	UFUNCTION(BlueprintCallable)
	void EndThrowPot();
	
	// -------------------------------- Overridden UE Functions -------------------------------------------------
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay();
	virtual void Tick(float DeltaSeconds) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

	//*********************************************************************** *** ******************************************************************************
	//*********************************************************************** public *****************************************************************************
	//*******************************************************************************************************************************************************

public:
	AProject_JackOLanternCharacter();
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	
	//--------------------------------------------------------------------------------Blueprint Variables------------------------------------------------------------------------------------
	//----------------------- pickups------------------------
	UPROPERTY(BlueprintReadOnly)
	bool foundKey;
	UPROPERTY(BlueprintReadOnly)
	bool hasKey;
	UPROPERTY(BlueprintReadOnly)
	bool foundDoor;
	UPROPERTY(BlueprintReadOnly)
	bool foundPot;
	UPROPERTY(BlueprintReadWrite)
	bool hasPot;
	
	// ------------------- attacking --------------------
	UPROPERTY(BlueprintReadOnly)
	float health;
	UPROPERTY(BlueprintReadWrite)
	int selectedWeapon;
	
	//starts attack animation
	UPROPERTY(BlueprintReadWrite)
	bool isAttacking;
	
	UPROPERTY(BlueprintReadOnly)
	bool isDead;

	//--------------------movement---------------------
	UPROPERTY(BlueprintReadOnly)
	bool underTable;

	//--------------------------------------------------------------------------------------cpp Variables---------------------------------------------------------------------------------------
	FTimerHandle Timer;

	bool isInteracting;
	bool hasBallroomKey;

	//------attacking----
	float timeOfDeath;
	float timeSinceDeath;
	
	//------------------------------------------- States -------------------------------------------------
	UFUNCTION(BlueprintCallable)
	MovementState GetJackStateMovement() const {return PlayerStateMovement;}

	UFUNCTION(BlueprintCallable)
	AttackingState GetJackStateAttacking() const {return PlayerStateAttacking;}

	UFUNCTION(BlueprintCallable)
	WeaponState GetJackStateWeapon() const {return PlayerStateWeapon;}

	UFUNCTION(BlueprintCallable)
	void SetWeaponState(WeaponState PlayerWeaponState);

	void SetIdleState();
	void SetMoveState();

	//------------------ Utility functions--------------------------------------------
	void Print(FString message);
	void Death();
	void Respawn();
};

