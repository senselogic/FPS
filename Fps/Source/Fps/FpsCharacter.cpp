// == LOCAL

// -- IMPORTS

#include "FpsCharacter.h"
#include "FpsProjectile.h"
#include "FpsItem.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MotionControllerComponent.h"

// -- DECLARATIONS

DEFINE_LOG_CATEGORY_STATIC( LogFPChar, Warning, All );

// == PUBLIC

// -- CONSTRUCTORS

AFpsCharacter::AFpsCharacter(
    )
{
    PrimaryActorTick.bCanEverTick = true;

    GetCapsuleComponent()->InitCapsuleSize( 55.f, 96.0f );

    BaseTurnRate = 45.f;
    BaseLookUpRate = 45.f;

    FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>( TEXT( "FirstPersonCamera" ) );
    FirstPersonCameraComponent->SetupAttachment( GetCapsuleComponent() );
    FirstPersonCameraComponent->RelativeLocation = FVector( -39.56f, 1.75f, 64.f );
    FirstPersonCameraComponent->bUsePawnControlRotation = true;

    Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>( TEXT( "CharacterMesh1P" ) );
    Mesh1P->SetOnlyOwnerSee( true );
    Mesh1P->SetupAttachment( FirstPersonCameraComponent );
    Mesh1P->bCastDynamicShadow = false;
    Mesh1P->CastShadow = false;
    Mesh1P->RelativeRotation = FRotator( 1.9f, -19.19f, 5.2f );
    Mesh1P->RelativeLocation = FVector( -0.5f, -4.4f, -155.7f );

    FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>( TEXT( "FP_Gun" ) );
    FP_Gun->SetOnlyOwnerSee( true );
    FP_Gun->bCastDynamicShadow = false;
    FP_Gun->CastShadow = false;
    // FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));
    FP_Gun->SetupAttachment( RootComponent );

    FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>( TEXT( "MuzzleLocation" ) );
    FP_MuzzleLocation->SetupAttachment( FP_Gun );
    FP_MuzzleLocation->SetRelativeLocation( FVector( 0.2f, 48.4f, -10.6f ) );

    GunOffset = FVector( 100.0f, 0.0f, 10.0f );

    R_MotionController = CreateDefaultSubobject<UMotionControllerComponent>( TEXT( "R_MotionController" ) );
    R_MotionController->Hand = EControllerHand::Right;
    R_MotionController->SetupAttachment( RootComponent );
    L_MotionController = CreateDefaultSubobject<UMotionControllerComponent>( TEXT( "L_MotionController" ) );
    L_MotionController->SetupAttachment( RootComponent );

    VR_Gun = CreateDefaultSubobject<USkeletalMeshComponent>( TEXT( "VR_Gun" ) );
    VR_Gun->SetOnlyOwnerSee( true );    // only the owning player will see this mesh
    VR_Gun->bCastDynamicShadow = false;
    VR_Gun->CastShadow = false;
    VR_Gun->SetupAttachment( R_MotionController );
    VR_Gun->SetRelativeRotation( FRotator( 0.0f, -90.0f, 0.0f ) );

    VR_MuzzleLocation = CreateDefaultSubobject<USceneComponent>( TEXT( "VR_MuzzleLocation" ) );
    VR_MuzzleLocation->SetupAttachment( VR_Gun );
    VR_MuzzleLocation->SetRelativeLocation( FVector( 0.000004, 53.999992, 10.000000 ) );
    VR_MuzzleLocation->SetRelativeRotation( FRotator( 0.0f, 90.0f, 0.0f ) );

    // Uncomment the following line to turn motion controllers on by default:
    //bUsingMotionControllers = true;
}

// -- EVENTS

