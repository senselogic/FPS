#pragma once

// == LOCAL

// .. IMPORTS

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FpsGate.h"
#include "FpsTorusGate.generated.h"

// ~~

class UBoxComponent;

// == GLOBAL

// -- TYPES

UCLASS()
class FPS_API AFpsTorusGate :
    public AFpsGate
{
    GENERATED_BODY()

    // == PUBLIC

    public :

    // -- CONSTRUCTORS

    AFpsTorusGate(
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
        * DoorStaticMesh;
    UStaticMeshComponent
        * DoorStaticMeshComponent;
    UBoxComponent
        * OpeningBoxComponent,
        * ActivationBoxComponent;
    FVector
        DoorInitialLocationVector,
        DoorFinalLocationVector;
    float
        ElapsedTime;
};
