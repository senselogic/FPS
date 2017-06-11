// == LOCAL

// .. IMPORTS

#include "FpsHUD.h"
#include "FpsGameMode.h"
#include "Engine/Canvas.h"
#include "Engine/Engine.h"
#include "Engine/Texture2D.h"
#include "TextureResource.h"
#include "CanvasItem.h"
#include "UObject/ConstructorHelpers.h"

// == PUBLIC

// -- CONSTRUCTORS

AFpsHUD::AFpsHUD(
    )
{
    static ConstructorHelpers::FObjectFinder<UTexture2D>
        crosshair_texture( TEXT( "/Game/FirstPerson/Textures/FirstPersonCrosshair" ) );

    CrosshairTexture = crosshair_texture.Object;
}

// -- OPERATIONS

void AFpsHUD::DrawHaircross(
    )
{
    FCanvasTileItem
     TileItem(
         FVector2D(
             Canvas->ClipX * 0.5f,
             Canvas->ClipY * 0.5f + 20.0f
             ),
         CrosshairTexture->Resource,
         FLinearColor::White
         );

    TileItem.BlendMode = SE_BLEND_Translucent;

    Canvas->DrawItem( TileItem );
}

// ~~

void AFpsHUD::DrawMessage(
    const FString & message,
    const float x_position,
    const float y_position,
    const float text_width_factor,
    const float text_height_factor,
    const float scale,
    const FLinearColor & linear_color
    )
{
    float
        text_width,
        text_height;

    GetTextSize( message, text_width, text_height, GEngine->GetMediumFont(), scale );

    FText
        text = FText::FromString( message );

    FCanvasTextItem
        canvas_text_item(
            FVector2D(
                x_position + text_width * text_width_factor,
                y_position + text_height * text_height_factor
                ),
            text,
            GEngine->GetMediumFont(),
            linear_color
            );

    canvas_text_item.Scale.Set( scale, scale );

    Canvas->DrawItem( canvas_text_item );
}

// ~~

void AFpsHUD::DrawHUD(
    )
{
    Super::DrawHUD();

    if ( AFpsGameMode::State == AFpsGameMode::EState_Played )
    {
        DrawMessage(
            FString::Printf( TEXT( "Level %d" ), AFpsGameMode::LevelIndex + 1 ),
            Canvas->ClipX * 0.05f,
            Canvas->ClipY * 0.05f,
            0.0f,
            0.0f,
            3.0f,
            FLinearColor( 1.0f, 1.0f, 1.0f )
            );

        DrawMessage(
            FString::Printf( TEXT( "Time %d" ), int32( AFpsGameMode::RemainingTime ) ),
            Canvas->ClipX * 0.5f,
            Canvas->ClipY * 0.05f,
            -0.5f,
            0.0f,
            3.0f,
            FLinearColor( 1.0f, 1.0f, 1.0f )
            );

        DrawMessage(
            FString::Printf( TEXT( "Hit %d" ), int32( AFpsGameMode::HitTargetCount ) ),
            Canvas->ClipX * 0.95f,
            Canvas->ClipY * 0.05f,
            -1.0f,
            0.0f,
            3.0f,
            FLinearColor( 1.0f, 1.0f, 1.0f )
            );

        DrawHaircross();
    }
    else
    {
        if ( AFpsGameMode::State == AFpsGameMode::EState_Failed )
        {
            DrawMessage(
                FString( TEXT( "Out of time !" ) ),
                Canvas->ClipX * 0.5f,
                Canvas->ClipY * 0.5f,
                -0.5f,
                -0.5f,
                4.0f,
                FLinearColor( 1.0f, 0.0f, 0.0f )
                );
        }
        else if ( AFpsGameMode::State == AFpsGameMode::EState_Succeeded )
        {
            DrawMessage(
                FString( TEXT( "Success !" ) ),
                Canvas->ClipX * 0.5f,
                Canvas->ClipY * 0.5f,
                -0.5f,
                -0.5f,
                4.0f,
                FLinearColor( 0.0f, 1.0f, 0.0f )
                );
        }
    }
}
