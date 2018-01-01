/***********************************************************************
* Program:
*    Homework 13, Linked lists
*    Brother Cameron, CS 165
* Author:
*    Brother Michael Carey
* Summary:
*    This program demonstrates the use of classes and pointers and
*    using them in a linked list.
***********************************************************************/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/*************************************************************************
*   Class:
*     Josephus
*   Purpose:
*     Class to hold a name as a node in a linked list
**************************************************************************/
class Josephus
{
public:
   Josephus();
   Josephus( Josephus &acObj );
   Josephus( Josephus *acObj );
   Josephus( string sName );
   Josephus( string sName, Josephus *prev );
   Josephus( string sName, Josephus *prev, Josephus *next );

   Josephus *moveNext( void );
   void setNext( Josephus *next );

   Josephus *removeNode( Josephus *prev );

   string getName( void );
   void setName( string sName );

      
protected:
private:
   Josephus *nxt;
   string name;
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
*      Program return value ( void ).
**************************************************************************/
int main( int argc, char *argv[] )
{

   Josephus *headNode;  // Head node
   Josephus *currNode;  // Current node
   Josephus *tempNode;  // Temp node
   string temp;

   ifstream readFile;

   headNode    = NULL;
   currNode    = NULL;
   tempNode    = NULL;

   // open a file
   readFile.open( "class.txt" );

   getline( readFile, temp );

   // init the first node if not empty
   if( temp.length() > 0 )
      headNode = new Josephus( temp );
   else
   {
      cout << "You have an empty head... must exit\n";
      exit( 1 );
   }

   if ( !headNode )
   {
      cerr << "Failed to allocate memory\n";
      exit( 1 );
   }

   headNode->setNext( headNode );
   currNode = headNode;

   // create the rest of the node list
   while ( !readFile.eof() )
   {
      getline( readFile, temp );

      if ( temp.length() > 1 )
      {
         tempNode = new Josephus( temp, currNode, headNode );

         if ( !tempNode )
         {
            cerr << "Failed to allocate memory\n";
            exit( 1 );
         }

         currNode = tempNode;
      }

      if ( readFile.eof() )
         break;
   }

   int death = 1;
   tempNode = currNode = headNode; // start at the beginning of the circle

   // go through the list until the next node points to it's parent node
   while ( currNode != currNode->moveNext() )
   {
      currNode = currNode->moveNext();
      death++;

      // remove every third node
      if ( death >= 3 )
      {
         cout << "Deleted...." << currNode->getName() << endl;

         currNode = currNode->removeNode( tempNode );

         if ( currNode )
            delete currNode;

         currNode = tempNode;
         death = 0;
      }
      else
      {
         tempNode = currNode;
      }
   }

   cout << "Survivor..." << currNode->getName() << endl;

   // a.out Rest Of The Story
   if ( argc > 1 )
   {
      cout << "\n\nHowever after surviving the mass deletion "
         << currNode->getName() << "\ncould never forget those students "
         << "who spent so many hours\nof hard work in class. "
         << "Long shall their sacrifices be\nremembered.\n";
   }

   // kill the last person standing
   if ( currNode )
      delete currNode;

   tempNode = currNode = headNode = NULL;

   readFile.close();

   return ( 0 );
}

/*************************************************************************
*   Purpose:
*      default constructor
**************************************************************************/
Josephus::Josephus()
{
   nxt = NULL;
   name = "";
}

/*************************************************************************
*   Purpose:
*      copy constructor
**************************************************************************/
Josephus::Josephus( Josephus &jsObj )
{
   if ( jsObj.nxt )
      this->nxt = jsObj.nxt;
   else
      nxt = NULL;

   name = jsObj.getName();
}

/*************************************************************************
*   Purpose:
*      copy constructor for pointers
**************************************************************************/
Josephus::Josephus( Josephus *jsObj )
{
   if ( jsObj->nxt )
      this->nxt = jsObj->nxt;
   else
      nxt = NULL;

   name = jsObj->getName();
}

/*************************************************************************
*   Purpose:
*      overloaded constructor
**************************************************************************/
Josephus::Josephus( string sName )
{
   name = sName;
   this->nxt = NULL;
}

/*************************************************************************
*   Purpose:
*      overloaded constructor
**************************************************************************/
Josephus::Josephus( string sName, Josephus *prev )
{
   name = sName;
   prev->setNext( this );
   this->nxt = NULL;
}

/*************************************************************************
*   Purpose:
*      overloaded constructor
**************************************************************************/
Josephus::Josephus( string sName, Josephus *prev, Josephus *next )
{
   name = sName;
   prev->setNext( this );
   this->nxt = next;
}

/*************************************************************************
*   Purpose:
*      get the name stored in the object
**************************************************************************/
string Josephus::getName( )
{
   return ( name );
}

/*************************************************************************
*   Purpose:
*      move to the next node element
**************************************************************************/
Josephus *Josephus::moveNext( )
{
   if ( this->nxt != NULL )
      return ( this->nxt );

   return ( NULL );
}

/*************************************************************************
*   Purpose:
*      set the next nodes element
**************************************************************************/
void Josephus::setNext( Josephus *next )
{
   this->nxt = next;
}

/*************************************************************************
*   Purpose:
*      set the name stored in the object to a new name
**************************************************************************/
void Josephus::setName( string sName )
{
   name = sName;
}

/*************************************************************************
*   Purpose:
*      remove the current node from the center of the list and return a
*      the pointer for it's self back.
**************************************************************************/
Josephus *Josephus::removeNode( Josephus *prev )
{
   prev->setNext( this->nxt );

   this->nxt = NULL;
   this->name = "";

   return ( this );
}
