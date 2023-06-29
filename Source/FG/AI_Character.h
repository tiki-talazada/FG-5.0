// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FGCharacter.h"
#include "AI_Character.generated.h"

/**
 * 
 */
UCLASS()
class FG_API AAI_Character : public AFGCharacter
{
	GENERATED_BODY()


public:
	AAI_Character();

protected:
	virtual void BeginPlay() override;



public:

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
