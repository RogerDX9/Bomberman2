// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterComponent.h"
#include "Components/CapsuleComponent.h"


//-------------------------------------------------------
UCharacterComponent::UCharacterComponent()
    : m_NbOfBombs(1)
    , m_MaxNbOfBombs(1)
    , m_ExplosionDistance(200)
    , m_bRemoteControlledBombs(false)
    , m_bDetonate(false)
    , m_Name("Player 1")
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

//-------------------------------------------------------
void UCharacterComponent::BeginPlay()
{
	Super::BeginPlay();
}

//-------------------------------------------------------
void UCharacterComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

//-------------------------------------------------------
void UCharacterComponent::OnBombExplode()
{
    ++m_NbOfBombs;
    m_bDetonate = false;
}

