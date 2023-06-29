// Fill out your copyright notice in the Description page of Project Settings.


#include "PinkMannequin.h"

APinkMannequin::APinkMannequin()
{
	PrimaryActorTick.bCanEverTick = true;
}
void APinkMannequin::BeginPlay() {
	Super::BeginPlay();
}
void APinkMannequin::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}
void APinkMannequin::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}