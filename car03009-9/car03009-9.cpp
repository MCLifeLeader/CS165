/***********************************************************************
* Program:
*    Homework 9, Working with Stings
*    Brother Cameron, CS 165
* Author:
*    Brother Michael Carey
* Summary:
*    This program demonstrates the use of pointers by performing
*    mathematical operations on Polynomials.
***********************************************************************/

#include <stdio.h>
#include <iostream>
#include <cctype>
#include <fstream>
#include <string>
#include <math.h>

using namespace std;

/*************************************************************************
*   Struct:
*     TERMELEMENT
*   Purpose:
*     To hold individual term Elements
*************************************************************************/
struct TERMELEMENT
{
   string elem;
   string strVar;
   double dConst;
   double dPower;
};

/*************************************************************************
*   Class:
*     Term
*   Purpose:
*     To hold individual term notations in a polynomial
*************************************************************************/
class Term
{
public:
   Term();  // default constructor
   ~Term(); // destructor
   Term( string strItem );    // overloaded constructor
   Term( Term &objTerm );     // overloaded copy constructor

   string getTerm( void );    // get the term string
   double calcTerm( double dValue );
   int getElmCount( void );   // get the number of term elements
   TERMELEMENT getElement( int iIndex );  // return a term element
   string convertDouble( double dValue ); // convert a double to a string
   void setTermtoZero( void );

   void operator = ( string strTerm ); // copy string into term
   void operator = ( Term objTerm );   // copy string into term

private:
   void setElmtoZero( int iIndex );
   void parseEngine( string strNewStr );  // main term parse engine
   void combineTermElementValues( void ); // parse engine clean up
   void copyTermObj( Term &objTerm );     // the actual copy function

   string strTerm;            // the full term
   TERMELEMENT *termPoint;    // term elements
   int iElmCount;             // number of term elements
};

// Subtraction
Term operator - ( Term &objTerm1, Term &objTerm2 );
// Addition
Term operator + ( Term &objTerm1, Term &objTerm2 );
// Multiplication
Term operator * ( Term &objTerm1, Term &objTerm2 );
// Multiplication
bool operator == ( Term &objTerm1, Term &objTerm2 );
// using ostream for output
ostream &operator << ( ostream &objStream, Term &objTerm );

/*************************************************************************
*   Class:
*     Poly
*   Purpose:
*     To hold a group of individual terms for a polynomial
*************************************************************************/
class Poly
{
public:
   Poly();
   ~Poly();
   Poly( string strNewPoly );
   Poly( Poly &objPoly );

   int getTermCount( void );
   string getPoly( void );
   Term getTerm( int iIndex );
   double calcPoly( double dValue );

   Term * gatherTermList( Poly &objPoly, int &iListSize );
   Term * gatherTermList( Term *term, Term *pTerm,
          int &iListSize, int iOldTerm );
   void operator = ( string strNewPoly ); // copy string into term
   void operator = ( Poly objTerm );      // copy string into term

private:
   void sortPoly( void );
   void parseEngine( string strNewPoly );
   void copyPolyObj( Poly &objPoly );

   string strPoly;
   Term *terms;
   int iLength;
};

// Subtraction
Poly operator - ( Poly &objPoly1, Poly &objPoly2 );
// Addition
Poly operator + ( Poly &objPoly1, Poly &objPoly2 );
// Multiplication
Poly operator * ( Poly &objPoly1, Poly &objPoly2 );
// using ostream for output
ostream &operator << ( ostream &objStream, Poly &objPoly );

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
   int iCount  = 0;
   string sGetVal = "";
   string strFirst   = "";
   string strSecond  = "";

   Poly poly1;
   Poly poly2;
   Poly poly3;

   if ( argc > 0 )
   {
      cout << endl << endl;
      cout << "Enter 2 Polynomials" << endl;
      cout << "Example: 3 + 8x + 5x^2 + 11x^3 + 6x^4 + 3x^5" << endl;
      cout << endl;

      while ( !strFirst.length() )
      {
         cout << "First: ";
         getline( cin, strFirst );
      }

      while ( !strSecond.length() )
      {
         cout << "Second: ";
         getline( cin, strSecond );
      }

      poly1 = strFirst;
      poly2 = strSecond;

      cout << endl;

      cout << "Polynomial s = q*r" << endl;
      poly3 = poly1 * poly2;
      cout << poly3 << endl;

      cout << "Value of q(2) = ";
      cout << poly1.calcPoly( 2 );
      cout << endl;

      cout << "Value of r(2) = ";
      cout << poly2.calcPoly( 2 );
      cout << endl;

      cout << "Value of (q + r)(2) = ";
      poly3 = poly1 + poly2;
      cout << poly3.calcPoly( 2 );
      cout << endl;

      cout << "Value of (q - r)(2) = ";
      poly3 = poly1 - poly2;
      cout << poly3.calcPoly( 2 );
      cout << endl;

      cout << "Value of (s)(2) = ";
      poly3 = poly1 * poly2;
      cout << poly3.calcPoly( 2 );
      cout << endl << endl;
   }

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
Term::Term()
{
   strTerm     = "";
   termPoint   = NULL;
   iElmCount   = 0;
}

/*************************************************************************
*   Purpose:
*      Default Destructor
*   Input:
*      none
*   Output:
*      none
*   Return:
*      none
*   Parameters:
*      none ( none )
**************************************************************************/
Term::~Term()
{
   if ( iElmCount )
      delete [] termPoint;

   strTerm     = "";
   termPoint   = NULL;
   iElmCount   = 0;
}

/*************************************************************************
*   Purpose:
*      Parameterized Constructor
*   Input:
*      none
*   Output:
*      none
*   Return:
*      none
*   Parameters:
*      none ( string containing the term to be grabbed )
**************************************************************************/

Term::Term( string strNewTerm )
{
   termPoint = NULL;
   iElmCount = 0;
   parseEngine( strNewTerm );
}

/*************************************************************************
*   Purpose:
*      Parameterized Constructor
*   Input:
*      none
*   Output:
*      none
*   Return:
*      none
*   Parameters:
*      none ( object to be copied )
**************************************************************************/
Term::Term( Term &objTerm )
{
   termPoint = NULL;
   iElmCount = 0;
   copyTermObj( objTerm );
}

