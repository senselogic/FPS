// == LOCAL

// .. IMPORTS

#include "FpsLevelStart.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"

// == PUBLIC

// -- CONSTRUCTORS

AFpsLevelStart::AFpsLevelStart(
    )
{
    PrimaryActorTick.bCanEverTick = true;

    StaticMesh = LoadObject<UStaticMesh>( NULL, TEXT( "StaticMesh'/Game/Geometry/Meshes/LevelStartStaticMesh.LevelStartStaticMesh'" ) );

    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "StaticMesh" ) );
    StaticMeshComponent->SetStaticMesh( StaticMesh );

    RootComponent = StaticMeshComponent;

    SetActorEnableCollision( true );

    Reset();
}

// -- OPERATIONS

void AFpsLevelStart::Reset(
    )
{
}

// ~~

void AFpsLevelStart::BeginPlay(
    )
{
    Super::BeginPlay();

    Reset();
}

// ~~

void AFpsLevelStart::Tick(
    float elapsed_time
    )
{
    Super::Tick( elapsed_time );
}
