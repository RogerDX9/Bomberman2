// Fill out your copyright notice in the Description page of Project Settings.

#include "BombComponent.h"
#include "CollisionQueryParams.h"
#include "CharacterComponent.h"
#include "DestructibleComponent.h"


//-------------------------------------------------------
UBombComponent::UBombComponent()
    : m_TimeToExplode(3)
    , m_TimeToRemoteExplode(10)
    , m_ExplosionClass(NULL)
    , m_CharacterComponent(NULL)
    , m_DestructibleComponent(NULL)
    , m_ExplosionDistance(200)
{
	PrimaryComponentTick.bCanEverTick = true;
}

//-------------------------------------------------------
void UBombComponent::BeginPlay()
{
	Super::BeginPlay();
    
    AActor* bombActor = GetOwner();
    if (bombActor != NULL)
    {
        AActor* characterActor = bombActor->GetOwner();
        if (characterActor != NULL)
        {
            m_CharacterComponent = Cast<UCharacterComponent>(characterActor->GetComponentByClass(UCharacterComponent::StaticClass()));
        }

        m_DestructibleComponent = Cast<UDestructibleComponent>(bombActor->GetComponentByClass(UDestructibleComponent::StaticClass()));
    }
    
    check(m_DestructibleComponent != NULL);
    check(m_CharacterComponent != NULL);
}

//-------------------------------------------------------
void UBombComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    m_TimeToExplode -= DeltaTime;
    m_TimeToRemoteExplode -= DeltaTime;

    const bool shouldDetonate = m_CharacterComponent->IsRemoteControlledBombs() ? m_TimeToRemoteExplode < 0 : m_TimeToExplode < 0;

    if (shouldDetonate || m_CharacterComponent->ShouldDetonate() || m_DestructibleComponent->IsExploded())
    {
        DirectionalExplosion(FVector::RightVector);
        DirectionalExplosion(FVector::RightVector * -1);
        DirectionalExplosion(FVector::ForwardVector);
        DirectionalExplosion(FVector::ForwardVector * -1);

        const FRotator  r(0, 0, 0);
        const FVector   l(GetOwner()->GetActorLocation());
        GetWorld()->SpawnActor(m_ExplosionClass, &l, &r);
        GetOwner()->Destroy();

        m_CharacterComponent->OnBombExplode();
    }
}

//-------------------------------------------------------
void UBombComponent::DirectionalExplosion(const FVector& inDirection)
{
    const FRotator explosionRotation(0, 0, 0);
    const FVector startTrace = GetOwner()->GetActorLocation();
    const FVector endTrace = startTrace + inDirection * m_ExplosionDistance;

    FCollisionQueryParams traceParams(NAME_None, FCollisionQueryParams::GetUnknownStatId(), true, GetOwner());
    traceParams.bTraceAsyncScene = true;
    traceParams.bReturnPhysicalMaterial = true;

    FHitResult hitResult(ForceInit);
    if (GetWorld()->LineTraceSingleByChannel(hitResult, startTrace, endTrace, ECC_WorldDynamic, traceParams))
    {
        if (hitResult.Actor != NULL)
        {
            AActor * actor(hitResult.Actor.Get());
            UDestructibleComponent* destructibleComp = Cast<UDestructibleComponent>(actor->GetComponentByClass(UDestructibleComponent::StaticClass()));

            if (destructibleComp != NULL)
            {
                const FVector l(actor->GetActorLocation());
                GetWorld()->SpawnActor(m_ExplosionClass, &l, &explosionRotation);
                destructibleComp->OnExplode();
            }
        }
    }
    else
    {
        const FVector endTrace1 = startTrace + inDirection * (m_ExplosionDistance * 0.5f);
        GetWorld()->SpawnActor(m_ExplosionClass, &endTrace1, &explosionRotation);
        GetWorld()->SpawnActor(m_ExplosionClass, &endTrace, &explosionRotation);
    }
}