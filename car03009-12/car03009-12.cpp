/***********************************************************************
* Program:
*    Homework 12, Polymorphism
*    Brother Cameron, CS 165
* Author:
*    Brother Michael Carey
* Summary:
*    This program demonstrates how to use class inheritance and
*    polymorphism.
***********************************************************************/

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <fstream>

using namespace std;

/*************************************************************************
*   Class:
*     Account
*   Purpose:
*     Base Class for others to manage accounts
**************************************************************************/
class Account
{
public:
   Account();
   Account( Account &acObj );
   Account( unsigned int accountNum,
            string customerName,
            double newBalance,
            double newRateAndFees );

   unsigned int getAccountNum( void );
   void setAccountNum( unsigned int accountNum );

   string getAccountName( void );
   void setAccountName( string customerName );

   double getBalance( void );
   void setBalance( double newBalance );

   double getIntrestRate( void );
   void setIntrestRate( double newRateAndFees );

   void print( void );

   virtual void update( void ) = 0;
   virtual void transaction( double trans ) = 0;
   virtual string getAccountInfo( void );

protected:
   string convertDouble( double dValue );

   unsigned int accntNum;
   string custName;
   double balance;
   double rateAndFees;
private:
};

/*************************************************************************
*   Class:
*     Savings : Account
*   Purpose:
*     Inherited class from Account, this is a savings account type
**************************************************************************/
class Savings : public Account
{
public:
   Savings();
   Savings( Savings &acObj );
   Savings( unsigned int accountNum,
            string customerName,
            double newBalance,
            double newRateAndFees );

   virtual string getAccountInfo( void );
   virtual void update( void );
   virtual void transaction( double trans );

protected:
private:
};

/*************************************************************************
*   Class:
*     Savings : Account
*   Purpose:
*     Inherited class from Account, this is a loan account type
**************************************************************************/
class Loan : public Account
{
public:
   Loan();
   Loan( Loan &acObj );
   Loan( unsigned int accountNum,
            string customerName,
            double newBalance,
            double newRateAndFees );

   virtual string getAccountInfo( void );
   virtual void update( void );
   virtual void transaction( double trans );

protected:
private:
};

/*************************************************************************
*   Class:
*     Savings : Account
*   Purpose:
*     Inherited class from Account, this is a checking account type
**************************************************************************/
class Checking : public Account
{
public:
   Checking();
   Checking( Checking &acObj );
   Checking( unsigned int accountNum,
            string customerName,
            double newBalance,
            double newRateAndFees );

   virtual string getAccountInfo( void );
   virtual void update( void );
   virtual void transaction( double trans );

protected:
private:
   double checkCount;
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
   unsigned int accountNum;
   int iAccountCount;

   ifstream readFile;
   string readData;

   // this is our accounts pointer array
   Account **pAccounts;

   readData = "";
   iAccountCount = 0;

   string cp0;
   string cp1;
   string cp2;
   string cp3;
   string cp4;

   // open the file
   readFile.open( "bank.txt", ios::in );

   if ( readFile.fail( ) )
   {
      cerr << "Failure to open file exiting.\n";
      exit( 1 );
   }

   // read the file and find out how many items needed to create the array
   while ( !readFile.eof() )
   {
      pos = 0;
      getline( readFile, readData );

      if ( readFile.eof() )
         break;

      switch ( readData[ 0 ] )
      {
      case 'c':
      case 'l':
      case 's':
         iAccountCount++;
         break;
      }
   }

   readFile.close();
   readFile.open( "bank.txt" );

   if ( readFile.fail( ) )
   {
      cerr << "Unable to open from file exiting.\n";
      exit( 1 );
   }

   // create a whole bunch of accounts
   pAccounts = new Account* [ iAccountCount ];

   iAccountCount = 0;

   if ( !pAccounts )
   {
      cerr << "Not enough memory exiting\n";
      exit( 1 );
   }

   // read the file
   while ( !readFile.eof() )
   {
      pos = 0;
      getline( readFile, readData );

      if ( readFile.eof() )
         break;

      // read in portions of the string
      cp0 = substr( readData, pos );
      cp1 = substr( readData, pos );
      cp2 = substr( readData, pos );
      cp3 = substr( readData, pos );
      cp4 = substr( readData, pos );

      accountNum = atoi( cp1.c_str() );

      // pick the option based on data file
      switch ( readData[ 0 ] )
      {
         // checking
      case 'c':
         pAccounts[ accountNum ] = new Checking;

         if ( !pAccounts[ accountNum ] )
         {
            cerr << "Not enough memory exiting\n";
            exit( 1 );
         }

         *pAccounts[ accountNum ] = Checking( accountNum, cp2,
                  ( double ) atof( cp3.c_str() ),
                  ( double ) atof( cp4.c_str() ) );
                  iAccountCount++;
         break;
         // loan
      case 'l':
         pAccounts[ accountNum ] = new Loan;

         if ( !pAccounts[ accountNum ] )
         {
            cerr << "Not enough memory exiting\n";
            exit( 1 );
         }

         *pAccounts[ accountNum ] = Loan( accountNum, cp2,
                  ( double ) atof( cp3.c_str() ),
                  ( double ) atof( cp4.c_str() ) );
                  iAccountCount++;
         break;
         // savings
      case 's':
         pAccounts[ accountNum ] = new Savings;

         if ( !pAccounts[ accountNum ] )
         {
            cerr << "Not enough memory exiting\n";
            exit( 1 );
         }

         *pAccounts[ accountNum ] = Savings ( accountNum, cp2,
                  ( double ) atof( cp3.c_str() ),
                  ( double ) atof( cp4.c_str() ) );
                  iAccountCount++;
         break;
         // process transaction
      case 't':
         pAccounts[ accountNum ]->transaction(
                  ( double ) atof( cp2.c_str() ) );
         break;
         // update account
      case 'u':
         pAccounts[ accountNum ]->update();
         break;
      default:
         break;
      }
   }

