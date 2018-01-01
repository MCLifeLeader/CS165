/**************************************************************************
* Program:
*    Homework 4, CS165
* Author:
*    Brother Michael Carey
* Summary:
*    To find all of the prime numbers between 2 and an upper value.
*    
* Work log:
*    Date     Start Stop  Interruption Work
*    mm/dd/yy hh:mm hh:mm mmm          mmm
 *************************************************************************/
#include <iostream>
using namespace std;

//  Student record structure
struct StudentInfo
{
   int iStudentNumber;     // Student Number
   char cFinalGrade;       // Final Letter Grade
   double dQuizScores;     // Quiz Score Total
   double dMidTerm;        // Midterm Score
   double dFinal;          // Final Score
   double dAverageTotal;   // Total Grade
};

// Calculates out the grades
void calculateGrades( StudentInfo studentInfo[], int iNumOfStudents );
// Gets the student data
void getStudentData( StudentInfo studentInfo[], int iNumOfStudents );
// Prints the student scores
void printStudentData( const StudentInfo STUDENTINFO[], int iNumofStudents );

/**************************************************************************
   Purpose:
      Gather some Student information.
   Input:
      void
   Output:
      none
   Return: 
      int
   Parameters:
      Program return value ( void ).
 *************************************************************************/

int main( void )
{
   const int NUM_OF_STUDENTS = 3;

   // Declaration of my student structure array
   StudentInfo studentInfo[ NUM_OF_STUDENTS ];

   getStudentData( studentInfo, NUM_OF_STUDENTS );

   calculateGrades( studentInfo, NUM_OF_STUDENTS );

   printStudentData( studentInfo, NUM_OF_STUDENTS );

   return( 0 );
}

/**************************************************************************
   Purpose:
      Calculate Student Grades.
   Input:
      void
   Output:
      none
   Return: 
      void
   Parameters:
      void ( structure array of type StudentInfo, int number of students ).
 *************************************************************************/

void calculateGrades( StudentInfo studentInfo[], int iNumOfStudents )
{
   for( int iCount = 0; iCount < iNumOfStudents; iCount++ )
   {
      // Add up the total grade
      studentInfo[ iCount ].dAverageTotal = 
      ( 
         studentInfo[ iCount ].dQuizScores + 
         studentInfo[ iCount ].dMidTerm +
         studentInfo[ iCount ].dFinal 
      ) * 100;

      // Figure out the grade letter
      if( studentInfo[ iCount ].dAverageTotal > 90 )
         studentInfo[ iCount ].cFinalGrade = 'A';
      else if( studentInfo[ iCount ].dAverageTotal > 80 )
         studentInfo[ iCount ].cFinalGrade = 'B';
      else if( studentInfo[ iCount ].dAverageTotal > 70 )
         studentInfo[ iCount ].cFinalGrade = 'C';
      else if( studentInfo[ iCount ].dAverageTotal > 60 )
         studentInfo[ iCount ].cFinalGrade = 'D';
      else
         studentInfo[ iCount ].cFinalGrade = 'F';
   }
}

/**************************************************************************
   Purpose:
      Gather some Student information.
   Input:
      void
   Output:
      none
   Return: 
      void
   Parameters:
      void ( structure array of type StudentInfo, int number of students ).
 *************************************************************************/

void getStudentData( StudentInfo studentInfo[], int iNumOfStudents )
{
   bool  bContinueFlag;
   float fTempValue = 0; // Get User Input

   const double QUIZ_WEIGHT      = 0.125;
   const double MIDTERM_WEIGHT   = 0.25;
   const double FINAL_WEIGHT     = 0.5;

   for( int iCount = 0; iCount < iNumOfStudents; iCount++ )
   {
      cout << "\n";

      // Get the student number
      while( 1 )
      {
         cout << "Enter student number: ";
         cin >> studentInfo[ iCount ].iStudentNumber;
         if( studentInfo[ iCount ].iStudentNumber > 0 )
            break;
      }

      // Get the quiz scores
      while( 1 )
      {
         bContinueFlag = true;

         cout << "Enter two quiz scores (out of 10): ";
         cin >> fTempValue;
         if( fTempValue >= 0 && fTempValue <= 10 )
            studentInfo[ iCount ].dQuizScores = ( fTempValue / 10 )
            * QUIZ_WEIGHT;
         else
            bContinueFlag = false;

         cin >> fTempValue;
         if( fTempValue >= 0 || fTempValue <= 10 )
            studentInfo[ iCount ].dQuizScores += ( fTempValue / 10 )
            * QUIZ_WEIGHT;
         else
            bContinueFlag = false;

         if( bContinueFlag == true )
            break;
      }

      // Get the midterm test score
      while( 1 )
      {
         cout << "Enter midterm (out of 100): ";
         cin >> fTempValue;
         if( fTempValue >= 0 || fTempValue <= 10 )
         {
            studentInfo[ iCount ].dMidTerm = ( fTempValue / 100 )
            * MIDTERM_WEIGHT;
            break;
         }
      }

      // Get the final test score
      while( 1 )
      {
         cout << "Enter final (out of 100): ";
         cin >> fTempValue;
         if( fTempValue >= 0 || fTempValue <= 10 )
         {
            studentInfo[ iCount ].dFinal = ( fTempValue / 100 )
            * FINAL_WEIGHT;
            break;
         }
      }
   }

   cout << "\n";
}

/**************************************************************************
   Purpose:
      Print Student information.
   Input:
      void
   Output:
      none
   Return:
      void
   Parameters:
      void ( structure array of type StudentInfo, int number of students ).
 *************************************************************************/

void printStudentData( const StudentInfo STUDENTINFO[], int iNumofStudents )
{
   for( int iCount = 0; iCount < iNumofStudents; iCount++ )
   {
      cout << "\n";
      // output the student number
      cout << "Student " << STUDENTINFO[ iCount ].iStudentNumber
           << " Summary\n";
      // output the students grade points
      cout << "Average: " << STUDENTINFO[ iCount ].dAverageTotal << "\n";
      // output the letter grade
      cout << "Grade: " << STUDENTINFO[ iCount ].cFinalGrade << "\n";
   }

   cout << "\n";
}

