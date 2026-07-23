#pragma once

#include "CoreMinimal.h"
#include "Types.h"

namespace Snake
{

class Grid;

class SNAKE_API Game
{
public:
    Game(const Settings& settings);
    ~Game() = default;

    /**
     * Returns the pointer to the grid object
     * @return TSharedPtr<Grid>  pointer to the grid object
     */
    inline TSharedPtr<Grid> grid() const { return m_grid; }

private:
    const Settings m_settings;
    TSharedPtr<Grid> m_grid;
};

}  // namespace Snake
