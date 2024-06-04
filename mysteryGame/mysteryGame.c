#include "mysteryGame.h"

// NAME: Shailee Patel  NETID: shailee2

/* INTRODUCTORY PARAGRAPH: This code utilizes the struct provided in game.h
   to develop a new game board with a size of the user's choice. The board is
   able to be cleared and destroyed when the user presses the "n" key, which 
   uses the free function call. When playing the game, the user is able to press
   the wasd keys to move up, left, down, and right respectively. To implement
   this behavior, I had to traverse through each of the columns and slide the 
   numbers to the furthest empty rows possible (for the up and down functions)
   and traverse through each of the rows and slide the numbers to the furthest
   empty columns possible (for the left and right functions). After each number
   slides in the direction that the function determines, the code checks whether
   or not it is adjacent to a cell (in the same direction that it is sliding)
   that has the same value. If this is the case, then the cells combine into one
   with double their original values and the score increases by the value of the
   new cell. In order to ensure that the game ends when there are no possible
   moves left, a copy of the current game board is made after each move to
   test whether or not the move_w/a/s/d moves are applicable on the board.
   The functions move_w/a/s/d will return a 1 if the board was able to slide
   or merge at all when the function is called. If all of the functions 
   return 0, then the game ends. The board copy is destroyed after each move.
*/


game * make_game(int rows, int cols)
/*! Create an instance of a game structure with the given number of rows
    and columns, initializing elements to -1 and return a pointer
    to it. (See game.h for the specification for the game data structure) 
    The needed memory should be dynamically allocated with the malloc family
    of functions.
*/
{
    //Dynamically allocate memory for game and cells (DO NOT modify this)
    game * mygame = malloc(sizeof(game));
    mygame->cells = malloc(rows*cols*sizeof(cell));

    //YOUR CODE STARTS HERE:  Initialize all other variables in game struct
	mygame->rows = rows;
	mygame->cols = cols;
	mygame->score = 0;

	for (int i = 0; i < rows; i++){
		for (int j = 0; j < cols; j++){
			mygame->cells[i*cols+j] = -1;
	}
}


    return mygame;
}

void remake_game(game ** _cur_game_ptr,int new_rows,int new_cols)
/*! Given a game structure that is passed by reference, change the
	game structure to have the given number of rows and columns. Initialize
	the score and all elements in the cells to -1. Make sure that any 
	memory previously allocated is not lost in this function.	
*/
{
	/*Frees dynamically allocated memory used by cells in previous game,
	 then dynamically allocates memory for cells in new game.  DO NOT MODIFY.*/
	free((*_cur_game_ptr)->cells);
	(*_cur_game_ptr)->cells = malloc(new_rows*new_cols*sizeof(cell));

	 //YOUR CODE STARTS HERE:  Re-initialize all other variables in game struct

	(*_cur_game_ptr)->rows = new_rows;  //utilizes variables provided in game.h to initialize rows, cols, and score
	(*_cur_game_ptr)->cols = new_cols;
	(*_cur_game_ptr)->score = 0;

	for (int i = 0; i<new_rows; i++){       //fills the newly created board with -1s in row-major order
	  for (int j = 0; j<new_cols; j++){
	    (*_cur_game_ptr)->cells[i*new_cols+j] = -1;
	  }
	}

	return;	
}

void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains. Do not modify this function.*/
{
    free(cur_game->cells);
    free(cur_game);
    cur_game = NULL;
    return;
}

cell * get_cell(game * cur_game, int row, int col)
/*! Given a game, a row, and a column, return a pointer to the corresponding
    cell on the game. (See game.h for game data structure specification)
    This function should be handy for accessing game cells. Return NULL
	if the row and col coordinates do not exist.
*/
{
    //YOUR CODE STARTS HERE
  if (row<0 || row>cur_game->rows-1) return  NULL;    //if the cell is not in the row bounds, return null
  if (col<0 || col>cur_game->cols-1) return  NULL;    //if the cell is not in the col bounds, return null

  return &cur_game->cells[row*cur_game->cols+col];    //returns the pointer for the corresponding cell on the game
}

