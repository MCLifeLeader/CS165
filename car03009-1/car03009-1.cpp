/**************************************************************************
* Program:
*    Homework 1, CS165 Calculating interest
* Author:
*    Brother Michael Carey
* Summary:
*    Calculate interest payments and the number of months until the
*    debt is settled.
*    
* Work log:
*    Date     Start Stop  Interruption Work
*    mm/dd/yy hh:mm hh:mm mmm          mmm
 *************************************************************************/

#include <iostream>
#include <stdlib.h>
using namespace std;

// Get a user inputted value.
float GetUserInput( char *sUserQuestion );
// Calculate the interest payment amount
float CalcInterestPayment( float fAmountOwed,    // Total Amount Owed
                          float fInterest        // Monthly Interest Rate
                         );
// Calculate the remaining debt after the payment has been paid.
float CalcRemainingDebt( float fAmountOwed,     // Total Amount Owed
                         float fInterestPayment,// Interest Payment Amount
                         float fPayment         // Payment Amount
                       );

/**************************************************************************
 Application entry point
 Takes three user arguments

 Amount Owed
 Monthly Interest Rate
 Monthly Payment Amount
 *************************************************************************/

int main( int argc, char *argv[] )
{
   // Init my variables
   int iMonth = 0;   // Months

   // Interest Payment amount, this is a calculated value
   float fInterestPayment   = 0;
   // Total amount owed
   float fAmountOwed       = 0;
   // The monthly interest rate
   float fInterest          = 0;
   // The monthly payment rate
   float fPayment          = 0;

   cout << "\n\nCalculate the number of Months until a debt is settled\n\n";

   // Check the command line argument and see if it is just the program name
   if( argc == 1 )
   {
      fAmountOwed = GetUserInput( "Enter Total Amount Owed: " );
      fInterest   = GetUserInput( "Enter Monthly Interest Rate: " );
      fPayment    = GetUserInput( "Enter Your Monthly Payment Amount: " );
   }
   else if( argc > 1 && argc < 3 )   // Check the users cmd line arg length.
   {
      // Report the command line error to the user.
      cout << "Usage: car03009_Proj1 TotalAmountOwed "
           << "MonthlyInterestRate MonthlyPaymentAmount\n\n";

      return( 1 );
   }
   else
   {
      fAmountOwed = ( float ) atof( argv[ 1 ] );
      fInterest   = ( float ) atof( argv[ 2 ] );
      fPayment    = ( float ) atof( argv[ 3 ] );

      // If the value is invalid have the user input it again
      if( fAmountOwed <= 0)
         fAmountOwed = GetUserInput( "Enter Total Amount Owed: " );

      // If the value is invalid have the user input it again
      if( fInterest <= 0)
         fInterest    = GetUserInput( "Enter Monthly Interest Rate: " );

      // If the value is invalid have the user input it again
      if( fPayment <= 0)
         fPayment    = GetUserInput( "Enter Your Monthly Payment Amount: " );
   }

   cout << "\nTotal Amount Owed: " << fAmountOwed << "\n";
   cout << "Monthly Interest Rate: " << fInterest << "\n";
   cout << "Monthly Payment Amount: " << fPayment << "\n";

   cout << "\n\nMonth\tInterest\tPrincible\n";
   cout << "-------------------------\n";

   // String format settings
   cout.setf(ios::fixed);
   cout.setf(ios::showpoint);
   cout.precision(2);

   while( fAmountOwed > 0 )
   {
      // Get the new amount owed from the previous amount owed
      fAmountOwed = CalcRemainingDebt(
                     fAmountOwed,
                     fInterestPayment = CalcInterestPayment(
                                       fAmountOwed,
                                       fInterest ),
                     fPayment );

      if( fPayment < fIntrestPayment )
      {
         cout << "\n\nYour Payment is less then the Interest owed each month.";
         cout << "\nYour Interest = " << fInterest;
         cout << "\nYour Payment = " fPayment;
         cout << "\n\n";
         return( 2 );
      }
      // if the Amount owed goes negative don't display the value
      if( fAmountOwed > fPayment )
         cout << ++iMonth << "\t$" << fInterestPayment << "\t$"
              << fAmountOwed << "\n";
   }

   // Display to the user the last month, interest payment, and amount owed.
   cout << "\n";
   cout << "Last Month = " << ++iMonth
        << "\nFinal Interest Payment: $" << fInterestPayment
        << "\nFinal Payment = $" << fAmountOwed + fPayment
        << "\n";

   return( 0 );
}

/**************************************************************************
 Calculate the interest payment amount and return it as a float
 *************************************************************************/

float CalcInterestPayment( float fAmountOwed, float fInterest )
{
   return( ( fAmountOwed * fInterest ) / 100 );
}

/**************************************************************************
 Get a user input value and return it as a float
 *************************************************************************/

float GetUserInput( char *sUserQuestion )
{
   char *sUserInput = NULL;
   float fUserValue = 0;

   // Allocate some memory for a char array
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

   // Clean up memory from char array
   delete [] sUserInput;
   sUserInput = NULL;
}

/**************************************************************************
  Calculate the remaining debt after the payment has been paid
  and return it as a float.
 *************************************************************************/

float CalcRemainingDebt( float fAmountOwed,     // Total Amount Owed
                         float fInterestPayment,// Interest Payment Amount
                         float fPayment         // Payment Amount
                        )
{
   return( fAmountOwed + fInterestPayment - fPayment );
}
