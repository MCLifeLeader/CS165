/**************************************************************************
* Program:
*    Homework 3, CS165
* Author:
*    Brother Michael Carey
* Summary:
*    To find all of the prime numbers between 2 and an upper value.
*    
* Work log:
*    Date     Start Stop  Interruption Work
*    mm/dd/yy hh:mm hh:mm mmm          mmm
 *************************************************************************/
#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

// Allocate memory and create the number array list
void AllocNumberArrayList( int *&iPrimeValueArray, int &iMaxPrimeValue );
// Find all the prime numbers
void FindAllPrimeNumbers( int *&iPrimeValueArray, int iMaxPrimeValue );
// Display the prime numbers
void DisplayPrimeNumbers( const int *iPrimeValueArray, int iMaxPrimeValue );
// Get a user inputted value of y or Y to run the program again.
bool DoAgain( void );
// Get user input and give it an int value.
void GetUserInput( char *sUserQuestion, int &iUsersValue );

/**************************************************************************
   Purpose:
      Main application entry point
   Input:
      int, char *[]
   Output:
      none
   Return:
      int
   Parameters:
      Program return code ( number of command line arguments,
      the command line arguments listed )
**************************************************************************/

int main( int argc, char *argv[] )
{
   // By default we want to have prime numbers to 100.
   int iMaxPrimeValue = 100;
   int *iPrimeValueArray = NULL;

   // Check the argument length. Is there enough arguments to attempt to
   // process the users request
   if( argc == 2 )
   {
      // Get the command line value
      iMaxPrimeValue = atoi( argv[ 1 ] );
   }
   else if( argc > 1 )   // Check the users cmd line arg length.
   {
      // tell the user how to use the program if they enter the
      // wrong number of arguments on the command line.
      cout << "Usage: car03009-3 ANumber\n\n";
      return( 1 );
   }

   do
   {
      cout << "\n\n";

      // Keep looping until the user enters a valid value
      while( iMaxPrimeValue < 2 )
         GetUserInput( "Enter a Positive Number: ", iMaxPrimeValue );

      // Allocate memory for the array
      AllocNumberArrayList( iPrimeValueArray, iMaxPrimeValue );
      // Find the prime numbers
      FindAllPrimeNumbers( iPrimeValueArray, iMaxPrimeValue );
      // Display the results
      DisplayPrimeNumbers( iPrimeValueArray, iMaxPrimeValue );

      // Check to see if there was any memory allocated if so
      // free it up
      if( iPrimeValueArray )
         delete [] iPrimeValueArray;

      // Set the pointer back to NULL for error checking purposes
      iPrimeValueArray = NULL;
      // Set iMaxPrimeValue to zero so we can run the process again.
      iMaxPrimeValue = 0;

   } while( DoAgain( ) );

   return( 0 );
}

/**************************************************************************
   Purpose:
      Allocate memory for the number array
   Input:
      int *&, int &
   Output:
      int *&, int &
   Return:
      void
   Parameters:
      void( pointer to a reference to an int array
            , reference to an int which is the max value to search for a
            prime number )
**************************************************************************/
void AllocNumberArrayList( int *&iPrimeValueArray, int &iMaxPrimeValue )
{
   // The ++ makes sure we have the right number of memory
   // elements
   iPrimeValueArray = new int [ ++iMaxPrimeValue ];

   // Fill the array with values
   for( int iCount = 0; iCount < iMaxPrimeValue; iCount++ )
      iPrimeValueArray[ iCount ] = iCount;
}


/**************************************************************************
   Purpose:
      To Find all of the prime numbers given a max value to search to.
   Input:
      int *&, int
   Output:
      int *&
   Return:
      void
   Parameters:
      void( pointer to a reference to an int array
            , an int which is the max value to search for a
            prime number )
**************************************************************************/

void FindAllPrimeNumbers( int *&iPrimeValueArray, int iMaxPrimeValue )
{
   // Search and destroy non-prime numbers!
   for( int iCount = 2; iCount < iMaxPrimeValue; iCount++ )
   {
      // if the array value is 0 then we have already removed that
      // value from the list, skip to the next one in the list
      if( iPrimeValueArray[ iCount ] )
      {
         // This for loop is the actual loop the finds the prime numbers
         for( int iPrimeFinder = iCount; iPrimeFinder < iMaxPrimeValue;
                  iPrimeFinder += iCount )
         {
            // if the iCount value and the iPrimeFinder != then it is
            // not a prime number.
            // ie when iCount first comes into this loop it should be
            // the prime number already, skip to the next value in the
            // loop.
            if( iPrimeFinder != iCount )
               iPrimeValueArray[ iPrimeFinder ] = 0;
         }
      }
   }
}

/**************************************************************************
   Purpose:
      To display all of the prime numbers found
   Input:
      int *, int
   Output:
      none
   Return:
      void
   Parameters:
      void( constant pointer to an int array
            , an int which is the max value to search for a
            prime number )
**************************************************************************/

void DisplayPrimeNumbers( const int *iPrimeValueArray, int iMaxPrimeValue )
{
   int iDisplayCount = 0;  // counter to display only 10 across.

   // loop through the array to display the valid prime numbers
   for( int iCount = 2; iCount < iMaxPrimeValue; iCount++ )
   {
      // if the value in the iPrimeValueArray is != 0 then
      // display that value
      if( iPrimeValueArray[ iCount ] != 0 )
      {
         iDisplayCount++;
         cout << iPrimeValueArray[ iCount ] << " ";

         // if the 10th item then print a \n to the screen after it.
         if( iDisplayCount % 10 == 0 )
            cout << "\n";
         }
   }
   cout << "\n\n";
}

/**************************************************************************
   Purpose:
      Request from the user weather they desire to check more numbers
   Input:
      void
   Output:
      none
   Return:
      bool
   Parameters:
      true to repeat ( void )
 **************************************************************************/

bool DoAgain( void )
{
   // By default we do not want to do this loop again.
   bool bDoAgain = false;
   char sUserInput[ 20 ] = {0};

   cout << "\nEnter Y or y to repeat, any other character ends: ";
   cin >> sUserInput;

   if( !strcmp( "y", sUserInput ) || !strcmp( "Y", sUserInput ) )
      bDoAgain = true;

   return( bDoAgain );
}

/**************************************************************************
   Purpose:
      To get a users inputted value and convert it to a float value
   Input:
      char *, int &
   Output:
      int &
   Return:
      float
   Parameters:
      void ( A question to a user, Reference to an int return user value )
 **************************************************************************/

void GetUserInput( char *sUserQuestion, int &iUsersValue )
{
   char *sUserInput = NULL;

   // allocate some memory for a char array
   sUserInput = new char [ 20 ];

   // Force the loop to continue until broken
   while( 1 )
   {
      cout << sUserQuestion;
      cin >> sUserInput;

      iUsersValue = atoi( sUserInput );

      // Return if Value greater than 0
      if( iUsersValue > 0 )
         break;
   }

   // clean up memory from char array
   delete [] sUserInput;
   sUserInput = NULL;
}
