#include "sudoku.h"

//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------

// You are free to declare any private functions if needed.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.


int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

/////////////////////////////////////////////////////////////
// since 'i' is given, we don't need a loop to go through different rows
// the only thing changing is the colum in the row so that's why i have a loop that goes through the
// columns in the row ('j')

for (int j=0; j<=8; j=j+1) { /////
if (sudoku[i][j] == val) { ///////
return 1; //////
}
}
// not sure if this goes before or after the assert line
/////////////////////////////////////////////////////////////


  // BEG TODO
  
  return 0;
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);

////////////////////////////////////////////////////////////////////
for (int i=0; i<=8; i=i+1) {
if (sudoku[i][j] == val) { ////////////
return 1; ////////////
} ////////////
}

/////////////////////////////////////////////////////////////////////

  // BEG TODO
  
  return 0;
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   
  assert(i>=0 && i<9);

////////////////////////////////////////////////////////////////////
int startRowCube = (i - (i%3)); ////
int startColCube = (j - (j%3)); ///

for (int rowA=0; rowA<3; rowA=rowA+1) { ////
for (int colA=0; colA<3; colA=colA+1) {
if (sudoku[startRowCube + rowA][startColCube + colA] == val) {
return 1;
}
} ////////////
}
////////////////////////////////////////////////////////////////////
  
  // BEG TODO
  
  return 0;
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);

  // BEG TODO
  if (is_val_in_row(val, i, sudoku) == 1){ //checks if the value is in row
	return 0;
  }
  if(is_val_in_col(val, j, sudoku) == 1){ //checks if the value is in the col
	return 0;
  }
  if (is_val_in_3x3_zone(val, i, j, sudoku) == 1){ //checks if the value is in the 3x3
	return 0;
  }
  return 1;
  // END TODO
}













// Procedure: solve_sudoku
// Solve the given sudoku instance.!


int solve_sudoku(int sudoku[9][9]) {

  // BEG TODO.


//////////////what///////////////////

for (int i=0; i<9; i=i+1) {
    for (int j=0; j<9; j=j+1) {
        if (sudoku[i][j] == 0) {
            for (int num =1; num<=9; num= num+1) {
                if (is_val_valid(num, i, j,sudoku)) {
                    sudoku[i][j] = num;
                    if (solve_sudoku(sudoku)) {
                      return 1;
                    }
                    else {
                      sudoku[i][j] = 0;
                    }
                }
            }
      return 0;
        }
    }
}


return 1;

  // END TODO.
}







void print_sudoku(int sudoku[9][9]){
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}
