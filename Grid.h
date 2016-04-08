
#ifndef GRID_H
#define GRID_H

class Grid
{
public:
	// Grid();
	// ~Grid();

	int		m_randomX, m_randomY;			// Random values to create grid size		(X and Y)
	int		m_gridSize;						// Total number of grid spaces
	int		m_numCities;					// Number of cities on the grid each side

	int		*m_playerGrid;					// Array to create the player's grid
	int		*m_enemyGrid;					// Array to create the enemy's grid			(same size as player's)
	char	*m_playerGridRender;			// Characters for player grid spaces:		' ', '-', '*', 'C', '='
	char	*m_enemyGridRender;				// Characters for enemy grid spaces:		' ', '-', '*', 'C'
	
	void	InitialiseGrid();				// Fill grid with 0s or 1s
	void	RenderGrid();					// Display character and update grid
	void	DisplayGrid();					// Display the grid
	void	DeleteAndResetArrays();			

private:
};

#define		ColourGrey		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7)		// BG Black, TXT Grey
#define		ColourGreen		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10)	// BG Black, TXT Green
#define		ColourCyan		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11)	// BG Black, TXT Cyan
#define		ColourRed		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12)	// BG Black, TXT Red
#define		ColourYellow	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14)	// BG Black, TXT Yellow
#define		ColourWhite		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15)	// BG Black, TXT White

#endif // GRID_H