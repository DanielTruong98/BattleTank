// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
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

	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.3f;

	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.33333f;

	UPROPERTY(VisibleAnywhere)
	int32 LineTraceRange = 1000000;

	bool GetLookDirection(FVector2D ScreenLocation, FVector &LookDirection) const;
	
	bool GetLookVectorHitLocation(FVector &LookDirection, FVector &HitLocation) const;
};
