/***********************************************************************
* Program:
*    Homework 7, Working with Classes overloaded operators
*    Brother Cameron, CS 165
* Author:
*    Brother Michael Carey, Portions provided by Brother Cameron.
* Summary:
*    This program demonstrates the use of overloaded operators to make
*    various comparisons in two sets of randomly generated numbers using
*    a personally defined class
***********************************************************************/

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <time.h>
#include <math.h>

using namespace std;

/******************************************************************
 *
 *  Class: Random
 *
 ******************************************************************/
class Random
{
public:
  Random();

  /* --- Get next integer in range low-high --- */
  int nextInt( const int LOW, const int HIGH );
};

// max size of iNumberList array
const int MAX_NUMBER_LIST = 75;

/*************************************************************************
*   class:
*      Set
*   Purpose:
*
*************************************************************************/
class Set
{
public:
   Set();                        // Default Constructor
   Set( int iInitArrayValue );   // Overloaded
   int getSize( void );          // Return Size
   int getArrItm( int iItem );         // Get Array Element Item
   bool isNumberInList( int iNumber ); // is a number in the list
   bool addNumber( int iNumber );      // add the number to the list
   void operator = ( Set objSet );    // copy object values

private:
   int iArraySize;                     // The lenght of the array
   int iNumberList[ MAX_NUMBER_LIST ]; // The array
};

// Difference
Set operator -  ( Set &objSet1, Set &objSet2 );
// Intersection
Set operator && ( Set &objSet1, Set &objSet2 );
// Union
Set operator || ( Set &objSet1, Set &objSet2 );
// using ostream for output
ostream &operator << ( ostream &objStream, Set &objSet );

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
int main( void )
{

   Random randnum;
   Set obj1( 0 );
   Set obj2( 0 );
   Set obj3( 0 );

   // --- Create set A
   while ( obj1.getSize() < 50 )
      obj1.addNumber( randnum.nextInt( 0, 99 ) );

   // --- Create set B
   while ( obj2.getSize() < 25 )
      obj2.addNumber( randnum.nextInt( 0, 99 ) );

   // --- Output set A and B
   cout << "Set Program Output: " << endl << endl;
   cout << "Set A: " << endl;
   cout << obj1 << endl << endl;
   cout << "Set B: " << endl;
   cout << obj2 << endl << endl;

   // --- Intersection
   obj3 = obj1 && obj2;
   cout << "Intersection of A and B: " << endl;
   cout << obj3 << endl << endl;

   // --- Union
   obj3 = obj1 || obj2;
   cout << "Union of A and B: " << endl;
   cout << obj3 << endl << endl;

   // --- Difference
   obj3 = obj1 - obj2;
   cout << "Difference of A and B: " << endl;
   cout << obj3 << endl << endl;

   // --- Difference
   obj3 = obj2 - obj1;
   cout << "Difference of B and A: " << endl;
   cout << obj3 << endl << endl;

   return( 0 );
}

/*********************************************************
 *
 *    FUNCTION: Random
 *
 *  PARAMETERS: None
 *
 *     PURPOSE: Random constructor.  Sets the random number
 *              seed to the current time.  The srand function
 *              is provided by stdlib.h and time by time.h
 *              Passing NULL to the time function returns
 *              the current time (in clock ticks) and this
 *              is then passed to srand.
 *
 *       USAGE: Creates a random object to generate random numbers
 *
 *              Random r1;
 *
 *********************************************************/
Random::Random()
{
  srand( ( int ) time( NULL ) );
}

/*********************************************************
 *
 *    FUNCTION: nextInt
 *
 *  PARAMETERS: low - smallest number in range
 *              high - largest number in range
 *
 *     PURPOSE: This function does the following:
 *                1. Generate a real number between 0 and 1
 *                   by calling rand() and dividing by
 *                   the constant RAND_MAX + 1
 *                2. Scale this number to the appropriate range
 *                   size (high - low)
 *                3. Truncate the value to an integer
 *                4. Translate the number to the appropriate
 *                   starting point.
 *
 *        USAGE: Assumes random object has been created.
 *               This call will create 1 random number between
 *               1 and 50.
 *
 *               num = r1.nextInt( 1, 50 );
 *
 *******************************************************/
