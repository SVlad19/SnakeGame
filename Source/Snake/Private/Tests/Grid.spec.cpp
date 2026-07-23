// Snake game copyright

#if WITH_AUTOMATION_TESTS

#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "Core/Grid.h"

DEFINE_SPEC(
    FSnakeGrid, "Snake", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)

void FSnakeGrid::Define()
{
    using namespace Snake;

    Describe("CoreGrid",
        [this]()
        {
            It("DimsMightIncludeWalls",
                [this]()
                {
                    const Grid grid(Dim{10, 10});
                    TestTrueExpr(grid.dim().height == 12);
                    TestTrueExpr(grid.dim().width == 12);
                });
        });
}

#endif
