/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

//blank tile coordinates
int blank_row, blank_col;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}



/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(200);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    // Work on the board array
    for (int row = 0; row < d; row++)
    {
        for (int col = 0; col < d; col++)
        {
            //Fill in the board[row][column] from (d*d-1) to 0
            board[row][col] = (d*d - 1) - (row*d + col);
        }
    }
    
    //In case of an odd number of tiles, swap '1' and '2'. These will always be found in the last row, 2nd and 3rd last columns
    if ((d*d - 1) % 2 != 0)
    {
        board[d-1][d-2] = 2;
        board[d-1][d-3] = 1;
    }
    
    //set blank tile coordinates
    blank_row = d - 1;
    blank_col = d - 1;
    
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    // Draw the board to the terminal window
    for (int row = 0; row < d; row++)
    {
        for (int col = 0; col < d; col++)
        {
            //Print the current tile with 
            printf("%3.i", board[row][col]);
        }
        printf("\n");
    }
    
    
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{

    //First, find the tile's coordinates by a sort of linear search
    int row = 0, col = 0, tile_row = -1, tile_col = -1;
    bool stop = false, found = false;
    
    do
    {
        //check the current tile's value
        if (board[row][col] == tile) 
        {
            //store the coordinates and set boolean conditions
            tile_row = row;
            tile_col = col;
            found = true;
            stop = true;
        }
        
        //increment the tile search indices
        row = (col + 1 == d) ? row + 1 : row;
        col = (col + 1 == d) ? 0 : col + 1;
        
        //loop stopping condition - reached the end of the board space
        stop = ( (row * d + col) > (d*d - 1)) ? true : false;
    } 
    while (stop == false);
    
    if (found == false)
        return false;
    
    //The tile was found and we have its coordinates - now to check if the move is valid (the zero case is handled in main)
    //Valid moves are tiles with coordinates that differ by exactly 1 in either row or col (not both!)
    bool valid_move = false;
    int diff_row, diff_col;
    
    //Get the absolute differences of row and col
    diff_row = abs(tile_row - blank_row);
    diff_col = abs(tile_col - blank_col);
    
    //Construct and XOR to check if the move is valid
    if ((diff_row == 1 && diff_col == 0) || (diff_row == 0 && diff_col == 1))
        valid_move = true;
    
    //If move is valid, perform the move
    if (valid_move)
    {
        //perform swap
        board[blank_row][blank_col] = tile;
        board[tile_row][tile_col] = 0;
        
        //take note of the new position of the blank tile
        blank_row = tile_row;
        blank_col = tile_col;
        
        //report completed move
        return true;
    }
    
    //move is not legit
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    // Check if the game is won, i.e. if each the top left tile is 1 and bottom right tile is zero, and all following tiles are sorted ascendingly.
    int board_onedim[d * d];
    int checksum = 0;
    
    if (board[0][0] == 1 && board[d-1][d-1] == 0)
    {
        //Map into one-dimensional array for ease of checking
        for (int row = 0; row < d; row++)
        {
            for (int col = 0; col < d; col++)
            {
                board_onedim[row * d + col] = board[row][col];
            }
        }
        
        //run through and check ascending order, except for last tile ( ==0 in a winning combination).
        for (int i = 1; i < (d*d - 1); i++)
        {
            checksum = (board_onedim[i] == 1 + board_onedim[i-1]) ? checksum + 0 : checksum + 1;
        }
        
        //logic : true or false
        if (checksum == 0)
            return true;
    }
    
    //not yet won
    return false;
}