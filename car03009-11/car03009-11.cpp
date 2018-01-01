/***********************************************************************
* Program:
*    Homework 11, Working with File IO and class inheritance
*    Brother Cameron, CS 165
* Author:
*    Brother Michael Carey
* Summary:
*    This program demonstrates how to use class inheritance
***********************************************************************/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

using namespace std;

/*************************************************************************
*   Class:
*     Money
*   Purpose:
*     For use in the Vehicle inheritance project. The requirements in the
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

/*************************************************************************
*   Class:
*     Vehicle
*   Purpose:
*     To deal with different vehicle types of type 'class'
*************************************************************************/
class Vehicle
{
public:
   Vehicle();
   Vehicle( string sLicense,
            string sVIN,
            string sOwner,
            string sMake,
            string sModel,
            unsigned int iYear );

   void setLicense( const string sLicense );
   void setVIN( const string sVIN );
   void setOwner( const string sOwner );
   void setMake( const string sMake );
   void setModel( const string sModel );
   void setYear( const unsigned int iyear );

   string getLicense( void );
   string getVIN( void );
   string getOwner( void );
   string getMake( void );
   string getModel( void );
   unsigned int getYear( void );

   void print( void );
   double getFee( void );

protected:
   string strLicense;   // License number string, 7 char Max
   string strVIN;       // VIN (Vehicle ID Number) 4-digit number 
                        // (really a 20 digit number)
   string strOwner;     // Registered owner string
   string strMake;      // Make string
   string strModel;     // Model string
   unsigned int iYear;  // Year positive integer
private:
};

/*************************************************************************
*   Class:
*     PrivateVehicle
*   Purpose:
*     To deal with different vehicle types of type 'class'
*************************************************************************/
class PrivateVehicle : public Vehicle
{
public:
   PrivateVehicle();
   PrivateVehicle( string sLicense, 
                  string sVIN, 
                  string sOwner, 
                  string sMake, 
                  string sModel, 
                  unsigned int iYear,
                  string operatorName, 
                  string doSmogCheck );
   void setOperator( const string );
   void setbSmogCheck( const string );
   string getOperator( void );
   string smogCheck( void );

   void print( void );
   double getFee( void );

protected:
   string sOperator;  // Operating owner string
   string sSmogCheck;  // Smog check required true of false
private:
};

/*************************************************************************
*   Class:
*     CommercialVehicle
*   Purpose:
*     To deal with different vehicle types of type 'class'
*************************************************************************/
class CommercialVehicle : public Vehicle
{
public:
   CommercialVehicle();
   CommercialVehicle( string sLicense, 
                  string sVIN, 
                  string sOwner, 
                  string sMake, 
                  string sModel, 
                  unsigned int iYear,
                  Money amountPaid,
                  string strCounty );

   void setLicensePaid( const double fee );
   void setCounty( const string sCounty );

   double getLicensePaid( void );
   string getCounty( void );

   void print( void );
   double getFee( void );

protected:
   Money licensePaid;   // Amount of annual business license paid
                        // money type (use the money class)
   string county;       // County where business is head quartered string
private:
};

/*************************************************************************
*   Class:
*     PrivateSedan
*   Purpose:
*     To deal with different vehicle types of type 'class'
*************************************************************************/
class PrivateSedan : public PrivateVehicle
{
public:
   PrivateSedan();
   PrivateSedan( string sLicense,
                  string sVIN,
                  string sOwner,
                  string sMake,
                  string sModel,
                  unsigned int iYear,
                  string operatorName,
                  string doSmogCheck,
                  unsigned int theDoors );
   void setNumberofDoors( const unsigned int theDoors );
   unsigned int getNumberofDoors( void );

   void print( void );
   double getFee( void );

protected:
private:
   unsigned int iDoors; // Number of doors positive even Integer
};

/*************************************************************************
*   Class:
*     PrivateVan
*   Purpose:
*     To deal with different vehicle types of type 'class'
*************************************************************************/
class PrivateVan : public PrivateVehicle
{
public:
   PrivateVan();
   PrivateVan( string sLicense,
                  string sVIN,
                  string sOwner,
                  string sMake,
                  string sModel,
                  unsigned int iYear,
                  string operatorName,
                  string doSmogCheck );

protected:
private:
};

/*************************************************************************
*   Class:
*     PrivateMotorCycle
*   Purpose:
*     To deal with different vehicle types of type 'class'
*************************************************************************/
class PrivateMotorCycle : public PrivateVehicle
{
public:
   PrivateMotorCycle();
   PrivateMotorCycle( string sLicense,
                  string sVIN,
                  string sOwner,
                  string sMake,
                  string sModel,
                  unsigned int iYear,
                  string operatorName,
                  string doSmogCheck,
                  double theEngineSize );
   void setEngineSize( const double theEngineSize );
   double getEngineSize( void );

