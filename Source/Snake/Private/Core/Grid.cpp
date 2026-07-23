#include "Core/Grid.h"

using namespace Snake;

DEFINE_LOG_CATEGORY_STATIC(LogGrid, All, All);

Grid::Grid(const Dim& dim) : m_dim(Dim{dim.width + 2, dim.height + 2})
{
    m_cells.Init(CellType::Empty, m_dim.width * m_dim.height);
    initWalls();
    printDebug();
}

void Grid::initWalls()
{
    for (int32 y = 0; y < m_dim.height; ++y)
    {
        for (int32 x = 0; x < m_dim.width; ++x)
        {
            if (x == 0 || x == m_dim.width - 1 || y == 0 || y == m_dim.height - 1)
            {
                m_cells[positionToIndex(x, y)] = CellType::Wall;
            }
        }
    }
}

void Grid::printDebug() const
{
    for (int32 y = 0; y < m_dim.height; ++y)
    {
        FString line;
        for (int32 x = 0; x < m_dim.width; ++x)
        {
            TCHAR symbol{};
            switch (m_cells[positionToIndex(x, y)])
            {
                case CellType::Empty:
                {
                    symbol = '0';
                    break;
                }
                case CellType::Wall:
                {
                    symbol = '*';
                    break;
                }
                default: break;
            }
            line.AppendChar(symbol).AppendChar(' ');
        }
        UE_LOG(LogGrid, Display, TEXT("%s"), *line);
    }
}

inline int32 Grid::positionToIndex(int32 x, int32 y) const
{
    return x + y * m_dim.width;
}
