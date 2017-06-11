// == LOCAL

// .. IMPORTS

#include "FpsTombGate.h"
#include "FpsCharacter.h"
#include "Runtime/Engine/Classes/Components/BoxComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"

// == PUBLIC

// -- CONSTRUCTORS

AFpsTombGate::AFpsTombGate(
    )
{
    PrimaryActorTick.bCanEverTick = true;

    StaticMesh = LoadObject<UStaticMesh>( NULL, TEXT( "StaticMesh'/Game/Geometry/Meshes/TombGateStaticMesh.TombGateStaticMesh'" ) );
    RightDoorStaticMesh = LoadObject<UStaticMesh>( NULL, TEXT( "StaticMesh'/Game/Geometry/Meshes/TombRightDoorStaticMesh.TombRightDoorStaticMesh'" ) );
    LeftDoorStaticMesh = LoadObject<UStaticMesh>( NULL, TEXT( "StaticMesh'/Game/Geometry/Meshes/TombLeftDoorStaticMesh.TombLeftDoorStaticMesh'" ) );

    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "StaticMesh" ) );
    StaticMeshComponent->SetStaticMesh( StaticMesh );

    RootComponent = StaticMeshComponent;

    LeftDoorStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "LeftDoorStaticMesh" ) );
    LeftDoorStaticMeshComponent->SetStaticMesh( LeftDoorStaticMesh );
    LeftDoorStaticMeshComponent->SetupAttachment( RootComponent );

    RightDoorStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "RightDoorStaticMesh" ) );
    RightDoorStaticMeshComponent->SetStaticMesh( RightDoorStaticMesh );
    RightDoorStaticMeshComponent->SetupAttachment( RootComponent );

    OpeningBoxComponent = CreateDefaultSubobject<UBoxComponent>( TEXT( "OpeningBox" ) );
    OpeningBoxComponent->bGenerateOverlapEvents = true;
    OpeningBoxComponent->OnComponentBeginOverlap.AddDynamic( this, &AFpsTombGate::OnOpeningBoxComponentBeginOverlap );
    OpeningBoxComponent->SetupAttachment( RootComponent );

    ActivationBoxComponent = CreateDefaultSubobject<UBoxComponent>( TEXT( "ActivationBox" ) );
    ActivationBoxComponent->bGenerateOverlapEvents = true;
    ActivationBoxComponent->OnComponentBeginOverlap.AddDynamic( this, &AFpsTombGate::OnActivationBoxComponentBeginOverlap );
    ActivationBoxComponent->SetupAttachment( RootComponent );

    SetActorEnableCollision( true );

    Reset();
}

// -- OPERATIONS

void AFpsTombGate::Reset(
    )
{
    LeftDoorStaticMeshComponent->SetRelativeLocation( FVector( 25, 0, 0 ) );
    RightDoorStaticMeshComponent->SetRelativeLocation( FVector( 25, 0, 0 ) );
    OpeningBoxComponent->SetRelativeLocation( FVector( 150, 0, 200 ) );
    OpeningBoxComponent->SetRelativeScale3D( FVector( 5, 5, 5 ) );
    ActivationBoxComponent->SetRelativeLocation( FVector( -200, 0, 200 ) );
    ActivationBoxComponent->SetRelativeScale3D( FVector( 5, 10, 5 ) );

    State = EState_Locked;
    ElapsedTime = 0.0f;

    LeftDoorInitialLocationVector = LeftDoorStaticMeshComponent->GetRelativeTransform().GetTranslation();
    LeftDoorFinalLocationVector = LeftDoorInitialLocationVector;
    LeftDoorFinalLocationVector.Y += 250.0f;

    RightDoorInitialLocationVector = RightDoorStaticMeshComponent->GetRelativeTransform().GetTranslation();
    RightDoorFinalLocationVector = RightDoorInitialLocationVector;
    RightDoorFinalLocationVector.Y -= 250.0f;
}

// ~~

void AFpsTombGate::BeginPlay(
    )
{
    Super::BeginPlay();

    Reset();
}

// ~~

void AFpsTombGate::Tick(
    float elapsed_time
    )
{
    FVector
        left_door_location_vector,
        right_door_location_vector;

    Super::Tick( elapsed_time );

    if ( State == EState_Opening )
    {
        ElapsedTime += elapsed_time;

        if ( ElapsedTime <= 1.0f )
        {
            left_door_location_vector = FMath::Lerp( LeftDoorInitialLocationVector, LeftDoorFinalLocationVector, ElapsedTime );
            right_door_location_vector = FMath::Lerp( RightDoorInitialLocationVector, RightDoorFinalLocationVector, ElapsedTime );

            LeftDoorStaticMeshComponent->SetRelativeLocation( left_door_location_vector );
            RightDoorStaticMeshComponent->SetRelativeLocation( right_door_location_vector );
        }
        else
        {
            State = EState_Opened;

            LeftDoorStaticMeshComponent->SetRelativeLocation( LeftDoorFinalLocationVector );
            RightDoorStaticMeshComponent->SetRelativeLocation( RightDoorFinalLocationVector );
        }
    }
}
