#pragma once

// == LOCAL

// .. IMPORTS

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FpsTarget.generated.h"

// == GLOBAL

// -- TYPES

UCLASS()
class FPS_API AFpsTarget :
    public AActor
{
    GENERATED_BODY()

    // == PUBLIC

    public :

    // -- TYPES

    enum EState
    {
        EState_Standing,
        EState_Falling,
        EState_Activated
    };

    // -- CONSTRUCTORS

    AFpsTarget(
        );

    // -- EVENTS

    UFUNCTION()
    void OnStaticMeshComponentHit(
        UPrimitiveComponent * component,
        AActor * other_actor,
        UPrimitiveComponent * other_component,
        FVector normal_impulse_vector,
        const FHitResult & hit_result
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
        * StaticMesh,
        * StandStaticMesh;
    UStaticMeshComponent
        * StaticMeshComponent,
        * StandStaticMeshComponent;
    EState
        State;
    FRotator
        InitialRotationRotator,
        FinalRotationRotator;
    float
        ElapsedTime;
    USoundBase
        * HitSound;
};
