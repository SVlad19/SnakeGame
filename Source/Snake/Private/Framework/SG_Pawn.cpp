#include "Framework/SG_Pawn.h"
#include "Camera/CameraComponent.h"

namespace
{
float HalfFOVTan(float FOVDegrees)
{
    return FMath::DegreesToRadians(FOVDegrees * 0.5f);
}

float VerticalFOV(float HFOVDegrees, float ViewportAspect)
{
    return FMath::RadiansToDegrees(2.f * FMath::Atan(FMath::Tan(FMath::DegreesToRadians(HFOVDegrees) * 0.5f) * ViewportAspect));
}

}  // namespace

ASG_Pawn::ASG_Pawn()
{
    PrimaryActorTick.bCanEverTick = false;

    Origin = CreateDefaultSubobject<USceneComponent>(TEXT("Origin"));
    check(Origin);
    SetRootComponent(Origin);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    check(Camera);
    Camera->SetupAttachment(Origin);
}

void ASG_Pawn::UpdateLocation(const Snake::Dim& InDim, int32 InCellSize, const FTransform& InGridOrigin)
{
    Dim = InDim;
    CellSize = InCellSize;
    GridOrigin = InGridOrigin;

    check(GEngine);
    check(GEngine->GameViewport);
    check(GEngine->GameViewport->Viewport);

    auto Viewport = GEngine->GameViewport->Viewport;
    Viewport->ViewportResizedEvent.AddUObject(this, &ThisClass::OnViewportResized);

#if WITH_EDITOR
    OnViewportResized(Viewport, 0);
#endif
}

void ASG_Pawn::OnViewportResized(FViewport* Viewport, uint32 Val)
{
    if (!Viewport || Viewport->GetSizeXY().Y == 0 || Dim.height == 0)
    {
        return;
    }

    const float WorldWidth = Dim.width * CellSize;
    const float WorldHeight = Dim.height * CellSize;

    float LocationZ = 0.f;

    const float ViewportAspect = static_cast<float>(Viewport->GetSizeXY().X) / Viewport->GetSizeXY().Y;
    const float GridAspect = static_cast<float>(Dim.width) / Dim.height;

    if (ViewportAspect <= GridAspect)
    {
        LocationZ = WorldWidth / HalfFOVTan(Camera->FieldOfView);
    }
    else
    {
        check(ViewportAspect);
        const float VFOV = VerticalFOV(Camera->FieldOfView, 1.f / ViewportAspect);
        LocationZ = WorldHeight / HalfFOVTan(VFOV);
    }

    const FVector NewPawnLocation = GridOrigin.GetLocation() + 0.5f * FVector(WorldHeight, WorldWidth, LocationZ);

    SetActorLocation(NewPawnLocation);
}