/*************************************************************************
*   Purpose:
*      return the stored term as a string
*   Input:
*      none
*   Output:
*      none
*   Return:
*      string
*   Parameters:
*      a string that contains the term ( void )
**************************************************************************/
string Term::getTerm( void )
{
   string strReturn = "";

   // Check to see if the term is a valid term if not return the string '0'
   if ( termPoint != NULL && iElmCount && termPoint[ 0 ].dConst )
   {
      for ( int iTerm = 0; iTerm < iElmCount; iTerm++ )
      {
         // format the text string for the constant
         if ( termPoint[ iTerm ].dConst &&
           ( termPoint[ iTerm ].dConst != 1 ) || iElmCount == 1 )
            strReturn += convertDouble( termPoint[ iTerm ].dConst );

         // format the text string for the variable
         if ( termPoint[ iTerm ].elem.length() &&
             termPoint[ iTerm ].strVar.length() )
         {
            if ( termPoint[ iTerm ].dPower )
               strReturn += termPoint[ iTerm ].strVar;
            else
               strReturn += termPoint[ iTerm ].strVar[ 0 ];
         }

         // format the text string for the exponent
         if ( termPoint[ iTerm ].dPower && termPoint[ iTerm ].dPower != 1 )
            strReturn += convertDouble( termPoint[ iTerm ].dPower );
      }
   }
   else
      return ( "0" );

   return ( strReturn );
}

/*************************************************************************
*   Purpose:
*      to insert a value for x
*   Input:
*       double
*   Output:
*      none
*   Return:
*      void
*   Parameters:
*      double ( multiplier )
**************************************************************************/
double Term::calcTerm( double dValue )
{
   double dConst = 0;
   double dPower = 0;
   double dResult = 0;

   TERMELEMENT tempTerm;

   for ( int iCount = 0; iCount < getElmCount(); iCount++ )
   {
      tempTerm = getElement( iCount );
      if ( !dConst )
        dConst = tempTerm.dConst;
      if ( !dPower )
        dPower = tempTerm.dPower;
   }

   if ( dPower )
      dResult +=  dConst * pow( dValue , dPower );
   else
      dResult +=  dConst * dValue;

   return ( dResult );
}

/*************************************************************************
*   Purpose:
*      Get the element count in the single term
*   Input:
*      none
*   Output:
*      none
*   Return:
*      int
*   Parameters:
*      an int containing the number of term elements ( void )
**************************************************************************/
int Term::getElmCount( void )
{
   return ( iElmCount );
}

/*************************************************************************
*   Purpose:
*      Return a term element
*   Input:
*      int
*   Output:
*      none
*   Return:
*      TERMELEMENT
*   Parameters:
*      TERMELEMENT ( int iIndex )
**************************************************************************/
TERMELEMENT Term::getElement( int iIndex )
{

   TERMELEMENT returnElm;

   returnElm.dConst = 0;
   returnElm.dPower = 0;
   returnElm.elem   = "";
   returnElm.strVar = "";

   if ( iElmCount )
   {
      if ( iIndex <= iElmCount || iIndex >= 0 )
         return ( termPoint[ iIndex ] );
   }

   return ( returnElm );
}

/*************************************************************************
*   Purpose:
*      To change double's to a text string using the iostream
*   Input:
*      double
*   Output:
*      none
*   Return:
*      string
*   Parameters:
*      string ( double to change to a string )
**************************************************************************/
string Term::convertDouble( double dValue )
{
   ifstream ifile;
   ofstream ofile;
   string strTemp;

   ofile.precision( 5 );

   ofile.open( "~car03009.StringTouch.txt.tmp", ios::trunc );
   ofile << dValue;
   ofile.close();

   ifile.open( "~car03009.StringTouch.txt.tmp" );
   getline( ifile, strTemp );
   ifile.close();

   remove( "~car03009.StringTouch.txt.tmp" );

   return ( strTemp );
}

/*************************************************************************
*   Purpose:
*      Do the actual copy work
*   Input:
*       Term &
*   Output:
*      none
*   Return:
*      void
*   Parameters:
*      void ( Term object to be copied )
**************************************************************************/
void Term::copyTermObj( Term &objTerm )
{
   iElmCount = objTerm.getElmCount();
   termPoint = new TERMELEMENT [ iElmCount ];

   if ( termPoint == NULL )
   {
      cout << "Memory allocation failed\n";
      exit( 1 );
   }

   strTerm = objTerm.getTerm();

   for ( int iCount = 0; iCount < iElmCount; iCount++ )
      termPoint[ iCount ] = objTerm.getElement( iCount );
}

