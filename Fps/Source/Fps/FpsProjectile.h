#pragma once

// == LOCAL

// -- IMPORTS

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FpsProjectile.generated.h"

// == GLOBAL

// -- TYPES

UCLASS( config = Game )
class AFpsProjectile : 
    public AActor
{
    GENERATED_BODY()
    
    // == PUBLIC
    
    public :

    // -- CONSTRUCTORS
    
    AFpsProjectile(
        );

    // -- EVENTS
    
    UFUNCTION()
    void OnCollisionComponentHit( 
        UPrimitiveComponent * primitive_component, 
        AActor * other_actor, 
        UPrimitiveComponent * other_component, 
        FVector normal_impulse_vector, 
        const FHitResult & hit_result 
        );

    // -- ACCESSORS
    
    FORCEINLINE class USphereComponent * GetSphereCollisionComponent(
        ) const
    {
        return CollisionComp;
    }
    
    // ~~

    FORCEINLINE class UProjectileMovementComponent * GetProjectileMovementComponent(
        ) const
    {
        return ProjectileMovement;
    }

    // -- PROPERTIES

    UPROPERTY( VisibleDefaultsOnly, Category = Projectile )
    class USphereComponent 
        * CollisionComp;

    // ~~
    
    UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = ( AllowPrivateAccess = "true" ) )
    class UProjectileMovementComponent 
        * ProjectileMovement;
};
