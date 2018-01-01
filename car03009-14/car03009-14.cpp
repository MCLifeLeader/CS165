/***********************************************************************
* Program:
*    Homework 14, STL 
*    Brother Cameron, CS 165
* Author:
*    Brother Michael Carey
* Summary:
*    This program demonstrates the use of the STL using the stack data
*    structure type
* Note:
*    Style checker has an issue with '*&' no matter where I put it.
*    Weather it is next to the int in the middle or next to the variable.
***********************************************************************/
#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <stack>
using namespace std;

// Display the prime numbers
void DisplayPrimeNumbers( int iMaxPrimeValue );
// Get a user inputted value of y or Y to run the program again.
bool DoAgain( void );
// Get user input and give it an int value.
void GetUserInput( char *sUserQuestion, int &iUsersValue );

/**************************************************************************
*   Purpose:
*      Main application entry point
*   Input:
*      int, char *[]
*   Output:
*      none
*   Return:
*      int
*   Parameters:
*      Program return code ( number of command line arguments,
*      the command line arguments listed )
**************************************************************************/
int main( int argc, char *argv[] )
{
   int iMaxPrimeValue = 0;

   // Check the argument length. Is there enough arguments to attempt to
   // process the users request
   if ( argc == 2 )
   {
      // Get the command line value
      iMaxPrimeValue = atoi( argv[ 1 ] );
   }
   else if ( argc > 1 )   // Check the users cmd line arg length.
   {
      // tell the user how to use the program if they enter the
      // wrong number of arguments on the command line.
      cout << "Usage: car03009-14 Number\n\n";
      return ( 1 );
   }

   do
   {
      cout << "\n\n";

      // Keep looping until the user enters a valid value
      while ( ( iMaxPrimeValue < 2 ) && ( iMaxPrimeValue < sizeof ( int ) ) )
         GetUserInput( "Enter a Positive integer: ", iMaxPrimeValue );

      DisplayPrimeNumbers( iMaxPrimeValue );

      // Set iMaxPrimeValue to zero so we can run the process again.
      iMaxPrimeValue = 0;
   } while ( DoAgain( ) );

   return ( 0 );
}

/**************************************************************************
*   Purpose:
*      Calculate and print the prime number value for the desgnated int
*   Input:
*      void
*   Output:
*      none
*   Return:
*      bool
*   Parameters:
*      true to repeat ( int )
***************************************************************************/
void DisplayPrimeNumbers( int iMaxPrimeValue )
{
   int iPrimeValue;
   int iMaxPrimeValueTemp;

   iMaxPrimeValueTemp = iMaxPrimeValue;

   iPrimeValue = 2;

   // This is where my Stack is located
   stack < int, vector < int > > myStack;

   while( ( iMaxPrimeValueTemp != 1 ) )
   {
      if( !( iMaxPrimeValueTemp % iPrimeValue ) )
      {
         iMaxPrimeValueTemp /= iPrimeValue;
         myStack.push( iPrimeValue );
      }
      else
         iPrimeValue++;
   }

   cout << "Prime Factorization of " << iMaxPrimeValue << " is:";

   //11 * 5 * 3 * 3 * 2 * 2 * 2
   while ( !myStack.empty() )
   {
      if ( myStack.size() > 1 )
         cout << " " << myStack.top() << " *";
      else
         cout << " " << myStack.top() << endl;
      myStack.pop();
   }
}

/**************************************************************************
*   Purpose:
*      Request from the user weather they desire to check more numbers
*   Input:
*      void
*   Output:
*      none
*   Return:
*      bool
*   Parameters:
*      true to repeat ( void )
***************************************************************************/
bool DoAgain( void )
{
   // By default we do not want to do this loop again.
   bool bDoAgain = false;
   char *sUserInput = NULL;

   // Allocate some memory for a char array
   sUserInput = new char [ 20 ];

   cout << "\nEnter Y or y to repeat, any other character ends: ";
   cin >> sUserInput;

   if ( !strcmp( "y", sUserInput ) || !strcmp( "Y", sUserInput ) )
      bDoAgain = true;

   // Clean up memory from char array
   delete [] sUserInput;
   sUserInput = NULL;

   return ( bDoAgain );
}

/**************************************************************************
*   Purpose:
*      To get a users inputted value and convert it to a float value
*   Input:
*      char *, int &
*   Output:
*      int &
*   Return:
*      float
*   Parameters:
*      void ( A question to a user, Reference to an int return user value )
***************************************************************************/
void GetUserInput( char *sUserQuestion, int &iUsersValue )
{
   char *sUserInput = NULL;

   // allocate some memory for a char array
   sUserInput = new char [ 20 ];

   // Force the loop to continue until broken
   while ( 1 )
   {
      cout << sUserQuestion;
      cin >> sUserInput;

      iUsersValue = atoi( sUserInput );

      // Return if Value greater than 0
      if ( iUsersValue > 0 )
         break;
   }

   // clean up memory from char array
   delete [] sUserInput;
   sUserInput = NULL;
}