void AFpsCharacter::OnFire(
    )
{
    if ( State == EState_Holding )
    {
        ThrowItem();
    }
    else if ( State == EState_Shooting )
    {
        if ( ProjectileClass != NULL )
        {
            UWorld * const World = GetWorld();
            if ( World != NULL )
            {
                if ( bUsingMotionControllers )
                {
                    const FRotator SpawnRotation = VR_MuzzleLocation->GetComponentRotation();
                    const FVector SpawnLocation = VR_MuzzleLocation->GetComponentLocation();
                    World->SpawnActor<AFpsProjectile>( ProjectileClass, SpawnLocation, SpawnRotation );
                }
                else
                {
                    const FRotator SpawnRotation = GetControlRotation();
                    const FVector SpawnLocation = ( ( FP_MuzzleLocation != nullptr ) ? FP_MuzzleLocation->GetComponentLocation() : GetActorLocation() ) + SpawnRotation.RotateVector( GunOffset );

                    FActorSpawnParameters ActorSpawnParams;
                    ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

                    World->SpawnActor<AFpsProjectile>( ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams );
                }
            }
        }

        if ( FireSound != NULL )
        {
            UGameplayStatics::PlaySoundAtLocation( this, FireSound, GetActorLocation() );
        }

        if ( FireAnimation != NULL )
        {
            UAnimInstance * AnimInstance = Mesh1P->GetAnimInstance();
            if ( AnimInstance != NULL )
            {
                AnimInstance->Montage_Play( FireAnimation, 1.f );
            }
        }
    }
}

// ~~

