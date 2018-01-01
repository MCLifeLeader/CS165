/***********************************************************************
* Program:
*    Homework Final, Assignment Final Project
*    Brother Cameron, CS 165
* Author:
*    Brother Michael Carey
* Summary:
*    Using information found in a gedcom file, will output various
*    valid and invalid dates into three different files.
***********************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

/*************************************************************************
*   Class:
*     DateTime
*   Purpose:
*     Calculate Dates and Times
**************************************************************************/
class DateTime
{
public:
   DateTime();
   DateTime( DateTime &dtObj );
   DateTime( string sOrgDate );

   void setRawDate( string date );
   string getRawDate( void );

   void setYear( int year );
   void setYear( string year );

   void setMonth( int month );
   void setMonth( string month );

   void setDay( int day );
   void setDay( string day );

   int getYear( void );
   int getMonth( void );
   string getMonths( void );
   int getDay( void );

   bool isGoodDate( void );
   int daysInMonth( int month );

   void printFlag( bool bFlag );
   bool printFlag( void );

protected:
private:
   bool bPrintCalc;
   string sDateTime;
   string sMonths[ 13 ];
   int iYear;
   int iMonth;
   int iDay;
};

DateTime operator - ( DateTime& dtObj1, DateTime& dtObj2 );
bool operator > ( DateTime& dtObj1, DateTime& dtObj2 );
bool operator < ( DateTime& dtObj1, DateTime& dtObj2 );
ostream &operator << ( ostream &objStream, DateTime &dtObj );

/*************************************************************************
*   Class:
*     Person
*   Purpose:
*     To store a persons information from a gedcom file
**************************************************************************/
class GedPerson
{
public:
   GedPerson();
   GedPerson( GedPerson &gpObj );
   GedPerson( GedPerson *gpObj );
   GedPerson( string name );

   void setName( string name );
   void setGiven( string fname );
   void setSurn( string sname );
   void setBDate( string bdate );
   void setDDate( string ddate );

   void setBDate( DateTime &bdate );
   void setDDate( DateTime &ddate );

   string getName( void );
   string getGiven( void );
   string getSurn( void );
   DateTime getBDate( void );
   DateTime getDDate( void );

   bool printBirth();
   bool printDeath();

   void printBirth( bool bFlag );
   void printDeath( bool bFlag );

   void operator = ( GedPerson &gpObj );   // copy string into term

protected:
private:
   bool bPrintBirth;
   bool bPrintDeath;
   string sName;
   string sGiven;
   string sSurn;
   DateTime dtBirth;
   DateTime dtDeath;
};

ostream &operator << ( ostream &objStream, GedPerson &gpObj );
ostream &operator << ( ostream &objStream, GedPerson *gpObj );

string substr( string str, unsigned int &pos, bool bRestOfLine );

