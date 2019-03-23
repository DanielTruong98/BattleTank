// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
	//UE_LOG(LogTemp, Warning, TEXT("Tick functioning"));
}


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possesing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possesing: %s"), *(ControlledTank->GetName()));
	}
}

//Returns current tank child if it exists
ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) {
		return;
	}

	FVector OUTHitLocation;	//Out parameter
	if (!GetSightRayHitLocation(OUTHitLocation)) // Has "side-effect", is going to line trace
	{
		GetControlledTank()->AimAt(OUTHitLocation);
		//Get world location through crosshair intersecting with world
		//If linetrace hits landscape
			//Aim at lanscape
	}
}

//Returns true if landscape hit and passes location to OUTHitLocation, else return false
bool ATankPlayerController::GetSightRayHitLocation(FVector &OUTHitLocation) const
{
	//Find crosshair location on viewport
	//Both variables are out parameters in the following function
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		//Line-trace along that direction, see what is hit
		GetLookVectorHitLocation(LookDirection, OUTHitLocation);
	}
	return false;
}

//"De-project" screen position of the crosshair to a world direction
bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector &LookDirection)const
{
	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		LookDirection
	);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector &LookDirection, FVector &OUTHitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(
			HitResult,
			StartLocation,
			EndLocation,
			ECollisionChannel::ECC_Visibility)
		)
		{
		OUTHitLocation = HitResult.Location;
		return true;
		}
	OUTHitLocation = FVector(0, 0, 0);
	return false;
}