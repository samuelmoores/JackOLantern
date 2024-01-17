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
enum AttackingState { NOTATTACKING, PUNCHING, THROWING_POT, SHOOOTING_PISTOL,SHOOTING_RIFLE, RELOADING_PISTOL,RELOADING_RIFLE, AIMING_PISTOL, AIMING_RIFLE};

UENUM(BlueprintType)
enum WeaponState { UNARMED, HAS_PISTOL, HAS_RIFLE, HAS_MELEEWEAPON };

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

	/** IDK */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UParticleSystem* HitParticles;

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
	UInputAction* AimAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ChangeWeaponAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ShootAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ReloadAction;
	
	// -------------------------------------- Variables ---------------------------------------------------------
	MovementState PlayerStateMovement;
	AttackingState PlayerStateAttacking;
	WeaponState PlayerStateWeapon;

	class APot* Pot;
	class APickup* Key;
	class ADoor* Door;

	//movement
	float runSpeed;
	float sprintSpeed;
	float crouchSpeed;
	bool isSprinting;
	bool isCrouching;
	float dodgeSpeed;
	bool isDodging;

	//attacking
	int attackStrength;
	bool hasGun;
	bool hasPistol;
	bool hasRifle;
	bool isAiming;
	bool isReloading;
	bool foundBat;

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
	void AimStart(const FInputActionValue& Value);
	void AimStop(const FInputActionValue& Value);
	void ChangeWeapon(const FInputActionValue& Value);
	void ShootStart(const FInputActionValue& Value);
	void ReloadStart(const FInputActionValue& Value);
	void InteractStart(const FInputActionValue& Value);
	void InteractStop(const FInputActionValue& Value);

	//--------------------------------------Respawning-----------------------------------------------------------
	virtual void Destroyed() override;
	void CallRestartPlayer();

	//--------------------------------- Anim Functions -----------------------------------------------------------
	UFUNCTION(BlueprintCallable)
	void EndDodge();

	UFUNCTION(BlueprintCallable)
	void ShootStop();

	UFUNCTION(BlueprintCallable)
	void ReloadStop();

	UFUNCTION(BlueprintCallable)
	void ThrowPot();

	UFUNCTION(BlueprintCallable)
	void EndThrowPot();

	UFUNCTION(BlueprintCallable)
	void EndAttackAnim();

	UFUNCTION(BlueprintCallable)
	void DoDamage(float DamageAmount);
	
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
	
	//-----------------------------------Blueprint Variables-----------------------------------------------------------
	UPROPERTY(BlueprintReadOnly)
	float health;
	UPROPERTY(BlueprintReadWrite)
	int selectedWeapon;
	UPROPERTY(BlueprintReadWrite)
	bool hasPot;
	UPROPERTY(BlueprintReadOnly)
	bool isShooting;
	UPROPERTY(BlueprintReadOnly)
	bool isAttacking;
	UPROPERTY(BlueprintReadOnly)
	bool foundKey;
	UPROPERTY(BlueprintReadOnly)
	bool foundDoor;
	UPROPERTY(BlueprintReadOnly)
	bool foundPot;
	UPROPERTY(BlueprintReadOnly)
	bool hasKey;
	UPROPERTY(BlueprintReadOnly)
	bool isDead;
	UPROPERTY(BlueprintReadOnly)
	bool playAttackAnim;
	UPROPERTY(BlueprintReadOnly)
	bool underTable;
	
	//--------------------------------------------Our Variables-------------------------------------------------
	TArray<AActor*> AEnemies;
	TArray<AEnemy*> Enemies;
	AEnemy* EnemyToDamage;
	FTimerHandle Timer;

	bool isInteracting;
	bool overlappedEnemy;
	bool hasBallroomKey;

	float timeOfDeath;
	float timeSinceDeath;
	
	//------------------------------------------- Our Functions -------------------------------------------------
	void Print(FString message);

	UFUNCTION(BlueprintCallable)
	MovementState GetJackStateMovement() const {return PlayerStateMovement;}

	UFUNCTION(BlueprintCallable)
	AttackingState GetJackStateAttacking() const {return PlayerStateAttacking;}

	UFUNCTION(BlueprintCallable)
	WeaponState GetJackStateWeapon() const {return PlayerStateWeapon;}

	UFUNCTION(BlueprintCallable)
	void SetWeaponState(WeaponState PlayerWeaponState);

	void SetState();
	void SetIdleState();
	void SetMoveState();
	void Death();
	void Respawn();
};

