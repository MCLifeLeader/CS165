/**************************************************************************
* Program:
*    Homework 2, CS165 Calculate clothing sizes
* Author:
*    Brother Michael Carey
* Summary:
*    This program calculates clothing sizes based on
*    Height
*    Weight
*    Age
* Work log:
*    Date     Start Stop  Interruption Work
*    mm/dd/yy hh:mm hh:mm mmm          mmm
 *************************************************************************/

#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

// Return and Report user information.
void Report( float fHatSize, float fJacketSize, float fWaistSize );
// Calculate Hat Size.
float CalculateHatSize( float fWeight, float fHeight );
// Calculate Jacket Size.
float CalculateJacketSize( float fWeight, float fHeight, int iAge );
// Calculate Waist Size.
float CalculateWaistSize( float fWeight, int iAge );
// Get a user inputted value of y or Y to run the program again.
bool DoAgain( void );
// Get a user inputted value return float.
float GetUserInput( char *sUserQuestion );


/**************************************************************************
   Purpose:
      Main application starting point for gathering and reporting
      to the user the requested calculations
   Input:
      int, char *[]
   Output:
      none
   Return: 
      int
   Parameters:
      Program return value ( Number of command line arguments found,
                             What those command line arguments were.
 *************************************************************************/

int main( int argc, char *argv[] )
{
   // Init my variables
   int iAge      = 0;  // A Persons Age

   float fHeight = 0;  // A Persons Height
   float fWeight = 0;  // A Persons Weight

   // Check the argument length. Is there enough arguments to attempt to
   // process the the users request
   if( argc > 3 )
   {
      fHeight  = ( float ) atof( argv[ 1 ] );
      fWeight  = ( float ) atof( argv[ 2 ] );
      iAge     = atoi( argv[ 3 ] );
   }
   else if( argc > 1 )   // Check the users cmd line arg length.
   {
      // Tell the user how to use the program.
      cout << "Usage: car03009-2 Height Weight Age\n\n";

      return( 1 );
   }

   do
   {
      cout << "\n\n";

      // If the value is invalid have the user input it again
      if( fHeight <= 0)
         fHeight = GetUserInput( "Height (in inches): " );

      // If the value is invalid have the user input it again
      if( fWeight <= 0)
         fWeight = GetUserInput( "Weight (in pounds): " );

      // If the value is invalid have the user input it again
      if( iAge <= 0)
         iAge = ( int ) GetUserInput( "Age (in years): " );

      // calculate the values out and report to the user
      Report(  CalculateHatSize(    fWeight, fHeight ), 
               CalculateJacketSize( fWeight, fHeight, iAge ), 
               CalculateWaistSize(  fWeight, iAge ) 
            );

      // Reset the variables for use again if the user selects y
      fHeight = fWeight = 0;
      iAge = 0;

   } while( DoAgain( ) );

   return( 0 );
}

/**************************************************************************
   Purpose:
      Calculate a persons hat size
   Input:
        float, float
   Output: 
      none
   Return: 
      float
   Parameters:
      A persons hat size ( Persons weight, Persons height )
 *************************************************************************/

float CalculateHatSize( float fWeight, float fHeight )
{
   return( ( float )( ( fWeight / fHeight ) * 2.9 ) );
}

/**************************************************************************
   Purpose:
      Calculate a persons jacket size
   Input: 
      float, float, int
   Output: 
      none
   Return: 
      float
   Parameters:
      A persons Jacket size ( Persons weight, Persons height, Persons age )
 *************************************************************************/

float CalculateJacketSize( float fWeight, float fHeight, int iAge )
{
   const float ONEEIGTH = 0.125;
   float fJacketSize = 0;
   int iAdjustedSize = 0;

   fJacketSize = ( fWeight * fHeight ) / 288;

   // adjust the fJacketSize only if the
   // person is older than 30
   // dividing by 10 to create an easy multiplier value
   if( ( iAdjustedSize = iAge / 10 ) > 3 ) 
      fJacketSize += ( ONEEIGTH * ( iAdjustedSize - 3 ) );

   return( fJacketSize );
}

/**************************************************************************
   Purpose:
      Calculate a persons waist size
   Input:
      float, int
   Output:
      none
   Return:
      float
   Parameters:
      A persons waist size ( Persons weight, Persons age )
 *************************************************************************/

float CalculateWaistSize( float fWeight, int iAge )
{
   const float ONETENTH = ( float ) 0.1;
   float fWaistSize = 0;

   fWaistSize = ( float )( fWeight / 5.7 );

   // adjust the fWaistSize value only if the person is
   // over 28 years of age.
   if( iAge > 28 )
   {
      for( int iCount = iAge; iCount > 28; iCount-- )
      {
         if( iCount % 2 == 0 )
            fWaistSize += ONETENTH;
      }
   }

   return( fWaistSize );
}

/**************************************************************************
   Purpose:
      Report to the user the evaluated calculations
   Input:
      float, float, float
   Output:
      none
   Return:
      void
   Parameters:
      void ( Persons hat size, Persons jacket size, Persons waist size )
 *************************************************************************/

void Report( float fHatSize, float fJacketSize, float fWaistSize )
{
   // String format settings
   cout.setf(ios::right);
   cout.setf(ios::fixed);
   cout.setf(ios::showpoint);
   cout.precision(2);

   // Report to the user the results
   cout << "\n\nHat Size: " << fHatSize;
   cout << "\nJacket Size: " << fJacketSize;
   cout << "\nWaist Size: " << fWaistSize;
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
 *************************************************************************/

bool DoAgain( void )
{
   // By default we do not want to do this loop again.
   bool bDoAgain = false;
   char *sUserInput = NULL;

   // Allocate some memory for a char array
   sUserInput = new char [ 20 ];

   cout << "\nEnter Y or y to repeat, any other character ends: ";
   cin >> sUserInput;

   if( !strcmp( "y", sUserInput ) || !strcmp( "Y", sUserInput ) )
      bDoAgain = true;

   // Clean up memory from char array
   delete [] sUserInput;
   sUserInput = NULL;

   return( bDoAgain );
}

/**************************************************************************
   Purpose:
      To get a users inputted value and convert it to a float value
   Input:
      char *
   Output:
      none
   Return:
      float
   Parameters:
      Users returned value( A question to a user )
 *************************************************************************/

float GetUserInput( char *sUserQuestion )
{
   char *sUserInput = NULL;
   float fUserValue = 0;

   // allocate some memory for a char array
   sUserInput = new char [ 20 ];

   // Force the loop to continue until broken
   while( 1 )
   {
      cout << sUserQuestion;
      cin >> sUserInput;

      fUserValue = ( float ) atof( sUserInput );

      // Return if Value greater than 0
      if( fUserValue > 0 )
         return( fUserValue );
   }

   // clean up memory from char array
   delete [] sUserInput;
   sUserInput = NULL;
}

