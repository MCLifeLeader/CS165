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

// Allocate memory and create the number array list
void AllocNumberArrayList( int *&iPrimeValueArray, int &iMaxPrimeValue );
// Find all the prime numbers
void FindAllPrimeNumbers( int *&iPrimeValueArray, int iMaxPrimeValue );
// Display the prime numbers
void DisplayPrimeNumbers( int *iPrimeValueArray, int iMaxPrimeValue );
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
   int *iPrimeValueArray = NULL;

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

      // Allocate memory for the array
      AllocNumberArrayList( iPrimeValueArray, iMaxPrimeValue );
      // Find the prime numbers
      FindAllPrimeNumbers( iPrimeValueArray, iMaxPrimeValue );
      // Displays the prime factorization of iMaxPrimeValue
      DisplayPrimeNumbers( iPrimeValueArray, iMaxPrimeValue );

      // Check to see if there was any memory allocated if so
      // free it up
      if ( iPrimeValueArray )
         delete [] iPrimeValueArray;

      // Set the pointer back to NULL for error checking purposes
      iPrimeValueArray = NULL;
      // Set iMaxPrimeValue to zero so we can run the process again.
      iMaxPrimeValue = 0;
   } while ( DoAgain( ) );

   return ( 0 );
}

/**************************************************************************
*   Purpose:
*      Allocate memory for the number array
*   Input:
*      int *&, int &
*   Output:
*      int *&, int &
*   Return:
*      void
*   Parameters:
*   void( pointer to a reference to an int array
*      , reference to an int which is the max value to search for a
*      prime number )
**************************************************************************/
void AllocNumberArrayList( int *&iPrimeValueArray, int &iMaxPrimeValue )
{
   // The ++ makes sure we have the right number of memory
   // elements
   iPrimeValueArray = new int [ ++iMaxPrimeValue ];

   // Fill the array with values
   for ( int iCount = 0; iCount < iMaxPrimeValue; iCount++ )
      iPrimeValueArray[ iCount ] = iCount;
}


/**************************************************************************
*   Purpose:
*      To Find all of the prime numbers given a max value to search to.
*   Input:
*      int *&, int
*   Output:
*      int *&
*   Return:
*      void
*   Parameters:
*      void( pointer to a reference to an int array
*            , an int which is the max value to search for a
*            prime number )
**************************************************************************/
void FindAllPrimeNumbers( int *&iPrimeValueArray, int iMaxPrimeValue )
{
   // Search and destroy non-prime numbers!
   for ( int iCount = 2; iCount < iMaxPrimeValue; iCount++ )
   {
      // if the array value is 0 then we have already removed that
      // value from the list, skip to the next one in the list
      if ( iPrimeValueArray[ iCount ] )
      {
         // This for loop is the actual loop the finds the prime numbers
         for ( int iPrimeFinder = iCount; iPrimeFinder < iMaxPrimeValue;
                  iPrimeFinder += iCount )
         {
            // if the iCount value and the iPrimeFinder != then it is
            // not a prime number.
            // ie when iCount first comes into this loop it should be
            // the prime number already, skip to the next value in the
            // loop.
            if ( iPrimeFinder != iCount )
               iPrimeValueArray[ iPrimeFinder ] = 0;
         }
      }
   }
}

/**************************************************************************
*   Purpose:
*      Find and display the prime factorization of iMaxPrimeValue
*   Input:
*      int *, int
*   Output:
*      none
*   Return:
*      void
*   Parameters:
*      void( constant pointer to an int array
*            , an int which is the max value to search for a
*            prime number )
**************************************************************************/
void DisplayPrimeNumbers( int *iPrimeValueArray, int iMaxPrimeValue )
{
   int iPrimeValue;
   int iCount;
   int iMaxPrimeValueTemp;

   iMaxPrimeValue--;
   iMaxPrimeValueTemp = iMaxPrimeValue;

   iPrimeValue = iCount = 2;

   // This is where my Stack is located
   stack < int, vector < int > > myStack;

   while ( ( iCount < iMaxPrimeValueTemp + 1 ) &&
           ( iMaxPrimeValueTemp != 1 ) )
   {
      if ( iPrimeValueArray[ iCount ] )
      {
         iPrimeValue = iPrimeValueArray[ iCount ];

         while ( ( iMaxPrimeValueTemp % iPrimeValue == 0 ) )
         {
            iMaxPrimeValueTemp /= iPrimeValue;
            myStack.push( iPrimeValue );
         }
      }

      iCount++;
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