/*************************************************************************
*   Purpose:
*      main function for parsing a gedcom file
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
   bool bAddPeople = false;
   unsigned int pos;

   string readData;
   string parts[ 3 ];

   // temp variables for handling some data issues.
   DateTime objBirth1;
   DateTime objBirth2;
   DateTime objDeath1;
   DateTime objDeath2;
   DateTime objTest1;
   DateTime objTest2;

   ifstream readFile;

   ofstream writeFile1;
   ofstream writeFile2;
   ofstream writeFile3;

   GedPerson *newItem;

   vector < GedPerson * > peopleList;   // total people list
   vector < GedPerson * > goodDates;    // just the good dates
   vector < GedPerson * > badBDates;    // just the bad birth dates
   vector < GedPerson * > badDDates;    // just the bad death dates

   parts[ 0 ] = parts[ 1 ] = parts[ 2 ] = "";

   // open a file
   readFile.open( "cameron.ged" );

   writeFile1.open( "names.txt" );
   writeFile2.open( "invalid_birth.txt" );
   writeFile3.open( "invalid_death.txt" );

   // create the rest of the node list
   while ( getline( readFile, readData ) )
   {
      pos = 0;

      // break it into parts
      parts[ 0 ] = substr( readData, pos, false );
      parts[ 1 ] = substr( readData, pos, false );
      parts[ 2 ] = substr( readData, pos, true );

      // look for a new person
      if ( atoi( readData.c_str() ) == 0 &&
         !strcmp( "INDI", parts[ 2 ].c_str() ) )
      {
         newItem = new GedPerson( "" );

         if ( !newItem )
         {
            cerr << "There is not enough memory in this computer"
                 << "for the both of us!\n";
            cerr << "Are you sure you're not running windows?\n";
            exit( 1 );
         }

         // Create Person Record
         peopleList.push_back( newItem );

         bAddPeople = true;
      }

      // this flag is here to keep it from adding records until the
      // first person is found
      if ( bAddPeople )
      {
         if ( !strcmp( "NAME", parts[ 1 ].c_str() ) )
            peopleList[ peopleList.size() - 1 ]->setName( parts[ 2 ] );
         else if ( !strcmp( "GIVN", parts[ 1 ].c_str() ) )
            peopleList[ peopleList.size() - 1 ]->setGiven( parts[ 2 ] );
         else if ( !strcmp( "SURN", parts[ 1 ].c_str() ) )
            peopleList[ peopleList.size() - 1 ]->setSurn( parts[ 2 ] );
         else if ( !strcmp( "BIRT", parts[ 1 ].c_str() ) )
         {
            pos = 0;
            getline( readFile, readData );

            // break it into parts
            parts[ 0 ] = substr( readData, pos, false );
            parts[ 1 ] = substr( readData, pos, false );
            parts[ 2 ] = substr( readData, pos, true );

            if ( !strcmp( "DATE", parts[ 1 ].c_str() ) )
               peopleList[ peopleList.size() - 1 ]->setBDate( parts[ 2 ] );
         }
         else if ( !strcmp( "DEAT", parts[ 1 ].c_str() ) )
         {
            pos = 0;
            getline( readFile, readData );

            // break it into parts
            parts[ 0 ] = substr( readData, pos, false );
            parts[ 1 ] = substr( readData, pos, false );
            parts[ 2 ] = substr( readData, pos, true );

            if ( !strcmp( "DATE", parts[ 1 ].c_str() ) )
               peopleList[ peopleList.size() - 1 ]->setDDate( parts[ 2 ] );
         }
      }
   }

   // copy out all of the items into their respective containers
   for ( unsigned int i = 0; i < peopleList.size(); i++ )
   {
      if ( peopleList[ i ]->getBDate().isGoodDate() &&
          peopleList[ i ]->getDDate().isGoodDate() )
      {
         goodDates.push_back( peopleList[ i ] );
      }

      if ( peopleList[ i ]->getBDate().isGoodDate() == false )
         badBDates.push_back( peopleList[ i ] );

      if ( peopleList[ i ]->getDDate().isGoodDate() == false )
         badDDates.push_back( peopleList[ i ] );
   }

   // sort based on date information that is good.
   // simple quick sort
   for ( unsigned int iCount1 = 0; iCount1 < goodDates.size(); iCount1++ )
   {
      for ( unsigned int iCount2 = 0; iCount2 < goodDates.size(); iCount2++ )
      {
         if ( iCount1 != iCount2 )
         {
            objBirth1 = goodDates[ iCount1 ]->getBDate();
            objDeath1 = goodDates[ iCount1 ]->getDDate();

            objBirth2 = goodDates[ iCount2 ]->getBDate();
            objDeath2 = goodDates[ iCount2 ]->getDDate();

            objTest1 = objDeath1 - objBirth1;
            objTest2 = objDeath2 - objBirth2;

            if ( objTest1 > objTest2 )
            {
               newItem = goodDates[ iCount1 ];
               goodDates[ iCount1 ] = goodDates[ iCount2 ];
               goodDates[ iCount2 ] = newItem;
            }
         }
      }
   }

   // sort bad birth dates based on last name information.
   // simple quick sort
   for ( unsigned int iCount1 = 0; iCount1 < badBDates.size(); iCount1++ )
   {
      for ( unsigned int iCount2 = 0; iCount2 < badBDates.size(); iCount2++ )
      {
         if ( iCount1 != iCount2 )
         {
            if ( strcmp( badBDates[ iCount1 ]->getSurn().c_str(),
                badBDates[ iCount2 ]->getSurn().c_str() ) < 0 )
            {
               newItem = badBDates[ iCount1 ];
               badBDates[ iCount1 ] = badBDates[ iCount2 ];
               badBDates[ iCount2 ] = newItem;
            }
         }
      }
   }

   // sort bad death dates based on last name information.
   // simple quick sort
   for ( unsigned int iCount1 = 0; iCount1 < badDDates.size(); iCount1++ )
   {
      for ( unsigned int iCount2 = 0; iCount2 < badDDates.size(); iCount2++ )
      {
         if ( iCount1 != iCount2 )
         {
            if ( strcmp( badDDates[ iCount1 ]->getSurn().c_str(),
                badDDates[ iCount2 ]->getSurn().c_str() ) < 0 )
            {
               newItem = badDDates[ iCount1 ];
               badDDates[ iCount1 ] = badDDates[ iCount2 ];
               badDDates[ iCount2 ] = newItem;
            }
         }
      }
   }

   // output good dates
   for ( unsigned int i = 0; i < goodDates.size(); i++ )
   {
      goodDates[ i ]->getBDate().printFlag( false );
      goodDates[ i ]->printBirth( false );
      goodDates[ i ]->printDeath( false );
      writeFile1 << goodDates[ i ];
   }

   // output bad birth dates
   for ( unsigned int i = 0; i < badBDates.size(); i++ )
   {
      badBDates[ i ]->getBDate().printFlag( false );
      badBDates[ i ]->printBirth( true );
      badBDates[ i ]->printDeath( false );
      writeFile2 << badBDates[ i ];
   }

   // output bad death dates
   for ( unsigned int i = 0; i < badDDates.size(); i++ )
   {
      badDDates[ i ]->getBDate().printFlag( false );
      badDDates[ i ]->printDeath( true );
      badDDates[ i ]->printBirth( false );
      writeFile3 << badDDates[ i ];
   }


   // clean up memory
   for ( unsigned int i = 0; i < peopleList.size(); i++ )
   {
      delete peopleList[ i ];
   }

   // close the files
   readFile.close();

   writeFile1.close();
   writeFile2.close();
   writeFile3.close();

   return ( 0 );
}

/*************************************************************************
*   Purpose:
*      To return a small segment from a string
**************************************************************************/
string substr( string str, unsigned int &pos, bool bRestOfLine )
{
   string strReturn = "";
   int iSpaces = 0;

   // search for spaces as delimiters
   for ( ; pos < str.length(); pos++ )
   {
      if ( iSpaces >= 1 && str[ pos ] != ' ' )
         break;

      strReturn += str[ pos ];

      if ( bRestOfLine == true )
         iSpaces = 0;
      else if ( str[ pos ] == ' ' )
         iSpaces++;
      else
         iSpaces = 0;
   }

   while ( strReturn[ strReturn.length() - 1 ] == ' ' )
      strReturn[ strReturn.length() - 1 ] = '\0';

   return ( strReturn );
}

