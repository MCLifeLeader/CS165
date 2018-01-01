/***********************************************************************
* Program:
*    Homework 6, Working with Classes
*    Brother Cameron, CS 165
* Author:
*    Brother Michael Carey
* Summary:
*    Working with a Time class hh:mm:ss In this case we are working with
*    our first class and we have added two overloaded operators.
***********************************************************************/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

/**************************************************************************
*   class:
*      Time
*   Purpose:
*      To store and report time differences between two of the same class
*************************************************************************/

class Time
{
public:
   // Default Constructor
   Time();
   // Init class from Time Object ref
   Time( Time &objTime );
   // Init class from Time String
   Time( char *sTime );
   // Init class from a total number of seconds
   Time( int iTotSeconds );
   // Time compare function
   Time timeDiff( Time &objTime );
   // Get the Hours Time class access function
   int getHour( void );
   // Get the Minutes Time class access function
   int getMinutes( void );
   // Get the Seconds Time class access function
   int getSeconds( void );
   // Get the Total Seconds Time class access function
   int getTotalSeconds( void );
   // Single increment function
   void incTime( void );
   // Increment on total number of seconds
   void incTime( int iIncrementSeconds );
   // Display the time value
   void displayTime( void );

private:
   // Convert a time value into total seconds
   void setTotSecondsFromTime( void );
   // Move from seconds to minutes to hours
   void adjustTime( void );

   int iHours;
   int iMinutes;
   int iSeconds;
   int iTotalSeconds;
};

Time operator ++ ( Time &objIncTime );
Time operator - ( Time &objDiffTime1, Time &objDiffTime2 );

/**************************************************************************
*   Purpose:
*      main function for using Time class
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
   // Time objects we're going to be using
   Time objTime1;
   Time objTime2;
   Time objTime3;

   // A buffer for our user to input string values
   char sGetUserInput[ 20 ];

   cout << "Enter first time: ";
   cin >> sGetUserInput;
   objTime1 = Time( sGetUserInput );

   cout << "Enter second time: ";
   cin >> sGetUserInput;
   objTime2 = Time( sGetUserInput );

   // Set objTime3 with the difference
   objTime3 = objTime1 - objTime2;

   // display the difference
   cout << "Difference: ";
   objTime3.displayTime();

   cout << "\n";

   return( 0 );
}

/**************************************************************************
*   Purpose:
*      Default Constructor
*   Input:
*      none
*   Output:
*      none
*   Return:
*      none
*   Parameters:
*      none
**************************************************************************/

Time::Time()
{
   // Set values to NULL
   iHours = iMinutes = iSeconds = 0;
   this->setTotSecondsFromTime();
}

/**************************************************************************
*   Purpose:
*      Overloaded Constructor for initializing the object from another
*      object of same type.
*   Input:
*      Time &
*   Output:
*      none
*   Return:
*      none
*   Parameters:
*      none ( reference to a Time object )
*************************************************************************/

Time::Time( Time &objTime )
{
   // Use the incoming object's values to set the new
   // out going objects values.
   iHours   = objTime.getHour();
   iMinutes = objTime.getMinutes();
   iSeconds = objTime.getSeconds();

   iTotalSeconds = objTime.getTotalSeconds();
}

/**************************************************************************
*   Purpose:
*      Overloaded Constructor for initializing the object from a text based
*      time string
*   Input:
*      char []
*   Output:
*      none
*   Return:
*      none
*   Parameters:
*      none ( char array with a time based string "hh:mm:ss" )
**************************************************************************/

