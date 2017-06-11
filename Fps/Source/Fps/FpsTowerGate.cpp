// == LOCAL

// .. IMPORTS

#include "FpsTowerGate.h"
#include "FpsCharacter.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"

// == PUBLIC

// -- CONSTRUCTORS

AFpsTowerGate::AFpsTowerGate(
    )
{
    PrimaryActorTick.bCanEverTick = true;

    StaticMesh = LoadObject<UStaticMesh>( NULL, TEXT( "StaticMesh'/Game/Geometry/Meshes/TowerGateStaticMesh.TowerGateStaticMesh'" ) );
    DoorStaticMesh = LoadObject<UStaticMesh>( NULL, TEXT( "StaticMesh'/Game/Geometry/Meshes/TowerDoorStaticMesh.TowerDoorStaticMesh'" ) );

    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "StaticMesh" ) );
    StaticMeshComponent->SetStaticMesh( StaticMesh );

    RootComponent = StaticMeshComponent;

    DoorStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "DoorStaticMesh" ) );
    DoorStaticMeshComponent->SetStaticMesh( DoorStaticMesh );
    DoorStaticMeshComponent->SetupAttachment( RootComponent );

    OpeningBoxComponent = CreateDefaultSubobject<UBoxComponent>( TEXT( "OpeningBox" ) );
    OpeningBoxComponent->bGenerateOverlapEvents = true;
    OpeningBoxComponent->OnComponentBeginOverlap.AddDynamic( this, &AFpsTowerGate::OnOpeningBoxComponentBeginOverlap );
    OpeningBoxComponent->SetupAttachment( RootComponent );

    ActivationBoxComponent = CreateDefaultSubobject<UBoxComponent>( TEXT( "ActivationBox" ) );
    ActivationBoxComponent->bGenerateOverlapEvents = true;
    ActivationBoxComponent->OnComponentBeginOverlap.AddDynamic( this, &AFpsTowerGate::OnActivationBoxComponentBeginOverlap );
    ActivationBoxComponent->SetupAttachment( RootComponent );

    SetActorEnableCollision( true );

    Reset();
}

// -- OPERATIONS

void AFpsTowerGate::Reset(
    )
{
    DoorStaticMeshComponent->SetRelativeLocation( FVector( 0, 0, 0 ) );
    OpeningBoxComponent->SetRelativeLocation( FVector( 800, 0, 200 ) );
    OpeningBoxComponent->SetRelativeScale3D( FVector( 5, 5, 5 ) );
    ActivationBoxComponent->SetRelativeLocation( FVector( 0, 0, 200 ) );
    ActivationBoxComponent->SetRelativeScale3D( FVector( 15, 15, 5 ) );

    State = EState_Locked;
    ElapsedTime = 0.0f;

    DoorInitialLocationVector = DoorStaticMeshComponent->GetRelativeTransform().GetTranslation();

    DoorFinalLocationVector = DoorInitialLocationVector;
    DoorFinalLocationVector.Z += 900.0f;
}

// ~~


void AFpsTowerGate::BeginPlay(
    )
{
    Super::BeginPlay();

    Reset();
}

// ~~

void AFpsTowerGate::Tick(
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
