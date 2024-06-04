//Shailee Patel
//netid: shailee2
//partner netids: amanda51, bijoucl2
/*Introduction: This program is a game where the user inputs guesses to try to find the correct solution. In the set_seed function, we set the seed value to create the solution for this game using the srand() function. In the start_game function, we utilize the rand() function to create the actual numbers for the solution, making sure to only choose integers from 1-8. In the make_guess function, we utilize an algorithm that first checks if the guesses are valid. Then, we pair correct guesses and correct solutions to check if the user has entered the solution or not, placing this value in correct guesses. Then, if the solutions are not paired yet, we check if their guess matches with any of the other numbers that are part of the solution, placing this value in misplaced guesses. The program then prints out a statement saying the amount of correct numbers and misplaced numbers the user has entered, as well as the number of guesses they have. */

/*			
 *
 * prog5.c - source file adapted from UIUC ECE198KL Spring 2013 Program 4
 *           student code -- GOLD VERSION by Steven S. Lumetta
 */


/*
 * The functions that you must write are defined in the header file.
 * Blank function prototypes with explanatory headers are provided
 * in this file to help you get started.
 */



#include <stdio.h>
#include <stdlib.h>

#include "prog5.h"


/*
 * You will need to keep track of the solution code using file scope
 * variables as well as the guess number.
 */

static int guess_number;
static int solution1;
static int solution2;
static int solution3;
static int solution4;


/*
 * set_seed -- This function sets the seed value for pseudorandom
 * number generation based on the number the user types.
 * The input entered by the user is already stored in the string seed_str by the code in main.c.
 * This function should use the function sscanf to find the integer seed value from the 
 * string seed_str, then initialize the random number generator by calling srand with the integer
 * seed value. To be valid, exactly one integer must be entered by the user, anything else is invalid. 
 * INPUTS: seed_str -- a string (array of characters) entered by the user, containing the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (string contains anything
 *               other than a single integer), or 1 if string is valid (contains one integer)
 * SIDE EFFECTS: initializes pseudo-random number generation using the function srand. Prints "set_seed: invalid seed\n"
 *               if string is invalid. Prints nothing if it is valid.
 */
int
set_seed (const char seed_str[])
{
	int seed;
	int ret;
	char post[2];
	ret = sscanf(seed_str, "%d%1s", &seed, post); //puts the user input into seed
	if (ret != 1){
		printf("set_seed: invalid seed\n"); //invalid was entered
		return 0;
	}
	srand(seed); //if it's valid, execute function
	return 1;
}
	

//    Example of how to use sscanf to read a single integer and check for anything other than the integer
//    "int seed" will contain the number typed by the user (if any) and the string "post" will contain anything after the integer
//    The user should enter only an integer, and nothing else, so we will check that only "seed" is read. 
//    We declare
//    int seed;
//    char post[2];
//    The sscanf statement below reads the integer into seed. 
//    sscanf (seed_str, "%d%1s", &seed, post)
//    If there is no integer, seed will not be set. If something else is read after the integer, it will go into "post".
//    The return value of sscanf indicates the number of items read succesfully.
//    When the user has typed in only an integer, only 1 item should be read sucessfully. 
//    Check that the return value is 1 to ensure the user enters only an integer. 
//    Feel free to uncomment these statements, modify them, or delete these comments as necessary. 
//    You may need to change the return statement below
   


/*
 * start_game -- This function is called by main.c after set_seed but before the user makes guesses.
 *               This function creates the four solution numbers using the approach
 *               described in the wiki specification (using rand())
 *               The four solution numbers should be stored in the static variables defined above. 
 *               The values at the pointers should also be set to the solution numbers.
 *               The guess_number should be initialized to 1 (to indicate the first guess)
 * INPUTS: none
 * OUTPUTS: *one -- the first solution value (between 1 and 8)
 *          *two -- the second solution value (between 1 and 8)
 *          *three -- the third solution value (between 1 and 8)
 *          *four -- the fourth solution value (between 1 and 8)
 * RETURN VALUE: none
 * SIDE EFFECTS: records the solution in the static solution variables for use by make_guess, set guess_number
 */
void
start_game (int* one, int* two, int* three, int* four)
{
    //your code here
	*one = rand() % 8; //divides all numbers into numbers 0-7
	*one = *one + 1; //all numbers are 1-8
	solution1 = *one; //copy this into the solution
	*two = rand() % 8;
	*two = *two + 1;
	solution2 = *two;
	*three = rand() % 8;
	*three = *three + 1;
	solution3 = *three;
	*four = rand() % 8;
	*four = *four + 1;
	solution4 = *four;
	guess_number = 1; //increment guess_number
    
}

