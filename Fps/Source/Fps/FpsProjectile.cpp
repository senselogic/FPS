// == LOCAL

// -- IMPORTS

#include "FpsProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

// == PUBLIC

// -- CONSTRUCTORS

AFpsProjectile::AFpsProjectile(
    )
{
    CollisionComp = CreateDefaultSubobject<USphereComponent>( TEXT( "SphereComp" ) );
    CollisionComp->InitSphereRadius( 5.0f );
    CollisionComp->BodyInstance.SetCollisionProfileName( "Projectile" );
    CollisionComp->OnComponentHit.AddDynamic( this, &AFpsProjectile::OnCollisionComponentHit );

    CollisionComp->SetWalkableSlopeOverride( FWalkableSlopeOverride( WalkableSlope_Unwalkable, 0.f ) );
    CollisionComp->CanCharacterStepUpOn = ECB_No;

    RootComponent = CollisionComp;

    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>( TEXT( "ProjectileComp" ) );
    ProjectileMovement->UpdatedComponent = CollisionComp;
    ProjectileMovement->InitialSpeed = 3000.f;
    ProjectileMovement->MaxSpeed = 3000.f;
    ProjectileMovement->bRotationFollowsVelocity = true;
    ProjectileMovement->bShouldBounce = true;

    InitialLifeSpan = 3.0f;
}

// -- EVENTS

void AFpsProjectile::OnCollisionComponentHit( 
    UPrimitiveComponent * primitive_component, 
    AActor * other_actor, 
    UPrimitiveComponent * other_primitive_component, 
    FVector normal_impulse_vector, 
    const FHitResult & hit_result
    )
{
    if ( other_actor != NULL
         && other_actor != this
         && other_primitive_component != NULL
         && other_primitive_component->IsSimulatingPhysics() )
    {
        other_primitive_component->AddImpulseAtLocation( GetVelocity() * 100.0f, GetActorLocation() );

        Destroy();
    }
}
