#pragma once

// == LOCAL

// .. IMPORTS

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FpsGate.generated.h"

// == GLOBAL

// -- TYPES

UCLASS()
class FPS_API AFpsGate :
    public AActor
{
    GENERATED_BODY()

    // == PUBLIC

    public :

    // -- TYPES

    enum EState
    {
        EState_Locked,
        EState_Unlocked,
        EState_Opening,
        EState_Opened,
        EState_Activated
    };

    // -- CONSTRUCTORS

    AFpsGate(
        );

    // -- EVENTS

    UFUNCTION()
    void OnOpeningBoxComponentBeginOverlap(
        class UPrimitiveComponent * primitive_component,
        class AActor * other_actor,
        class UPrimitiveComponent * other_primitive_component,
        int32 other_body_index,
        bool from_sweep,
        const FHitResult & hit_result
        );

    // ~~

    UFUNCTION()
    void OnActivationBoxComponentBeginOverlap(
        class UPrimitiveComponent * primitive_component,
        class AActor * other_actor,
        class UPrimitiveComponent * other_primitive_component,
        int32 other_body_index,
        bool from_sweep,
        const FHitResult & hit_result
        );

    // -- ATTRIBUTES

    UStaticMesh
        * StaticMesh;
    UStaticMeshComponent
        * StaticMeshComponent;
    EState
        State;
    USoundBase
        * LockedSound,
        * OpeningSound,
        * ActivatedSound;
};
