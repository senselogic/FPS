#pragma once

// == LOCAL

// .. IMPORTS

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FpsLevelStart.generated.h"

// == GLOBAL

// -- TYPES

UCLASS()
class FPS_API AFpsLevelStart :
    public AActor
{
    GENERATED_BODY()

    // == PUBLIC

    public :

    // -- CONSTRUCTORS

    AFpsLevelStart(
        );

    // -- OPERATIONS

    void Reset(
        );

    // ~~

    virtual void BeginPlay(
        ) override;

    // ~~

    virtual void Tick(
        float elapsed_time
        ) override;

    // -- ATTRIBUTES

    UStaticMesh
        * StaticMesh;
    UStaticMeshComponent
        * StaticMeshComponent;
};
