// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseNPC.h"


ABaseNPC::ABaseNPC()
{
	PrimaryActorTick.bCanEverTick = true;
}
void ABaseNPC::BeginPlay() {
	Super::BeginPlay();
}

void ABaseNPC::MoveChar()
{
	//while (inSight //&& !inrange)
	//	{
	//		FVector newLocation = GetActorLocation() - FVector::RightVector * 1.f; 
	//		SetActorLocation(newLocation);
	//	}
}
void ABaseNPC::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	
	
	if (otherPlayer) {
		FVector locaA = otherPlayer->GetActorLocation();
		FVector locaB = this->GetActorLocation();
		float Dt = FVector::Distance(locaA, locaB);
		distance = Dt;
}

	if (distance > 120 && distance <= 180) {
		inputType = EInputType::MoveRight;
		Attack2();
		inputType = EInputType::Default;
	}
	else if (distance <= 120)
	{
		Attack1();
	}
	else{
		inRange = true;
	}



	
}



