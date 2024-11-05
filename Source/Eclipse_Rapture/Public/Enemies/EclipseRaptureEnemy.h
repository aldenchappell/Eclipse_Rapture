// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Character/CharacterTypes.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EclipseRaptureEnemy.generated.h"


UCLASS()
class ECLIPSE_RAPTURE_API AEclipseRaptureEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	AEclipseRaptureEnemy();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Character | Character Properties")
	ECharacterType CharacterType = ECharacterType::ECT_Enemy;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Character | Character Properties")
	TObjectPtr<class UHealthComponent> HealthComponent;
protected:
	
	virtual void BeginPlay() override;

};
