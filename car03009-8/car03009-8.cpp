/***********************************************************************
* Program:
*    Homework 8, Working with Stings
*    Brother Cameron, CS 165
* Author:
*    Brother Michael Carey
* Summary:
*    This program demonstrates the use of strings using the string
*    type class.
***********************************************************************/

#include <iostream>
#include <fstream>
#include <cctype>
#include <string>

using namespace std;

const int LETTERS    = 26; // letters in alphabet
const int MAXWORDLEN = 16; // max word length

/*************************************************************************
*   class:
*     WordCount
*   Purpose:
*     To gather statistical data about a text file counting words and
*     letter frequencies.
*************************************************************************/
class WordCount
{
public:
   WordCount();
   void wordCounter( string strWord );
   void rptLetterFrequencies( void );
   void rptWordLenFrequencies( void );
private:
   int letterCounter( char cLetter );
   int iWords[ MAXWORDLEN ];
   int iLetters[ LETTERS ];
};

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
*      Program return value ( argument count pointer to a char array list ).
**************************************************************************/
int main( int argc, char *argv[] )
{
   WordCount wordCounter;
   string inString;
   ifstream ifile;

   // Check to see if we are going to need file read.
   switch( argc )
   {
   case 2:
      ifile.open( argv[ 1 ] );               // Open the file
      while( ifile.good() )                  // While not at EOF
      {
         // Get Lines from the file
         getline( ifile, inString );
         wordCounter.wordCounter( inString );// Do the counting
      }
      break;
   default:
      while( cin.good() )                    // While cin stream is good
      {
         // Get a line of text data
         getline( cin, inString );
         wordCounter.wordCounter( inString );// Do the counting
      }
      break;
   }

   // Report the letter findings
   wordCounter.rptLetterFrequencies( );   
   cout << endl;
   // Report the word findings
   wordCounter.rptWordLenFrequencies();

   return( 0 );
}

/*************************************************************************
*   Purpose:
*      Default Constructor to initialize the counting arrays
*   Input:
*      none
*   Output:
*      none
*   Return:
*      none
*   Parameters:
*      none ( none )
**************************************************************************/
WordCount::WordCount( )
{
   // Initialize the strings to zero
   for( int iCount = 0; iCount < LETTERS; iCount++ )
      iLetters[ iCount ] = 0;

   for( int iCount = 0; iCount < MAXWORDLEN; iCount++ )
      iWords[ iCount ] = 0;
}

/*************************************************************************
*   Purpose:
*      Count letters from the alphabet both lower and capitals are to be
*      Counted.
*   Input:
*      char
*   Output:
*      none
*   Return:
*      int
*   Parameters:
*      A value that is to be used for counting ( The letter to be counted )
**************************************************************************/
int WordCount::letterCounter( char cLetter )
{
   // This is the letter counter statement it also is set to
   // always return the value 1 for word counting purposes.
   // This will add a single count digit to the iLetters
   // array between 0 and 25.
   // note: 0x61 = 'a';
   return( ( ++iLetters[ ( tolower( cLetter ) - 0x61 ) ] ) || 0x61 );
}

/*************************************************************************
*   Purpose:
*      To do all of the word length and letter length statistical counting
*   Input:
*      string
*   Output:
*      none
*   Return:
*      void
*   Parameters:
*      void ( The string that is to be checked and counted )
**************************************************************************/
void WordCount::wordCounter( string strWord )
{
   int iWordLen = 0;
   char cLetter = 0;

   // This loop runs through a string for counting letters and words.
   for( unsigned int iCount = 0; iCount < strWord.length(); iCount++ )
   {
      // Find out if we are with in the alpha character range.
      if( isalpha( strWord[ iCount ] ) )
      {
         // Count the letters and add 1 to the word length
         iWordLen += letterCounter( strWord[ iCount ] );
      }
      else
      {
         // array bounds protection
         if( iWordLen > 0 && iWordLen <= MAXWORDLEN )
         {
            // set iWordLen = 0 by bit wise xor'ing the same value
            // after adding one to the word length.
            iWordLen = ( ( ++iWords[ iWordLen - 1 ] ) ^
                         (   iWords[ iWordLen - 1 ] ) );
         }
      }
   }

   // if the line does not end with an 'endl' capture anything
   // left from the string.
   if( iWordLen > 0 && iWordLen <= MAXWORDLEN )
      iWords[ iWordLen - 1 ]++;
}

/*************************************************************************
*   Purpose:
*      Formatting the text display output for the user for letter lengths
*   Input:
*      void
*   Output:
*      none
*   Return:
*      void
*   Parameters:
*      void ( void ).
**************************************************************************/
void WordCount::rptLetterFrequencies( void )
{
   // Set the starting letter value for display in the report.
   char cLetter = 'a';

   cout << "Letter Frequencies" << endl;
   cout << "=====================" << endl;

   for( int iCount = 0; iCount < 13; iCount++ )
   {
      // This is for the first row of items for display
      cout << ( char ) cLetter << " - ";
      if( iLetters[ iCount ] < 10 )
         cout << "  ";  // Text formatting to handle larger digits
      else if( iLetters[ iCount ] < 100 )
         cout << " ";   // Text formatting to handle larger digits

      cout << iLetters[ iCount ] << "\t      ";
      
      // This is for the second row of items for display
      cout << ( char ) ( cLetter + 13 ) << " - ";
      if( iLetters[ iCount + 13 ] < 10 )
         cout << "  ";  // Text formatting to handle larger digits
      else if( iLetters[ iCount + 13 ] < 100 )
         cout << " ";   // Text formatting to handle larger digits

      cout << iLetters[ iCount + 13 ] << endl;

      cLetter++;
   }
}

/*************************************************************************
*   Purpose:
*      Formatting the text display output for the user for word lengths
*   Input:
*      void
*   Output:
*      none
*   Return:
*      void
*   Parameters:
*      void ( void ).
**************************************************************************/
void WordCount::rptWordLenFrequencies( void )
{
   cout << "Word Length Frequencies" << endl;
   cout << "==================================================" << endl;

   for( int iCount = 0; iCount < 8; iCount++ )
   {
      // This is for the first row of items for display
      cout << ( iCount + 1 ) << " letter words - ";
      if( iWords[ iCount ] < 10 )
         cout << "  ";  // Text formatting to handle larger digits
      else if( iWords[ iCount ] < 100 )
         cout << " ";   // Text formatting to handle larger digits
      
      cout << iWords[ iCount ] << "\t     ";
      if( iCount + 9 < 10 )
         cout << " ";   // Text formatting to handle larger digits

      // This is for the second row of items for display
      cout << ( iCount + 9 ) << " letter words - ";
      if( iWords[ iCount + 8 ] < 10 )
         cout << "  ";  // Text formatting to handle larger digits
      else if( iWords[ iCount + 8 ] < 100 )
         cout << " ";   // Text formatting to handle larger digits

      cout << iWords[ iCount + 8 ] << endl;
   }
}
