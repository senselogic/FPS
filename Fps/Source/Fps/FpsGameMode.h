#pragma once

// == LOCAL

// .. IMPORTS

#include "CoreMinimal.h"
#include "EngineUtils.h"
#include "GameFramework/GameModeBase.h"
#include "FpsGameMode.generated.h"

// ~~

class AFpsCharacter;
class AFpsLevelStart;
class AFpsGate;
class AFpsCubeBox;
class AFpsSphereBox;

// == GLOBAL

// -- TYPES

UCLASS( minimalapi )
class AFpsGameMode :
    public AGameModeBase
{
    GENERATED_BODY()

    // == PUBLIC

    public :

    // -- CONSTANTS

    enum
    {
        LevelCount = 3
    };

    // -- TYPES

    enum EState
    {
        EState_Played,
        EState_Failed,
        EState_Succeeded
    };

    // -- CONSTRUCTORS

    AFpsGameMode(
        );

    // -- OPERATIONS

    template <typename _ActorType_>
    _ActorType_ * GetActor(
        )
    {
        for ( TActorIterator<_ActorType_> actor_iterator( GetWorld() );
              actor_iterator;
              ++actor_iterator )
        {
            return *actor_iterator;
        }

        return NULL;
    }

    // ~~

    template <typename _ActorType_>
    _ActorType_ * GetActor(
        const FString & name
        )
    {
        for ( TActorIterator<_ActorType_> actor_iterator( GetWorld() );
              actor_iterator;
              ++actor_iterator )
        {
            if ( actor_iterator->GetName() == name )
            {
                return *actor_iterator;
            }
        }

        return NULL;
    }

    // ~~

    void MoveCharacter(
        AFpsLevelStart * level_start
        );

    // ~~

    virtual void BeginPlay(
        ) override;

    // ~~

    virtual void Tick(
        float elapsed_time
        ) override;

    // -- ATTRIBUTES

    static AFpsCharacter
        * Character;
    static AFpsLevelStart
        * LevelStartArray[ LevelCount ];
    static AFpsGate
        * GateArray[ LevelCount ];
    static AFpsCubeBox
        * CubeBoxArray[ LevelCount ];
    static AFpsSphereBox
        * SphereBoxArray[ LevelCount ];
    static EState
        State;
    static float
        RemainingTime;
    static int32
        LevelIndex,
        HitTargetCount;
    USoundBase
        * FailedSound,
        * SucceededSound;
};
