// == LOCAL

// .. IMPORTS

#include "FpsCubeBox.h"
#include "FpsCube.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"

// == PUBLIC

// -- CONSTRUCTORS

AFpsCubeBox::AFpsCubeBox(
    )
{
    PrimaryActorTick.bCanEverTick = true;

    StaticMesh = LoadObject<UStaticMesh>( NULL, TEXT( "StaticMesh'/Game/Geometry/Meshes/CubeBoxStaticMesh.CubeBoxStaticMesh'" ) );

    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "StaticMesh" ) );
    StaticMeshComponent->SetStaticMesh( StaticMesh );

    RootComponent = StaticMeshComponent;

    ActivationBoxComponent = CreateDefaultSubobject<UBoxComponent>( TEXT( "ActivationBox" ) );
    ActivationBoxComponent->bGenerateOverlapEvents = true;
    ActivationBoxComponent->OnComponentBeginOverlap.AddDynamic( this, &AFpsCubeBox::OnActivationBoxComponentBeginOverlap );
    ActivationBoxComponent->SetupAttachment( RootComponent );

    SetActorEnableCollision( true );

    Reset();
}

// -- EVENTS

void AFpsCubeBox::OnActivationBoxComponentBeginOverlap(
    class UPrimitiveComponent * primitive_component,
    class AActor * other_actor,
    class UPrimitiveComponent * other_primitive_component,
    int32 other_body_index,
    bool from_sweep,
    const FHitResult & hit_result
    )
{
    if ( State == EState_Empty
         && other_actor->IsA( AFpsCube::StaticClass() ) )
    {
        State = EState_Activated;

        UGameplayStatics::PlaySoundAtLocation( this, ActivatedSound, GetActorLocation() );
    }
}

// -- OPERATIONS

void AFpsCubeBox::Reset(
    )
{
    ActivationBoxComponent->SetRelativeLocation( FVector( 0, 0, 200 ) );
    ActivationBoxComponent->SetRelativeScale3D( FVector( 7, 7, 5 ) );

    State = EState_Empty;
}

// ~~

void AFpsCubeBox::BeginPlay(
    )
{
    Super::BeginPlay();

    Reset();
}

// ~~

void AFpsCubeBox::Tick(
    float elapsed_time
    )
{
    Super::Tick( elapsed_time );
}
