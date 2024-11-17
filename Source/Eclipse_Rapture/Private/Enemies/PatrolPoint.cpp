// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/PatrolPoint.h"
#include "Components/SphereComponent.h"

// Sets default values
APatrolPoint::APatrolPoint()
{
	PrimaryActorTick.bCanEverTick = false;

	PatrolPointSphere = CreateDefaultSubobject<USphereComponent>(TEXT("PatrolPointSphere"));
	SetRootComponent(PatrolPointSphere);

	PatrolPointSphere->SetVisibility(bEnablePointSphere);
}