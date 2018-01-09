// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralGeneratedMap.generated.h"

UCLASS()
class BOMBERMAN2_API AProceduralGeneratedMap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProceduralGeneratedMap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    void SpawnWall(UClass* InClass, const FVector& InLocation, float InRadius);

    UPROPERTY(EditAnywhere, Category = Instances)
    uint32 NbOfRows;

    UPROPERTY(EditAnywhere, Category = Instances)
    uint32 NbOfCols;

    UPROPERTY(EditAnywhere, Category = Instances)
    float SpawnOffset;

    UPROPERTY(EditAnywhere, Category = Instances)
    UClass* MetallicWallClass;

    UPROPERTY(EditAnywhere, Category = Instances)
    UClass* BrickWallClass;

    UPROPERTY(EditAnywhere, Category = Instances)
    TArray<AActor*> PlayerStartPoints;
};
