#include "DestructibleComponent.h"


//-------------------------------------------------------
UDestructibleComponent::UDestructibleComponent()
    : m_bAutoDestroy(true)
    , m_bExploded(false)
{
}

//-------------------------------------------------------
void UDestructibleComponent::OnExplode()
{
    m_bExploded = true;

    if (m_bAutoDestroy)
    {
        GetOwner()->Destroy();
    }
}