   void print( void );
   double getFee( void );

protected:
private:
   double dEngineSize;
};

/*************************************************************************
*   Class:
*     PrivatePickupTruck
*   Purpose:
*     To deal with different vehicle types of type 'class'
*************************************************************************/
class PrivatePickupTruck : public PrivateVehicle
{
public:
   PrivatePickupTruck();
   PrivatePickupTruck( string sLicense,
                  string sVIN,
                  string sOwner,
                  string sMake,
                  string sModel,
                  unsigned int iYear,
                  string operatorName,
                  string doSmogCheck,
                  double theGrossULoaded );
   void setGrossULoaded( const double theGrossULoaded );
   double getGrossULoaded( void );
   void print( void );

protected:
private:
   double dGrossULoaded;
};

/*************************************************************************
*   Class:
*     Commercial Bus
*   Purpose:
*     To deal with different vehicle types of type 'class'
*************************************************************************/
class CommericalBus : public CommercialVehicle
{
public:
   CommericalBus();
   CommericalBus( string sLicense,
                  string sVIN,
                  string sOwner,
                  string sMake,
                  string sModel,
                  unsigned int iYear,
                  Money amountPaid,
                  string strCounty,
                  unsigned short seating,
                  Money insure );
   void setInsurance( Money insure );
   void setCapacity( const unsigned short seating );

   double getInsurance( void );
   unsigned short getCapacity( void );

   void print( void );
   double getFee( void );

protected:
private:
   Money insurance;  // Liability insurance per passenger money_type
                     // (use money class)
   unsigned short capacity;   // Maximum passengers passenger_count_type
                              // (no negatives!)
};

/*************************************************************************
*   Class:
*     CommercialTaxi
*   Purpose:
*     To deal with different vehicle types of type 'class'
*************************************************************************/
class CommercialTaxi : public CommercialVehicle
{
public:
   CommercialTaxi();
   CommercialTaxi( string sLicense,
                  string sVIN,
                  string sOwner,
                  string sMake,
                  string sModel,
                  unsigned int iYear,
                  Money amountPaid,
                  string strCounty,
                  Money insure );
   void setInsurance( Money insure );
   double getInsurance( void );

   void print( void );
   double getFee( void );

protected:
private:
   Money insurance;  // Liability insurance per passenger money_type
                     // (use money class)
};

/*************************************************************************
*   Class:
*     CommericalTruck
*   Purpose:
*     To deal with different vehicle types of type 'class'
*************************************************************************/
class CommericalTruck : public CommercialVehicle
{
public:
   CommericalTruck();
   CommericalTruck( string sLicense,
                  string sVIN,
                  string sOwner,
                  string sMake,
                  string sModel,
                  unsigned int iYear,
                  Money amountPaid,
                  string strCounty,
                  double tons,
                  unsigned short axles );
   void setTons( double tons );
   void setNumOfAxles( const unsigned short axles );
   double getTons( void );
   unsigned short getNumOfAxles( void );

   void print( void );
   double getFee( void );

protected:
private:
   double dTons;   // Max cargo rating (tons) digits 3
   unsigned short numOfAxles;  // Number of axles axle_type
                              // (no negative values allowed)
};