int move_w(game * cur_game)
/*!Slides all of the tiles in cur_game upwards. If a tile matches with the 
   one above it, the tiles are merged by adding their values together. When
   tiles merge, increase the score by the value of the new tile. A tile can 
   not merge twice in one turn. If sliding the tiles up does not cause any 
   cell to change value, w is an invalid move and return 0. Otherwise, return 1. 
*/
{
    //YOUR CODE STARTS HERE
  int * merged = (int *)(malloc(cur_game->rows*sizeof(int)));  //blocks off a number of cells based on the size of the game
                                                               //and returns a pointer to the first value [0][0]. This new
                                                               //array will hold ones wherever it has been merged already

        int i, j , k, val, i2;
        int ret_val = 0;
	for (j=0; j<cur_game->cols; j++){          //traverses in column major order
	  for (i2 = 0; i2<cur_game->rows; i2++){   //goes through each row in the column
	    merged[i2] = 0;  //sets the previously initialized merge array to 0
   }
   
 for (i=0; i<cur_game->rows; i++){
   val = cur_game->cells[i*cur_game->cols+j];    //grabs the value of each cell
 

   int tgt = -1;  //initializes where the value of the current cell should slide
   if (val != -1){  //if the cell is not empty
     if (i>0 && (val == cur_game->cells[(i-1)*cur_game->cols+j])){   //if the cell has the same val as the cell above
       if (merged[i-1] != 1){                                        //if the row above has not been merged yet
	 cur_game->cells[(i-1)*cur_game->cols+j] = val*2;            //replace cell above with val*2
	 cur_game->cells[i*cur_game->cols+j] = -1;                   //clear current cell
	 cur_game->score += val*2;                                   //increase score by current cell num
	 merged[i-1] = 1;                                            //set the cell that was merged to 1 in the other array
	 ret_val = 1;                                                
       }
     }

     
     for (k=i-1; k>=0; k--){                                  //traverses rows from bottom to top
       if (cur_game->cells[k*cur_game->cols+j] == -1){        //checks if cell is empty
	 tgt = k;                                             //tells cell to move up
	  }
	}
     if (tgt != -1){                                          //if there are empty spaces above current cell, swap the cells
            cur_game->cells[tgt*cur_game->cols+j] = val;
            cur_game->cells[i*cur_game->cols+j] = -1;
	    ret_val = 1;


	    //SPECIAL CASE I FOUND
	    if (merged[i-1] == 1){                               //if the cell above the newly moved cell has the same val
	      cur_game->cells[(tgt)*cur_game->cols+j] += val;    //increase the cell above's value by val
	      cur_game->cells[(j-1)*cur_game->cols+j] = -1;      //clear original cell
	      merged[i-1] = 0;                                 
	      merged[tgt] = 1;
	    }
	      

      //MERGING
	    if (tgt !=  0 && merged[tgt-1] != 1){               //if the target row is not out of bounds and the cell above is not merged
	      if ((cur_game->cells[tgt*cur_game->cols+j]) == (cur_game->cells[(tgt-1)*cur_game->cols+j])){
		cur_game->cells[(tgt-1)*cur_game->cols+j] = val*2;  //set cell above to val*2
		cur_game->cells[tgt*cur_game->cols+j] = -1;   //clear target cell
		cur_game->score = cur_game->score + val*2;    //increase score by new cell value
		 merged[tgt-1] = 1;                           //merge cell above
		  ret_val = 1;
           }
	}
    }
   }
  }
 }

    return ret_val;
};