/*************************************************************************
*   Purpose:
*      Simple term parsing engine
*   Input:
*       const string
*   Output:
*      none
*   Return:
*      void
*   Parameters:
*      void ( plain text string to be parsed )
*   Note:
*      This is the main parse engine for converting a plain text term
*      into items that can be manipulated and worked with.
**************************************************************************/
void Term::parseEngine( string strtNewTerm )
{
   bool bAddConst = true;

   int iSpaceCount = 0;
   unsigned int iCount = 0;

   string strTmpTerm = "";
   string strNewTerm = strtNewTerm;

   TERMELEMENT *tmpElm;

   if ( strNewTerm.length() == 0 )
      return;

   // remove any trailing spaces from the terms we are using.
   for ( iCount = ( unsigned int ) strNewTerm.length(); iCount > 0; iCount-- )
   {
      if ( strNewTerm[ iCount ] == ' ' )
         strNewTerm[ iCount ] = '\0';
   }

   // First add spaces between the term elements.
   for ( iCount = 0; iCount < strNewTerm.length(); iCount++ )
   {
      // Use the alpha characters as the key marker to add the space after
      // the number value.
      if ( isalpha( strNewTerm[ iCount ] ) )
      {
         strTmpTerm += " ";
         strTmpTerm += strNewTerm[ iCount ];
      }
      else
      {
         if ( iCount > 0 )
         {
            // if the previous value is an alphabetical character
            // and the next character is a digit character
            // then add a space.
            if ( isalpha( strNewTerm[ iCount - 1 ] ) &&
              ( isdigit( strNewTerm[ iCount ] ) ) )
            {
               strTmpTerm += " ";
               strTmpTerm += strNewTerm[ iCount ];
            }
            else
               strTmpTerm += strNewTerm[ iCount ];
         }
         else
            strTmpTerm += strNewTerm[ iCount ];
      }
   }

   // Remove extra white space from each term element
   // this removes from the beginning of the line
   while ( strTmpTerm[ 0 ] == ' ' )
   {
      for ( iCount = 1; iCount < strTmpTerm.length(); iCount++ )
         strTmpTerm[ iCount - 1 ] = strTmpTerm[ iCount ];

      strTmpTerm[ strTmpTerm.length() - 1 ] = '\0';
   }

   // Remove extra white space from each term element
   // this removes those white spaces from the center of the line.
   for ( iCount = 1; iCount < strTmpTerm.length(); iCount++ )
   {
      if ( strTmpTerm[ iCount - 1 ] == ' ' && strTmpTerm[ iCount ] == ' ' )
      {
         for ( unsigned int iCount1 = iCount;
              iCount1 < strTmpTerm.length(); iCount1++ )
         {
            strTmpTerm[ iCount1 - 1 ] = strTmpTerm[ iCount1 ];
         }

         strTmpTerm[ strTmpTerm.length() - 1 ] = '\0';
      }
   }

   // Remove extra white space from each term element
   // move the '-' character next to the term element that it belongs too.
   for ( iCount = 1; iCount < strTmpTerm.length(); iCount++ )
   {
      if ( strTmpTerm[ iCount - 1 ] == '-' && strTmpTerm[ iCount ] == ' ' )
      {
         strTmpTerm[ iCount ] = '-';

         for ( unsigned int iCount1 = iCount;
            iCount1 < strTmpTerm.length(); iCount1++ )
         {
            strTmpTerm[ iCount1 - 1 ] = strTmpTerm[ iCount1 ];
         }

         strTmpTerm[ strTmpTerm.length() - 1 ] = '\0';
      }
   }

   // Count the number of spaces we have.
   for ( iCount = 0; iCount < strTmpTerm.length(); iCount++ )
   {
      if ( strTmpTerm[ iCount ] == ' ' )
         iSpaceCount++;
   }

   // Each term element can have an exponent value allocate memory for
   // a structure that stores these term elements.
   termPoint = new TERMELEMENT [ iSpaceCount + 1 ];

   if ( termPoint == NULL )
   {
      cout << "Memory allocation failed\n";
      exit( 1 );
   }

   iElmCount = iSpaceCount + 1;

   // clear the memory of spurious information
   for ( iSpaceCount = 0; iSpaceCount < iElmCount; iSpaceCount++ )
   {
      termPoint[ iSpaceCount ].elem    = "";
      termPoint[ iSpaceCount ].strVar  = "";
      termPoint[ iSpaceCount ].dConst  = 0;
      termPoint[ iSpaceCount ].dPower  = 0;
   }

   iSpaceCount = iCount = 0;

   // Parse out the term elements and store them in a TERMELEMENT structure
   // array.
   for ( ; iCount < strTmpTerm.length(); iCount++ )
   {
      if ( strTmpTerm[ iCount ] == ' ' )
         iSpaceCount++;
      else
      {
         if ( iSpaceCount == 0 && iCount == 0 && strTmpTerm[ iCount ] == '-' )
         {
            if ( ( iCount + 1 ) < strTmpTerm.length() )
               if ( isalpha( strTmpTerm[ iCount + 1 ] ) )
                  termPoint[ iSpaceCount ].strVar += strTmpTerm[ iCount ];
         }
         else if ( isalpha( strTmpTerm[ iCount ] ) ||
                           strTmpTerm[ iCount ] == '^' )
         {
               termPoint[ iSpaceCount ].strVar += strTmpTerm[ iCount ];
         }

         termPoint[ iSpaceCount ].elem += strTmpTerm[ iCount ];
      }
   }

   iSpaceCount = 0;

   // Parse out the term elements and store the correct values.
   // Store Constants in the dConst and powers in the dPower
   // element.
   for ( ; iSpaceCount < iElmCount; iSpaceCount++ )
   {
      string strTemp = "";
      for ( iCount = 0; iCount < termPoint[ iSpaceCount ].elem.length();
           iCount++ )
      {
         if ( isalpha( termPoint[ iSpaceCount ].elem[ iCount ] ) ||
             termPoint[ iSpaceCount ].elem[ iCount ] == '^' )
            break;

         strTemp += termPoint[ iSpaceCount ].elem[ iCount ];
      }

      // if we have a constant store it here.
      termPoint[ iSpaceCount ].dConst = atof( strTemp.c_str() );

      strTemp = "";
      for ( ; iCount < termPoint[ iSpaceCount ].elem.length(); iCount++ )
      {
         if ( isdigit( termPoint[ iSpaceCount ].elem[ iCount ] ) ||
             termPoint[ iSpaceCount ].elem[ iCount ] == '-' ||
             termPoint[ iSpaceCount ].elem[ iCount ] == '.' )
         {
             strTemp += termPoint[ iSpaceCount ].elem[ iCount ];
         }
      }

      // if we have an exponent store it here.
      termPoint[ iSpaceCount ].dPower = atof( strTemp.c_str() );
   }

   // check to see if the term has a constant as part of the term string
   for ( int iTerms1 = 0; iTerms1 < iElmCount; iTerms1++ )
      if ( termPoint[ iTerms1 ].dConst != 0 )
         bAddConst = false;

   // if the term does not have at least one constant of the value of 1
   // add a term element and then set the constant with the value of 1
   if ( bAddConst )
   {
      tmpElm = termPoint;
      termPoint = new TERMELEMENT [ ++iElmCount ];

      if ( termPoint == NULL )
      {
         cout << "Memory allocation failed\n";
         exit( 1 );
      }

      for ( int iCount = 1; iCount < iElmCount; iCount++ )
         termPoint[ iCount ] = tmpElm[ iCount - 1 ];

      termPoint[ 0 ].dConst   = 1;
      termPoint[ 0 ].dPower   = 0;
      termPoint[ 0 ].elem     = "";
      termPoint[ 0 ].strVar   = "";

      delete [] tmpElm;
   }

   combineTermElementValues( );

   strTerm = strTmpTerm;
}

/*************************************************************************
*   Purpose:
*      To correct terms into a single term value. This is needed if a term
*      has two associated constants or variables where the two values are of
*      the same type, where the user did not correctly input the correct
*      term values
*   Input:
*      none
*   Output:
*      none
*   Return:
*      none
*   Parameters:
*      void ( void )
**************************************************************************/
void Term::combineTermElementValues( void )
{
   TERMELEMENT tempTerm;

   // Process Exponents first
   for ( int iTerms1 = 0; iTerms1 < iElmCount; iTerms1++ )
   {
      if ( termPoint[ iTerms1 ].dConst && termPoint[ iTerms1 ].dPower )
      {
         termPoint[ iTerms1 ].dConst =
         pow( termPoint[ iTerms1 ].dConst, termPoint[ iTerms1 ].dPower );

         termPoint[ iTerms1 ].dPower = 0;
      }
   }

   // First Constants pass, multiplier constants together to create one
   // constants term value
   for ( int iTerms1 = 0; iTerms1 < iElmCount; iTerms1++ )
   {
      for ( int iTerms2 = 0; iTerms2 < iElmCount; iTerms2++ )
      {
         if ( iTerms1 != iTerms2 )
         {
            if ( termPoint[ iTerms1 ].dConst && termPoint[ iTerms2 ].dConst )
            {
               termPoint[ iTerms1 ].dConst *= termPoint[ iTerms2 ].dConst;
               termPoint[ iTerms2 ].dConst = 0;
            }
         }
      }
   }

   // Second Constants pass, move all constants to the left most position.
   for ( int iTerms1 = 0; iTerms1 < iElmCount; iTerms1++ )
   {
      for ( int iTerms2 = 0; iTerms2 < iElmCount; iTerms2++ )
      {
         if ( termPoint[ iTerms1 ].dConst && !termPoint[ iTerms2 ].dConst )
         {
            tempTerm = termPoint[ iTerms1 ];
            termPoint[ iTerms1 ] = termPoint[ iTerms2 ];
            termPoint[ iTerms2 ] = tempTerm;
         }
      }
   }
}

