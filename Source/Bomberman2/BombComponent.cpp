// Fill out your copyright notice in the Description page of Project Settings.

#include "BombComponent.h"
#include "CollisionQueryParams.h"
#include "CharacterComponent.h"
#include "DestructibleComponent.h"

//-------------------------------------------------------
UBombComponent::UBombComponent()
    : m_TimeToBlast             (3)
    , m_TimeToBlastControlled   (10)
    , m_BlastParticle           (NULL)
    , m_CharacterOwner          (NULL)
    , m_DestructibleComponent   (NULL)
    , m_BlastDistance           (200)
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
            m_CharacterOwner = Cast<UCharacterComponent>(characterActor->GetComponentByClass(UCharacterComponent::StaticClass()));
        }

        m_DestructibleComponent = Cast<UDestructibleComponent>(bombActor->GetComponentByClass(UDestructibleComponent::StaticClass()));
    }
    
    check(m_DestructibleComponent != NULL);
    check(m_CharacterOwner != NULL);
}

//-------------------------------------------------------
void UBombComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    m_TimeToBlast           -= DeltaTime;
    m_TimeToBlastControlled -= DeltaTime;

    const bool bTimeToBlast = m_CharacterOwner->IsControlledBlast() ? m_TimeToBlastControlled < 0.f : m_TimeToBlast < 0.f;

    if (bTimeToBlast || m_CharacterOwner->ShouldBlast() || m_DestructibleComponent->IsBlasted())
    {
        m_CharacterOwner->OnBombBlasted();

        DirectionalBlast(FVector::RightVector);
        DirectionalBlast(FVector::RightVector * -1);
        DirectionalBlast(FVector::ForwardVector);
        DirectionalBlast(FVector::ForwardVector * -1);

        const FRotator  r(0, 0, 0);
        const FVector   l(GetOwner()->GetActorLocation());
        GetWorld()->SpawnActor(m_BlastParticle, &l, &r);

        GetOwner()->Destroy();
    }
}

//-------------------------------------------------------
void UBombComponent::DirectionalBlast(const FVector& inDirection)
{
    const FRotator  rotation(0, 0, 0);
    const FVector   startTrace = GetOwner()->GetActorLocation();
    const FVector   endTrace = startTrace + inDirection * m_BlastDistance;

    FCollisionQueryParams traceParams(NAME_None, FCollisionQueryParams::GetUnknownStatId(), true, GetOwner());
    traceParams.bTraceAsyncScene = true;

    FHitResult hitResult(ForceInit);
    if (GetWorld()->LineTraceSingleByChannel(hitResult, startTrace, endTrace, ECC_WorldDynamic, traceParams))
    {
        if (hitResult.Actor != NULL)
        {
            AActor*                 actor(hitResult.Actor.Get());
            UDestructibleComponent* otherDestructibleComponent = Cast<UDestructibleComponent>(actor->GetComponentByClass(UDestructibleComponent::StaticClass()));

            if (otherDestructibleComponent != NULL)
            {
                otherDestructibleComponent->Blast();

                const FVector location(actor->GetActorLocation());
                GetWorld()->SpawnActor(m_BlastParticle, &location, &rotation);
            }
        }
    }
    else
    {
        const FVector endTrace1 = startTrace + inDirection * (m_BlastDistance * 0.5f);
        GetWorld()->SpawnActor(m_BlastParticle, &endTrace1, &rotation);
        GetWorld()->SpawnActor(m_BlastParticle, &endTrace, &rotation);
    }
}