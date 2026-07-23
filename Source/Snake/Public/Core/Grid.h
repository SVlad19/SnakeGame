#pragma once

#include "CoreMinimal.h"
#include "Types.h"

namespace Snake
{

class Grid
{
public:
    Grid(const Dim& dim);
    ~Grid() = default;

    /**
     * Returns grid dimensions including walls (width + 2; height + 2)
     * @return Dim  grid dimensions
     */
    Dim dim() const { return m_dim; }

private:
    void initWalls();
    void printDebug() const;
    inline int32 positionToIndex(int32 x, int32 y) const;

    const Dim m_dim;
    TArray<CellType> m_cells;
};

}  // namespace Snake