/*************************************************************************
*   Purpose:
*      To set a specific element to null
*   Input:
*      int
*   Output:
*      none
*   Return:
*      void
*   Parameters:
*      void ( term element position )
**************************************************************************/
void Term::setElmtoZero( int iIndex )
{
   if ( iIndex <= iElmCount || iIndex >= 0 )
   {
      strTerm = "";

      termPoint[ iIndex ].elem   = "";
      termPoint[ iIndex ].strVar = "";
      termPoint[ iIndex ].dConst = 0;
      termPoint[ iIndex ].dPower = 0;
   }
}

/*************************************************************************
*   Purpose:
*      To set a whole term to null
*   Input:
*      void
*   Output:
*      none
*   Return:
*      void
*   Parameters:
*      void ( void )
**************************************************************************/
void Term::setTermtoZero( void )
{
   for ( int iTerm = 0; iTerm < iElmCount; iTerm++ )
      setElmtoZero( iTerm );
}

/*************************************************************************
*   Purpose:
*      Parameterized Constructor
*   Input:
*      none
*   Output:
*      none
*   Return:
*      none
*   Parameters:
*      none ( object to be copied )
**************************************************************************/
void Term::operator = ( Term objTerm )
{
   termPoint = NULL;
   iElmCount = 0;
   copyTermObj( objTerm );
}

/*************************************************************************
*   Purpose:
*      Overloaded assignment operator
*   Input:
*       const string
*   Output:
*      none
*   Return:
*      void
*   Parameters:
*      void ( plain text string to be parsed )
**************************************************************************/
void Term::operator = ( string strNewTerm )
{
   termPoint = NULL;
   iElmCount = 0;
   parseEngine( strNewTerm );
}

/*************************************************************************
*   Purpose:
*      Overloaded operator for subtraction
*   Input:
*       Term &, Term &
*   Output:
*      none
*   Return:
*      Term
*   Parameters:
*      Term ( term object1 and term object2 )
*   Note:
*      To properly create a new term all math operations must be preformed
*      the term must be converted into a string and then the new term object
*      can be called into existence.
**************************************************************************/
Term operator - ( Term &objTerm1, Term &objTerm2 )
{
   bool bBadTerm = false;
   string strReturn = "";
   Term returnObj;

   TERMELEMENT tempTerm1;
   TERMELEMENT tempTerm2;

   // the element count should match if it is like terms
   if ( objTerm1.getElmCount() == objTerm2.getElmCount() )
   {
      for ( int iCount = 0; iCount < objTerm1.getElmCount(); iCount++ )
      {
         tempTerm1 = objTerm1.getElement( iCount );
         tempTerm2 = objTerm2.getElement( iCount );

         // check to see if we have matching parts to do the
         // math on.
         if ( ( tempTerm1.dPower != tempTerm2.dPower ) ||
             ( tempTerm1.strVar[ 0 ] != tempTerm2.strVar[ 0 ] ) )
         {
            bBadTerm = true;
            break;
         }

         // if our constant becomes Zero then the term must = 0
         // set the flag so it can be evaluated as Zero
         if ( tempTerm1.dConst || tempTerm2.dConst )
         {
            tempTerm1.dConst -= tempTerm2.dConst;
            if ( !tempTerm1.dConst )
            {
               bBadTerm = true;
               break;
            }
         }

         // format the text string for the constant
         if ( tempTerm1.dConst &&
            ( ( tempTerm1.dConst != 1 ) || objTerm1.getElmCount() == 1 ) )
         {
            strReturn += returnObj.convertDouble( tempTerm1.dConst );
         }

         // format the text string for the variable
         if ( tempTerm1.elem.length() &&
             tempTerm1.strVar.length() )
         {
            if ( tempTerm1.dPower )
               strReturn += tempTerm1.strVar;
            else
               strReturn += tempTerm1.strVar[ 0 ];
         }

         // format the text string for the exponent
         if ( tempTerm1.dPower && tempTerm1.dPower != 1 )
            strReturn += returnObj.convertDouble( tempTerm1.dPower );
      }
   }

   // if the term is good use the parsed string to build the new term
   // and return the result
   if ( !bBadTerm )
      returnObj = strReturn;

   return ( returnObj );
}

/*************************************************************************
*   Purpose:
*      Overloaded operator for addition
*   Input:
*       Term &, Term &
*   Output:
*      none
*   Return:
*      Term
*   Parameters:
*      Term ( term object1 and term object2 )
**************************************************************************/
Term operator + ( Term &objTerm1, Term &objTerm2 )
{
   bool bBadTerm = false;
   string strReturn = "";
   Term returnObj;

   TERMELEMENT tempTerm1;
   TERMELEMENT tempTerm2;

   // the element count should match if it is like terms
   if ( objTerm1.getElmCount() == objTerm2.getElmCount() )
   {
      for ( int iCount = 0; iCount < objTerm1.getElmCount(); iCount++ )
      {
         tempTerm1 = objTerm1.getElement( iCount );
         tempTerm2 = objTerm2.getElement( iCount );

         // check to see if we have matching parts to do the
         // math on.
         if ( ( tempTerm1.dPower != tempTerm2.dPower ) ||
             ( tempTerm1.strVar[ 0 ] != tempTerm2.strVar[ 0 ] ) )
         {
            bBadTerm = true;
            break;
         }

         // if our constant becomes Zero then the term must = 0
         // set the flag so it can be evaluated as Zero
         if ( tempTerm1.dConst || tempTerm2.dConst )
         {
            tempTerm1.dConst += tempTerm2.dConst;
            if ( !tempTerm1.dConst )
            {
               bBadTerm = true;
               break;
            }
         }

         // format the text string for the constant
         if ( tempTerm1.dConst &&
            ( ( tempTerm1.dConst != 1 ) || objTerm1.getElmCount() == 1 ) )
         {
            strReturn += returnObj.convertDouble( tempTerm1.dConst );
         }

         // format the text string for the variable
         if ( tempTerm1.elem.length() &&
             tempTerm1.strVar.length() )
         {
            if ( tempTerm1.dPower )
               strReturn += tempTerm1.strVar;
            else
               strReturn += tempTerm1.strVar[ 0 ];
         }

         // format the text string for the exponent
         if ( tempTerm1.dPower && tempTerm1.dPower != 1 )
            strReturn += returnObj.convertDouble( tempTerm1.dPower );
      }
   }

   // if the term is good use the parsed string to build the new term
   // and return the result
   if ( !bBadTerm )
      returnObj = strReturn;

   return ( returnObj );
}