/*************************************************************************
*   Purpose:
*      default constructor
**************************************************************************/
DateTime::DateTime()
{
   sMonths[ 0 ] = "NIL";
   sMonths[ 1 ] = "JAN";
   sMonths[ 2 ] = "FEB";
   sMonths[ 3 ] = "MAR";
   sMonths[ 4 ] = "APR";
   sMonths[ 5 ] = "MAY";
   sMonths[ 6 ] = "JUN";
   sMonths[ 7 ] = "JUL";
   sMonths[ 8 ] = "AUG";
   sMonths[ 9 ] = "SEP";
   sMonths[ 10 ] = "OCT";
   sMonths[ 11 ] = "NOV";
   sMonths[ 12 ] = "DEC";

   iYear    = 0;
   iMonth   = 0;
   iDay     = 0;

   sDateTime = "";
   bPrintCalc = false;
}

/*************************************************************************
*   Purpose:
*      copy constructor
**************************************************************************/
DateTime::DateTime( DateTime &dtObj )
{
   sMonths[ 0 ] = "NIL";
   sMonths[ 1 ] = "JAN";
   sMonths[ 2 ] = "FEB";
   sMonths[ 3 ] = "MAR";
   sMonths[ 4 ] = "APR";
   sMonths[ 5 ] = "MAY";
   sMonths[ 6 ] = "JUN";
   sMonths[ 7 ] = "JUL";
   sMonths[ 8 ] = "AUG";
   sMonths[ 9 ] = "SEP";
   sMonths[ 10 ] = "OCT";
   sMonths[ 11 ] = "NOV";
   sMonths[ 12 ] = "DEC";

   iYear    = 0;
   iMonth   = 0;
   iDay     = 0;

   iYear    = dtObj.getYear();
   iMonth   = dtObj.getMonth();
   iDay     = dtObj.getDay();

   sDateTime = dtObj.getRawDate();
   bPrintCalc = dtObj.printFlag();
}