int Random::nextInt( const int LOW, const int HIGH)
{
  int k;
  double d;

  d = ( double ) rand() / ( ( double ) RAND_MAX + 1 );
  k = ( int )( d * ( HIGH - LOW + 1 ) );
  return( LOW + k );
}

/*************************************************************************
*   Purpose:
*      Default Constructor to init an empty array
*   Input:
*      none
*   Output:
*      none
*   Return:
*      none
*   Parameters:
*      none
**************************************************************************/
Set::Set()
{
   // Set values to NULL
   for( int iCount = 0; iCount < MAX_NUMBER_LIST; iCount++ )
      iNumberList[ iCount ] = '\0';
   
   iArraySize = 0;
}

/*************************************************************************
*   Purpose:
*      init array with a user defined value.
*   Input:
*      const int 
*   Output:
*      none
*   Return:
*      Set
*   Parameters:
*      returns Set object ( constant int value )
**************************************************************************/
Set::Set( int iInitArrayValue )
{
   // Set values to iInitArrayValue
   for( int iCount = 0; iCount < MAX_NUMBER_LIST; iCount++ )
      iNumberList[ iCount ] = iInitArrayValue;
   
   iArraySize = 0;
}

/*************************************************************************
*   Purpose:
*      Get the number of used elements in the array.
*   Input:
*      void
*   Output:
*      none
*   Return:
*      int
*   Parameters:
*      returns size array ( void )
**************************************************************************/
int Set::getSize( void )
{
   return( iArraySize );
}

/*************************************************************************
*   Purpose:
*      Get an element number and return it given a position in the array.
*   Input:
*      const int
*   Output:
*      none
*   Return:
*      int
*   Parameters:
*      returns an element from the array ( index point in array )
**************************************************************************/
int Set::getArrItm( int iItem )
{
   // Get a number from the array stored in the class
   if( ( iItem <= MAX_NUMBER_LIST ) || ( iItem >= 0 ) )
      return( iNumberList[ iItem ] );

   return( -1 );
}

/*************************************************************************
*   Purpose:
*      Add a unique element to the array.
*   Input:
*      const int
*   Output:
*      none
*   Return:
*      Set
*   Parameters:
*      returns true if element is added ( number to add to the array )
**************************************************************************/
bool Set::addNumber( int iNumber )
{
   // By default the number has not been added
   bool bIsNumberAdded = false;

   // check to see if we have room to add a value to the array
   if( iArraySize <= MAX_NUMBER_LIST )
   {
      // Check to see if the number is already in the array
      if( !( bIsNumberAdded = isNumberInList( iNumber ) ) )
         iNumberList[ iArraySize++ ] = iNumber; // Add the number, move index
   }

   // return the result if added or not
   return( !bIsNumberAdded );
}

/*************************************************************************
*   Purpose:
*      Check to see if a number is already in the list
*   Input:
*      const int
*   Output:
*      none
*   Return:
*      Set
*   Parameters:
*      returns true if number is present ( number to check in the array )
**************************************************************************/
bool Set::isNumberInList( int iNumber )
{
   // By default the number is not in the array
   bool bIsNumberPresent = false;

   for( int iCount = 0; iCount < iArraySize; iCount++ )
   {
      // If the number is present set the flag to true and break;
      if( iNumberList[ iCount ] == iNumber )
      {
         bIsNumberPresent = true;
         break;
      }
   }

   // return the result if present or not
   return( bIsNumberPresent );
}

/*************************************************************************
*   Purpose:
*      To create a Set object with the differences between two Set objects
*   Input:
*      Set &, Set &
*   Output:
*      none
*   Return:
*      Set
*   Parameters:
*      returns new Set object ( Two references to a Set object )
**************************************************************************/
Set operator -  ( Set &objSet1, Set &objSet2 )
{
   Set objReturn( 0 );
   bool bAddItem = true;   // By default we are going to add the item.

   // Use temp variables instead of making multiple calls to the access
   // function thus reducing function call over head and slowing down the
   // application.
   int iArraySize1 = objSet1.getSize();
   int iArraySize2 = objSet2.getSize();

   for( int iCount1 = 0; iCount1 < iArraySize1; iCount1++ )
   {
      bAddItem = true;

      for( int iCount2 = 0; iCount2 < iArraySize2; iCount2++ )
      {
         // if the item is found in both lists then do not add it, so set
         // flag to false and break;
         if( objSet1.getArrItm( iCount1 ) == objSet2.getArrItm( iCount2 ) )
         {
            bAddItem = false;
            break;
         }
      }

      // only add the item if it is unique to the first array
      if( bAddItem )
         objReturn.addNumber( objSet1.getArrItm( iCount1 ) );
   }

   // return the new object
   return( objReturn );
}