/*************************************************************************
*   Purpose:
*      Overloaded operator for multiplication
*   Input:
*       Term &, Term &
*   Output:
*      none
*   Return:
*      Term
*   Parameters:
*      Term ( term object1 and term object2 )
**************************************************************************/
Term operator * ( Term &objTerm1, Term &objTerm2 )
{
   bool bBadTerm  = false;
   bool bAddPower = false;

   string strReturn = "";
   string strReturnAppend = "";

   Term returnObj;

   TERMELEMENT tempTerm1;
   TERMELEMENT tempTerm2;

   // In multiplication we are building a whole new unique string
   // parse through each term element for term1
   for ( int iCount1 = 0; iCount1 < objTerm1.getElmCount(); iCount1++ )
   {
      tempTerm1 = objTerm1.getElement( iCount1 );
      objTerm1.getTerm();
      // parse through each term element for term2
      for ( int iCount2 = 0; iCount2 < objTerm2.getElmCount(); iCount2++ )
      {
         // copy the values for quick access
         tempTerm2 = objTerm2.getElement( iCount2 );
         objTerm2.getTerm();
         // are our term parts the same
         if ( ( tempTerm1.strVar[ 0 ] == tempTerm2.strVar[ 0 ] ) ||
             ( tempTerm1.dConst > 0 && tempTerm2.dConst > 0 ) )
         {
            // are we working with a variable value in term 1
            // because the previous value matched add 1 to the power
            if ( tempTerm1.dPower == 0 && isalpha( tempTerm1.strVar[ 0 ] ) )
               tempTerm1.dPower++;

            // are we working with a variable value in term 2
            // because the previous value matched add 1 to the power
            if ( tempTerm2.dPower == 0 && isalpha( tempTerm2.strVar[ 0 ] ) )
               tempTerm2.dPower++;

            // add the power values
            tempTerm1.dPower += tempTerm2.dPower;

            // check to see if our constant has be come zero after
            // multiplication if so our term is now zero
            if ( tempTerm1.dConst || tempTerm2.dConst )
            {
               tempTerm1.dConst *= tempTerm2.dConst;
               if ( !tempTerm1.dConst )
               {
                  bBadTerm = true;
                  break;
               }
               else
                 break;
            }
         }
         else
         {
            // This is to address differing types of terms being multiplied
            // Term term1 = "-5x^2y^2";
            // Term term2 = "2x^2";
            // or
            // Term term1 = "-5x^2";
            // Term term2 = "2x^2y^2";
            if ( isalpha( tempTerm1.strVar[ 0 ] ) &&
                isalpha( tempTerm2.strVar[ 0 ] ) &&
                ( objTerm2.getElmCount() >
                  objTerm1.getElmCount() ) )
            {
               // format the text string for the constant
               if ( ( tempTerm2.dConst > 0 ) &&
               ( ( tempTerm2.dConst != 1 ) || objTerm2.getElmCount() == 1 ) )
               {
                  strReturn += returnObj.convertDouble( tempTerm2.dConst );
               }

               // format the text string for the variable
               if ( tempTerm2.elem.length() &&
                  tempTerm2.strVar.length() )
               {
                  if ( tempTerm2.dPower )
                     strReturnAppend += tempTerm2.strVar;
                  else
                     strReturnAppend += tempTerm2.strVar[ 0 ];
               }

                  if ( tempTerm2.dPower )
                  {
                     bAddPower = true;
                     for ( unsigned int iPower = 0;
                           iPower < tempTerm2.elem.length(); iPower++ )
                     {
                        if ( tempTerm2.elem[ iPower ] == '^' )
                        {
                           bAddPower = false;
                           break;
                        }
                     }
                  }

                  if ( bAddPower )
                  {
                     strReturn += "^";
                     bAddPower = false;
                  }

               // format the text string for the exponent
               if ( tempTerm2.dPower && tempTerm2.dPower != 1 )
               {
                  strReturnAppend +=
                  returnObj.convertDouble( tempTerm2.dPower );
               }
            }
         }
      }

      // format the text string for the constant
      if ( ( tempTerm1.dConst != 0 ) &&
         ( ( tempTerm1.dConst != 1 ) || objTerm1.getElmCount() == 1 ) )
      {
         strReturn += returnObj.convertDouble( tempTerm1.dConst );
      }

      // format the text string for the variable
      if ( tempTerm1.elem.length() &&
            tempTerm1.strVar.length() )
      {
         if ( tempTerm1.dPower )
            strReturn += tempTerm1.strVar;
         else
            strReturn += tempTerm1.strVar[ 0 ];
      }

      if ( tempTerm1.dPower )
      {
         bAddPower = true;
         for ( unsigned int iPower = 0;
               iPower < tempTerm1.elem.length(); iPower++ )
         {
            if ( tempTerm1.elem[ iPower ] == '^' )
            {
               bAddPower = false;
               break;
            }
         }
      }

      if ( bAddPower )
      {
         strReturn += "^";
         bAddPower = false;
      }

      // format the text string for the exponent
      if ( tempTerm1.dPower && tempTerm1.dPower != 1 )
         strReturn += returnObj.convertDouble( tempTerm1.dPower );
   }

   // if the term is good use the parsed string to build the new term
   // and return the result
   if ( !bBadTerm )
      returnObj = strReturn + " " + strReturnAppend;

   return ( returnObj );
}

/*************************************************************************
*   Purpose:
*      Overloaded operator for comparing two like terms
*   Input:
*       Term &, Term &
*   Output:
*      none
*   Return:
*      bool
*   Parameters:
*      true if like terms ( term object and term object )
*   Note:
*      This only is comparing like terms and nothing more.
**************************************************************************/
bool operator == ( Term &objTerm1, Term &objTerm2 )
{
   bool bGoodTerm = false;
   TERMELEMENT tempTerm1;
   TERMELEMENT tempTerm2;

   string str1;
   string str2;

   if ( objTerm1.getElmCount() == objTerm2.getElmCount() )
   {
      for ( int iTerm = 0; iTerm < objTerm1.getElmCount(); iTerm++ )
      {
         tempTerm1 = objTerm1.getElement( iTerm );
         tempTerm2 = objTerm2.getElement( iTerm );

         str1 = objTerm1.getTerm();
         str2 = objTerm2.getTerm();

         if ( tempTerm1.strVar[ 0 ] == tempTerm2.strVar[ 0 ] )
         {
            if ( tempTerm1.dPower == tempTerm2.dPower )
            {
               if ( isalpha( tempTerm1.strVar[ 0 ] ) &&
                   isalpha( tempTerm2.strVar[ 0 ] ) )
                  bGoodTerm = true;
               else if ( tempTerm1.dConst && tempTerm2.dConst )
                  bGoodTerm = true;
               else
                  bGoodTerm = false;
            }
            else
               bGoodTerm = false;
         }
         else
            bGoodTerm = false;
      }
   }
   else
      bGoodTerm = false;

   return ( bGoodTerm );
}

