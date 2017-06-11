// == LOCAL

// .. IMPORTS

#include "FpsTarget.h"
#include "FpsProjectile.h"
#include "FpsItem.h"
#include "FpsGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"

// == PUBLIC

// -- CONSTRUCTORS

AFpsTarget::AFpsTarget(
    )
{
    PrimaryActorTick.bCanEverTick = true;

    StaticMesh = LoadObject<UStaticMesh>( NULL, TEXT( "StaticMesh'/Game/Geometry/Meshes/TargetStaticMesh.TargetStaticMesh'" ) );
    StandStaticMesh = LoadObject<UStaticMesh>( NULL, TEXT( "StaticMesh'/Game/Geometry/Meshes/TargetStandStaticMesh.TargetStandStaticMesh'" ) );

    StandStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "StandStaticMesh" ) );
    StandStaticMeshComponent->SetStaticMesh( StandStaticMesh );

    RootComponent = StandStaticMeshComponent;

    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "StaticMesh" ) );
    StaticMeshComponent->SetStaticMesh( StaticMesh );
    StaticMeshComponent->SetupAttachment( RootComponent );
    StaticMeshComponent->OnComponentHit.AddDynamic( this, &AFpsTarget::OnStaticMeshComponentHit );

    SetActorEnableCollision( true );

    HitSound = LoadObject<USoundBase>( NULL, TEXT( "/Game/Audio/Sounds/TargetHitSound" ) );

    Reset();
}

// -- EVENTS

void AFpsTarget::OnStaticMeshComponentHit(
        UPrimitiveComponent * component,
        AActor * other_actor,
        UPrimitiveComponent * other_component,
        FVector normal_impulse_vector,
        const FHitResult & hit_result
        )
{
    if ( State == EState_Standing
         && ( other_actor->IsA( AFpsProjectile::StaticClass() )
              || other_actor->IsA( AFpsItem::StaticClass() ) ) )
    {
        State = EState_Falling;

        UGameplayStatics::PlaySoundAtLocation( this, HitSound, GetActorLocation() );

        ++AFpsGameMode::HitTargetCount;
    }
}

// -- OPERATIONS

void AFpsTarget::Reset(
    )
{
    StaticMeshComponent->SetRelativeLocation( FVector( 0, 0, 200 ) );

    State = EState_Standing;
    ElapsedTime = 0.0f;

    InitialRotationRotator = FRotator( 0.0f, 0.0f, 0.0f );
    FinalRotationRotator = InitialRotationRotator;
    FinalRotationRotator.Pitch = -180.0f;
}

// ~~

void AFpsTarget::BeginPlay(
    )
{
    Super::BeginPlay();

    Reset();
}

// ~~

void AFpsTarget::Tick(
    float elapsed_time
    )
{
    FRotator
        rotation_rotator;

    Super::Tick( elapsed_time );

    if ( State == EState_Falling )
    {
        ElapsedTime += elapsed_time;

        if ( ElapsedTime <= 0.5f )
        {
            rotation_rotator = FMath::Lerp( InitialRotationRotator, FinalRotationRotator, ElapsedTime / 0.5f );

            StaticMeshComponent->SetRelativeRotation( rotation_rotator );
        }
        else
        {
            State = EState_Activated;

            StaticMeshComponent->SetRelativeRotation( FinalRotationRotator );
        }
    }
}
