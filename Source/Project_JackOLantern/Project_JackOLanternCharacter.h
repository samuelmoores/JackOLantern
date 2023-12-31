// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Project_JackOLanternCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UENUM(BlueprintType)
enum MovementState { IDLE, RUNNING, JUMPING, DODGING, HURT, CROUCHING, SPRINTING };

UENUM(BlueprintType)
enum AttackingState { NOTATTACKING, SHOOOTING, RELOADING, AIMING, MELEE };

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

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ThrowAction;

	/** Interact Input Action */
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

	// -------------------------------------- Variables ---------------------------------------------------------
	MovementState PlayerStateMovement;
	AttackingState PlayerStateAttacking;
	float runSpeed;
	float sprintSpeed;
	float crouchSpeed;
	bool isSprinting;
	bool isCrouching;
	float dodgeSpeed;
	bool isDodging;
	int attackStrength;
	bool isAttacking;
	
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
	void Throw();

	//--------------------------------- Anim Functions-----------------------------------------------------------
	UFUNCTION(BlueprintCallable)
	void EndDodge();

	UFUNCTION(BlueprintCallable)
	void EndAttack();

	// -------------------------------- Overridden UE Functions -------------------------------------------------
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay();
	virtual void Tick(float DeltaSeconds) override;
	
public:
	AProject_JackOLanternCharacter();
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	//------------------------------------------- Our Functions -------------------------------------------------
	void Print(FString message);

	UFUNCTION(BlueprintCallable)
	MovementState GetJackStateMovement() const {return PlayerStateMovement;}

	UFUNCTION(BlueprintCallable)
	AttackingState GetJackStateAttacking() const {return PlayerStateAttacking;}

	void SetState();
	void SetIdleState();
	void SetMoveState();
};

