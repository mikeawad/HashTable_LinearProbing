#include <cassert>
#include <iomanip>
#include <iostream>
using namespace std;

#include "hash_lp.h"

Table::Table( )
{
   used = 0;
   for ( int i = 0; i < CAPACITY; i++ )
      table[i].key = -1;
}

void Table::insert( const RecordType& entry, bool del = false )
{
   bool alreadyThere;
   int index;

   assert( entry.key >= 0 );

   findIndex( entry.key, alreadyThere, index );
    //cout << "alreadyThere = " << alreadyThere << endl;
   if (alreadyThere && del)                         // <--------------------- inserting some code to modify here
   {
        table[index].key = -2;
        table[index].data = 0;
        used--;
   }                                                // <--------------------- inserting some code to modify here
    
   else if( alreadyThere )
      table[index] = entry;
    
   else if (!del)
   {
      assert( size( ) < CAPACITY );
      index = hash( entry.key );
      //cout << endl << "<DEBUG>: above loop(2), i = " << index << ", table[i].key = " << table[index].key << endl << endl;
      while ( table[index].key != -1 )
      {
         //cout << endl << "<DEBUG>: Inside insert loop(2)" << endl;
         index = ( index + 1 ) % CAPACITY;
      }

      table[index] = entry;
      used++;
   }
}


int Table::hash( int key ) const
{
   return key % CAPACITY;
}

int Table::size( ) const
{
   return used;
}

// findIndex function
//     void findIndex( int key, bool& found, int &index ) const;
// Preconditions:  key >= 0.
// Postconditions: If a record with the indicated key is in the table,
//    then found is true and index is set to index of the found record.
//    Otherwise, found is false and index is garbage.

void Table::findIndex( int key, bool& found, int& i ) const
{
   int count = 0;

   assert( key >=0 );

   i = hash( key );
   //cout << endl << "<DEBUG>: above loop, i = " << i << ", table[i].key = " << table[i].key << endl << endl;
   while ( count < CAPACITY && table[i].key != -1 && table[i].key != key )
   {
      //cout << endl << "<DEBUG>: Inside findIndex loop" << endl;
      count++;
      i = (i + 1) % CAPACITY;
   }
   found = table[i].key == key;
}

void Table::find( int key, bool& found, RecordType& result ) const
{
   int index;

   assert( key >=0 );

   findIndex( key, found, index );
   if ( found )
      result = table[index];
}

/// print function: prints the hash table with only valid items. i.e anything without a key == -1, -2
void Table::print() const
{
	for (int i = 0; i < CAPACITY;i++)
	{
      if (table[i].key == -1 || table[i].key == -2) continue;
      else
      {
         cout << "table[" << i <<"].key = " << table[i].key << ", hash = " << hash(table[i].key) << endl;
         cout << "table[" << i <<"].data = " << table[i].data << endl << endl;
      }

	}
}

/// erase function to delete records from the table. This works by calling the insert function with the delete bool
/// set to true.
void Table::erase(int key, bool& found, RecordType& result)
{
    int index;
    result.key = key;
    //cout << "Debug: erase(): result.key = " << result.key << " found = " << found << endl;
    findIndex( key, found, index );
    insert( result , true);
    //cout << "Debug: after insert(): found = " << found << endl;
    found ? (cout << "Record deleted from table " << endl): (cout << "Record not found" << endl);
}
