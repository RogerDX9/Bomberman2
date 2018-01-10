// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DestructibleComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOMBERMAN2_API UDestructibleComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
    UDestructibleComponent();

    void Blast();
    bool IsBlasted() const { return m_bBlasted; }

protected:

    UPROPERTY(EditAnywhere, Category = Instances)
    bool m_bAutoDestroy;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Instances)
    bool m_bBlasted;
};