Time::Time( char *sTime )
{
   int iTimeLen   = ( int ) strlen( sTime );
   int iCount     = 0;
   int iColonCnt  = 0;

   // Create a variable that we can manipulate
   char *sTmpTime = new char [ iTimeLen + 1 ];

   // Copy the string into that variable
   sprintf( sTmpTime, "%s", sTime );

   // Set all characters with : to NULL
   for( iColonCnt = 0, iCount = 0; iCount < iTimeLen; iCount++ )
   {
      if( sTmpTime[ iCount ] == ':' )
      {
         iColonCnt++;
         sTmpTime[ iCount ] = '\0';
      }
   }

   // report to the user the bad time values and terminate
   if( iColonCnt != 2 )
   {
      cout << "Invalid time format used, should be hh:mm:ss\n";
      exit( 1 );
   }

   iCount = 0;
   // Set the Hours
   iHours = atoi( sTmpTime );

   // Move the string pointer
   while( sTmpTime[ 0 ] != '\0' )
   {
      iCount++;
      sTmpTime++;
   }
   // Set the minutes
   iMinutes = atoi( ++sTmpTime );

   // Move the string pointer
   while( sTmpTime[ 0 ] != '\0' )
   {
      iCount++;
      sTmpTime++;
   }
   // Set the Seconds
   iSeconds = atoi( ++sTmpTime );

   iCount += 2;

   // Return the pointer back to it's original location
   for( ; iCount > 0; iCount-- ) sTmpTime--;

   this->setTotSecondsFromTime();

   delete [] sTmpTime;

   // check to see if the time values are with in correct range
   if( iHours > 23 )
   {
      cout << "Hours value is invalid\n";
      exit( 2 );
   }
   if( iMinutes > 59 )
   {
      cout << "Minutes value is invalid\n";
      exit( 3 );
   }
   if( iSeconds > 59 )
   {
      cout << "Seconds value is invalid\n";
      exit( 4 );
   }

}

/**************************************************************************
*   Purpose:
*      Overloaded Constructor for initializing the object from a integer
*      seconds based counter
*   Input:
*      int
*   Output:
*      none
*   Return:
*      none
*   Parameters:
*      none ( total number of seconds to set the clock to )
**************************************************************************/

Time::Time( int iTotSeconds )
{
   iHours = iMinutes = iSeconds = 0;

   // set the total seconds
   iTotalSeconds = iTotSeconds;

   // use the iTotSeconds to create the actual time value using the
   // incTime function to perform the operation.
   this->incTime( iTotSeconds );
}


/**************************************************************************
*   Purpose:
*      Get the Hours Time class access function
*   Input:
*      void
*   Output:
*      none
*   Return:
*      int
*   Parameters:
*      returns Hours ( void )
**************************************************************************/

int Time::getHour( void )
{
   return( iHours );
}

/**************************************************************************
*   Purpose:
*      Get the Minutes Time class access function
*   Input:
*      void
*   Output:
*      none
*   Return:
*      int
*   Parameters:
*      returns minutes ( void )
**************************************************************************/

int Time::getMinutes( void )
{
   return( iMinutes );
}

/**************************************************************************
*   Purpose:
*      Get the Seconds Time class access function
*   Input:
*      void
*   Output:
*      none
*   Return:
*      int
*   Parameters:
*      returns seconds ( void )
**************************************************************************/

int Time::getSeconds( void )
{
   return( iSeconds );
}

/**************************************************************************
*   Purpose:
*      Get the Total Seconds Time class access function
*   Input:
*      void
*   Output:
*      none
*   Return:
*      int
*   Parameters:
*      returns total seconds from 00:00:00 ( void )
**************************************************************************/

int Time::getTotalSeconds( void )
{
   return( iTotalSeconds );
}

/**************************************************************************
*   Purpose:
*      Compare the current time object to another object of same type
*   Input:
*      Time &
*   Output:
*      none
*   Return:
*      Time
*   Parameters:
*      Time object containing the difference( Time object to run the
*      compare against )
**************************************************************************/

Time Time::timeDiff( Time &objTime )
{
   // the Object to return to the user
   Time objReturnTime( "0:0:0" );

   if( this->iTotalSeconds > objTime.getTotalSeconds() )
   {
      while( this->iTotalSeconds != objTime.getTotalSeconds() )
      {
         objTime.incTime();
         objReturnTime.incTime();
      }
   }
   else
   {
      while( this->iTotalSeconds != objTime.getTotalSeconds() )
      {
         this->incTime();
         objReturnTime.incTime();
      }
   }

   // return to the user the difference found.
   return( objReturnTime );
}