void AFpsCharacter::OnResetVR(
    )
{
    UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

// -- OPERATIONS

void AFpsCharacter::BeginPlay(
    )
{
    Super::BeginPlay();

    FP_Gun->AttachToComponent( Mesh1P, FAttachmentTransformRules( EAttachmentRule::SnapToTarget, true ), TEXT( "GripPoint" ) );

    if ( bUsingMotionControllers )
    {
        VR_Gun->SetHiddenInGame( false, true );
        Mesh1P->SetHiddenInGame( true, true );
    }
    else
    {
        VR_Gun->SetHiddenInGame( true, true );
        Mesh1P->SetHiddenInGame( false, true );
    }
}

// ~~

void AFpsCharacter::MoveForward(
    float value
    )
{
    if ( value != 0.0f )
    {
        AddMovementInput( GetActorForwardVector(), value );
    }
}

// ~~

void AFpsCharacter::MoveRight(
    float value
    )
{
    if ( value != 0.0f )
    {
        AddMovementInput( GetActorRightVector(), value );
    }
}

// ~~

void AFpsCharacter::TurnAtRate(
    float rate
    )
{
    AddControllerYawInput( rate * BaseTurnRate * GetWorld()->GetDeltaSeconds() );
}

// ~~

void AFpsCharacter::LookUpAtRate(
    float rate
    )
{
    AddControllerPitchInput( rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds() );
}

// ~~

void AFpsCharacter::BeginTouch(
    const ETouchIndex::Type finger_index,
    const FVector location_vector
    )
{
    if ( TouchItem.bIsPressed == true )
    {
        return;
    }

    TouchItem.bIsPressed = true;
    TouchItem.FingerIndex = finger_index;
    TouchItem.Location = location_vector;
    TouchItem.bMoved = false;
}

// ~~

void AFpsCharacter::EndTouch(
    const ETouchIndex::Type finger_index,
    const FVector location_vector
    )
{
    if ( TouchItem.bIsPressed == false )
    {
        return;
    }

    if ( ( TouchItem.FingerIndex == finger_index )
         && ( TouchItem.bMoved == false ) )
    {
        OnFire();
    }

    TouchItem.bIsPressed = false;
}

// ~~

//Commenting this section out to be consistent with FPS BP template.
//This allows the user to turn without using the right virtual joystick

//void AFpsCharacter::TouchUpdate(
//    const ETouchIndex::Type finger_index,
//    const FVector location_vector
//    )
//{
//    if ((TouchItem.bIsPressed == true) && (TouchItem.FingerIndex == finger_index))
//    {
//        if (TouchItem.bIsPressed)
//        {
//            if (GetWorld() != nullptr)
//            {
//                UGameViewportClient* ViewportClient = GetWorld()->GetGameViewport();
//                if (ViewportClient != nullptr)
//                {
//                    FVector MoveDelta = location_vector - TouchItem.Location;
//                    FVector2D ScreenSize;
//                    ViewportClient->GetViewportSize(ScreenSize);
//                    FVector2D ScaledDelta = FVector2D(MoveDelta.X, MoveDelta.Y) / ScreenSize;
//                    if (FMath::Abs(ScaledDelta.X) >= 4.0 / ScreenSize.X)
//                    {
//                        TouchItem.bMoved = true;
//                        float Value = ScaledDelta.X * BaseTurnRate;
//                        AddControllerYawInput(Value);
//                    }
//                    if (FMath::Abs(ScaledDelta.Y) >= 4.0 / ScreenSize.Y)
//                    {
//                        TouchItem.bMoved = true;
//                        float Value = ScaledDelta.Y * BaseTurnRate;
//                        AddControllerPitchInput(Value);
//                    }
//                    TouchItem.Location = location_vector;
//                }
//                TouchItem.Location = location_vector;
//            }
//        }
//    }
//}

// ~~

void AFpsCharacter::SetupPlayerInputComponent(
    class UInputComponent * input_component
    )
{
    check( input_component );

    input_component->BindAction( "Jump", IE_Pressed, this, &ACharacter::Jump );
    input_component->BindAction( "Jump", IE_Released, this, &ACharacter::StopJumping );

    //InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AFpsCharacter::TouchStarted);
    if ( EnableTouchscreenMovement( input_component ) == false )
    {
        input_component->BindAction( "Fire", IE_Pressed, this, &AFpsCharacter::OnFire );
    }

    input_component->BindAction( "ResetVR", IE_Pressed, this, &AFpsCharacter::OnResetVR );

    input_component->BindAxis( "MoveForward", this, &AFpsCharacter::MoveForward );
    input_component->BindAxis( "MoveRight", this, &AFpsCharacter::MoveRight );

    input_component->BindAxis( "Turn", this, &APawn::AddControllerYawInput );
    input_component->BindAxis( "TurnRate", this, &AFpsCharacter::TurnAtRate );
    input_component->BindAxis( "LookUp", this, &APawn::AddControllerPitchInput );
    input_component->BindAxis( "LookUpRate", this, &AFpsCharacter::LookUpAtRate );
}

// ~~

bool AFpsCharacter::EnableTouchscreenMovement(
    class UInputComponent * input_component
    )
{
    bool
        result;

    result = false;

    if ( FPlatformMisc::GetUseVirtualJoysticks()
         || GetDefault<UInputSettings>()->bUseMouseForTouch )
    {
        result = true;
        input_component->BindTouch( EInputEvent::IE_Pressed, this, &AFpsCharacter::BeginTouch );
        input_component->BindTouch( EInputEvent::IE_Released, this, &AFpsCharacter::EndTouch );

        //Commenting this out to be more consistent with FPS BP template.
        //player_input_component->BindTouch(EInputEvent::IE_Repeat, this, &AFpsCharacter::TouchUpdate);
    }

    return result;
}

// ~~

void AFpsCharacter::Tick(
    float elapsed_time
    )
{
    FVector
        held_item_location_vector;

    Super::Tick( elapsed_time );

    if ( State == EState_Holding )
    {
        held_item_location_vector = GetActorLocation() + FirstPersonCameraComponent->GetForwardVector() * 300.0f;

        HeldItem->SetActorLocation( held_item_location_vector );
    }
}

// ~~

void AFpsCharacter::HoldItem(
    AFpsItem * item
    )
{
    if ( State == EState_Shooting )
    {
        HeldItem = item;
        HeldItem->Hold();

        UGameplayStatics::PlaySoundAtLocation( this, HeldItem->HeldSound, GetActorLocation() );

        State = EState_Holding;
    }
}

// ~~

void AFpsCharacter::ThrowItem(
    )
{
    HeldItem->Free();
    HeldItem->Throw( FirstPersonCameraComponent->GetForwardVector() * 1500.0f );

    UGameplayStatics::PlaySoundAtLocation( this, HeldItem->ThrownSound, GetActorLocation() );

    HeldItem = NULL;

    State = EState_Shooting;
}
