// Fill out your copyright notice in the Description page of Project Settings.

#include "DestructibleComponent.h"

//-------------------------------------------------------
UDestructibleComponent::UDestructibleComponent()
    : m_bAutoDestroy(true)
    , m_bBlasted(false)
{
}

//-------------------------------------------------------
void UDestructibleComponent::Blast()
{
    m_bBlasted = true;

    if (m_bAutoDestroy)
    {
        GetOwner()->Destroy();
    }
}
