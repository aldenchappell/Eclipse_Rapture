// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/PatrolPoint.h"
#include "Components/SplineComponent.h"

// Sets default values
APatrolPoint::APatrolPoint()
{
	PrimaryActorTick.bCanEverTick = false;

	PatrolSpline = CreateDefaultSubobject<USplineComponent>(TEXT("Patrol Spline"));
	SetRootComponent(PatrolSpline);

	//PatrolPointSphere->SetVisibility(bEnablePointSphere);
}