/*************************************************************************
*   Purpose:
*      Overloaded operator for sending the values to the stream
*   Input:
*       ostream &, Term &
*   Output:
*      none
*   Return:
*      ostream &
*   Parameters:
*      ostream ( ostream object and term object )
**************************************************************************/
ostream &operator << ( ostream &objStream, Term &objTerm )
{
   objStream << objTerm.getTerm();

   return ( objStream );
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
Poly::Poly()
{
   strPoly  = "";
   terms    = NULL;
   iLength  = 0;
}

/*************************************************************************
*   Purpose:
*     Destroy used memory
*   Input:
*      none
*   Output:
*      none
*   Return:
*      none
*   Parameters:
*      none ( none )
**************************************************************************/
Poly::~Poly()
{
   if ( iLength )
      delete [] terms;

   strPoly  = "";
   terms    = NULL;
   iLength  = 0;
}

/*************************************************************************
*   Purpose:
*     Copy the Poly object
*   Input:
*      Poly &
*   Output:
*      none
*   Return:
*      none
*   Parameters:
*      none ( reference to a Poly object to be copied )
**************************************************************************/
Poly::Poly( Poly &objPoly )
{
   strPoly  = "";
   terms    = NULL;
   iLength  = 0;

   copyPolyObj( objPoly );
}

/*************************************************************************
*   Purpose:
*     The actual poly copy function
*   Input:
*      Poly &
*   Output:
*      none
*   Return:
*      void
*   Parameters:
*      void ( reference to a Poly object to be copied )
**************************************************************************/
void Poly::copyPolyObj( Poly &objPoly )
{
   iLength  = objPoly.getTermCount();
   terms    = new Term [ iLength ];

   if ( terms == NULL )
   {
      cout << "Memory allocation failed\n";
      exit( 1 );
   }

   for ( int iCount = 0; iCount < iLength; iCount++ )
      terms[ iCount ] = objPoly.getTerm( iCount );
}

/*************************************************************************
*   Purpose:
*     Constructor for parsing a text string to build a polynomial
*   Input:
*      none
*   Output:
*      none
*   Return:
*      none
*   Parameters:
*      none ( term to be parsed )
**************************************************************************/
Poly::Poly( string strNewPoly )
{
   strPoly  = "";
   terms    = NULL;
   iLength  = 0;

   parseEngine( strNewPoly );
}

/*************************************************************************
*   Purpose:
*     Return the length of the polynomial
*   Input:
*      none
*   Output:
*      none
*   Return:
*      int
*   Parameters:
*      the number of polynomial terms ( none )
**************************************************************************/
int Poly::getTermCount( void )
{
   return ( iLength );
}

/*************************************************************************
*   Purpose:
*     Get the text string of the polynomial and return it to the user
*   Input:
*      none
*   Output:
*      none
*   Return:
*      string
*   Parameters:
*      the polynomial string ( void )
**************************************************************************/
string Poly::getPoly( void )
{
   string strNewPoly = "";
   string strTmp     = "";

   sortPoly( );

   for ( int iCount = 0; iCount < iLength; iCount++ )
   {
      strTmp = terms[ iCount ].getTerm();

      if ( strTmp[ 0 ] != '0' )
      {
         if ( strNewPoly.length() )
         {
            if ( iCount < iLength && iCount > 0 )
            {
               if ( terms[ iCount ].getElement( 0 ).dConst != 0 )
                  strNewPoly += " + ";
               else
                  strNewPoly += " ";
            }
         }

         strNewPoly += strTmp;
      }
   }

   return ( strNewPoly );
}

/*************************************************************************
*   Purpose:
*     To sort the polynomials
*   Input:
*      void
*   Output:
*      none
*   Return:
*      void
*   Parameters:
*      void ( void )
**************************************************************************/
void Poly::sortPoly( void )
{
   int iElmCount1;
   int iElmCount2;
   double dPower1;
   double dPower2;

   Term tmpTerm;

   TERMELEMENT tempTerm1;
   TERMELEMENT tempTerm2;

   if ( iLength <= 1 )
      return;

   // This runs a quick sort on the polynomial
   for ( int iCount1 = 0; iCount1 < iLength; iCount1++ )
   {
      // order based on power
      dPower1 = dPower2 = 0;

      // inner loop
      for ( int iCount2 = 0; iCount2 < iLength; iCount2++ )
      {
         if ( iCount1 != iCount2 )
         {
            iElmCount1 = terms[ iCount1 ].getElmCount();
            iElmCount2 = terms[ iCount2 ].getElmCount();

            // gather some info
            for ( int iElm1 = 0; iElm1 < iElmCount1; iElm1++ )
            {
               tempTerm1 = terms[ iCount1 ].getElement( iElm1 );

               if ( dPower1 < tempTerm1.dPower )
                  dPower1 = tempTerm1.dPower;
            }

            // gather some info
            for ( int iElm2 = 0; iElm2 < iElmCount2; iElm2++ )
            {
               tempTerm2 = terms[ iCount2 ].getElement( iElm2 );
               if ( dPower2 < tempTerm2.dPower )
                  dPower2 = tempTerm2.dPower;
            }

            // swap the order of the elements.
            if ( dPower1 < dPower2 )
            {
               tmpTerm = terms[ iCount1 ];
               terms[ iCount1 ] = terms[ iCount2 ];
               terms[ iCount2 ] = tmpTerm;
            }
         }
      }
   }
}

/*************************************************************************
*   Purpose:
*     Get a term element to work with.
*   Input:
*      int
*   Output:
*      none
*   Return:
*      Term
*   Parameters:
*      The term value returned ( int index of term )
**************************************************************************/
Term Poly::getTerm( int iIndex )
{
   Term returnObj;

   if ( iIndex <= iLength )
      returnObj = terms[ iIndex ];

   return ( returnObj );
}

/*************************************************************************
*   Purpose:
*     The polynomial parse engine
*   Input:
*      none
*   Output:
*      none
*   Return:
*      void
*   Parameters:
*      void ( a string to parse into terms )
**************************************************************************/
void Poly::parseEngine( string strNewPoly )
{
   int iTerm      = 0;
   string strTerm = "";

   strPoly = strNewPoly;

   for ( unsigned int iCount = 0; iCount < strNewPoly.length(); iCount++ )
   {
      if ( ( ( strNewPoly[ iCount ] == '-' ) &&
            ( strNewPoly[ iCount + 1 ] == ' ' ) )
            || strNewPoly[ iCount ] == '+' )
      {
         iLength++;
      }
   }

   // Length is always one greater.
   terms = new Term [ ++iLength ];

   if ( terms == NULL )
   {
      cout << "Memory allocation failed\n";
      exit( 1 );
   }

   iTerm = 0;

   for ( unsigned int iCount = 0; iCount < strNewPoly.length(); iCount++ )
   {
      if ( strNewPoly[ iCount ] != '+' && strNewPoly[ iCount ] != ' ' )
         strTerm += strNewPoly[ iCount ];  // continue parsing info

      if ( strNewPoly[ iCount ] == ' ' && strTerm.length() )
      {
         terms[ iTerm++ ] = strTerm;   // init the term
         strTerm = "";                 // reset the term string
      }
   }

   terms[ iTerm++ ] = strTerm;

   strPoly = strNewPoly;
}

/*************************************************************************
*   Purpose:
*      gather all of the term elements into one term list
*   Input:
*       Poly *, int &
*   Output:
*      none, int &
*   Return:
*      Term *
*   Parameters:
*      Term * ( Polyobject with term list to copy from,
*               length of copy from list )
**************************************************************************/
Term * Poly::gatherTermList( Poly &objPoly, int &iListSize )
{
   int iTermCount = 0;
   Term *term     = NULL;
   Term *tmpTerm  = NULL;

   // Gather all all of the items into a new list
   for ( int iCount = 0; iCount < objPoly.getTermCount(); iCount++ )
   {
      tmpTerm = term;
      term = new Term [ ++iTermCount ];

      if ( term == NULL )
      {
         cout << "Memory allocation failed\n";
         exit( 1 );
      }

      term[ 0 ] = objPoly.getTerm( iCount );
      term->getTerm();

      if ( tmpTerm )
      {
         for ( int iTerms = 1; iTerms < iTermCount; iTerms++ )
            term[ iTerms ] = tmpTerm[ iTerms - 1 ];

         delete [] tmpTerm;
         tmpTerm = NULL;
      }
   }

   // return the new size
   iListSize = iTermCount;

   return ( term );
}

/*************************************************************************
*   Purpose:
*      gather all of the term elements into one term list
*   Input:
*       Term *, Term *, int &, int
*   Output:
*      none, none, int &, none
*   Return:
*      Term *
*   Parameters:
*      Term * ( Term list to copy too, term list to copy from,
*               length of copy too list, length of copy from list )
**************************************************************************/
Term * Poly::gatherTermList( Term *term, Term *pTerm,
                             int &iListSize, int iOldTerm )
{
   int iTermCount = iListSize;   // set the initial size
   Term *tmpTerm  = NULL;

   // Gather all all of the items into a new list
   for ( int iCount = 0; iCount < iOldTerm; iCount++ )
   {
      tmpTerm = term;
      term = new Term [ ++iTermCount ];

      if ( term == NULL )
      {
         cout << "Memory allocation failed\n";
         exit( 1 );
      }

      term[ 0 ] = pTerm[ iCount ];

      if ( tmpTerm )
      {
         for ( int iTerms = 1; iTerms < iTermCount; iTerms++ )
            term[ iTerms ] = tmpTerm[ iTerms - 1 ];

         delete [] tmpTerm;
         tmpTerm = NULL;
      }
   }

   // return the new size
   iListSize = iTermCount;

   return ( term );
}

/*************************************************************************
*   Purpose:
*      Parameterized Constructor
*   Input:
*      none
*   Output:
*      none
*   Return:
*      none
*   Parameters:
*      none ( object to be copied )
**************************************************************************/
void Poly::operator = ( Poly objTerm )
{
   strPoly  = "";
   terms    = NULL;
   iLength  = 0;

   copyPolyObj( objTerm );
}

/*************************************************************************
*   Purpose:
*      Overloaded assignment operator
*   Input:
*       const string
*   Output:
*      none
*   Return:
*      void
*   Parameters:
*      void ( plain text string to be parsed )
**************************************************************************/
void Poly::operator = ( string strNewPoly )
{
   iLength  = 0;
   terms    = NULL;

   parseEngine( strNewPoly );
}

/*************************************************************************
*   Purpose:
*      to insert a value for x
*   Input:
*       double
*   Output:
*      none
*   Return:
*      void
*   Parameters:
*      double ( multiplier )
**************************************************************************/
double Poly::calcPoly( double dValue )
{
   double dResult = 0;

   for ( int iCount = 0; iCount < iLength; iCount++ )
      dResult += terms[ iCount ].calcTerm( dValue );

   return ( dResult );
}

/*************************************************************************
*   Purpose:
*      Overloaded operator for subtraction
*   Input:
*       Poly &, Poly &
*   Output:
*      none
*   Return:
*      Poly
*   Parameters:
*      Poly ( Poly object1 and Poly object2 )
**************************************************************************/
Poly operator - ( Poly &objPoly1, Poly &objPoly2 )
{
   bool bAddTerm  = true;
   int iTermCount = 0;
   int iLeft      = 0;
   int iRight     = 0;

   string strNewPoly = "";
   string strTmp     = "";

   Poly returnObj;

   Term tValue;

   Term *tLeft;
   Term *tRight;

   tLeft  = returnObj.gatherTermList( objPoly1, iLeft );
   tRight = returnObj.gatherTermList( objPoly2, iRight );

   Term *term    = NULL;
   Term *tmpTerm = NULL;

   for ( int iTerm1 = 0; iTerm1 < iLeft; iTerm1++ )
   {
      for ( int iTerm2 = 0; iTerm2 < iRight; iTerm2++ )
      {
         if ( tLeft[ iTerm1 ] == tRight[ iTerm2 ] )
         {
            tmpTerm = term;
            term = new Term [ ++iTermCount ];

            if ( term == NULL )
            {
               cout << "Memory allocation failed\n";
               exit( 1 );
            }

            tValue = tLeft[ iTerm1 ] - tRight[ iTerm2 ];
            term[ 0 ] = tValue;

            tLeft[ iTerm1 ].setTermtoZero();
            tRight[ iTerm2 ].setTermtoZero();

            if ( tmpTerm )
            {
               for ( int iTerms = 1; iTerms < iTermCount; iTerms++ )
                  term[ iTerms ] = tmpTerm[ iTerms - 1 ];

               delete [] tmpTerm;
               tmpTerm = NULL;
            }
         }
      }
   }

   term = returnObj.gatherTermList( term, tLeft, iTermCount, iLeft );
   term = returnObj.gatherTermList( term, tRight, iTermCount, iRight );

   // Collect like terms
   for ( int iTerm1 = 0; iTerm1 < iTermCount; iTerm1++ )
   {
      for ( int iTerm2 = 0; iTerm2 < iTermCount; iTerm2++ )
      {
         if ( ( term[ iTerm1 ] == term[ iTerm2 ] ) && ( iTerm1 != iTerm2 ) )
         {
            tValue = term[ iTerm1 ] + term[ iTerm2 ];
            term[ iTerm1 ] = tValue;
            term[ iTerm2 ].setTermtoZero();
         }
      }
   }

   // format the string for creating the new polynomial
   for ( int iCount = 0; iCount < iTermCount; iCount++ )
   {
      strTmp = term[ iCount ].getTerm();

      if ( strTmp[ 0 ] != '0' )
      {
         if ( strNewPoly.length() )
         {
            if ( iCount < iTermCount && iCount > 0 )
            {
               if ( term[ iCount ].getElement( 0 ).dConst != 0 )
                  strNewPoly += " + ";
               else
                  strNewPoly += " ";
            }
         }

         strNewPoly += strTmp;
      }
   }

   returnObj = strNewPoly;

   delete [] term;
   term = NULL;

   return ( returnObj );
}

/*************************************************************************
*   Purpose:
*      Overloaded operator for subtraction
*   Input:
*       Poly &, Poly &
*   Output:
*      none
*   Return:
*      Poly
*   Parameters:
*      Poly ( Poly object1 and Poly object2 )
**************************************************************************/
Poly operator + ( Poly &objPoly1, Poly &objPoly2 )
{
   bool bAddTerm  = true;
   int iTermCount = 0;
   int iLeft      = 0;
   int iRight     = 0;

   string strNewPoly = "";
   string strTmp     = "";

   Poly returnObj;

   Term tValue;

   Term *tLeft;
   Term *tRight;

   tLeft  = returnObj.gatherTermList( objPoly1, iLeft );
   tRight = returnObj.gatherTermList( objPoly2, iRight );

   Term *term    = NULL;
   Term *tmpTerm = NULL;

   for ( int iTerm1 = 0; iTerm1 < iLeft; iTerm1++ )
   {
      for ( int iTerm2 = 0; iTerm2 < iRight; iTerm2++ )
      {
         if ( tLeft[ iTerm1 ] == tRight[ iTerm2 ] )
         {
            tmpTerm = term;
            term = new Term [ ++iTermCount ];

            if ( term == NULL )
            {
               cout << "Memory allocation failed\n";
               exit( 1 );
            }

            tValue = tLeft[ iTerm1 ] + tRight[ iTerm2 ];
            term[ 0 ] = tValue;

            tLeft[ iTerm1 ].setTermtoZero();
            tRight[ iTerm2 ].setTermtoZero();

            if ( tmpTerm )
            {
               for ( int iTerms = 1; iTerms < iTermCount; iTerms++ )
                  term[ iTerms ] = tmpTerm[ iTerms - 1 ];

               delete [] tmpTerm;
               tmpTerm = NULL;
            }
         }
      }
   }

   term = returnObj.gatherTermList( term, tLeft, iTermCount, iLeft );
   term = returnObj.gatherTermList( term, tRight, iTermCount, iRight );

   // Collect like terms
   for ( int iTerm1 = 0; iTerm1 < iTermCount; iTerm1++ )
   {
      for ( int iTerm2 = 0; iTerm2 < iTermCount; iTerm2++ )
      {
         if ( ( term[ iTerm1 ] == term[ iTerm2 ] ) && ( iTerm1 != iTerm2 ) )
         {
            tValue = term[ iTerm1 ] + term[ iTerm2 ];
            term[ iTerm1 ] = tValue;
            term[ iTerm2 ].setTermtoZero();
         }
      }
   }

   // format the string for creating the new polynomial
   for ( int iCount = 0; iCount < iTermCount; iCount++ )
   {
      strTmp = term[ iCount ].getTerm();

      if ( strTmp[ 0 ] != '0' )
      {
         if ( strNewPoly.length() )
         {
            if ( iCount < iTermCount && iCount > 0 )
            {
               if ( term[ iCount ].getElement( 0 ).dConst != 0 )
                  strNewPoly += " + ";
               else
                  strNewPoly += " ";
            }
         }

         strNewPoly += strTmp;
      }
   }

   returnObj = strNewPoly;

   delete [] term;
   term = NULL;

   return ( returnObj );
}

/*************************************************************************
*   Purpose:
*      Overloaded operator for subtraction
*   Input:
*       Poly &, Poly &
*   Output:
*      none
*   Return:
*      Poly
*   Parameters:
*      Poly ( Poly object1 and Poly object2 )
**************************************************************************/
Poly operator * ( Poly &objPoly1, Poly &objPoly2 )
{
   bool bAddTerm  = true;
   int iTermCount = 0;
   int iLeft      = 0;
   int iRight     = 0;

   string strNewPoly = "";
   string strTmp     = "";

   Poly returnObj;

   Term tValue;

   Term *tLeft;
   Term *tRight;

   tLeft  = returnObj.gatherTermList( objPoly1, iLeft );
   tRight = returnObj.gatherTermList( objPoly2, iRight );

   Term *term    = NULL;
   Term *tmpTerm = NULL;

   for ( int iTerm1 = 0; iTerm1 < iLeft; iTerm1++ )
   {
      for ( int iTerm2 = 0; iTerm2 < iRight; iTerm2++ )
      {
         {
            tmpTerm = term;
            term = new Term [ ++iTermCount ];

            if ( term == NULL )
            {
               cout << "Memory allocation failed\n";
               exit( 1 );
            }

            tValue = tLeft[ iTerm1 ] * tRight[ iTerm2 ];
            term[ 0 ] = tValue;

            if ( tmpTerm )
            {
               for ( int iTerms = 1; iTerms < iTermCount; iTerms++ )
                  term[ iTerms ] = tmpTerm[ iTerms - 1 ];

               delete [] tmpTerm;
               tmpTerm = NULL;
            }
         }
      }
   }

   // format the string for creating the new polynomial
   for ( int iCount = 0; iCount < iTermCount; iCount++ )
   {
      strTmp = term[ iCount ].getTerm();

      if ( strTmp[ 0 ] != '0' )
      {
         if ( strNewPoly.length() )
         {
            if ( iCount < iTermCount && iCount > 0 )
            {
               if ( term[ iCount ].getElement( 0 ).dConst != 0 )
                  strNewPoly += " + ";
               else
                  strNewPoly += " ";
            }
         }

         strNewPoly += strTmp;
      }
   }

   Poly tmpReturn1;
   Poly tmpReturn2;

   tmpReturn1 = strNewPoly;

   returnObj = tmpReturn1 + tmpReturn2;

   delete [] term;
   term = NULL;

   return ( returnObj );
}

/*************************************************************************
*   Purpose:
*      Overloaded operator for sending the values to the stream
*   Input:
*       ostream &, Term &
*   Output:
*      none
*   Return:
*      ostream &
*   Parameters:
*      ostream ( ostream object and term object )
**************************************************************************/
ostream &operator << ( ostream &objStream, Poly &objPoly )
{
   objStream << objPoly.getPoly();

   return ( objStream );
}
