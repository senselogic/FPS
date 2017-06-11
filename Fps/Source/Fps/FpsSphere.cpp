// == LOCAL

// .. IMPORTS

#include "FpsSphere.h"
#include "FpsCharacter.h"
#include "FpsGameMode.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"

// == PUBLIC

// -- CONSTRUCTORS

AFpsSphere::AFpsSphere(
    )
{
    PrimaryActorTick.bCanEverTick = true;

    StaticMesh = LoadObject<UStaticMesh>( NULL, TEXT( "StaticMesh'/Game/Geometry/Meshes/SphereStaticMesh.SphereStaticMesh'" ) );

    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "StaticMesh" ) );
    StaticMeshComponent->SetStaticMesh( StaticMesh );
    StaticMeshComponent->SetSimulatePhysics( true );
    StaticMeshComponent->SetCollisionProfileName( TEXT( "Pawn" ) );

    RootComponent = StaticMeshComponent;

    ActivationSphereComponent = CreateDefaultSubobject<USphereComponent>( TEXT( "ActivationSphere" ) );
    ActivationSphereComponent->bGenerateOverlapEvents = true;
    ActivationSphereComponent->OnComponentBeginOverlap.AddDynamic( this, &AFpsSphere::OnActivationSphereComponentBeginOverlap );
    ActivationSphereComponent->SetupAttachment( RootComponent );

    SetActorEnableCollision( true );

    Reset();
}

// -- EVENTS

void AFpsSphere::OnActivationSphereComponentBeginOverlap(
    class UPrimitiveComponent * primitive_component,
    class AActor * other_actor,
    class UPrimitiveComponent * other_primitive_component,
    int32 other_body_index,
    bool from_sweep,
    const FHitResult & hit_result
    )
{
    if ( State == EState_Free
         && other_actor->IsA( AFpsCharacter::StaticClass() ) )
    {
        AFpsGameMode::Character->HoldItem( this );
    }
}

// -- OPERATIONS

void AFpsSphere::Reset(
    )
{
    ActivationSphereComponent->SetRelativeLocation( FVector( 0, 0, 0 ) );
    ActivationSphereComponent->SetRelativeScale3D( FVector( 2, 2, 2 ) );

    State = EState_Free;
}

// ~~

void AFpsSphere::BeginPlay(
    )
{
    Super::BeginPlay();

    Reset();
}

// ~~

void AFpsSphere::Tick(
    float elapsed_time
    )
{
    Super::Tick( elapsed_time );
}
