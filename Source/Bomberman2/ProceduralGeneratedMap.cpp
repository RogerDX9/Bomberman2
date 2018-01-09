// Fill out your copyright notice in the Description page of Project Settings.

#include "ProceduralGeneratedMap.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/StaticMeshActor.h"

//-------------------------------------------------------
AProceduralGeneratedMap::AProceduralGeneratedMap()
    : NbOfRows(9)
    , NbOfCols(9)
    , SpawnOffset(190.f)
    , MetallicWallClass(NULL)
    , BrickWallClass(NULL)
{
	PrimaryActorTick.bCanEverTick = true;

    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
}

//-------------------------------------------------------
void AProceduralGeneratedMap::BeginPlay()
{
	Super::BeginPlay();

    FVector location(GetActorLocation());

    for (uint32 x = 0; x < NbOfRows; ++x)
    {
        for (uint32 y = 0; y < NbOfCols; ++y)
        {
            const FVector offset(x * SpawnOffset, y * SpawnOffset, 0);

            if (x % 2 && y % 2)
                SpawnWall(MetallicWallClass, location + offset, 190);
            else
            {
                if (FMath::RandRange(1, 2) == 1)
                {
                    SpawnWall(BrickWallClass, location + offset, 380);
                }
            }
        }
    }
}

//-------------------------------------------------------
void AProceduralGeneratedMap::SpawnWall(UClass* InClass, const FVector& InLocation, float InRadius)
{
    for (const AActor* playerStart : PlayerStartPoints)
    {
        FVector pLoc(playerStart->GetActorLocation());
        FVector diff(pLoc - InLocation);
        float s = diff.Size();

        if (s < InRadius)
        {
            return;
        }
    }

    FRotator r(0, 0, 0);
    AActor* spawnedActor = GetWorld()->SpawnActor(InClass, &InLocation, &r);

#if WITH_EDITOR
    spawnedActor->SetFolderPath("/LevelGenerator");
#endif
}
