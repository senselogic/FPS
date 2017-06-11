#pragma once

// == LOCAL

// .. IMPORTS

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FpsItem.h"
#include "FpsSphere.generated.h"

// ~~

class USphereComponent;

// == GLOBAL

// -- TYPES

UCLASS()
class FPS_API AFpsSphere :
    public AFpsItem
{
    GENERATED_BODY()

    // == PUBLIC

    public :

    // -- CONSTRUCTORS

    AFpsSphere(
        );

    // -- EVENTS

    UFUNCTION()
    void OnActivationSphereComponentBeginOverlap(
        class UPrimitiveComponent * primitive_component,
        class AActor * other_actor,
        class UPrimitiveComponent * other_primitive_component,
        int32 other_body_index,
        bool from_sweep,
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

    USphereComponent
        * ActivationSphereComponent;
};
