// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BombComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOMBERMAN2_API UBombComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBombComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

    void DirectionalBlast(const FVector& inDirection);

    UPROPERTY(EditAnywhere, Category = Instances)
    float m_TimeToBlast;
	
    UPROPERTY(EditAnywhere, Category = Instances)
    UClass* m_BlastParticle;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Instances)
    float m_BlastDistance;

private:
    class UCharacterComponent*      m_CharacterOwner;
    class UDestructibleComponent*   m_DestructibleComponent;
};
