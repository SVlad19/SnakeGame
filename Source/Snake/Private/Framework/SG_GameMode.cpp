#include "Framework/SG_GameMode.h"
#include "Core/Types.h"
#include "World/SG_Grid.h"
#include "Framework/SG_Pawn.h"
#include "Core/Grid.h"

using namespace Snake;

void ASG_GameMode::StartPlay()
{
    Super::StartPlay();

    // Init core game
    const Settings GameSettings{GridDims.X, GridDims.Y};
    Game = MakeUnique<Snake::Game>(GameSettings);
    check(Game.IsValid());

    // Init world grid
    const FTransform GridOrigion = FTransform::Identity;
    check(GetWorld());

    GridVisual = GetWorld()->SpawnActorDeferred<ASG_Grid>(GridVisualClass, GridOrigion);
    check(GridVisual);

    GridVisual->SetModel(Game->grid(), CellSize);
    GridVisual->FinishSpawning(GridOrigion);

    // Set camera location
    APlayerController* PC = GetWorld()->GetFirstPlayerController();
    check(PC);

    ASG_Pawn* Pawn = Cast<ASG_Pawn>(PC->GetPawn());
    check(Pawn);

    Pawn->UpdateLocation(Game->grid()->dim(), CellSize, GridOrigion);
    check(Pawn);
}
