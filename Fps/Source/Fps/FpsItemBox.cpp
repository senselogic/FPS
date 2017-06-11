// == LOCAL

// .. IMPORTS

#include "FpsItemBox.h"

// == PUBLIC

// -- CONSTRUCTORS

AFpsItemBox::AFpsItemBox(
    )
{
    StaticMesh = NULL;
    StaticMeshComponent = NULL;

    State = EState_Empty;

    ActivatedSound = LoadObject<USoundBase>( NULL, TEXT( "/Game/Audio/Sounds/ItemBoxActivatedSound" ) );
}
