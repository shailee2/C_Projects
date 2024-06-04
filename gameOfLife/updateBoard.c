/*Shailee Patel
netid: shailee2
Introduction: Today, I am implementing three functions to integrate into the Game of Life. The first function, countLiveNeighbor, goes through the board and accesses each cell's neighboring cells. It counts the amount of neighboring cells that are alive, and ignores the one that is dead. It also accounts for the bounds of the board to provide a more accurate count. The next function, updateBoard, I create a copy of the board. With the copy, I access each cell and find the amount of live neighbors each cell has using the countLiveNeighbor function. After counting the amount of live neighbors it has, I utilize this to reflect the rules of the game that determine if the cell lives or dies. Then, I store this value into the original board, and repeat for all cells. This updates the board. The third function, aliveStable, we check each cell to see if it stayed the same, or if it changed. A cell only stays the same if it has 2 or 3 live neighbors, so by checking this, we can determine if the cell has changed or not, and determine the return value.
*/
/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */
#include <stdlib.h>
int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){
	int curcol = col; //copy columns and rows
	int currow = row;
	int count = 0; //initialize a counter that counts the number of alive neighbors
	int tempcell; //initialize a tempcell that can access its value
	for (int i = currow - 1; i <= currow + 1; i++){ //create a loop through rows
		if (i >= 0 && i < boardRowSize){ //make sure it's in bounds
			for (int j = curcol - 1; j <= curcol + 1; j++){ //create a loop through columns
				if (j >= 0 && j < boardColSize){ //make sure it's in bounds
					if (i != currow || j != curcol){ //accesses all neighbors except for main
						tempcell = board[(i * boardColSize) + j]; //access value
						if (tempcell == 1){ //checks if alive
							count++; //increments alive number
						}
					}
				}
			}
		}
	}
	return count; //returns value
}
			

/*
 * Update the game board to the next step.
 * Input: 
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize) {
	int *newboard = (int*) malloc(sizeof(int)*boardRowSize*boardColSize); //creates a new board
	for (int z = 0; z < boardRowSize * boardColSize; z++){ //fills in the values
		newboard[z] = board[z];
	}	
	for (int i = 0; i < boardRowSize; i++){ //loops through the rows
		for (int j = 0; j < boardColSize; j++){ //loops through the columns
			int cell = newboard[(i * boardColSize) + j]; //accesses the value of the cell being accessed
			int count = countLiveNeighbor(newboard, boardRowSize, boardColSize, i, j); //counts live neighbors
			if (cell == 0){ //checks if cell is dead
				if (count == 3){ //checks if cell has 3 live neighbors
					board[(i * boardColSize) + j] = 1; //revives cell
				}
			}
			else{
				if (count == 2 || count == 3){ //if cell has 2 or 3 live neighbors
					board[(i * boardColSize) + j] = 1; //cell stays the same
				}
				else{
					board[(i * boardColSize) + j] = 0; //cell dies
				}
			}
		}
	}
}

/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with 
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */ 
int aliveStable(int* board, int boardRowSize, int boardColSize){
	int count; //initializes a count
	for (int i = 0; i < boardRowSize; i++){ //loops through rows
		for (int j = 0; j < boardColSize; j++){ //loops through columns
			count = countLiveNeighbor(board, boardRowSize, boardColSize, i, j); //accesses number of live neighbors for cell
			if (board[i * boardColSize + j] == 1){ //if cell is alive
				if (count < 2 || count > 3){ //if cell changed
					return 0; //cell changed
				}
			}
		}
	}
	return 1; //cell didn't change
}

				
				
			
