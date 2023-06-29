// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "hitbox.generated.h"

UENUM(BlueprintType)
enum class hitboxEnum : uint8 {
	proximity_HB	UMETA(DisplayName = "Proximity"),
	strike_HB		UMETA(DisplayName = "Strike"),
	hurtbox			UMETA(DisplayName = "Hurtbox")
};

UCLASS()
class FG_API Ahitbox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Ahitbox();

	UFUNCTION(BlueprintCallable)
		void TriggerVisualizeHitbox();

	UFUNCTION(BlueprintImplementableEvent)
		void VisualizeHitbox();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
		float hitboxDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
		float hitstunTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
		float blockstunTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
		hitboxEnum hitboxType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
		FVector hitboxLocation;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
