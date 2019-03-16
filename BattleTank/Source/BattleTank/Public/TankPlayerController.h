// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Containers/UnrealString.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"	//Must be the last include

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay() override;

	ATank* GetControlledTank() const;

	virtual void Tick(float DeltaTime) override;

	//Start moving barrel towards crosshair direction
	void AimTowardsCrosshair();
private:

	bool GetSightRayHitLocation(FVector &OutHitLocation) const;
};
