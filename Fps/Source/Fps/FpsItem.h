#pragma once

// == LOCAL

// .. IMPORTS

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FpsItem.generated.h"

// == GLOBAL

// -- TYPES

UCLASS()
class FPS_API AFpsItem :
    public AActor
{
    GENERATED_BODY()

    // == PUBLIC

    public :

    // -- TYPES

    enum EState
    {
        EState_Free = 0,
        EState_Held = 1
    };

    // -- CONSTRUCTORS

    AFpsItem(
        );

    // -- OPERATIONS

    void Hold(
        );

    // ~~

    void Free(
        );

    // ~~

    void Throw(
        const FVector impulse_vector
        );

    // -- ATTRIBUTES

    UStaticMesh
        * StaticMesh;
    UStaticMeshComponent
        * StaticMeshComponent;
    EState
        State;
    USoundBase
        * HeldSound,
        * ThrownSound;
};
