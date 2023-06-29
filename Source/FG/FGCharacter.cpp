// Copyright Epic Games, Inc. All Rights Reserved.

#include "FGCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "FGGameMode.h"
#include "GameFramework/CharacterMovementComponent.h"

AFGCharacter::AFGCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	//// Create a camera boom attached to the root (capsule)
	//CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	//CameraBoom->SetupAttachment(RootComponent);
	//CameraBoom->SetUsingAbsoluteRotation(true); // Rotation of the character should not affect rotation of boom
	//CameraBoom->bDoCollisionTest = false;
	//CameraBoom->TargetArmLength = 500.f;
	//CameraBoom->SocketOffset = FVector(0.f,0.f,75.f);
	//CameraBoom->SetRelativeRotation(FRotator(0.f,180.f,0.f));

	//// Create a camera and attach to boom
	//SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	//SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	//SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.0f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	Range = nullptr;
	Sight = nullptr;
	otherPlayer = nullptr;
	hurtbox = nullptr;
	transform = FTransform();
	inputType = EInputType::Default;
	scale =  FVector(0.0f, 0.0f, 0.0f);
	playerHealth = 1.00f;
	defaultAttack = false;
	heavyAttack = false;
	specialAttack = false;
	attacking = false;
	facing =false;
	canMove = true;
	stunTime = 0.0f;
	playerStamina = 0.5f;
	inRange = false;
	inSight = false;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void AFGCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	//if (auto gameMode = Cast<AFGGameMode>(GetWorld()->GetAuthGameMode()))
	//{
		//if (gameMode->player1 == this) {
			// set up gameplay key bindings Player 1
			UE_LOG(LogTemp, Warning, TEXT("player 1 control"));
			PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFGCharacter::Jump);
			PlayerInputComponent->BindAction("Jump", IE_Released, this, &AFGCharacter::StopJumping);
			PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AFGCharacter::crouching);
			PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AFGCharacter::stopCrouch);

			PlayerInputComponent->BindAction("Block", IE_Pressed, this, &AFGCharacter::beginBlock);
			PlayerInputComponent->BindAction("Block", IE_Released, this, &AFGCharacter::stopBlock);

			PlayerInputComponent->BindAxis("MoveRight", this, &AFGCharacter::MoveRight);
			PlayerInputComponent->BindAction("Attack1", IE_Pressed, this, &AFGCharacter::Attack1);
			PlayerInputComponent->BindAction("Attack2", IE_Pressed, this, &AFGCharacter::Attack2);
			PlayerInputComponent->BindAction("Attack3", IE_Pressed, this, &AFGCharacter::Attack3);

			//PlayerInputComponent->BindAction("Block", IE_Pressed, this, &AFGCharacter::beginBlock).bExecuteWhenPaused = true;
			//PlayerInputComponent->BindKey(EKeys::S, IE_Pressed, this, &AFGCharacter::beginBlock).bExecuteWhenPaused = true;
			//PlayerInputComponent->BindKey(EKeys::W, IE_Pressed, this, &AFGCharacter::beginBlock).bExecuteWhenPaused = true;
			//PlayerInputComponent->BindAction("Block", IE_Released, this, &AFGCharacter::stopBlock).bExecuteWhenPaused = true;
			//PlayerInputComponent->BindKey(EKeys::S, IE_Released, this, &AFGCharacter::stopBlock).bExecuteWhenPaused = true;
			//PlayerInputComponent->BindKey(EKeys::W, IE_Released, this, &AFGCharacter::stopBlock).bExecuteWhenPaused = true;

			PlayerInputComponent->BindTouch(IE_Pressed, this, &AFGCharacter::TouchStarted);
			PlayerInputComponent->BindTouch(IE_Released, this, &AFGCharacter::TouchStopped);
	//	}
	//	else {
	//		// set up gameplay key bindings Player 2
	//		UE_LOG(LogTemp, Warning, TEXT("player 2 control"));
	//		PlayerInputComponent->BindAction("JumpP2", IE_Pressed, this, &AFGCharacter::Jump);
	//		PlayerInputComponent->BindAction("JumpP2", IE_Released, this, &AFGCharacter::StopJumping);
	//		PlayerInputComponent->BindAction("CrouchP2", IE_Pressed, this, &AFGCharacter::crouching);
	//		PlayerInputComponent->BindAction("CrouchP2", IE_Released, this, &AFGCharacter::stopCrouch);
	//		PlayerInputComponent->BindAxis("moveRightP2", this, &AFGCharacter::MoveRight);
	//		PlayerInputComponent->BindAction("Attack1P2", IE_Pressed, this, &AFGCharacter::Attack1);
	//		PlayerInputComponent->BindAction("Attack2P2", IE_Pressed, this, &AFGCharacter::Attack2);
	//		PlayerInputComponent->BindAction("Attack3P2", IE_Pressed, this, &AFGCharacter::Attack3);

	//		PlayerInputComponent->BindTouch(IE_Pressed, this, &AFGCharacter::TouchStarted);
	//		PlayerInputComponent->BindTouch(IE_Released, this, &AFGCharacter::TouchStopped);
	//	}
	//}

}

void AFGCharacter::Jump() {
	ACharacter::Jump();
	inputType = EInputType::Jumping;
	
}

void AFGCharacter::StopJumping() {
	ACharacter::StopJumping();
}

