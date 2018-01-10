// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOMBERMAN2_API UCharacterComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacterComponent();

    void OnBombBlasted();
    bool ShouldBlast() const        { return m_bDetonateSpawnedBomb; }
    bool IsControlledBlast() const  { return m_bControlledBlast; }

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Instances)
    int32 m_NbOfBombs;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Instances)
    int32 m_MaxNbOfBombs;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Instances)
    float m_BlastDistance;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Instances)
    bool m_bControlledBlast;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Instances)
    bool m_bDetonateSpawnedBomb;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Instances)
    FString m_Name;
};
