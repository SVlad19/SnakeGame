#include "World/SG_Grid.h"
#include "Core/Grid.h"
#include "DrawDebugHelpers.h"
#include "Components/LineBatchComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogWorldGrid, All, All);

ASG_Grid::ASG_Grid()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ASG_Grid::BeginPlay()
{
    Super::BeginPlay();
}

void ASG_Grid::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    DrawGrid();
}

void ASG_Grid::SetModel(const TSharedPtr<Snake::Grid>& Grid, int32 InCellSize)
{
    if (!Grid.IsValid())
    {
        UE_LOG(LogWorldGrid, Fatal, TEXT("Grid is null"));
    }

    GridDim = Grid.Get()->dim();
    CellSize = InCellSize;
    WorldWidth = GridDim.width * CellSize;
    WorldHeight = GridDim.height * CellSize;
}

void ASG_Grid::DrawGrid() const
{
    if (!GetWorld() || !GetWorld()->GetLineBatcher(UWorld::ELineBatcherType::Foreground))
    {
        return;
    }
    for (size_t i = 0; i < GridDim.height + 1; ++i)
    {
        const FVector StartLocation = GetActorLocation() + GetActorForwardVector() * CellSize * i;
        // DrawDebugLine(GetWorld(), StartLocation, StartLocation + GetActorRightVector() * WorldWidth, FColor::Red, false, -1.f, 0, 2.f);
        GetWorld()
            ->GetLineBatcher(UWorld::ELineBatcherType::Foreground)
            ->DrawLine(StartLocation, StartLocation + GetActorRightVector() * WorldWidth, FLinearColor::Red, 0, 2.f);
    }

    for (size_t i = 0; i < GridDim.width + 1; ++i)
    {
        const FVector StartLocation = GetActorLocation() + GetActorRightVector() * CellSize * i;
        // DrawDebugLine(GetWorld(), StartLocation, StartLocation + GetActorForwardVector() * WorldHeight, FColor::Red, false, -1.f,
        // 0, 2.f);
        GetWorld()
            ->GetLineBatcher(UWorld::ELineBatcherType::Foreground)
            ->DrawLine(StartLocation, StartLocation + GetActorForwardVector() * WorldWidth, FLinearColor::Red, 0, 2.f);
    }
}
