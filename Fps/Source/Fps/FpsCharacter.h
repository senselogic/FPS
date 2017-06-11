#pragma once

// == LOCAL

// -- IMPORTS

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FpsCharacter.generated.h"

// ~~

class UInputComponent;
class AFpsItem;

// == GLOBAL

// -- TYPES

UCLASS( config = Game )
class AFpsCharacter :
    public ACharacter
{
    GENERATED_BODY()

    // == PUBLIC

    public :

    // -- TYPES

    struct TouchData
    {
        // == PUBLIC
        
        // -- CONSTRUCTORS
        
        TouchData(
            )
        {
            bIsPressed = false;
            Location = FVector::ZeroVector;
        }
        
        // -- ATTRIBUTES

        bool
            bIsPressed;
        ETouchIndex::Type
            FingerIndex;
        FVector
            Location;
        bool
            bMoved;
    };

    // ~~

    enum EState
    {
        EState_Shooting,
        EState_Holding
    };

    // -- CONSTRUCTORS

    AFpsCharacter(
        );

    // -- EVENTS

    void OnFire(
        );

    // ~~

    void OnResetVR(
        );

    // -- ACCESSORS

    FORCEINLINE class USkeletalMeshComponent * GetMesh1P(
        ) const
    {
        return Mesh1P;
    }

    // ~~

    FORCEINLINE class UCameraComponent * GetFirstPersonCameraComponent(
        ) const
    {
        return FirstPersonCameraComponent;
    }

    // -- OPERATIONS

    virtual void BeginPlay(
        );

    // ~~

    void MoveForward( 
        float value 
        );

    // ~~

    void MoveRight( 
        float value 
        );

    // ~~

    void TurnAtRate( 
        float rate 
        );

    // ~~

    void LookUpAtRate( 
        float rate 
        );

    // ~~

    void BeginTouch( 
        const ETouchIndex::Type finger_index, 
        const FVector location_vector 
        );

    // ~~

    void EndTouch( 
        const ETouchIndex::Type finger_index, 
        const FVector location_vector 
        );

    // ~~

    void TouchUpdate( 
        const ETouchIndex::Type finger_index, 
        const FVector location_vector 
        );

    // ~~

    virtual void SetupPlayerInputComponent( 
        UInputComponent * input_component 
        ) override;

    // ~~

    bool EnableTouchscreenMovement( 
        UInputComponent * input_component 
        );

    // ~~

    virtual void Tick(
        float elapsed_time
        ) override;

    // ~~

    void HoldItem(
        AFpsItem * item
        );

    // ~~

    void ThrowItem(
        );

    // -- PROPERTIES

    UPROPERTY( VisibleDefaultsOnly, Category = Mesh )
    class USkeletalMeshComponent
        * Mesh1P;

    // ~~

    UPROPERTY( VisibleDefaultsOnly, Category = Mesh )
    class USkeletalMeshComponent 
        * FP_Gun;

    // ~~

    UPROPERTY( VisibleDefaultsOnly, Category = Mesh )
    class USceneComponent 
        * FP_MuzzleLocation;

    // ~~

    UPROPERTY( VisibleDefaultsOnly, Category = Mesh )
    class USkeletalMeshComponent 
        * VR_Gun;

    // ~~

    UPROPERTY( VisibleDefaultsOnly, Category = Mesh )
    class USceneComponent 
        * VR_MuzzleLocation;

    // ~~

    UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = ( AllowPrivateAccess = "true" ) )
    class UCameraComponent 
        * FirstPersonCameraComponent;

    // ~~

    UPROPERTY( VisibleAnywhere, BlueprintReadOnly, meta = ( AllowPrivateAccess = "true" ) )
    class UMotionControllerComponent 
        * R_MotionController;

    // ~~

    UPROPERTY( VisibleAnywhere, BlueprintReadOnly, meta = ( AllowPrivateAccess = "true" ) )
    class UMotionControllerComponent 
        * L_MotionController;

    // ~~

    UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = Camera )
    float 
        BaseTurnRate;

    // ~~

    UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = Camera )
    float 
        BaseLookUpRate;

    // ~~

    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = Gameplay )
    FVector 
        GunOffset;

    // ~~

    UPROPERTY( EditDefaultsOnly, Category = Projectile )
    TSubclassOf<class AFpsProjectile> 
        ProjectileClass;

    // ~~

    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = Gameplay )
    class USoundBase 
        * FireSound;

    // ~~

    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = Gameplay )
    class UAnimMontage 
        * FireAnimation;

    // ~~

    UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = Gameplay )
    uint32 
        bUsingMotionControllers : 1;

    // -- ATTRIBUTES

    TouchData
        TouchItem;
    EState
        State;
    AFpsItem
        * HeldItem;
};