//void AFGCharacter::Landed(const FHitResult& Hit) {
//	inputType = EInputType::Default;
//}

void AFGCharacter::crouching() {
	isCrouch = true;
	inputType = EInputType::Blocking;
	UE_LOG(LogTemp, Warning, TEXT("crouch"));
}

void AFGCharacter::stopCrouch() {
	isCrouch = false;
	inputType = EInputType::Default;
	UE_LOG(LogTemp, Warning, TEXT("crouch end"));
}

void AFGCharacter::MoveRight(float Value)
{
	if (isCrouch == false && canMove == true && inputType != EInputType::Blocking) {
		//UE_LOG(LogTemp, Warning, TEXT("input %f"), Value);
		if (Value > 0.20f)
		{
			if (facing == true)
			{
				inputType = EInputType::MoveRight;
			}
			else
			{
				inputType = EInputType::MoveLeft;
			}

		}
		else if (Value < -0.20f)
		{
			if (facing == false)
			{
				inputType = EInputType::MoveRight;
			}
			else
			{
				inputType = EInputType::MoveLeft;
			}
		}
		else
		{
			inputType = EInputType::Default;
		}
		AddMovementInput(FVector(0.f, -1.f, 0.f), Value);
	}


	// add movement in that direction


}

void AFGCharacter::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// jump on any touch
	Jump();
}

void AFGCharacter::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	StopJumping();
}
void AFGCharacter::Attack1() {
	UE_LOG(LogTemp, Warning, TEXT("Attack1 "));
	if (playerStamina > 0.01f) {
		defaultAttack = true;
		canMove = false;
	}

}
void AFGCharacter::Attack2() {
	UE_LOG(LogTemp, Warning, TEXT("Attack2"));
	if (playerStamina > 0.05f) {
		heavyAttack = true;
		canMove = false;
	}
}
void AFGCharacter::Attack3() {
	if (playerStamina > 0.1f) {
		specialAttack = true;
		canMove = false;
	}
	UE_LOG(LogTemp, Warning, TEXT("Attack3"));
}

//P2 controller
void AFGCharacter::Attack1P2() {
	Attack1();
}
void AFGCharacter::Attack2P2() {
	Attack2();
}
void AFGCharacter::Attack3P2() {
	Attack3();
}
void AFGCharacter::JumpP2() {
	Jump();
}
void AFGCharacter::stopJumpP2() {
	StopJumping();
}
void AFGCharacter::moveRightP2(float _value) {
	MoveRight(_value);
}

void AFGCharacter::takeDamage(float damageAmount, float hitstunTime, float _blockstunTime) {
	if (playerStamina <= 0) {
		canMove = false;
	}
	if (inputType != EInputType::Blocking) {
		playerHealth = playerHealth - damageAmount;
		stunTime = hitstunTime;
		if (hitstunTime > 0.0f) {
			inputType = EInputType::Stunned;
			BeginStun();
		}
	}
	else
	{
		float reduceDame = damageAmount * 0.5f;
		playerHealth = playerHealth - reduceDame;
		stunTime = _blockstunTime;
		if (stunTime > 0.0f) {
			BeginStun();
		}
		else
		{
			inputType = EInputType::Default;
		}

	}
	if (playerHealth < 0) {
		playerHealth = 0;
	}

}
void AFGCharacter::BeginStun() {
	canMove = false;
	GetWorld()->GetTimerManager().SetTimer(stunTimerHandle, this, &AFGCharacter::EndStun, stunTime, false);
}

void AFGCharacter::EndStun() {
	inputType = EInputType::Default;
	canMove = true;
	
}

void AFGCharacter::beginBlock() {
	inputType = EInputType::Blocking;
}
void AFGCharacter::stopBlock() {
	inputType = EInputType::Default;
}


void AFGCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	while (otherPlayer->playerHealth <= 0) {
		win = true;
		break;
	}

		if(isCrouch || inputType == EInputType::Blocking || inputType == EInputType::Stunned){
			playerStamina = playerStamina + 0.0025f;
		}
		else
		{
			playerStamina += 0.001f;
		}


	//facing function

	if (otherPlayer)
	{
		if (auto yourMovement = GetCharacterMovement())
		{
			if (auto enemyMoment = otherPlayer->GetCharacterMovement())
			{
				if (enemyMoment->GetActorLocation().Y >= yourMovement->GetActorLocation().Y)
				{
					if (facing)
					{
						if (auto mesh = GetCapsuleComponent()->GetChildComponent(1))
						{
							transform = mesh->GetRelativeTransform();
							scale = transform.GetScale3D();
							scale.Y = -1;
							transform.SetScale3D(scale);
							mesh->SetRelativeTransform(transform);
						}
						facing = false;
						left = false;
						UE_LOG(LogTemp, Warning, TEXT("facing left"));
					}
				}
				else
				{
					if (!facing)
					{
						if (auto mesh = GetCapsuleComponent()->GetChildComponent(1))
						{
							transform = mesh->GetRelativeTransform();
							scale = transform.GetScale3D();
							scale.Y = 1;
							transform.SetScale3D(scale);
							mesh->SetRelativeTransform(transform);
						}
						facing = true;
						left = true;
						UE_LOG(LogTemp, Warning, TEXT("facing right"));
					}
				}
			}
		}
	}
}