/*
 * make_guess -- This function is called by main.c after the user types in a guess.
 *               The guess is stored in the string guess_str. 
 *               The function must calculate the number of perfect and misplaced matches
 *               for a guess, given the solution recorded earlier by start_game
 *               The guess must be valid (contain only 4 integers, within the range 1-8). If it is valid
 *               the number of correct and incorrect matches should be printed, using the following format
 *               "With guess %d, you got %d perfect matches and %d misplaced matches.\n"
 *               If valid, the guess_number should be incremented.
 *               If invalid, the error message "make_guess: invalid guess\n" should be printed and 0 returned.
 *               For an invalid guess, the guess_number is not incremented.
 * INPUTS: guess_str -- a string consisting of the guess typed by the user
 * OUTPUTS: the following are only valid if the function returns 1 (A valid guess)
 *          *one -- the first guess value (between 1 and 8)
 *          *two -- the second guess value (between 1 and 8)
 *          *three -- the third guess value (between 1 and 8)
 *          *four -- the fourth color value (between 1 and 8)
 * RETURN VALUE: 1 if the guess string is valid (the guess contains exactly four
 *               numbers between 1 and 8), or 0 if it is invalid
 * SIDE EFFECTS: prints (using printf) the number of matches found and increments guess_number(valid guess) 
 *               or an error message (invalid guess)
 *               (NOTE: the output format MUST MATCH EXACTLY, check the wiki writeup)
 */
int
make_guess (const char guess_str[], int* one, int* two, 
	    int* three, int* four)
{
	char post[2];
	int paired1 = 0; //values of if the guess and solution are paired
	int paired2 = 0;
	int paired3 = 0;
	int paired4 = 0;
	int paireds1 = 0; //value of if the guess is paired with misplacednum
	int paireds2 = 0;
	int paireds3 = 0;
	int paireds4 = 0;
	int ret;
	int correctnum = 0;
	int misplacednum = 0;
	int w;
	int x;
	int y;
	int z;
	
	
	ret = sscanf (guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post); //scans guess into 4 variables
	if (ret != 4){
		printf("make_guess: invalid guess\n"); //if there are not four values entered, invalid guess
		return 0;
	}
	*one = w; //set each equal to their respective num
	*two = x;
	*three = y;
	*four = z;
	if ((w < 1 || w > 8) || (x < 1 || x > 8) || (y < 1 || y > 8) || (z < 1 || z > 8)){
		printf("make_guess: invalid guess\n"); //if values are not between 1 and 8, invalid guess
		return 0;
	}



	if (*one == solution1){ //if the guess is equal to solution, pair it, and increment correctnum
		paired1 = 1;
		correctnum++;
		paireds1 = 1;
	}
	if (*two == solution2){
		paired2 = 1;
		correctnum++;
		paireds2 = 1;
	}
	if (*three == solution3){
		paired3 = 1;
		correctnum++;
		paireds3 = 1;
	}
	if (*four == solution4){
		paired4 = 1;
		correctnum++;
		paireds4 = 1;
	}
	if (paired1 == 0){ //if first solution is not paired, check if the first guess is equal to a different number that is also not paired
		if (*one == solution2 && paireds2 == 0){
			misplacednum++;
			paireds2 = 1;
		}
		else if (*one == solution3 && paireds3 == 0){
			misplacednum++;
			paireds3 = 1;
		}
		else if (*one == solution4 && paireds4 == 0){
			misplacednum++;
			paireds4 = 1;
		}
	}
	if (paired2 == 0){
		if (*two == solution1 && paireds1 == 0){
			misplacednum++;
			paireds1 = 1;
		}
		else if (*two == solution3 && paireds3 == 0){
			misplacednum++;
			paireds3 = 1;
		}
		else if (*two == solution4 && paireds4 == 0){
			misplacednum++;
			paireds4 = 1;
		}
	}
	if (paired3 == 0){
		if (*three == solution1 && paireds1 == 0){
			misplacednum++;
			paireds1 = 1;
		}
		else if (*three == solution2 && paireds2 == 0){
			misplacednum++;
			paireds2 = 1;
		}
		else if (*three == solution4 && paireds4 == 0){
			misplacednum++;
			paireds4 = 1;
		}
	}
	if (paired4 == 0){
		if (*four == solution1 && paireds1 == 0){
			misplacednum++;
			paireds1 = 1;
		}
		else if (*four == solution2 && paireds2 == 0){
			misplacednum++;
			paireds2 = 1;
		}
		else if (*four == solution3 && paireds3 == 0){
			misplacednum++;
			paireds3 = 1;
		}
	}
			
	printf("With guess %d, you got %d perfect matches and %d misplaced matches.\n", guess_number, correctnum, misplacednum); //print statement
	guess_number++; //you have made one more guess
	return 1;
}