/*************************************************************************
*   Purpose:
*      overloaded constructor that converts a text string into a date
**************************************************************************/
DateTime::DateTime( string sOrgDate )
{
   int iSpaces = 0;
   unsigned int pos = 0;

   string parts[ 3 ];

   bPrintCalc = false;

   parts[ 0 ] = parts[ 1 ] = parts[ 2 ] = "";

   sMonths[ 0 ] = "NIL";
   sMonths[ 1 ] = "JAN";
   sMonths[ 2 ] = "FEB";
   sMonths[ 3 ] = "MAR";
   sMonths[ 4 ] = "APR";
   sMonths[ 5 ] = "MAY";
   sMonths[ 6 ] = "JUN";
   sMonths[ 7 ] = "JUL";
   sMonths[ 8 ] = "AUG";
   sMonths[ 9 ] = "SEP";
   sMonths[ 10 ] = "OCT";
   sMonths[ 11 ] = "NOV";
   sMonths[ 12 ] = "DEC";

   iYear    = 0;
   iMonth   = 0;
   iDay     = 0;

   // make a copy of the input string and store it in the class
   this->sDateTime = sOrgDate;

   // break the string down into usable parts
   for ( int part = 0; part < 3; part++ )
   {
      iSpaces = 0;
      // search for spaces as delimiters
      for ( ; pos < sOrgDate.length(); pos++ )
      {
         if ( iSpaces >= 1 && sOrgDate[ pos ] != ' ' )
            break;

         parts[ part ] += sOrgDate[ pos ];

         if ( sOrgDate[ pos ] == ' ' )
            iSpaces++;
         else
            iSpaces = 0;
      }

      // clean up white space at the end of each text grabbing
      while ( parts[ part ][ parts[ part ].length() - 1 ] == ' ' )
         parts[ part ][ parts[ part ].length() - 1 ] = '\0';
   }

   // use the broken parts for setting the various variables
   if ( isdigit( parts[ 0 ][ 0 ] ) &&
       isalpha( parts[ 1 ][ 0 ] ) &&
       isdigit( parts[ 2 ][ 0 ] ) )
   {
      // "2 Mar 1929"
      setYear( parts[ 2 ] );
      setMonth( parts[ 1 ] );
      setDay( parts[ 0 ] );
   }
   else if ( isalpha( parts[ 0 ][ 0 ] ) )
   {
      if ( isdigit( parts[ 1 ][ 0 ] ) )
      {
         // "MAY 1856"
         setYear( parts[ 1 ] );
         setMonth( parts[ 0 ] );
      }
      else if ( parts[ 1 ].length() == 0 )
      {
         // "AUG"
         setMonth( parts[ 0 ] );
      }
   }
   else if ( isdigit( parts[ 1 ][ 0 ] ) )
   {
      // "22 1920"
      setYear( parts[ 1 ] );
      setDay( parts[ 0 ] );
   }
   else if ( parts[ 1 ].length() == 0 )
   {
      // "1924"
      setYear( parts[ 0 ] );
   }
   else if ( parts[ 2 ].length() == 0 )
   {
      // "2 Feb"
      setMonth( parts[ 1 ] );
      setDay( parts[ 0 ] );
   }
   else
      sDateTime = "";
}

