
#include "Money.h"

/*************************************************************************
*   Purpose:
*      Add two money objects
*   Input:
*      const Money &, const Money &
*   Output:
*      none
*   Return:
*      const Money
*   Parameters:
*      returning a constant Money Object( constant reference to a Money
*      Object )
**************************************************************************/
const Money operator + ( const Money& amount1, const Money& amount2 )
{
   int allCents1 = amount1.getCents() + amount1.getDollars() * 100;
   int allCents2 = amount2.getCents() + amount2.getDollars() * 100;
   int sumAllCents = allCents1 + allCents2;
   int absAllCents = abs( sumAllCents ); // Money can be negative.
   int finalDollars = absAllCents / 100;
   int finalCents = absAllCents % 100;

   if( sumAllCents < 0 )
   {
      finalDollars = -finalDollars;
      finalCents = -finalCents;
   }

   return( Money( finalDollars, finalCents ) );
}

/*************************************************************************
*   Purpose:
*      Subtract two money objects
*   Input:
*      const Money &, const Money &
*   Output:
*      none
*   Return:
*      const Money
*   Parameters:
*      returning a constant Money Object( constant reference to a Money
*      Object )
**************************************************************************/
const Money operator - ( const Money& amount1, const Money& amount2 )
{
   int allCents1 = amount1.getCents() + amount1.getDollars() * 100;
   int allCents2 = amount2.getCents() + amount2.getDollars() * 100;
   int diffAllCents = allCents1 - allCents2;
   int absAllCents = abs( diffAllCents ); // Money can be negative.
   int finalDollars = absAllCents / 100;
   int finalCents = absAllCents % 100;

   if( diffAllCents < 0 )
   {
      finalDollars = -finalDollars;
      finalCents = -finalCents;
   }

   return( Money( finalDollars, finalCents ) );
}

/*************************************************************************
*   Purpose:
*      Compairs two money objects
*   Input:
*      const Money &, const Money &
*   Output:
*      none
*   Return:
*      bool
*   Parameters:
*      true or false ( Money Object1, Money Object2 )
**************************************************************************/
bool operator == ( const Money& amount1, const Money& amount2 )
{
   return( ( amount1.getDollars() == amount2.getDollars() ) &&
           ( amount2.getCents()   == amount2.getCents() ) );
}

/*************************************************************************
*   Purpose:
*      Self Subtract operation
*   Input:
*      const Money &
*   Output:
*      none
*   Return:
*      const Money
*   Parameters:
*      returning a constant Money Object( constant reference to a Money
*      Object )
**************************************************************************/
const Money operator - ( const Money& amount )
{
   return( Money( -amount.getDollars(), -amount.getCents() ) );
}

/*************************************************************************
*   Purpose:
*      Specialized copy function
*   Input:
*      Money &
*   Output:
*      none
*   Return:
*      void
*   Parameters:
*      void ( reference to a Money object )
**************************************************************************/
void Money::operator = ( Money moneyObj )
{
   this->cents = moneyObj.getCents();
   this->dollars = moneyObj.getDollars();
}

/*************************************************************************
*   Purpose:
*      Output data to an ostream
*   Input:
*      ostream &, const Money &
*   Output:
*      none
*   Return:
*      ostream &
*   Parameters:
*      reference to an ostream object ( reference to an ostream object,
*      reference to a Money object )
**************************************************************************/
ostream& operator << ( ostream& outputStream, const Money& amount )
{
   int absDollars = abs( amount.dollars );
   int absCents = abs( amount.cents );
   if( amount.dollars < 0 || amount.cents < 0 )
      outputStream << "$-";
   else
      outputStream << '$';

   outputStream << absDollars;

   if( absCents >= 10 )
      outputStream << '.' << absCents;
   else
      outputStream << ".0" << absCents;

   return( outputStream );
}

