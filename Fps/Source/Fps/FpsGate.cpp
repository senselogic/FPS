// == LOCAL

// .. IMPORTS

#include "FpsGate.h"
#include "FpsCharacter.h"
#include "Kismet/GameplayStatics.h"

// == PUBLIC

// -- CONSTRUCTORS

AFpsGate::AFpsGate(
    )
{
    StaticMesh = NULL;
    StaticMeshComponent = NULL;

    State = EState_Locked;

    LockedSound = LoadObject<USoundBase>( NULL, TEXT( "/Game/Audio/Sounds/GateLockedSound" ) );
    OpeningSound = LoadObject<USoundBase>( NULL, TEXT( "/Game/Audio/Sounds/GateOpeningSound" ) );
    ActivatedSound = LoadObject<USoundBase>( NULL, TEXT( "/Game/Audio/Sounds/GateActivatedSound" ) );
}

// -- EVENTS

void AFpsGate::OnOpeningBoxComponentBeginOverlap(
    class UPrimitiveComponent * primitive_component,
    class AActor * other_actor,
    class UPrimitiveComponent * other_primitive_component,
    int32 other_body_index,
    bool from_sweep,
    const FHitResult & hit_result
    )
{
    if ( State == EState_Unlocked
         && other_actor->IsA( AFpsCharacter::StaticClass() ) )
    {
        State = EState_Opening;

        UGameplayStatics::PlaySoundAtLocation( this, OpeningSound, GetActorLocation() );
    }
    else if ( State == EState_Locked
              && other_actor->IsA( AFpsCharacter::StaticClass() ) )
    {
        UGameplayStatics::PlaySoundAtLocation( this, LockedSound, GetActorLocation() );
    }
}

// ~~

void AFpsGate::OnActivationBoxComponentBeginOverlap(
    class UPrimitiveComponent * primitive_component,
    class AActor * other_actor,
    class UPrimitiveComponent * other_primitive_component,
    int32 other_body_index,
    bool from_sweep,
    const FHitResult & hit_result
    )
{
    if ( other_actor->IsA( AFpsCharacter::StaticClass() ) )
    {
        State = EState_Activated;
    }
}