/*************************************************************************
*   Purpose:
*      Set the raw date string
**************************************************************************/
void DateTime::setRawDate( string date )
{
   this->sDateTime = date;
}

/*************************************************************************
*   Purpose:
*      get the raw date string
**************************************************************************/
string DateTime::getRawDate( void )
{
   return ( this->sDateTime );
}

/*************************************************************************
*   Purpose:
*      set the year based on an int
**************************************************************************/
void DateTime::setYear( int year )
{
   this->iYear = year;

   if ( iYear <= 0 )
      iYear = 0;
}

/*************************************************************************
*   Purpose:
*      set the year based on a string
**************************************************************************/
void DateTime::setYear( string year )
{
   if ( isdigit( year[ 0 ] ) )
      iYear = atoi( year.c_str() );
   else
      iYear = 0;

   if ( iYear <= 0 )
      iYear = 0;
}

/*************************************************************************
*   Purpose:
*      set the month based on an int
**************************************************************************/
void DateTime::setMonth( int month )
{
   this->iMonth = month;

   if ( iMonth > 12 )
      iMonth = 0;
   else if ( iMonth <= 0 )
      iMonth = 0;
}

/*************************************************************************
*   Purpose:
*      set the month based on a string
**************************************************************************/
void DateTime::setMonth( string month )
{
   unsigned int iCount;

   if ( isdigit( month[ 0 ] ) )
      iMonth = atoi( month.c_str() );
   else
   {
      // First make sure that the month string is all caps
      for ( iCount = 0; iCount < month.length(); iCount++ )
         month[ iCount ] = toupper( month[ iCount ] );

      // find the month
      for ( iCount = 1; iCount < 13; iCount++ )
      {
         if ( !strcmp( month.c_str(), sMonths[ iCount ].c_str() ) )
            break;
      }

      iMonth = iCount;
   }

   if ( iMonth > 12 )
      iMonth = 0;
   else if ( iMonth <= 0 )
      iMonth = 0;
}

/*************************************************************************
*   Purpose:
*      set the day based on an int
**************************************************************************/
void DateTime::setDay( int day )
{
   this->iDay = day;

   // Jan 31 // Feb 28 // Mar 31 // Apr 30 // May 31 // Jun 30
   // Jul 31 // Aug 31 // Sep 30 // Oct 31 // Nov 30 // Dec 31

   if ( iMonth == 1 || iMonth == 3 ||
         iMonth == 5 || iMonth == 7 ||
         iMonth == 8 || iMonth == 10 ||
         iMonth == 12 )
   {
      if ( iDay > 31 )
         iDay = 31;
   }
   else if ( iMonth == 2 )
   {
      if ( iDay > 28 )
         iDay = 28;
   }
   else
   {
      if ( iDay > 30 )
         iDay = 30;
   }

   if ( iDay > 31 )
      iDay = 0;
   else if ( iDay <= 0 )
      iDay = 0;
}

/*************************************************************************
*   Purpose:
*      set the day based on a string
**************************************************************************/
void DateTime::setDay( string day )
{
   if ( !isdigit( day[ 0 ] ) )
      iDay = 0;
   else
   {
      iDay = atoi( day.c_str() );

      // Jan 31 // Feb 28 // Mar 31 // Apr 30 // May 31 // Jun 30
      // Jul 31 // Aug 31 // Sep 30 // Oct 31 // Nov 30 // Dec 31

      if ( iMonth == 1 || iMonth == 3 ||
            iMonth == 5 || iMonth == 7 ||
            iMonth == 8 || iMonth == 10 ||
            iMonth == 12 )
      {
         if ( iDay > 31 )
            iDay = 31;
      }
      else if ( iMonth == 2 )
      {
         if ( iDay > 28 )
            iDay = 28;
      }
      else
      {
         if ( iDay > 30 )
            iDay = 30;
      }

      if ( iDay > 31 )
         iDay = 0;
      else if ( iDay <= 0 )
         iDay = 0;
   }
}

