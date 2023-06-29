// Fill out your copyright notice in the Description page of Project Settings.


#include "hitbox.h"

// Sets default values
Ahitbox::Ahitbox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	hitboxDamage = 0.0f;
	hitstunTime = 0.00f;
	blockstunTime = 0.00f;


}

// Called when the game starts or when spawned
void Ahitbox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Ahitbox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void Ahitbox::TriggerVisualizeHitbox() {
	VisualizeHitbox();
}