string substr( string str, unsigned int &pos );

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
   unsigned int pos;
   ifstream readFile;
   string readData = "";

   string cp0;
   string cp1;
   string cp2;
   string cp3;
   string cp4;
   string cp5;
   string cp6;
   string cp7;
   string cp8;
   string cp9;


   CommericalBus        comBus;
   CommercialTaxi       comTaxi;
   CommericalTruck      comTruk;
   PrivateSedan         prvSedn;
   PrivateVan           prvVan;
   PrivateMotorCycle    prvCyle;
   PrivatePickupTruck   prvPtrk;

   cout.setf( ios::fixed );
   cout.setf( ios::showpoint );
   cout.precision( 2 );

   readFile.open( "vehicles.txt" );

   if ( readFile.fail( ) )
   {
      cerr << "Failure to open file exiting\n";
      exit( 1 );
   }

   while ( !readFile.eof() )
   {
      pos = 3;
      getline( readFile, readData );

      if ( readFile.eof() )
         break;

      // extract the various string parts
      cp0 = substr( readData, pos );
      cp1 = substr( readData, pos );
      cp2 = substr( readData, pos );
      cp3 = substr( readData, pos );
      cp4 = substr( readData, pos );
      cp5 = substr( readData, pos );
      cp6 = substr( readData, pos );
      cp7 = substr( readData, pos );
      cp8 = substr( readData, pos );
      cp9 = substr( readData, pos );

      // switch between the different vehicle types
      switch ( readData[ 0 ] )
      {
      case 'B':
         comBus = CommericalBus(
            cp0,
            cp1,
            cp2,
            cp3,
            cp4,
            atoi( cp5.c_str() ),
            Money( ( double ) atof( cp6.c_str() ) ),
            cp7,
            ( unsigned short ) atoi( cp8.c_str() ),
            Money( ( double ) atof( cp9.c_str() ) ) );

            comBus.print();
            cout << "License and Registration: $" << comBus.getFee( );
            cout << endl;
            cout << endl;
         break;
      case 'M':
         prvCyle = PrivateMotorCycle(
            cp0,
            cp1,
            cp2,
            cp3,
            cp4,
            atoi( cp5.c_str() ),
            cp6,
            cp7,
            ( double ) atof( cp8.c_str() ) );

            prvCyle.print();
            cout << "License and Registration: $" << prvCyle.getFee( );
            cout << endl;
            cout << endl;
         break;
      case 'P':
         prvPtrk = PrivatePickupTruck(
            cp0,
            cp1,
            cp2,
            cp3,
            cp4,
            atoi( cp5.c_str() ),
            cp6,
            cp7,
            ( double ) atof( cp8.c_str() ) );

            prvPtrk.print();
            cout << "License and Registration: $" << prvPtrk.getFee( );
            cout << endl;
            cout << endl;
         break;
      case 'S':
         prvSedn = PrivateSedan(
            cp0,
            cp1,
            cp2,
            cp3,
            cp4,
            atoi( cp5.c_str() ),
            cp6,
            cp7,
            ( unsigned int ) atoi( cp8.c_str() ) );

            prvSedn.print();
            cout << "License and Registration: $" << prvSedn.getFee( );
            cout << endl;
            cout << endl;
         break;
      case 'T':
         comTruk = CommericalTruck(
            cp0,
            cp1,
            cp2,
            cp3,
            cp4,
            atoi( cp5.c_str() ),
            Money( ( double ) atof( cp6.c_str() ) ),
            cp7,
            ( double ) atof( cp8.c_str() ),
            ( unsigned short ) atoi( cp9.c_str() ) );

            comTruk.print();
            cout << "License and Registration: $" << comTruk.getFee( );
            cout << endl;
            cout << endl;
         break;
      case 'V':
         prvVan = PrivateVan(
            cp0,
            cp1,
            cp2,
            cp3,
            cp4,
            atoi( cp5.c_str() ),
            cp6,
            cp7 );

            prvVan.print();
            cout << "License and Registration: $" << prvVan.getFee( );
            cout << endl;
            cout << endl;
         break;
      case 'X':
         comTaxi = CommercialTaxi(
            cp0,
            cp1,
            cp2,
            cp3,
            cp4,
            atoi( cp5.c_str() ),
            Money( ( double ) atof( cp6.c_str() ) ),
            cp7,
            Money( ( double ) atof( cp8.c_str() ) ) );

            comTaxi.print();
            cout << "License and Registration: $" << comTaxi.getFee( );
            cout << endl;
            cout << endl;
         break;
      default:
         cout << "default" << endl;
         break;
      }
   }

   readFile.close();

   return ( 0 );
}

string substr( string str, unsigned int &pos )
{
   string strReturn = "";
   int iSpaces = 0;

   for ( ; pos < str.length(); pos++ )
   {
      if ( iSpaces >= 2 && str[ pos ] != ' ' )
         break;

      strReturn += str[ pos ];

      if ( str[ pos ] == ' ' )
         iSpaces++;
      else
         iSpaces = 0;
   }

   while ( strReturn[ strReturn.length() - 2 ] == ' ' )
      strReturn[ strReturn.length() - 2 ] = '\0';

   return ( strReturn );
}

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

   if ( sumAllCents < 0 )
   {
      finalDollars = -finalDollars;
      finalCents = -finalCents;
   }

   Money object( finalDollars, finalCents );
   return ( object );
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

   if ( diffAllCents < 0 )
   {
      finalDollars = -finalDollars;
      finalCents = -finalCents;
   }

   Money object( finalDollars, finalCents );
   return ( object );
}

