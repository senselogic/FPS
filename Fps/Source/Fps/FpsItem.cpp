// == LOCAL

// .. IMPORTS

#include "FpsItem.h"

// == PUBLIC

// -- CONSTRUCTORS

AFpsItem::AFpsItem(
    )
{
    StaticMesh = NULL;
    StaticMeshComponent = NULL;

    State = EState_Free;

    HeldSound = LoadObject<USoundBase>( NULL, TEXT( "/Game/Audio/Sounds/ItemHeldSound" ) );
    ThrownSound = LoadObject<USoundBase>( NULL, TEXT( "/Game/Audio/Sounds/ItemThrownSound" ) );
}

// -- OPERATIONS

void AFpsItem::Hold(
    )
{
    State = EState_Held;

    SetActorEnableCollision( false );
    StaticMeshComponent->SetSimulatePhysics( false );
}

// ~~

void AFpsItem::Free(
    )
{
    State = EState_Free;

    SetActorEnableCollision( true );
    StaticMeshComponent->SetSimulatePhysics( true );
}

// ~~

void AFpsItem::Throw(
    const FVector impulse_vector
    )
{
    StaticMeshComponent->SetPhysicsLinearVelocity( impulse_vector );
}