/*************************************************************************
*   Purpose:
*      input data from an istream
*   Input:
*      istream &, Money &
*   Output:
*      none
*   Return:
*      istream &
*   Parameters:
*      reference to an istream object ( reference to an istream object,
*      reference to a Money object )
**************************************************************************/
istream& operator >> ( istream& inputStream, Money& amount )
{
   char dollarSign;
   inputStream >> dollarSign;
   if( dollarSign != '$' )
   {
      cout << "No dollar sign in Money input.\n";
      exit( 1 );
   }

   double amountAsDouble;
   inputStream >> amountAsDouble;
   amount.dollars = amount.dollarsPart( amountAsDouble );
   amount.cents = amount.centsPart( amountAsDouble );

   return( inputStream );
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
Money::Money() : dollars( 0 ), cents( 0 )
{

}

/*************************************************************************
*   Purpose:
*      Overloaded Constructor
*   Input:
*      double
*   Output:
*      none
*   Return:
*      none
*   Parameters:
*      none ( the whole dollar amount )
**************************************************************************/
Money::Money( double amount ) : dollars( dollarsPart( amount ) ), 
                                cents( centsPart( amount ) )
{

}

/*************************************************************************
*   Purpose:
*      Overloaded Constructor
*   Input:
*      int
*   Output:
*      none
*   Return:
*      none
*   Parameters:
*      none ( the dollars part ) default cents to zero
**************************************************************************/
Money::Money( int theDollars ) : dollars( theDollars ), cents( 0 )
{

}

/*************************************************************************
*   Purpose:
*      Copy Constructor, copy the dollars and cents
*   Input:
*      Money &
*   Output:
*      none
*   Return:
*      none
*   Parameters:
*      none ( a reference to a Money object )
**************************************************************************/
Money::Money( Money &moneyObj )
{
   this->cents = moneyObj.getCents();
   this->dollars = moneyObj.getDollars();
}

/*************************************************************************
*   Purpose:
*      Overloaded Constructor
*   Input:
*      int, int
*   Output:
*      none
*   Return:
*      none
*   Parameters:
*      none ( thedollars part and the cents part )
**************************************************************************/
Money::Money( int theDollars, int theCents )
{
   if( ( theDollars < 0 && theCents > 0 ) || 
       ( theDollars > 0 && theCents < 0 ) )
   {
      cout << "Inconsistent Money Data.\n";
      exit( 1 );
   }

   dollars  = theDollars;
   cents    = theCents;
}

/*************************************************************************
*   Purpose:
*      Get the dollars and cents
*   Input:
*      none
*   Output:
*      none
*   Return:
*      const double
*   Parameters:
*      The whole dollar amount ( none )
**************************************************************************/
double Money::getAmount( ) const
{
   return( dollars + cents * 0.01 );
}

/*************************************************************************
*   Purpose:
*      get just the dollar amount
*   Input:
*      none
*   Output:
*      none
*   Return:
*      const int
*   Parameters:
*      returning the dollars amount ( none )
**************************************************************************/
int Money::getDollars( ) const
{
   return( dollars );
}

/*************************************************************************
*   Purpose:
*      get just the cents amount
*   Input:
*      none
*   Output:
*      none
*   Return:
*      const int
*   Parameters:
*      returning the cents part ( none )
**************************************************************************/
int Money::getCents( ) const
{
   return( cents );
}

/*************************************************************************
*   Purpose:
*      output the money objects value
*   Input:
*      none
*   Output:
*      none
*   Return:
*      void
*   Parameters:
*      void ( none )
**************************************************************************/
void Money::output( ) const
{
   int absDollars = abs( dollars );
   int absCents = abs( cents );
   if( dollars < 0 || cents < 0 )
      cout << "$-";
   else
      cout << '$';

   cout << absDollars;

   if( absCents >= 10 )
      cout << '.' << absCents;
   else
      cout << ".0" << absCents;
}

/*************************************************************************
*   Purpose:
*      input data manually into the money object
*   Input:
*      none
*   Output:
*      none
*   Return:
*      void
*   Parameters:
*      void ( none )
**************************************************************************/
void Money::input( )
{
   char dollarSign;
   cin >> dollarSign;
   if( dollarSign != '$' )
   {
      cout << "No dollar sign in Money input.\n";
      exit( 1 );
   }

   double amountAsDouble;
   cin >> amountAsDouble;
   dollars = dollarsPart( amountAsDouble );
   cents = centsPart( amountAsDouble );
}

/*************************************************************************
*   Purpose:
*      get the dollars part
*   Input:
*      double
*   Output:
*      none
*   Return:
*      cosnt int
*   Parameters:
*      dallars part ( whole amount )
**************************************************************************/
int Money::dollarsPart( double amount ) const
{
   return( static_cast<int>( amount ) );
}

/*************************************************************************
*   Purpose:
*      get the cents part
*   Input:
*      double amount
*   Output:
*      none
*   Return:
*      const int
*   Parameters:
*      returning cents part ( whole amount )
**************************************************************************/
int Money::centsPart( double amount ) const
{
   double doubleCents = amount * 100;
   int intCents = ( round( fabs( doubleCents ) ) ) % 100;
   if( amount < 0 )
      intCents = -intCents;

   return( intCents );
}

/*************************************************************************
*   Purpose:
*      round the number
*   Input:
*      double
*   Output:
*      none
*   Return:
*      const int
*   Parameters:
*      rounded number ( number to be rounded )
**************************************************************************/
int Money::round( double number ) const
{
   return( static_cast<int>( floor( number + 0.5 ) ) );
}