/*************************************************************************
*   Purpose:
*      get year
**************************************************************************/
int DateTime::getYear( void )
{
   return ( this->iYear );
}

/*************************************************************************
*   Purpose:
*      get month
**************************************************************************/
int DateTime::getMonth( void )
{
   return ( this->iMonth );
}

/*************************************************************************
*   Purpose:
*      get month in string format
**************************************************************************/
string DateTime::getMonths( void )
{
   return ( this->sMonths[ iMonth ] );
}

/*************************************************************************
*   Purpose:
*      get day
**************************************************************************/
int DateTime::getDay( void )
{
   return ( this->iDay );
}

/*************************************************************************
*   Purpose:
*      do we have a good full date
**************************************************************************/
bool DateTime::isGoodDate( void )
{
   if ( this->iYear <= 0 || this->iMonth <= 0 || this->iDay <= 0 )
      return ( false );

   return ( true );
}

/*************************************************************************
*   Purpose:
*      how many days in a month
**************************************************************************/
int DateTime::daysInMonth( int month )
{
   iDay = 32;
   iMonth = month;

   // Jan 31 // Feb 28 // Mar 31 // Apr 30 // May 31 // Jun 30
   // Jul 31 // Aug 31 // Sep 30 // Oct 31 // Nov 30 // Dec 31

   if ( iMonth == 1 || iMonth == 3 ||
         iMonth == 5 || iMonth == 7 ||
         iMonth == 8 || iMonth == 10 ||
         iMonth == 12 )
   {
      if ( iDay > 31 )
         iDay = 31;
   }
   else if ( iMonth == 2 )
   {
      if ( iDay > 28 )
         iDay = 28;
   }
   else
   {
      if ( iDay > 30 )
         iDay = 30;
   }

   return ( iDay );
}

/*************************************************************************
*   Purpose:
*      toggle print format flag
**************************************************************************/
void DateTime::printFlag( bool bFlag )
{
   bPrintCalc = bFlag;
}

/*************************************************************************
*   Purpose:
*      return the print flag
**************************************************************************/
bool DateTime::printFlag( void )
{
   return ( this->bPrintCalc );
}

/*************************************************************************
*   Purpose:
*      Find the difference between two dates
**************************************************************************/
DateTime operator - ( DateTime& dtObj1, DateTime& dtObj2 )
{
   DateTime retObj;

   int day1    = dtObj1.getDay();
   int month1  = dtObj1.getMonth();
   int year1   = dtObj1.getYear();

   // check to see if both dates are good.
   if ( dtObj1.isGoodDate() && dtObj2.isGoodDate() )
   {
      // do some borrowing for subtraction
      if ( dtObj2.getDay() > day1 )
      {
         day1 += retObj.daysInMonth( month1 );
         month1--;
      }

      // do some more borrowing for subtraction
      if ( dtObj2.getMonth() > month1 )
      {
         month1 += 12;
         year1--;
      }

      // this is it a years up...
      if ( dtObj2.getYear() > year1 )
      {
         retObj = DateTime( "" );
         return ( retObj );
      }

      // do the math
      day1 -= dtObj2.getDay();
      month1 -= dtObj2.getMonth();
      year1 -= dtObj2.getYear();

      // make sure we don't have any 0 days
      if ( day1 <= 0 )
      {
         day1 += retObj.daysInMonth( month1 );
         month1--;
      }

      // make sure we don't have and 0 months
      if ( month1 <= 0 )
      {
         month1 += 12;
         year1--;
      }

      // and set the years to -1 if invalid
      if ( year1 < 0 )
      {
         year1 = -1;
      }

      // set the values into the return object
      retObj.setDay( day1 );
      retObj.setMonth( month1 );
      retObj.setYear( year1 );
   }

   retObj.printFlag( true );

   return ( retObj );
}

