// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterComponent.h"
#include "Components/CapsuleComponent.h"


//-------------------------------------------------------
UCharacterComponent::UCharacterComponent()
    : m_NbOfBombs(1)
    , m_MaxNbOfBombs(1)
    , m_BlastDistance(200)
    , m_bControlledBlast(false)
    , m_bDetonateSpawnedBomb(false)
    , m_Name("Player 1")
{
}

//-------------------------------------------------------
void UCharacterComponent::OnBombBlasted()
{
    ++m_NbOfBombs;
    m_bDetonateSpawnedBomb = false;
}

