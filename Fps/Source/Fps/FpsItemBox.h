#pragma once

// == LOCAL

// .. IMPORTS

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FpsItemBox.generated.h"

// == GLOBAL

// -- TYPES

UCLASS()
class FPS_API AFpsItemBox :
    public AActor
{
    GENERATED_BODY()

    // == PUBLIC

    public :

    // -- TYPES

    enum EState
    {
        EState_Empty = 0,
        EState_Activated = 1
    };

    // -- CONSTRUCTORS

    AFpsItemBox(
        );

    // -- ATTRIBUTES

    UStaticMesh
        * StaticMesh;
    UStaticMeshComponent
        * StaticMeshComponent;
    EState
        State;
    USoundBase
        * ActivatedSound;
};
