// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Character.h"

AAI_Character::AAI_Character()
{
	PrimaryActorTick.bCanEverTick = true;
}
void AAI_Character::BeginPlay() {
	Super::BeginPlay();
}
void AAI_Character::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}
void AAI_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
