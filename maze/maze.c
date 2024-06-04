/* Shailee Patel (netid: shailee2)
Introduction: I was tasked with creating a self solving maze. In order to do this, I had to first create a maze. I did this by opening the text file, and scanning in the variables that would help me solve this maze. After, I allocated memory to the different parts of a maze in the struct, therefore allowing me to set up a template for the maze. Then, I created two functions: print and destroy. Print would iterate through the new maze I created, and print out the unsolved version. Destroy would free the memory allocated to this maze. The solveMazeDFS function would help us to solve the maze using recursion. I first checked if the row being called was out of bounds, or if it was already solved. Then, I used recursion to check the cell's surrounding cells, creating a chain reaction to check which cells would reach me to the end. Once a cell reaches the end, the return statement would become 1, creating a chain reaction to make all cells 1, therefore causing the path to be "*"s. If it stays a 0 and does not reach the end, we would change the value to show "~"s, and never revisit this cell again.*/

#include <stdio.h>
#include <stdlib.h>
#include "maze.h"


/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
    // Your code here. Make sure to replace following line with your own code.
	FILE *file = fopen(fileName, "r"); //opens the file
	maze_t *maze = (maze_t *)malloc(sizeof(maze_t)); //allocates memoryspace to the maze
	fscanf(file, "%d %d\n", &maze->width, &maze->height); //scans file into variables
	maze->cells = calloc(maze->height,sizeof(char *)); //allocates memoryspace to the cells
	for (int i = 0; i < maze->height; i++){ //iterates through rows to allocate memory
		maze->cells[i] = calloc(maze->width + 1,sizeof(char)); //allocates memory to each row
		for (int j = 0; j < maze->width + 1; j++){
			fscanf(file, "%c", &maze->cells[i][j]); //scans file and puts in value at each array cell
			if (maze->cells[i][j] == START){
				maze->startRow = i;
				maze->startColumn = j;
			}
			if (maze->cells[i][j] == END){
				maze->endRow = i;
				maze->endColumn = j;
			}
		}
	}
	fclose(file);//closes file
   	return maze;
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    // Your code here.
	for (int i = 0; i < maze->height; i++){
		free(maze->cells[i]); //frees the memory at each row
	}
	free(maze->cells); //frees the memory of all cells
	free(maze); //frees the memory of the maze
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{	
    // Your code here.
	for (int i = 0; i < maze->height; i++){ //loops through the rows
		for (int j = 0; j < maze->width; j++){ //loops through the cols
      			printf("%c", maze->cells[i][j]); //prints each item
   		}
		printf("\n"); //newline
	}
}
/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int solveMazeDFS(maze_t * maze, int col, int row)
{
    // Your code here. Make sure to replace following line with your own code.
	if ((row<0 || row>=maze->height || col<0 || col>=maze->width)){
		return 0; //checks if it is out of bounds
	}
	if (maze->cells[row][col] == END){
		return 1; //checks if you have reached the end
	}
	if ((maze->cells[row][col] == PATH) || (maze->cells[row][col] == VISITED)){
		return 0; //if the cell is path or visited, then backtrack
	}
	if (maze->cells[row][col] == WALL){
		return 0; //if the cell is a wall, backtrack
	}
	if (maze->cells[row][col] != START){
		maze->cells[row][col] = PATH; //makes sure not to change start, changes cell to path
	}
	if ((solveMazeDFS(maze, col+1, row) == 1) || (solveMazeDFS(maze, col, row+1) == 1) || (solveMazeDFS(maze, col-1, row) == 1) || (solveMazeDFS(maze, col, row-1) == 1)){
		return 1; //checks all of its neighbors to see which is the next
	}
	maze->cells[row][col] = VISITED; //if it doesn't exit the function, backtrack because this isn't the right cell
   	return 0;

}