/*************************************************************************
*   Purpose:
*      Compare two money objects
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
   return ( ( amount1.getDollars() == amount2.getDollars() ) &&
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
   Money object( - amount.getDollars(), - amount.getCents() );
   return ( object );
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
   if ( amount.dollars < 0 || amount.cents < 0 )
      outputStream << "$-";
   else
      outputStream << '$';

   outputStream << absDollars;

   if ( absCents >= 10 )
      outputStream << '.' << absCents;
   else
      outputStream << ".0" << absCents;

   return ( outputStream );
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
   if ( dollarSign != '$' )
   {
      cout << "No dollar sign in Money input.\n";
      exit( 1 );
   }

   double amountAsDouble;
   inputStream >> amountAsDouble;
   amount.dollars = amount.dollarsPart( amountAsDouble );
   amount.cents = amount.centsPart( amountAsDouble );

   return ( inputStream );
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
Money::Money( Money& moneyObj )
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
*      none ( the dollars part and the cents part )
**************************************************************************/
Money::Money( int theDollars, int theCents )
{
   if ( ( theDollars < 0 && theCents > 0 ) ||
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
   return ( dollars + cents * 0.01 );
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
   return ( dollars );
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
   return ( cents );
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
   if ( dollars < 0 || cents < 0 )
      cout << "$-";
   else
      cout << '$';

   cout << absDollars;

   if ( absCents >= 10 )
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
   if ( dollarSign != '$' )
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
*      const int
*   Parameters:
*      dollars part ( whole amount )
**************************************************************************/
int Money::dollarsPart( double amount ) const
{
   return ( static_cast < int > ( amount ) );
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
   if ( amount < 0 )
      intCents = -intCents;

   return ( intCents );
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
   return ( static_cast < int > ( floor( number + 0.5 ) ) );
}

/*************************************************************************
*   Purpose:
*      Default constructor
**************************************************************************/
Vehicle::Vehicle() : strLicense( "Empty" ), strVIN( "Empty" ),
                     strOwner( "Empty" ), strMake( "Empty" ),
                     strModel( "Empty" ), iYear( 0 )
{

}

/*************************************************************************
*   Purpose:
*      overloaded constructor
**************************************************************************/
Vehicle::Vehicle( string sLicense,
                  string sVIN,
                  string sOwner,
                  string sMake,
                  string sModel,
                  unsigned int iYear )
                  : strLicense( sLicense ),
                  strVIN( sVIN ),
                  strOwner( sOwner ),
                  strMake( sMake ),
                  strModel( sModel ),
                  iYear( iYear )
{

}

/*************************************************************************
*   Purpose:
*      set license value
**************************************************************************/
void Vehicle::setLicense( const string sLicense )
{
   strLicense = sLicense;
}

/*************************************************************************
*   Purpose:
*      set VIN number
**************************************************************************/
void Vehicle::setVIN( const string sVIN )
{
   strVIN = sVIN;
}

/*************************************************************************
*   Purpose:
*      set Owner
**************************************************************************/
void Vehicle::setOwner( const string sOwner )
{
   strOwner = sOwner;
}

/*************************************************************************
*   Purpose:
*      set Make of car
**************************************************************************/
void Vehicle::setMake( const string sMake )
{
   strMake = sMake;
}

/*************************************************************************
*   Purpose:
*      set model of car
**************************************************************************/
void Vehicle::setModel( const string sModel )
{
   strModel = sModel;
}

/*************************************************************************
*   Purpose:
*      set set year of car
**************************************************************************/
void Vehicle::setYear( const unsigned int iyear )
{
   iYear = iyear;
}

/*************************************************************************
*   Purpose:
*      get license
**************************************************************************/
string Vehicle::getLicense( void )
{
   return ( strLicense );
}

/*************************************************************************
*   Purpose:
*      get VIN number
**************************************************************************/
string Vehicle::getVIN( void )
{
   return ( strVIN );
}

/*************************************************************************
*   Purpose:
*      get owners name
**************************************************************************/
string Vehicle::getOwner( void )
{
   return ( strOwner );
}

/*************************************************************************
*   Purpose:
*      get Cars make
**************************************************************************/
string Vehicle::getMake( void )
{
   return ( strMake );
}

/*************************************************************************
*   Purpose:
*      get cars model
**************************************************************************/
string Vehicle::getModel( void )
{
   return ( strModel );
}

/*************************************************************************
*   Purpose:
*      get year of car
**************************************************************************/
unsigned int Vehicle::getYear( void )
{
   return ( iYear );
}

/*************************************************************************
*   Purpose:
*      print out the bill with information
**************************************************************************/
void Vehicle::print( void )
{
   cout << "License: " << strLicense << endl;
   cout << "VIN#: " << strVIN << endl;
   cout << "Owner: " << strOwner << endl;
   cout << "Make: " << strMake << endl;
   cout << "Model: " << strModel << endl;
   cout << "Year: " << iYear << endl;
}

/*************************************************************************
*   Purpose:
*      calculate base fee plus other fees as deemed good by the state
*   1. All vehicles pay a base fee of $200 reduced by 15% for each year of
*   age of the vehicle, but in no case is the fee reduced by more than $120.
*   That means the lowest fee possible is $80. A 2000 car will received a
*   discount of (2003-2000) * 15% = 45% off the base fee.
**************************************************************************/
double Vehicle::getFee( void )
{
   double baseFee = 200.00;
   double newFee = 0;
   double year = iYear;

   newFee = baseFee * ( ( 2003 - year ) * .15 );

   if ( ( baseFee - newFee ) >= 80 )
      return ( baseFee - newFee );

   return ( 80.00 );
}

/*************************************************************************
*   Purpose:
*      default constructor
**************************************************************************/
PrivateVehicle::PrivateVehicle() : Vehicle( ), sOperator( "Empty" ),
                                   sSmogCheck( "undefined" )
{

}

/*************************************************************************
*   Purpose:
*      overloaded constructor
**************************************************************************/
PrivateVehicle::PrivateVehicle( string sLicense,
                  string sVIN,
                  string sOwner,
                  string sMake,
                  string sModel,
                  unsigned int iYear,
                  string operatorName,
                  string doSmogCheck )
                  : Vehicle( sLicense,
                     sVIN,
                     sOwner,
                     sMake,
                     sModel,
                     iYear ),
                  sOperator( operatorName ),
                  sSmogCheck( doSmogCheck )
{

}

/*************************************************************************
*   Purpose:
*      set the operators name
**************************************************************************/
void PrivateVehicle::setOperator( const string name )
{
   sOperator = name;
}

/*************************************************************************
*   Purpose:
*      set smog check status
**************************************************************************/
void PrivateVehicle::setbSmogCheck( const string smogStatus )
{
   if ( smogStatus == "true" || smogStatus == "TRUE" ||
       smogStatus == "false" || smogStatus == "FALSE" ||
       smogStatus == "False" || smogStatus == "True" )
   {
      sSmogCheck = smogStatus;
   }
   else
      sSmogCheck = "undefined";
}

/*************************************************************************
*   Purpose:
*      print out the bill with information
**************************************************************************/
string PrivateVehicle::getOperator( void )
{
   return ( sOperator );
}

/*************************************************************************
*   Purpose:
*      print out the bill with information
**************************************************************************/
string PrivateVehicle::smogCheck( void )
{
   return ( sSmogCheck );
}

/*************************************************************************
*   Purpose:
*      print out the bill with information
**************************************************************************/
void PrivateVehicle::print( void )
{
   Vehicle::print();
   cout << "Operator: " << sOperator << endl;
   cout << "Smog Check: " << sSmogCheck << endl;
}

/*************************************************************************
*   Purpose:
*      calculate base fee information plus Smog fees if they apply
*   3. All private (non-commercial) vehicles pay a smog check fee of $28.50
*   in those years when a smog check is required.
**************************************************************************/
double PrivateVehicle::getFee( void )
{
   double smogFee = 0;

   if ( sSmogCheck == "true" || sSmogCheck == "TRUE" ||
        sSmogCheck == "True" )
      smogFee = 28.50;

   return ( Vehicle::getFee() + smogFee );
}

/*************************************************************************
*   Purpose:
*      Default constructor
**************************************************************************/
CommercialVehicle::CommercialVehicle() : Vehicle( ), licensePaid( 0 ),
                                         county( "Empty" )
{

}

/*************************************************************************
*   Purpose:
*      overloaded constructor
**************************************************************************/
CommercialVehicle::CommercialVehicle( string sLicense,
                  string sVIN,
                  string sOwner,
                  string sMake,
                  string sModel,
                  unsigned int iYear,
                  Money amountPaid,
                  string sCounty )
                  : Vehicle( sLicense,
                     sVIN,
                     sOwner,
                     sMake,
                     sModel,
                     iYear ),
                  licensePaid( amountPaid ),
                  county( sCounty )
{

}

/*************************************************************************
*   Purpose:
*      set license fee information
**************************************************************************/
void CommercialVehicle::setLicensePaid( const double fee )
{
   licensePaid = Money( fee );
}

/*************************************************************************
*   Purpose:
*      set license county information
**************************************************************************/
void CommercialVehicle::setCounty( const string sCounty )
{
   county = sCounty;
}

/*************************************************************************
*   Purpose:
*      get license fee information
**************************************************************************/
double CommercialVehicle::getLicensePaid( void )
{
   return ( licensePaid.getAmount( ) );
}

/*************************************************************************
*   Purpose:
*      get the county
**************************************************************************/
string CommercialVehicle::getCounty( void )
{
   return ( county );
}

/*************************************************************************
*   Purpose:
*      print out the bill with information
**************************************************************************/
void CommercialVehicle::print( void )
{
   Vehicle::print();
   cout << "License Paid: " << licensePaid << endl;;
   cout << "County: " << county << endl;
}

/*************************************************************************
*   Purpose:
*      calculate base fee information plus commercial vehicle fees
*   2. All commercial vehicles are charged a surtax of 20% of the annual
*   business license with an upper limit of $100.
**************************************************************************/
double CommercialVehicle::getFee( void )
{
   double surTax;

   surTax = licensePaid.getAmount( ) * .2;

   if ( surTax > 100 )
      surTax = 100;

   return ( Vehicle::getFee() + surTax );
}

/*************************************************************************
*   Purpose:
*      default constructor
**************************************************************************/
PrivateSedan::PrivateSedan() : PrivateVehicle(), iDoors( 0 )
{

}

/*************************************************************************
*   Purpose:
*      overloaded constructor
**************************************************************************/
PrivateSedan::PrivateSedan( string sLicense,
                  string sVIN,
                  string sOwner,
                  string sMake,
                  string sModel,
                  unsigned int iYear,
                  string operatorName,
                  string doSmogCheck,
                  unsigned int theDoors )
                  : PrivateVehicle( sLicense,
                     sVIN,
                     sOwner,
                     sMake,
                     sModel,
                     iYear,
                     operatorName,
                     doSmogCheck ),
                  iDoors( theDoors )
{

}

/*************************************************************************
*   Purpose:
*      set the number of doors
**************************************************************************/
void PrivateSedan::setNumberofDoors( const unsigned int theDoors )
{
   iDoors = theDoors;
}

/*************************************************************************
*   Purpose:
*      get the number of doors
**************************************************************************/
unsigned int PrivateSedan::getNumberofDoors( void )
{
   return ( iDoors );
}

/*************************************************************************
*   Purpose:
*      print out vehicle information
**************************************************************************/
void PrivateSedan::print( void )
{
   PrivateVehicle::print();
   cout << "Doors: " << iDoors << endl;
}

/*************************************************************************
*   Purpose:
*      calculate base fee plus other fees as deemed good by the state
*   7. Private sedans: No additional charges
**************************************************************************/
double PrivateSedan::getFee( void )
{
   return ( PrivateVehicle::getFee() );
}

/*************************************************************************
*   Purpose:
*      default constructor
**************************************************************************/
PrivateVan::PrivateVan() : PrivateVehicle()
{

}

/*************************************************************************
*   Purpose:
*      overloaded constructor
**************************************************************************/
PrivateVan::PrivateVan( string sLicense,
                  string sVIN,
                  string sOwner,
                  string sMake,
                  string sModel,
                  unsigned int iYear,
                  string operatorName,
                  string doSmogCheck )
                  : PrivateVehicle( sLicense,
                     sVIN,
                     sOwner,
                     sMake,
                     sModel,
                     iYear,
                     operatorName,
                     doSmogCheck )
{

}

/*************************************************************************
*   Purpose:
*      default constructor
**************************************************************************/
PrivateMotorCycle::PrivateMotorCycle() : PrivateVehicle(), dEngineSize( 0 )
{

}

/*************************************************************************
*   Purpose:
*      overloaded constructor
**************************************************************************/
PrivateMotorCycle::PrivateMotorCycle( string sLicense,
                  string sVIN,
                  string sOwner,
                  string sMake,
                  string sModel,
                  unsigned int iYear,
                  string operatorName,
                  string doSmogCheck,
                  double theEngineSize )
                  : PrivateVehicle( sLicense,
                     sVIN,
                     sOwner,
                     sMake,
                     sModel,
                     iYear,
                     operatorName,
                     doSmogCheck ),
                  dEngineSize( theEngineSize )
{

}

/*************************************************************************
*   Purpose:
*      set the engine size
**************************************************************************/
void PrivateMotorCycle::setEngineSize( const double theEngineSize )
{
   dEngineSize = theEngineSize;
}

/*************************************************************************
*   Purpose:
*      get the engine size
**************************************************************************/
double PrivateMotorCycle::getEngineSize( void )
{
   return ( dEngineSize );
}

/*************************************************************************
*   Purpose:
*      print out vehicle information
**************************************************************************/
void PrivateMotorCycle::print( void )
{
   PrivateVehicle::print();
   cout << "Engine Size: " << dEngineSize << endl;
}

/*************************************************************************
*   Purpose:
*      calculate base fee plus other fees as deemed good by the state
*   8. Motorcycles: they pay and additional $0.25 per milliliter of
*   engine size above 100ml. Example, a motorcycle of 120 ml pays $0.25 *
*   (120 - 100) = $5 additional.
**************************************************************************/
double PrivateMotorCycle::getFee( void )
{
   double cycleFee = 0;
   if ( dEngineSize >= 100 )
      cycleFee = 0.25 * ( dEngineSize - 100 );

   return ( PrivateVehicle::getFee( ) + cycleFee );
}

/*************************************************************************
*   Purpose:
*      default constructor
**************************************************************************/
PrivatePickupTruck::PrivatePickupTruck() : PrivateVehicle(),
                                           dGrossULoaded( 0 )
{

}

/*************************************************************************
*   Purpose:
*      overloaded constructor
**************************************************************************/
PrivatePickupTruck::PrivatePickupTruck( string sLicense,
                  string sVIN,
                  string sOwner,
                  string sMake,
                  string sModel,
                  unsigned int iYear,
                  string operatorName,
                  string doSmogCheck,
                  double theGrossULoaded )
                  : PrivateVehicle( sLicense,
                     sVIN,
                     sOwner,
                     sMake,
                     sModel,
                     iYear,
                     operatorName,
                     doSmogCheck ),
                  dGrossULoaded( theGrossULoaded )
{

}

/*************************************************************************
*   Purpose:
*      set truck weight
**************************************************************************/
void PrivatePickupTruck::setGrossULoaded( const double theGrossULoaded )
{
   dGrossULoaded = theGrossULoaded;
}

/*************************************************************************
*   Purpose:
*      get truck weight
**************************************************************************/
double PrivatePickupTruck::getGrossULoaded( void )
{
   return ( dGrossULoaded );
}

/*************************************************************************
*   Purpose:
*      print the vehicle information
**************************************************************************/
void PrivatePickupTruck::print( void )
{
   PrivateVehicle::print();
   cout << "Gross Unloaded Weight: " << dGrossULoaded << endl;
}

/*************************************************************************
*   Purpose:
*      default constructor
**************************************************************************/
CommericalBus::CommericalBus() : CommercialVehicle(),
                                 insurance( 0 ), capacity( 0 )
{

}

/*************************************************************************
*   Purpose:
*      overloaded constructor
**************************************************************************/
CommericalBus::CommericalBus( string sLicense,
                  string sVIN,
                  string sOwner,
                  string sMake,
                  string sModel,
                  unsigned int iYear,
                  Money amountPaid,
                  string strCounty,
                  unsigned short seating,
                  Money insure )
                  : CommercialVehicle( sLicense,
                     sVIN,
                     sOwner,
                     sMake,
                     sModel,
                     iYear,
                     amountPaid,
                     strCounty ),
                  insurance( insure ),
                  capacity( seating )
{

}

/*************************************************************************
*   Purpose:
*      set insurance
**************************************************************************/
void CommericalBus::setInsurance( Money insure )
{
   insurance = insure;
}

/*************************************************************************
*   Purpose:
*      set seating
**************************************************************************/
void CommericalBus::setCapacity( const unsigned short seating )
{
   capacity = seating;
}

/*************************************************************************
*   Purpose:
*      get insurance
**************************************************************************/
double CommericalBus::getInsurance( void )
{
   return ( insurance.getAmount() );
}

/*************************************************************************
*   Purpose:
*      set seating
**************************************************************************/
unsigned short CommericalBus::getCapacity( void )
{
   return ( capacity );
}

/*************************************************************************
*   Purpose:
*      print out the bill with information
**************************************************************************/
void CommericalBus::print( void )
{
   CommercialVehicle::print();
   cout << "Capacity: " << capacity << endl;
   cout << "Insurance: " << insurance << endl;
}

/*************************************************************************
*   Purpose:
*      calculate base fee plus other fees as deemed good by the state
*   5. Commercial buses: they pay an additional $4 per passenger capacity.
*   Also, each bus pays an additional $1000 reduced by 0.1% of insurance
*   coverage exceeding $100000; however, the reduction cannot exceed $1000.
**************************************************************************/
double CommericalBus::getFee( void )
{
   double insurReduc = 1000.0;
   double seating = capacity;

   if ( insurance.getAmount( ) >= 100000 )
      insurReduc = 1000 - ( insurance.getAmount( ) * .001 );

   return ( CommercialVehicle::getFee() + insurReduc + ( seating * 4.0 ) );
}

/*************************************************************************
*   Purpose:
*      default constructor
**************************************************************************/
CommercialTaxi::CommercialTaxi() : CommercialVehicle(), insurance( 0 )
{

}

/*************************************************************************
*   Purpose:
*      overloaded constructor
**************************************************************************/
CommercialTaxi::CommercialTaxi( string sLicense,
                  string sVIN,
                  string sOwner,
                  string sMake,
                  string sModel,
                  unsigned int iYear,
                  Money amountPaid,
                  string strCounty,
                  Money insure )
                  : CommercialVehicle( sLicense,
                     sVIN,
                     sOwner,
                     sMake,
                     sModel,
                     iYear,
                     amountPaid,
                     strCounty ),
                  insurance( insure )
{

}

/*************************************************************************
*   Purpose:
*      set the insurance amount
**************************************************************************/
void CommercialTaxi::setInsurance( Money insure )
{
   insurance = insure;
}

/*************************************************************************
*   Purpose:
*      get the insurance amount
**************************************************************************/
double CommercialTaxi::getInsurance( void )
{
   return ( insurance.getAmount() );
}

/*************************************************************************
*   Purpose:
*      print out the bill with information
**************************************************************************/
void CommercialTaxi::print( void )
{
   CommercialVehicle::print();
   cout << "Insurance: " << insurance << endl;
}

/*************************************************************************
*   Purpose:
*      calculate base fee plus other fees as deemed good by the state
*   6. Commercial taxis: they pay an additional $100, which is reduce by
*   one-half if the liability coverage per passenger exceeds $1M.
**************************************************************************/
double CommercialTaxi::getFee( void )
{
   if ( insurance.getAmount() >= 1000000 )
      return ( CommercialVehicle::getFee() + 50.0 );

   return ( CommercialVehicle::getFee() + 100.0 );
}

/*************************************************************************
*   Purpose:
*      default constructor
**************************************************************************/
CommericalTruck::CommericalTruck() : CommercialVehicle(),
                                 dTons( 0 ), numOfAxles( 0 )
{

}

/*************************************************************************
*   Purpose:
*      overloaded constructor
**************************************************************************/
CommericalTruck::CommericalTruck( string sLicense,
                  string sVIN,
                  string sOwner,
                  string sMake,
                  string sModel,
                  unsigned int iYear,
                  Money amountPaid,
                  string strCounty,
                  double tons,
                  unsigned short axles )
                  : CommercialVehicle( sLicense,
                     sVIN,
                     sOwner,
                     sMake,
                     sModel,
                     iYear,
                     amountPaid,
                     strCounty ),
                  dTons( tons ),
                  numOfAxles( axles )
{

}

/*************************************************************************
*   Purpose:
*      set the tonnage of the truck
**************************************************************************/
void CommericalTruck::setTons( double tons )
{
   dTons = tons;
}

/*************************************************************************
*   Purpose:
*      set the number of axles on the truck
**************************************************************************/
void CommericalTruck::setNumOfAxles( const unsigned short axles )
{
   numOfAxles = axles;
}

/*************************************************************************
*   Purpose:
*      get the tonnage of the truck
**************************************************************************/
double CommericalTruck::getTons( void )
{
   return ( dTons );
}

/*************************************************************************
*   Purpose:
*      get the number of axles on the truck
**************************************************************************/
unsigned short CommericalTruck::getNumOfAxles( void )
{
   return ( numOfAxles );
}

/*************************************************************************
*   Purpose:
*      print out the bill with information
**************************************************************************/
void CommericalTruck::print( void )
{
   CommercialVehicle::print();
   cout << "Tons: " << dTons << endl;
   cout << "Axles: " << numOfAxles << endl;
}

/*************************************************************************
*   Purpose:
*      calculate base fee plus extra charges
*   4. Commercial trucks: they pay an additional fee equal to maximum
*   tonnage times $18 per ton plus $40 per axle.
**************************************************************************/
double CommericalTruck::getFee( void )
{
   double tmpAxels = numOfAxles;
   return ( CommercialVehicle::getFee() +
         ( ( dTons * 18.0 ) + ( 40.0 * tmpAxels ) ) );
}
