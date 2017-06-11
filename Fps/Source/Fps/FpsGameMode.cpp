// == LOCAL

// .. IMPORTS

#include "FpsGameMode.h"
#include "FpsHUD.h"
#include "FpsCharacter.h"
#include "FpsLevelStart.h"
#include "FpsGate.h"
#include "FpsCubeBox.h"
#include "FpsSphereBox.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

// == PUBLIC

// -- CONSTRUCTORS

AFpsGameMode::AFpsGameMode(
    ) :
    Super()
{
    static ConstructorHelpers::FClassFinder<APawn>
        PlayerPawnClassFinder( TEXT( "/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter" ) );

    PrimaryActorTick.bCanEverTick = true;

    DefaultPawnClass = PlayerPawnClassFinder.Class;

    HUDClass = AFpsHUD::StaticClass();

    FailedSound = LoadObject<USoundBase>( NULL, TEXT( "/Game/Audio/Sounds/GameFailedSound" ) );
    SucceededSound = LoadObject<USoundBase>( NULL, TEXT( "/Game/Audio/Sounds/GameSucceededSound" ) );
}

// -- OPERATIONS

void AFpsGameMode::MoveCharacter(
    AFpsLevelStart * level_start
    )
{
    Character->SetActorLocation( level_start->GetActorLocation() );
    Character->SetActorRotation( level_start->GetActorRotation() );
}

// ~~

void AFpsGameMode::BeginPlay(
    )
{
    Super::BeginPlay();
    Character = GetActor<AFpsCharacter>();
    LevelStartArray[ 0 ] = GetActor<AFpsLevelStart>( TEXT( "FpsLevelStart1" ) );
    LevelStartArray[ 1 ] = GetActor<AFpsLevelStart>( TEXT( "FpsLevelStart2" ) );
    LevelStartArray[ 2 ] = GetActor<AFpsLevelStart>( TEXT( "FpsLevelStart3" ) );
    GateArray[ 0 ] = GetActor<AFpsGate>( TEXT( "FpsGate1" ) );
    GateArray[ 1 ] = GetActor<AFpsGate>( TEXT( "FpsGate2" ) );
    GateArray[ 2 ] = GetActor<AFpsGate>( TEXT( "FpsGate3" ) );
    CubeBoxArray[ 0 ] = GetActor<AFpsCubeBox>( TEXT( "FpsCubeBox1" ) );
    CubeBoxArray[ 1 ] = GetActor<AFpsCubeBox>( TEXT( "FpsCubeBox2" ) );
    CubeBoxArray[ 2 ] = GetActor<AFpsCubeBox>( TEXT( "FpsCubeBox3" ) );
    SphereBoxArray[ 0 ] = GetActor<AFpsSphereBox>( TEXT( "FpsSphereBox1" ) );
    SphereBoxArray[ 1 ] = GetActor<AFpsSphereBox>( TEXT( "FpsSphereBox2" ) );
    SphereBoxArray[ 2 ] = GetActor<AFpsSphereBox>( TEXT( "FpsSphereBox3" ) );

    State = EState_Played;
    RemainingTime = 180.0f;
    LevelIndex = 0;
    HitTargetCount = 0;

    MoveCharacter( LevelStartArray[ 0 ] );
}

// ~~

void AFpsGameMode::Tick(
    float elapsed_time
    )
{
    Super::Tick( elapsed_time );

    if ( State == EState_Played )
    {
        RemainingTime -= elapsed_time;

        if ( RemainingTime < 0.0f )
        {
            RemainingTime = 0.0f;

            State = EState_Failed;

            UGameplayStatics::PlaySoundAtLocation( this, FailedSound, Character->GetActorLocation() );
        }

        if ( GateArray[ LevelIndex ]->State == AFpsGate::EState_Locked
             && CubeBoxArray[ LevelIndex ]->State == AFpsCubeBox::EState_Activated
             && SphereBoxArray[ LevelIndex ]->State == AFpsSphereBox::EState_Activated
             && HitTargetCount == ( LevelIndex + 1 ) * 2 )
        {
            GateArray[ LevelIndex ]->State = AFpsGate::EState_Unlocked;
        }
        else if ( GateArray[ LevelIndex ]->State == AFpsGate::EState_Activated )
        {
            ++LevelIndex;

            if ( LevelIndex < LevelCount )
            {
                MoveCharacter( LevelStartArray[ LevelIndex ] );

                UGameplayStatics::PlaySoundAtLocation( this, GateArray[ LevelIndex ]->ActivatedSound, Character->GetActorLocation() );
            }
            else
            {
                State = EState_Succeeded;

                UGameplayStatics::PlaySoundAtLocation( this, SucceededSound, Character->GetActorLocation() );
            }
        }
    }
}

// -- ATTRIBUTES

AFpsCharacter
    * AFpsGameMode::Character;
AFpsLevelStart
    * AFpsGameMode::LevelStartArray[ LevelCount ];
AFpsGate
    * AFpsGameMode::GateArray[ LevelCount ];
AFpsCubeBox
    * AFpsGameMode::CubeBoxArray[ LevelCount ];
AFpsSphereBox
    * AFpsGameMode::SphereBoxArray[ LevelCount ];
AFpsGameMode::EState
    AFpsGameMode::State;
float
    AFpsGameMode::RemainingTime;
int32
    AFpsGameMode::LevelIndex,
    AFpsGameMode::HitTargetCount;
