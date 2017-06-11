#pragma once

// == LOCAL

// .. IMPORTS

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FpsGate.h"
#include "FpsTombGate.generated.h"

// ~~

class UBoxComponent;

// == GLOBAL

// -- TYPES

UCLASS()
class FPS_API AFpsTombGate :
    public AFpsGate
{
    GENERATED_BODY()

    // == PUBLIC

    public :

    // -- CONSTRUCTORS

    AFpsTombGate(
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
        * LeftDoorStaticMesh,
        * RightDoorStaticMesh;
    UStaticMeshComponent
        * LeftDoorStaticMeshComponent,
        * RightDoorStaticMeshComponent;
    UBoxComponent
        * OpeningBoxComponent,
        * ActivationBoxComponent;
    float
        ElapsedTime;
    FVector
        LeftDoorInitialLocationVector,
        LeftDoorFinalLocationVector,
        RightDoorInitialLocationVector,
        RightDoorFinalLocationVector;
};
