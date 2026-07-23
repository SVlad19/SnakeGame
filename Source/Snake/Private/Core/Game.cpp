#include "Core/Game.h"
#include "Core/Grid.h"

using namespace Snake;

DEFINE_LOG_CATEGORY_STATIC(LogGame, All, All);

Game::Game(const Settings& settings) : m_settings(settings)
{
    m_grid = MakeShared<Grid>(settings.gridDims);
}
