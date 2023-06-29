// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FGCharacter.h"
#include "PinkMannequin.generated.h"

/**
 * 
 */
UCLASS()
class FG_API APinkMannequin : public AFGCharacter
{
	GENERATED_BODY()


public:
	APinkMannequin();

protected:
	virtual void BeginPlay() override;


	
public: 

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