   // delete the memory allocated
   for ( int iCount = 0; iCount < iAccountCount; iCount++ )
      delete pAccounts[ iCount ];

   // delete the array of accounts pointers
   delete [] pAccounts;

   // close the file
   readFile.close();

   return ( 0 );
}

/*************************************************************************
*   Purpose:
*      To return a small segment from a string
**************************************************************************/
string substr( string str, unsigned int &pos )
{
   string strReturn = "";
   int iSpaces = 0;

   // search for spaces as delimiters
   for ( ; pos < str.length(); pos++ )
   {
      if ( iSpaces >= 1 && str[ pos ] != ' ' )
         break;

      strReturn += str[ pos ];

      if ( str[ pos ] == ' ' )
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
Account::Account() : accntNum( 0 ), custName( "blank" )
{
}

/*************************************************************************
*   Purpose:
*      Overloaded Constructor, Copy Constructor
**************************************************************************/
Account::Account( Account &acObj )
{
   accntNum    = acObj.getAccountNum();
   custName    = acObj.getAccountName();
   balance    = acObj.getBalance();
   rateAndFees = acObj.getIntrestRate();
}

/*************************************************************************
*   Purpose:
*      Overloaded constructor initialize variables in the class
**************************************************************************/
Account::Account( unsigned int accountNum,
                  string customerName,
                  double newBalance,
                  double newRateAndFees ) :
                  accntNum( accountNum ),
                  custName( customerName ),
                  balance( newBalance ),
                  rateAndFees( newRateAndFees )
{
   cout.setf( ios::fixed );
   cout.setf( ios::showpoint );
   cout.precision( 2 );
}

/*************************************************************************
*   Purpose:
*      get the account number
**************************************************************************/
unsigned int Account::getAccountNum( void )
{
   return ( accntNum );
}

/*************************************************************************
*   Purpose:
*      set the account number
**************************************************************************/
void Account::setAccountNum( unsigned int accountNum )
{
   accntNum = accountNum;
}

/*************************************************************************
*   Purpose:
*      get the account name
**************************************************************************/
string Account::getAccountName( void )
{
   return ( custName );
}

/*************************************************************************
*   Purpose:
*      set the account name
**************************************************************************/
void Account::setAccountName( string customerName)
{
   custName = customerName;
}

/*************************************************************************
*   Purpose:
*      get the balance
**************************************************************************/
double Account::getBalance( void )
{
   return ( balance );
}

/*************************************************************************
*   Purpose:
*      set the balance
**************************************************************************/
void Account::setBalance( double newBalance )
{
   balance = newBalance;
}

/*************************************************************************
*   Purpose:
*      get the interest rate
**************************************************************************/
double Account::getIntrestRate( void )
{
   return ( rateAndFees );
}

/*************************************************************************
*   Purpose:
*      set the interest rate
**************************************************************************/
void Account::setIntrestRate( double newRateAndFees )
{
   rateAndFees = newRateAndFees;
}

/*************************************************************************
*   Purpose:
*      To change doubles to a text string using the iostream
**************************************************************************/
string Account::convertDouble( double dValue )
{
   ifstream ifile;
   ofstream ofile;
   string strTemp;

   ofile.setf( ios::fixed );
   ofile.setf( ios::showpoint );
   ofile.precision( 2 );

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
*      print the information using polymorphism
**************************************************************************/
void Account::print( void )
{
   cout << getAccountInfo();
}

/*************************************************************************
*   Purpose:
*      return account information
**************************************************************************/
string Account::getAccountInfo( void )
{
   return ( "Invalid Account\n" );
}

/*************************************************************************
*   Purpose:
*      default constructor
**************************************************************************/
Savings::Savings() : Account( 0, "Invalid", 0, 0 )
{
}

/*************************************************************************
*   Purpose:
*      Overloaded Constructor, Copy Constructor
**************************************************************************/
Savings::Savings( Savings &acObj ) : Account( acObj )
{
}

/*************************************************************************
*   Purpose:
*      Overloaded constructor initialize variables in the class
**************************************************************************/
Savings::Savings( unsigned int account,
                  string name,
                  double newBalance,
                  double newRateAndFees )
                  : Account( account,
                     name,
                     newBalance,
                     newRateAndFees )
{
   cout << "new account...\n";
   cout << custName << " (savings): balance is $" << balance << endl;
}

/*************************************************************************
*   Purpose:
*      return account information
**************************************************************************/
string Savings::getAccountInfo( void )
{
   string formatOutput;

   formatOutput = custName + " (savings): balance is $";
   formatOutput += convertDouble( balance ) + "\n";

   return ( formatOutput );
}

/*************************************************************************
*   Purpose:
*      update the account with business logic
**************************************************************************/
void Savings::update( void )
{
   cout << "update...\n";
   cout << custName << " (savings): $" << ( balance * rateAndFees )
        << " applied to account\n";

   balance += ( balance * rateAndFees );

   print( );
}

/*************************************************************************
*   Purpose:
*      Process a transaction
**************************************************************************/
void Savings::transaction( double trans )
{
   cout << "transaction..." << endl;

   if ( ( balance + trans ) < 0 )
      cout << custName << " (savings): $" << ( balance - trans )
           << " rejected (insufficient funds)\n";
   else
   {
      balance += trans;

      cout << custName << " (savings): $" << trans << " applied to account\n";
   }

   print( );
}

/*************************************************************************
*   Purpose:
*      default constructor
**************************************************************************/
Loan::Loan() : Account( 0, "Invalid", 0, 0 )
{
}

/*************************************************************************
*   Purpose:
*      Overloaded Constructor, Copy Constructor
**************************************************************************/
Loan::Loan( Loan &acObj ) : Account( acObj )
{
}

/*************************************************************************
*   Purpose:
*      Overloaded constructor initialize variables in the class
**************************************************************************/
Loan::Loan( unsigned int account,
                  string name,
                  double newBalance,
                  double newRateAndFees )
                  : Account( account,
                     name,
                     - newBalance,
                     newRateAndFees )
{
   cout << "new account...\n";
   cout << custName << " (loan): balance is $" << balance << endl;
}

/*************************************************************************
*   Purpose:
*      return account information
**************************************************************************/
string Loan::getAccountInfo( void )
{
   string formatOutput;

   formatOutput = custName + " (loan): balance is $";
   formatOutput += convertDouble( balance ) + "\n";

   return ( formatOutput );
}

/*************************************************************************
*   Purpose:
*      update the account with business logic
**************************************************************************/
void Loan::update( void )
{
   cout << "update...\n";
   cout << custName << " (loan): $" << ( balance * rateAndFees )
        << " applied to account\n";

   balance += ( balance * rateAndFees );

   print( );
}

/*************************************************************************
*   Purpose:
*      Process a transaction
**************************************************************************/
void Loan::transaction( double trans )
{
   cout << "transaction..." << endl;

   if ( ( balance + trans ) > 0 )
      cout << custName << " (loan): $" << ( balance - trans )
           << " rejected (over paid loan)\n";
   else
   {
      balance += trans;

      cout << custName << " (loan): $" << trans << " applied to account\n";
   }

   print( );
}

/*************************************************************************
*   Purpose:
*      default constructor
**************************************************************************/
Checking::Checking() : Account( 0, "Invalid", 0, 0 ), checkCount( - 1 )
{
}

/*************************************************************************
*   Purpose:
*      Overloaded Constructor, Copy Constructor
**************************************************************************/
Checking::Checking( Checking &acObj ) : Account( acObj ), checkCount( - 1 )
{
}

/*************************************************************************
*   Purpose:
*      Overloaded constructor initialize variables in the class
**************************************************************************/
Checking::Checking( unsigned int account,
                  string name,
                  double newBalance,
                  double newRateAndFees )
                  : Account( account,
                     name,
                     newBalance,
                     newRateAndFees ), checkCount( 0 )
{
   cout << "new account...\n";
   cout << custName << " (checking): balance is $" << balance << endl;
}

/*************************************************************************
*   Purpose:
*      return account information
**************************************************************************/
string Checking::getAccountInfo( void )
{
   string formatOutput;

   formatOutput = custName + " (checking): balance is $";
   formatOutput += convertDouble( balance ) + "\n";

   return ( formatOutput );
}

/*************************************************************************
*   Purpose:
*      update the account with business logic
**************************************************************************/
void Checking::update( void )
{
   cout << "update...\n";
   cout << custName << " (checking): $" << -( rateAndFees * checkCount )
        << " applied to account\n";

   balance -= ( rateAndFees * checkCount );

   checkCount = 0;

   print( );
}

/*************************************************************************
*   Purpose:
*      Process a transaction
**************************************************************************/
void Checking::transaction( double trans )
{
   cout << "transaction..." << endl;

   if ( ( balance + trans ) < 0 )
   {
      cout << custName << " (checking): $" << trans
           << " rejected (insufficient funds)\n";
      cout << custName << " (checking): $-25.00 applied to account\n";
      balance -= 25.0;
   }
   else
   {
      balance += trans;

      cout << custName << " (checking): $" << trans 
           << " applied to account\n";
   }

   checkCount++;

   print( );
}