int move_s(game * cur_game) //slide down
{
    //YOUR CODE STARTS HERE
   int * merged = (int *)(malloc(cur_game->rows*sizeof(int)));  //blocks off a number of cells based on the size of the game
                                                                //and returns a pointer to the first value [0][0]. This new
                                                                //array will hold ones wherever it has been merged already
  
   int i, j , k, val, i2;
   int ret_val = 0;
  for (j=0; j<cur_game->cols; j++){               //traverses in column major order
         for (i2 = 0; i2<cur_game->rows; i2++){   //goes through each row in the column
     merged[i2] = 0;  //sets the previously initialized merge array to 0
   }
   
    
    for (i=cur_game->rows-1; i>=0; i--){
      val = cur_game->cells[i*cur_game->cols+j];    //grabs the value of each cell

      
      int tgt = -1;  //initializes where the value of the current cell should slide
      if (val != -1){  //if the cell is not empty
        if (i>0 && (val == cur_game->cells[(i-1)*cur_game->cols+j])){   //if the cell has the same val as the cell below
         if (merged[i] != 1){                                           //if the row below has not been merged yet
            cur_game->cells[(i)*cur_game->cols+j] = val*2;              //replace cell below  with val*2
            cur_game->cells[(i-1)*cur_game->cols+j] = -1;               //clear current cell
	    cur_game->score += val*2;                                   //increase score by current cell num
	    merged[i] = 1;           
	       ret_val = 1;
       }
     }
	  
	for (k=i+1; k<cur_game->rows; k++){
	  if (cur_game->cells[k*cur_game->cols+j] == -1){
	  tgt = k;
	  }
	}
   if (tgt != -1){
      cur_game->cells[tgt*cur_game->cols+j] = val;
      cur_game->cells[i*cur_game->cols+j] = -1;
      ret_val = 1;

        if (merged[i] == 1){
	      cur_game->cells[(tgt)*cur_game->cols+j] += val;
	      cur_game->cells[i*cur_game->cols+j] = -1;
	      merged[i] = 0;
	      merged[tgt] = 1;
	    }

      //MERGING
            if (tgt !=  cur_game->rows-1  && merged[tgt+1] != 1){
	      if ((cur_game->cells[tgt*cur_game->cols+j]) == (cur_game->cells[(tgt+1)*cur_game->cols+j])){
		cur_game->cells[(tgt+1)*cur_game->cols+j] = val*2;
	         cur_game->cells[tgt*cur_game->cols+j] = -1;
     	         cur_game->score = cur_game->score + val*2;
	          merged[tgt+1] = 1;
		  ret_val = 1;
                }
	    }
     }
    }
   }
  }

    return ret_val;
};

//SLIDE LEFT FUNCTION IS VERY SIMILAR TO THE SLIDE UP FUNCTION BUT THE BOARD IS TRAVERSED
//IN ROW MAJOR ORDER.

int move_a(game * cur_game) //slide left
{
    //YOUR CODE STARTS HERE  
 int * merged = (int *)(malloc(cur_game->cols*sizeof(int)));
 
      int i, j , k, val, j2;
      int ret_val = 0;
  for (i=0; i<cur_game->rows; i++){
      for (j2 = 0; j2<cur_game->cols; j2++){
     merged[j2] = 0;
   }
    
    for (j=0; j<cur_game->cols; j++){
      val = cur_game->cells[i*cur_game->cols+j];

         int tgt = -1;
      if (val != -1){
	if (j>0 && (val == cur_game->cells[(i)*cur_game->cols+(j-1)])){
          if (merged[j-1] != 1){
 	    cur_game->cells[(i)*cur_game->cols+(j-1)] = val*2;
            cur_game->cells[i*cur_game->cols+j] = -1;
	    cur_game->score += val*2;
	       merged[j-1] = 1;
	       ret_val = 1;
       }
     }

	for (k=j-1; k>=0; k--){
	  if (cur_game->cells[i*cur_game->cols+k] == -1){
	  tgt = k;
	  }
	}
   if (tgt != -1){
      cur_game->cells[i*cur_game->cols+tgt] = val;
      cur_game->cells[i*cur_game->cols+j] = -1;
      ret_val = 1;

        if (merged[j-1] == 1){
	      cur_game->cells[i*cur_game->cols+tgt] += val;
	      cur_game->cells[i*cur_game->cols+(j-1)] = -1;
	      merged[j-1] = 0;
	      merged[tgt] = 1;
	    }

        if (tgt !=  0 && merged[tgt-1] != 1){
	  if ((cur_game->cells[i*cur_game->cols+tgt]) == (cur_game->cells[(i)*cur_game->cols+(tgt-1)])){
	    cur_game->cells[(i)*cur_game->cols+(tgt-1)] = val*2;
	         cur_game->cells[i*cur_game->cols+tgt] = -1;
     	         cur_game->score = cur_game->score + val*2;
	          merged[tgt-1] = 1;
		  ret_val = 1;
           }
	}
     }
    }
   }
  }
    return ret_val;
};