/**************************************************************************
*   Purpose:
*      Increment the seconds by one
*   Input:
*      void
*   Output:
*      none
*   Return:
*      void
*   Parameters:
*      void( void )
**************************************************************************/

void Time::incTime( void )
{
   // add a second
   iSeconds++;

   this->adjustTime( );
   this->setTotSecondsFromTime();
}

/**************************************************************************
*   Purpose:
*      Increment the seconds by one
*   Input:
*      int
*   Output:
*      none
*   Return:
*      void
*   Parameters:
*      void( the total number of seconds to increment the time value by )
**************************************************************************/

void Time::incTime( int iIncrementSeconds )
{
   // iIncrementSeconds counts to Zero while iSeconds increments
   for( ; iIncrementSeconds > 0; iIncrementSeconds-- , iSeconds++ )
      this->adjustTime( );

   this->adjustTime( );
   this->setTotSecondsFromTime();
}

/**************************************************************************
*   Purpose:
*      Format and then display the time in the object.
*   Input:
*      void
*   Output:
*      none
*   Return:
*      void
*   Parameters:
*      void( void )
**************************************************************************/

void Time::displayTime( void )
{
   // if the time is less than 10 add a leading 0 to make the time look
   // correct...
   // good 01:02:13
   // bad  1:2:13

   if( iHours < 10 )
      cout << "0" << iHours << ":";
   else
      cout << iHours << ":";

   if( iMinutes < 10 )
      cout << "0" << iMinutes << ":";
   else
      cout << iMinutes << ":";

   if( iSeconds < 10 )
      cout << "0" << iSeconds;
   else
      cout << iSeconds;
}

/**************************************************************************
*   Purpose:
*      Adjusts the clock values to display correctly when printed
*   Input:
*      void
*   Output:
*      none
*   Return:
*      void
*   Parameters:
*      void( void )
*   Note:
*      private function
**************************************************************************/

void Time::adjustTime( void )
{
   // keep seconds under 60
   if( iSeconds > 59 )
   {
      iSeconds = 0;
      iMinutes++;
   }

   // keep minutes under 60
   if( iMinutes > 59 )
   {
      iMinutes = 0;
      iHours++;
   }

   // keep hours under 24
   if( iHours > 23 )
      iHours = 0;
}

/**************************************************************************
*   Purpose:
*      Convert the time values into iTotalSeconds
*   Input:
*      void
*   Output:
*      none
*   Return:
*      void
*   Parameters:
*      void ( void )
*   Note:
*      This is a protected function
**************************************************************************/

void Time::setTotSecondsFromTime( void )
{
   // set the iTotalSeconds based on existing time values
   iTotalSeconds = iSeconds;
   iTotalSeconds += iMinutes * 60;
   iTotalSeconds += iHours * 3600;
}

/**************************************************************************
*   Purpose:
*      Add time to the seconds clock by one click
*   Input:
*      void
*   Output:
*      none
*   Return:
*      void
*   Parameters:
*      Time object ( Time object to be incremented )
**************************************************************************/

Time operator ++ ( Time &objIncTime )
{
   objIncTime.incTime();
   return( objIncTime );
}

/**************************************************************************
*   Purpose:
*      Subtract the absolute value of one time to another and return the
*      difference.
*   Input:
*      void
*   Output:
*      none
*   Return:
*      void
*   Parameters:
*      Time object returned ( first Time object, second Time object )
**************************************************************************/

Time operator - ( Time &objDiffTime1 , Time &objDiffTime2 )
{
   // the Object to return to the user
   Time objReturnTime( "0:0:0" );

   if( objDiffTime1.getTotalSeconds() > objDiffTime2.getTotalSeconds() )
   {
      while( objDiffTime1.getTotalSeconds() !=
             objDiffTime2.getTotalSeconds() )
      {
         ++objDiffTime2;
         ++objReturnTime;
      }
   }
   else
   {
      while( objDiffTime1.getTotalSeconds() !=
             objDiffTime2.getTotalSeconds() )
      {
         ++objDiffTime1;
         ++objReturnTime;
      }
   }

   // return to the user the difference found.
   return( objReturnTime );
}
