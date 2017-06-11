// == LOCAL

// .. IMPORTS

#include "FpsTorusGate.h"
#include "FpsCharacter.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"

// == PUBLIC

// -- CONSTRUCTORS

AFpsTorusGate::AFpsTorusGate(
    )
{
    PrimaryActorTick.bCanEverTick = true;

    StaticMesh = LoadObject<UStaticMesh>( NULL, TEXT( "StaticMesh'/Game/Geometry/Meshes/TorusGateStaticMesh.TorusGateStaticMesh'" ) );
    DoorStaticMesh = LoadObject<UStaticMesh>( NULL, TEXT( "StaticMesh'/Game/Geometry/Meshes/TorusDoorStaticMesh.TorusDoorStaticMesh'" ) );

    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "StaticMesh" ) );
    StaticMeshComponent->SetStaticMesh( StaticMesh );

    RootComponent = StaticMeshComponent;

    DoorStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "DoorStaticMesh" ) );
    DoorStaticMeshComponent->SetStaticMesh( DoorStaticMesh );
    DoorStaticMeshComponent->SetupAttachment( RootComponent );

    OpeningBoxComponent = CreateDefaultSubobject<UBoxComponent>( TEXT( "OpeningBox" ) );
    OpeningBoxComponent->bGenerateOverlapEvents = true;
    OpeningBoxComponent->OnComponentBeginOverlap.AddDynamic( this, &AFpsTorusGate::OnOpeningBoxComponentBeginOverlap );
    OpeningBoxComponent->SetupAttachment( RootComponent );

    ActivationBoxComponent = CreateDefaultSubobject<UBoxComponent>( TEXT( "ActivationBox" ) );
    ActivationBoxComponent->bGenerateOverlapEvents = true;
    ActivationBoxComponent->OnComponentBeginOverlap.AddDynamic( this, &AFpsTorusGate::OnActivationBoxComponentBeginOverlap );
    ActivationBoxComponent->SetupAttachment( RootComponent );

    SetActorEnableCollision( true );

    Reset();
}

// -- OPERATIONS

void AFpsTorusGate::Reset(
    )
{
    DoorStaticMeshComponent->SetRelativeLocation( FVector( 0, 0, 0 ) );
    OpeningBoxComponent->SetRelativeLocation( FVector( 0, 0, 100 ) );
    OpeningBoxComponent->SetRelativeScale3D( FVector( 15, 15, 2 ) );
    ActivationBoxComponent->SetRelativeLocation( FVector( 0, 0, 500 ) );
    ActivationBoxComponent->SetRelativeScale3D( FVector( 0.5, 5, 6 ) );

    State = EState_Locked;
    ElapsedTime = 0.0f;

    DoorInitialLocationVector = DoorStaticMeshComponent->GetRelativeTransform().GetTranslation();
    DoorFinalLocationVector = DoorInitialLocationVector;
    DoorFinalLocationVector.Z -= 100.0f;
}

// ~~

void AFpsTorusGate::BeginPlay(
    )
{
    Super::BeginPlay();

    Reset();
}

// ~~

void AFpsTorusGate::Tick(
    float elapsed_time
    )
{
    FVector
        door_location_vector;

    Super::Tick( elapsed_time );

    if ( State == EState_Opening )
    {
        ElapsedTime += elapsed_time;

        if ( ElapsedTime <= 1.0f )
        {
            door_location_vector = FMath::Lerp( DoorInitialLocationVector, DoorFinalLocationVector, ElapsedTime );

            DoorStaticMeshComponent->SetRelativeLocation( door_location_vector );
        }
        else
        {
            State = EState_Opened;

            DoorStaticMeshComponent->SetRelativeLocation( DoorFinalLocationVector );
        }
    }
}