/*************************************************************************
*   Purpose:
*      To create a Set object with the intersection between two Set objects
*   Input:
*      Set &, Set &
*   Output:
*      none
*   Return:
*      Set
*   Parameters:
*      returns new Set object ( Two references to a Set object )
**************************************************************************/
Set operator && ( Set &objSet1, Set &objSet2 )
{
   Set objReturn( 0 );

   // Use temp variables instead of making multiple calls to the access
   // function thus reducing function call over head and slowing down the
   // application.
   int iArraySize1 = objSet1.getSize();
   int iArraySize2 = objSet2.getSize();

   for( int iCount1 = 0; iCount1 < iArraySize1; iCount1++ )
   {
      for( int iCount2 = 0; iCount2 < iArraySize2; iCount2++ )
      {
         // check to see if the item is found in both arrays then add
         // the element and then break;
         if( objSet1.getArrItm( iCount1 ) == objSet2.getArrItm( iCount2 ) )
         {
            objReturn.addNumber( objSet1.getArrItm( iCount1 ) );
            break;
         }
      }
   }

   // return the new object
   return( objReturn );
}

/*************************************************************************
*   Purpose:
*      To create a Set object with the union between two Set objects
*   Input:
*      Set &, Set &
*   Output:
*      none
*   Return:
*      Set
*   Parameters:
*      returns new Set object ( Two references to a Set object )
**************************************************************************/
Set operator || ( Set &objSet1, Set &objSet2 )
{
   Set objReturn( 0 );

   // Use temp variable instead of making multiple calls to the access
   // function thus reducing function call over head and slowing down the
   // application.
   int iArraySize = objSet1.getSize();

   for( int iCount = 0; iCount < iArraySize; iCount++ )
   {
      // Add all the items found in the first list
      objReturn.addNumber( objSet1.getArrItm( iCount ) );
   }

   iArraySize = objSet2.getSize();
   for( int iCount = 0; iCount < iArraySize; iCount++ )
   {
      // Add all the items found in the second list
      // if they are not duplicates
      objReturn.addNumber( objSet2.getArrItm( iCount ) );
   }

   // return the new object
   return( objReturn );
}

/*************************************************************************
*   Purpose:
*      To send the contents of the set object to the out stream
*   Input:
*      ostream &, Set &
*   Output:
*      none
*   Return:
*      ostream &
*   Parameters:
*      returns reference to ostream ( reference to a outstream and 
*                                     a reference to a Set object )
**************************************************************************/
ostream &operator << ( ostream &objStream, Set &objSet )
{
   int iDisplayCount = 0;                 // counter to display 10 across.
   int iArraySize    = objSet.getSize();  // Get the size of the array.
   int iArrayItem    = 0;                 // Temp variable for Items
   
   objStream << "    ";    // For character formatting

   // loop through the array to display the gathered numbers
   for( int iCount = 0; iCount < iArraySize; iCount++ )
   {
      // if the value in the objSet.getArrItm() is > 0 then
      // display that value
      if( ( iArrayItem = objSet.getArrItm( iCount ) ) > 0 )
      {
         iDisplayCount++;

         // This is used for display formatting.
         if( iArrayItem >= 10 )
            objStream << iArrayItem << " ";
         else
            objStream << " " << iArrayItem << " ";

         // if the 10th item then print a \n to the screen after it.
         if( iDisplayCount % 10 == 0 )
         {
            objStream << endl;
            objStream << "    "; // For character formatting
         }
      }
   }

   // return an outstream object reference
   return( objStream );
}

/*************************************************************************
*   Purpose:
*      To copy the contents of one object into another object
*   Input:
*      Set &
*   Output:
*      none
*   Return:
*      void
*   Parameters:
*      void ( reference to Set object )
**************************************************************************/
void Set::operator = ( Set objCopy )
{
   // Copy the contents of one object into the new object
   iArraySize = objCopy.getSize();
   for( int iCount = 0; iCount < iArraySize; iCount++ )
   {
      iNumberList[ iCount ] = objCopy.getArrItm( iCount );
   }
}
