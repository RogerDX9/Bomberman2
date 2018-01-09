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

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    void OnBombExplode();
    bool ShouldDetonate() const { return m_bDetonate; }
    bool IsRemoteControlledBombs() const { return m_bRemoteControlledBombs; }

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Instances)
    int32 m_NbOfBombs;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Instances)
    int32 m_MaxNbOfBombs;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Instances)
    float m_ExplosionDistance;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Instances)
    bool m_bRemoteControlledBombs;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Instances)
    bool m_bDetonate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Instances)
    FString m_Name;
};
