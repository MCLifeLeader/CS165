#ifndef MONEY_H
#define MONEY_H

#include "global.h"

/*************************************************************************
*   Class:
*     Money
*   Purpose:
*     For use in the Vehicle inheritance project. The requirments in the
*     assignment required a money type object and so I copied the Money
*     object from the book as is. There are only two functions that I
*     added, which are "operator =" and a copy constructor.
*************************************************************************/
class Money
{
public:
   Money();
   Money( double amount );
   Money( int theDollars, int theCents );
   Money( int theDollars );
   Money( Money& moneyObj );
   double getAmount() const;
   int getDollars() const;
   int getCents() const;
   void input(); // Reads the dollar sign as well as the amount number.
   void output() const;
   friend ostream& operator << ( ostream& outputStream, const Money& amount );
   friend istream& operator >> ( istream& inputStream, Money& amount );   
   void operator = ( Money moneyObj );
protected:
private:
   int dollars; // A negative amount is represented as negative dollars and
   int cents; // negative cents. Negative $4.50 is represented as -4 and -50

   int dollarsPart( double amount ) const;
   int centsPart( double amount ) const;
   int round( double number ) const;
};

const Money operator + ( const Money& amount1, const Money& amount2 );
const Money operator - ( const Money& amount1, const Money& amount2 );
bool operator == ( const Money& amount1, const Money& amount2 );
const Money operator - ( const Money& amount );

#endif
