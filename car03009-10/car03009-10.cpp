/***********************************************************************
* Program:
*    Homework 10, Working with File IO
*    Brother Cameron, CS 165
* Author:
*    Brother Michael Carey
* Summary:
*    This program demonstrates how to use file stream reads
***********************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

using namespace std;

/*************************************************************************
*   Class:
*     Deviation
*   Purpose:
*     To calculate a average and a deviation from a data file
*************************************************************************/
class Deviation
{
public:
   Deviation();
   void openFile( const char *CFILENAME );
   void calculateAverage( void );
   void calculateDevation( void );
   void printDevation( void );

private:
   string sFileName;
   double dAverage;
   double dDeviation;
   double dCounter;
};

/*************************************************************************
*   Purpose:
*      main function for using Set class
*   Input:
*      void
*   Output:
*      none
*   Return:
*      int
*   Parameters:
*      Program return value ( void ).
**************************************************************************/
int main( int argc, char *argv[] )
{
   Deviation devObj;

   if ( argc > 1 )
      devObj.openFile( argv[ 1 ] );
   else
      devObj.openFile( "items.dat" );

   devObj.calculateAverage( );
   devObj.calculateDevation( );
   devObj.printDevation( );

   return ( 0 );
}

/*************************************************************************
*   Purpose:
*      Default Constructor
*   Input:
*      none
*   Output:
*      none
*   Return:
*      none
*   Parameters:
*      none ( none )
**************************************************************************/
Deviation::Deviation()
{
   dAverage = dDeviation = dCounter = 0;
   sFileName = "items.dat";
}

/*************************************************************************
*   Purpose:
*      To get the ifstream object a name to open the file with
*   Input:
*      const char *
*   Output:
*      none
*   Return:
*      void
*   Parameters:
*      void ( the file name to open )
**************************************************************************/
void Deviation::openFile( const char *CFILENAME )
{
   dAverage = dDeviation = dCounter = 0;
   sFileName = CFILENAME;
}

/*************************************************************************
*   Purpose:
*      To calculate the average of some numbers
*   Input:
*      void
*   Output:
*      none
*   Return:
*      void
*   Parameters:
*      void ( void )
**************************************************************************/
void Deviation::calculateAverage( void )
{
   char cRead        = 0;
   double dTemp      = 0;
   string strNumber  = "";

   // file stream object
   ifstream ifFile( sFileName.c_str() );

   // is the file open
   if ( !ifFile.is_open() )
   {
      cerr << "Unable to open file " << sFileName;
      cerr << ".\nThe file does not exist or ";
      cerr << "you do not have permissions to access it.\n";
      exit( 1 );
   }

   // read the file until the end
   while ( !ifFile.eof( ) )
   {
      // get some data
      ifFile >> dTemp;

      // protect vs. extra data read of null character
      if ( !ifFile.eof() || dTemp )
      {
         // count how many items
         dCounter++;
         // add the items as a whole
         dAverage += dTemp;
      }

      dTemp = 0;
   }

   // generate the average
   dAverage /= dCounter;

   // close the file
   ifFile.close();
}

/*************************************************************************
*   Purpose:
*      To calculate the deviation of a series of numbers
*   Input:
*      void
*   Output:
*      none
*   Return:
*      void
*   Parameters:
*      void ( void )
**************************************************************************/
void Deviation::calculateDevation( void )
{
   char cRead        = 0;
   double dTemp      = 0;
   string strNumber  = "";

   // check to see if average is zero if it is call
   if ( dAverage == 0 )
      calculateAverage( );

   if ( dCounter == 0 )
   {
      cerr << "No data was read in exiting\n";
      exit( 1 );
   }

   // file stream object
   ifstream ifFile( sFileName.c_str() );

   // check to see if the file is open
   if ( !ifFile.is_open() )
   {
      cerr << "Unable to open file " << sFileName;
      cerr << ".\nThe file does not exist or ";
      cerr << "you do not have permissions to access it.\n";
      exit( 1 );
   }

   // read until we reach the end of file
   while ( !ifFile.eof( ) )
   {
      // get some data
      ifFile >> dTemp;

      // protect vs. extra data read of null character
      if ( !ifFile.eof() || dTemp )
         dDeviation += pow( (dTemp - dAverage), 2 );   // do the math

      dTemp = 0;
   }

   // calculate the deviation
   dDeviation /= dCounter;
   dDeviation = sqrt( dDeviation );

   // close the file
   ifFile.close();
}

/*************************************************************************
*   Purpose:
*      To display the numbers that where calculated
*   Input:
*      none
*   Output:
*      none
*   Return:
*      none
*   Parameters:
*      none ( none )
**************************************************************************/
void Deviation::printDevation( void )
{
   cout.flags( ios::right );
   cout.setf( ios::fixed );
   cout.setf( ios::showpoint );
   cout.precision( 2 );

   // display all the data nice and pretty like.
   cout << endl << endl;
   cout.width( 25 );
   cout << "Number of data items: " << dCounter << endl;
   cout.width( 25 );
   cout << "Average: " << dAverage << endl;
   cout.width( 25 );
   cout << "Standard Deviation: " << dDeviation << endl;
   cout << endl << endl;

}