//SLIDE RIGHT FUNCTION IS VERY SIMILAR TO THE SLIDE DOWN FUNCTION BUT
//THE BOARD IS TRAVERED IN ROW MAJOR ORDER.
int move_d(game * cur_game){ //slide to the right
    //YOUR CODE STARTS HERE
 int * merged = (int *)(malloc(cur_game->cols*sizeof(int)));
 
 int i, j , k, val, j2;
 int ret_val = 0;
  for (i=0; i<cur_game->rows; i++){
    for (j2 = 0; j2<cur_game->cols; j2++){
     merged[j2] = 0;
   }
    
    for (j=cur_game->cols-1; j>=0; j--){
      val = cur_game->cells[i*cur_game->cols+j];

        int tgt = -1;
      if (val != -1){
	if (j>0 && (val == cur_game->cells[(i)*cur_game->cols+(j-1)])){
          if (merged[j] != 1){
 	    cur_game->cells[(i)*cur_game->cols+(j)] = val*2;
            cur_game->cells[i*cur_game->cols+(j-1)] = -1;
	    cur_game->score += val*2;
	       merged[j] = 1;
	       ret_val = 1;
       }
     }
	
	for (k=j+1; k<cur_game->cols; k++){
	  if (cur_game->cells[i*cur_game->cols+k] == -1){
	  tgt = k;
	  }
	}
	
   if (tgt != -1){
      cur_game->cells[i*cur_game->cols+tgt] = val;
      cur_game->cells[i*cur_game->cols+j] = -1;
      ret_val = 1;

        if (merged[j] == 1){
	      cur_game->cells[i*cur_game->cols+tgt] += val;
	      cur_game->cells[i*cur_game->cols+j] = -1;
	      merged[j] = 0;
	      merged[tgt] = 1;
	    }

      //MERGING
         if (tgt !=  cur_game->cols-1  && merged[tgt+1] != 1){
	      if ((cur_game->cells[i*cur_game->cols+tgt]) == (cur_game->cells[i*cur_game->cols+tgt+1])){
		 cur_game->cells[i*cur_game->cols+(tgt+1)] = val*2;
	         cur_game->cells[i*cur_game->cols+tgt] = -1;
     	         cur_game->score = cur_game->score + val*2;
	          merged[tgt+1] = 1;
		  ret_val = 1;
                }
	    }
     }
    }
   }
  }
    return ret_val;
};

int legal_move_check(game * cur_game)
/*! Given the current game check if there are any legal moves on the board. There are
    no legal moves if sliding in any direction will not cause the game to change.
	Return 1 if there are possible legal moves, 0 if there are none.
 */
{
    //YOUR CODE STARTS HERE
  game *copy_game = make_game(cur_game->rows, cur_game->cols); //creates a copy of the current board's size

  if (copy_game == NULL){  //tests if the board is null, wont really run into this issue
    return 0;
  }

  for (int i = 0; i <= copy_game->rows-1; i++){    //traverses the cells of the board
    for (int j = 0; j <= copy_game->cols-1; j++){
      copy_game->cells[i*copy_game->cols+j] = cur_game->cells[i*cur_game->cols+j]; //fills the new board with the same values of old board
    }
  }

  if (move_w(copy_game) == 1){  //if the board is able to slide up
    free(copy_game);            //destroy the board copy
    return 1;                   //game can continue
  }

  if (move_s(copy_game) == 1){  //if the board is able to slide down
    free(copy_game);            //destroy the board copy
    return 1;                   //game can continue
  }

  if (move_a(copy_game) == 1){  //if the board can slide left
    free(copy_game);
    return 1;                   //same as top two if statements
  }

  if (move_d(copy_game) == 1){  //if the board can slide right
    free(copy_game);
    return 1;                   //same as top two if statements
  }

  free(copy_game);   //destroy copy
  return 0;          //game ends
}