/*************************************************************************
*   Purpose:
*      Value compare overloaded operator
**************************************************************************/
bool operator > ( DateTime& dtObj1, DateTime& dtObj2 )
{
   if ( dtObj1.getYear() > dtObj2.getYear() )
      return ( true );
   else
   {
      if ( dtObj1.getYear() == dtObj2.getYear() )
      {
         if ( dtObj1.getMonth() > dtObj2.getMonth() )
            return ( true );
         else
         {
            if ( dtObj1.getMonth() == dtObj2.getMonth() )
            {
               if ( dtObj1.getDay() > dtObj2.getDay() )
                  return ( true );
               else
                  return ( false );
            }
            else
               return ( false );
         }
      }
      else
         return ( false );
   }
}

/*************************************************************************
*   Purpose:
*      Value compare overloaded operator
**************************************************************************/
bool operator < ( DateTime& dtObj1, DateTime& dtObj2 )
{
   if ( dtObj1.getYear() < dtObj2.getYear() )
      return ( true );
   else
   {
      if ( dtObj1.getYear() == dtObj2.getYear() )
      {
         if ( dtObj1.getMonth() < dtObj2.getMonth() )
            return ( true );
         else
         {
            if ( dtObj1.getMonth() == dtObj2.getMonth() )
            {
               if ( dtObj1.getDay() < dtObj2.getDay() )
                  return ( true );
               else
                  return ( false );
            }
            else
               return ( false );
         }
      }
      else
         return ( false );
   }
}

/*************************************************************************
*   Purpose:
*      Display the date info in a nice format
**************************************************************************/
ostream &operator << ( ostream &objStream, DateTime &dtObj )
{
   if ( dtObj.isGoodDate() )
   {
      if ( dtObj.printFlag() )
      {
         objStream << dtObj.getYear() << ", "
                   << dtObj.getMonth() << ", "
                   << dtObj.getDay();
      }
      else
      {
         objStream << dtObj.getDay() << " "
                   << dtObj.getMonths() << " "
                   << dtObj.getYear();
      }
   }

   return ( objStream );
}

/*************************************************************************
*   Purpose:
*      default constructor
**************************************************************************/
GedPerson::GedPerson()
{
   this->sGiven   = "";
   this->sName    = "";
   this->sSurn    = "";

   bPrintBirth = false;
   bPrintDeath = false;
}

/*************************************************************************
*   Purpose:
*      copy constructor
**************************************************************************/
GedPerson::GedPerson( GedPerson &gpObj )
{
   this->sGiven   = gpObj.getGiven();
   this->sName    = gpObj.getName();
   this->sSurn    = gpObj.getSurn();
   this->dtBirth  = gpObj.getBDate();
   this->dtDeath  = gpObj.getDDate();

   bPrintBirth = false;
   bPrintDeath = false;
}

/*************************************************************************
*   Purpose:
*      copy constructor
**************************************************************************/
GedPerson::GedPerson( GedPerson *gpObj )
{
   this->sGiven   = gpObj->getGiven();
   this->sName    = gpObj->getName();
   this->sSurn    = gpObj->getSurn();
   this->dtBirth  = gpObj->getBDate();
   this->dtDeath  = gpObj->getDDate();

   bPrintBirth = gpObj->printBirth();
   bPrintDeath = gpObj->printDeath();
}

/*************************************************************************
*   Purpose:
*      overloaded constructor
**************************************************************************/
GedPerson::GedPerson( string name )
{
   this->sName = name;

   bPrintBirth = false;
   bPrintDeath = false;
}

/*************************************************************************
*   Purpose:
*      set the full name
**************************************************************************/
void GedPerson::setName( string name )
{
   this->sName = name;
}

/*************************************************************************
*   Purpose:
*      set first name
**************************************************************************/
void GedPerson::setGiven( string fname )
{
   this->sGiven = fname;
}

/*************************************************************************
*   Purpose:
*      set last name
**************************************************************************/
void GedPerson::setSurn( string sname )
{
   this->sSurn = sname;
}

/*************************************************************************
*   Purpose:
*      set birth date by string
**************************************************************************/
void GedPerson::setBDate( string bdate )
{
   this->dtBirth = DateTime( bdate );
}

/*************************************************************************
*   Purpose:
*      set death date by string
**************************************************************************/
void GedPerson::setDDate( string ddate )
{
   this->dtDeath = DateTime( ddate );
}

