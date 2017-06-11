#pragma once

// == LOCAL

// .. IMPORTS

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FpsHUD.generated.h"

// == GLOBAL

// -- TYPES

UCLASS()
class AFpsHUD :
    public AHUD
{
    GENERATED_BODY()

    // == PUBLIC

    public :

    // -- CONSTRUCTORS

    AFpsHUD(
        );

    // -- OPERATIONS

    void DrawHaircross(
        );

    // ~~

    void DrawMessage(
        const FString & message,
        const float x_position,
        const float y_position,
        const float text_width_factor,
        const float text_height_factor,
        const float scale,
        const FLinearColor & linear_color
        );

    // ~~

    virtual void DrawHUD(
        ) override;

    // ~~

    class UTexture2D
        * CrosshairTexture;
};
