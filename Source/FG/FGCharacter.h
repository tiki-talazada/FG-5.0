// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FGCharacter.generated.h"

UENUM(BlueprintType)
enum class EInputType : uint8
{
	Default		UMETA(DisplayName = "NotMoving"),
	MoveRight	UMETA(DisplayName = "MoveRight"),
	MoveLeft	UMETA(DisplayName = "MoveLeft"),
	Jumping		UMETA(DisplayName = "Jumping"),
	Stunned		UMETA(DisplayName = "Stunned"),
	Blocking	UMETA(DisplayName = "Blocking")

};

UCLASS(config=Game)
class AFGCharacter : public ACharacter
{
	GENERATED_BODY()

	///** Side view camera */
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	//class UCameraComponent* SideViewCameraComponent;

	///** Camera boom positioning the camera beside the character */
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	//class USpringArmComponent* CameraBoom;



//P2 controller
	UFUNCTION(BlueprintCallable)
		void Attack1P2();
	UFUNCTION(BlueprintCallable)
		void Attack2P2();
	UFUNCTION(BlueprintCallable)
		void Attack3P2();
	UFUNCTION(BlueprintCallable)
		void JumpP2();
	UFUNCTION(BlueprintCallable)
		void stopJumpP2();
	UFUNCTION(BlueprintCallable)
		void moveRightP2(float _value);





protected:
	UFUNCTION(BlueprintCallable)
	void Attack1();
	UFUNCTION(BlueprintCallable)
	void Attack2();
	UFUNCTION(BlueprintCallable)
	void Attack3();

	/** Called for side to side input */
	UFUNCTION(BlueprintCallable)
	void MoveRight(float Val);

	/** Handle touch inputs. */
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Handle touch stop event. */
	void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

	virtual void Jump() override;
	virtual void StopJumping() override;
	//virtual void Landed(const FHitResult& Hit) override;

	UFUNCTION(BlueprintCallable)
		void crouching();

	UFUNCTION(BlueprintCallable)
		void stopCrouch();

	//blocking
	UFUNCTION(BlueprintCallable)
		void beginBlock();
	UFUNCTION(BlueprintCallable)
		void stopBlock();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
		AActor* hurtbox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
		AActor* Sight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
		AActor* Range;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		EInputType characterState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		EInputType inputType;

	//chracter transform
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Model")
		FTransform transform;

	//chracter scale
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Model")
		FVector scale;

	FTimerHandle stunTimerHandle;
	//FTimerHandle delayTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float playerHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float playerStamina;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC_AI")
		float distance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC_AI")
		bool inSight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC_AI")
		bool inRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
		bool defaultAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
		bool heavyAttack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
		bool win;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
		bool specialAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		bool isCrouch;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		bool hasLandedHit; 


	UFUNCTION(BlueprintCallable)
		void takeDamage(float damageAmount, float stunTime, float blockstunTime);

	UFUNCTION(BlueprintCallable)
	void BeginStun();
	UFUNCTION(BlueprintCallable)
	void EndStun();
	//void Move();


	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player references")
		AFGCharacter* otherPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		bool attacking;
	//is model flip
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Model")
		bool facing;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Model")
		bool left;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		bool canMove;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float stunTime;



public:
	AFGCharacter();



	///** Returns SideViewCameraComponent subobject **/
	//FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	///** Returns CameraBoom subobject **/
	//FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	virtual void Tick(float DeltaTime) override;
};