/*************************************************************************
*   Purpose:
*      set birth date by obj
**************************************************************************/
void GedPerson::setBDate( DateTime &bdate )
{
   this->dtBirth = bdate;
}

/*************************************************************************
*   Purpose:
*      set death date by obj
**************************************************************************/
void GedPerson::setDDate( DateTime &ddate )
{
   this->dtDeath = ddate;
}

/*************************************************************************
*   Purpose:
*      get the full name
**************************************************************************/
string GedPerson::getName( void )
{
   return ( this->sName );
}

/*************************************************************************
*   Purpose:
*      get the first name
**************************************************************************/
string GedPerson::getGiven( void )
{
   return ( this->sGiven );
}

/*************************************************************************
*   Purpose:
*      get the last name
**************************************************************************/
string GedPerson::getSurn( void )
{
   return ( this->sSurn );
}

/*************************************************************************
*   Purpose:
*      get the birth date obj
**************************************************************************/
DateTime GedPerson::getBDate( void )
{
   return ( this->dtBirth );
}

/*************************************************************************
*   Purpose:
*      get death date obj
**************************************************************************/
DateTime GedPerson::getDDate( void )
{
   return ( this->dtDeath );
}

/*************************************************************************
*   Purpose:
*      return the flags value
**************************************************************************/
bool GedPerson::printBirth()
{
   return ( bPrintBirth );
}

/*************************************************************************
*   Purpose:
*      return the flags value
**************************************************************************/
bool GedPerson::printDeath()
{
   return ( bPrintDeath );
}

/*************************************************************************
*   Purpose:
*      flag for printing some information from the class
**************************************************************************/
void GedPerson::printBirth( bool bFlag )
{
   bPrintBirth = bFlag;
}

/*************************************************************************
*   Purpose:
*      flag for printing some information from the class
**************************************************************************/
void GedPerson::printDeath( bool bFlag )
{
   bPrintDeath = bFlag;
}

/*************************************************************************
*   Purpose:
*      overloaded assignment operator
**************************************************************************/
void GedPerson::operator = ( GedPerson &gpObj )
{
   this->sGiven   = gpObj.getGiven();
   this->sName    = gpObj.getName();
   this->sSurn    = gpObj.getSurn();
   this->dtBirth  = gpObj.getBDate();
   this->dtDeath  = gpObj.getDDate();
}

/*************************************************************************
*   Purpose:
*      Display the contents of a gedperson object
**************************************************************************/
ostream &operator << ( ostream &objStream, GedPerson &gpObj )
{
   DateTime outputObj;
   DateTime out1;
   DateTime out2;

   out1 = gpObj.getBDate();
   out2 = gpObj.getDDate();

   objStream << gpObj.getName() << endl;
   objStream << out1 << endl;
   objStream << out2 << endl;


   outputObj = out2 - out1;

   objStream << outputObj << endl;

   return ( objStream );
}

/*************************************************************************
*   Purpose:
*      Display the contents of a gedperson object
**************************************************************************/
ostream &operator << ( ostream &objStream, GedPerson *gpObj )
{
   DateTime outputObj;
   DateTime out1;
   DateTime out2;

   out1 = gpObj->getBDate();
   out2 = gpObj->getDDate();

   if ( gpObj->getBDate().isGoodDate() && gpObj->getDDate().isGoodDate())
   {
      objStream << gpObj->getSurn() << ", ";
      objStream << gpObj->getGiven() << " \t";
      objStream << out1 << "\t age at death (";

      outputObj = out2 - out1;

      objStream << outputObj << ")";

      objStream << endl;
   }

   if ( gpObj->printBirth() )
   {
      objStream << gpObj->getSurn() << ", ";
      objStream << gpObj->getGiven() << " \t";

      objStream << out1.getRawDate();

      objStream << endl;
   }

   if ( gpObj->printDeath() )
   {
      objStream << gpObj->getSurn() << ", ";
      objStream << gpObj->getGiven() << " \t";

      objStream << out2.getRawDate();

      objStream << endl;
   }

   return ( objStream );
}