/*! code below is provided and should not be changed */

void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
*/
{
	
	cell * cell_ptr;
    cell_ptr = 	cur_game->cells;
	
    if (cell_ptr == NULL){ 	
        printf("Bad Cell Pointer.\n");
        exit(0);
    }
	
	
	//check for an empty cell
	int emptycheck = 0;
	int i;
	
	for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
		if ((*cell_ptr) == -1){
				emptycheck = 1;
				break;
		}		
        cell_ptr += 1;
	}
	if (emptycheck == 0){
		printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
		exit(0);
	}
	
    int ind,row,col;
	int num;
    do{
		ind = rand()%((cur_game->rows)*(cur_game->cols));
		col = ind%(cur_game->cols);
		row = ind/cur_game->cols;
    } while ( *get_cell(cur_game, row, col) != -1);
        //*get_cell(cur_game, row, col) = 2;
	num = rand()%20;
	if(num <= 1){
		*get_cell(cur_game, row, col) = 4; // 1/10th chance
	}
	else{
		*get_cell(cur_game, row, col) = 2;// 9/10th chance
	}
}

int print_game(game * cur_game) 
{
    cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int i,j;
	
	printf("\n\n\nscore:%d\n",cur_game->score); 
	
	
	printf("\u2554"); // topleft box char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // top box char
	printf("\u2557\n"); //top right char 
	
	
    for(i = 0; i < rows; i++){
		printf("\u2551"); // side box char
        for(j = 0; j < cols; j++){
            if ((*cell_ptr) == -1 ) { //print asterisks
                printf(" **  "); 
            }
            else {
                switch( *cell_ptr ){ //print colored text
                    case 2:
                        printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4:
                        printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8:
                        printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 16:
                        printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 32:
                        printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 64:
                        printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 128:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 256:
                        printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 512:
                        printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 1024:
                        printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 2048:
                        printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4096:
                        printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8192:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
					default:
						printf("  X  ");

                }

            }
            cell_ptr++;
        }
	printf("\u2551\n"); //print right wall and newline
    }
	
	printf("\u255A"); // print bottom left char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // bottom char
	printf("\u255D\n"); //bottom right char
	
    return 0;
}

int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{ 
	int rows,cols;
	char buf[200];
	char garbage[2];
    int move_success = 0;
	
    switch ( input_char ) {
    case 'w':
        move_success = move_w(cur_game);
        break;
    case 'a':
        move_success = move_a(cur_game);
        break;
    case 's':
        move_success = move_s(cur_game);
        break;
    case 'd':
        move_success = move_d(cur_game);
        break;
    case 'q':
        destroy_game(cur_game);
        printf("\nQuitting..\n");
        return 0;
        break;
	case 'n':
		//get row and col input for new game
		dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
		while (NULL == fgets(buf,200,stdin)) {
			printf("\nProgram Terminated.\n");
			return 0;
		}
		
		if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
		rows < 0 || cols < 0){
			printf("Invalid dimensions.\n");
			goto dim_prompt;
		} 
		
		remake_game(&cur_game,rows,cols);
		
		move_success = 1;
		
    default: //any other input
        printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
    }

	
	
	
    if(move_success == 1){ //if movement happened, insert new tile and print the game.
         rand_new_tile(cur_game); 
		 print_game(cur_game);
    } 

    if( legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
        printf("Game Over!\n");
        return 0;
    }
    return 1;
}
