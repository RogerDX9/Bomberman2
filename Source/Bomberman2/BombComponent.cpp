// Fill out your copyright notice in the Description page of Project Settings.

#include "BombComponent.h"
#include "CollisionQueryParams.h"
#include "CharacterComponent.h"
#include "DestructibleComponent.h"

//-------------------------------------------------------
UBombComponent::UBombComponent()
    : m_TimeToBlast             (3)
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

    m_TimeToBlast -= DeltaTime;
    const bool bTimeToBlast = m_TimeToBlast < 0.f;
    const bool bRemoteBlast = m_CharacterOwner->IsControlledBlast() ? m_CharacterOwner->ShouldBlast() : false;

    if (bTimeToBlast || bRemoteBlast || m_DestructibleComponent->IsBlasted())
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
                SpawnBlastEffect(inDirection, actor->GetActorLocation());
            }
        }
    }
    else
    {
        SpawnBlastEffect(inDirection, startTrace + inDirection * m_BlastDistance);
    }
}

//-------------------------------------------------------
void UBombComponent::SpawnBlastEffect(const FVector& inDirection, const FVector & inEndLocation)
{
    const float     spawnRate = 60;
    const FVector   startTrace = GetOwner()->GetActorLocation();
    const float     blastDist = (inEndLocation - startTrace).Size();
    const uint32    nbOfBlasts = blastDist / spawnRate;
    const FRotator  rotation(0, 0, 0);

    for (uint32 idx = 1; idx < nbOfBlasts; ++idx)
    {
        const FVector blastPos = startTrace + inDirection * (spawnRate * idx);
        GetWorld()->SpawnActor(m_BlastParticle, &blastPos, &rotation);
    }
}