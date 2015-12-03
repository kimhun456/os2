/**
 * Solution to dining philosophers using POSIX mutexes and condition varaibles.
 *
 * Operating System Concepts - Ninth Edition
 * John Wiley & Sons - 2013.
 */

#include <pthread.h>
#include <stdio.h>
#include "dp.h"

/* return the left neighbor */
int left_neighbor(int number)
{
	if (number == 0)
		return NUMBER - 1;
	else
		return number - 1;
}

/* return the right neighbor */
int right_neighbor(int number)
{
	if (number == NUMBER - 1)
		return 0;
	else
		return number + 1;
}

void test(int i)
{
	/** 
	 * Basic idea is this:
	 * If I'm hungry, and my left and right neighbors aren't eating, then let me eat.
	 */
	/****************************
	* FILL IN YOUR CODE HERE
	*****************************/

}

/**
 * A philosopher calls this when it 
 * wants to pick up its forks.
 */

void pickup_forks(int number)
{
	/****************************
	* FILL IN YOUR CODE HERE
	*****************************/
}

/**
 * A philosopher calls this when it 
 * wants to return its forks.
 */

void return_forks(int number)
{
	/****************************
	* FILL IN YOUR CODE HERE
	*****************************/
}
