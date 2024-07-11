#include "Soundex.h"
#include <cctype>
#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <vector>
 
std::string target;
std::string removeChars(std::string s, int pos, bool f( char c ) )
{
   if ( pos >= s.size() ) 
   {
       return s; 
   }
   std::string::iterator end = remove_if( s.begin() + pos, s.end(), f );  
   return s.substr( 0, end - s.begin() );                            
}
 
bool isIn( char c ) 
{ 
    return target.find( toupper( c ) ) != std::string::npos; 
}
 
bool notAlpha( char c ) 
{ 
    return !isalpha( c ); 
}
 
std::string generateSoundex(std::string name)
{
    if (name.empty()) 
    {
        return "";
    }
    
   std::map<char,char> cmap = 
   { 
        {'B','1'}, {'F','1'}, {'P','1'}, {'V','1'},
        
        {'C','2'}, {'G','2'}, {'J','2'}, {'K','2'}, {'Q','2'}, {'S','2'}, {'X','2'}, {'Z','2'},
        
        {'D','3'}, {'T','3'},
        
        {'L','4'},
        
        {'M','5'}, {'N','5'},
        
        {'R','6'},
    };
 
   std::string result = removeChars( name, 0, notAlpha );
   for ( char &c : result ) 
   {
        c = toupper( c ); 
   }
 
   char firstLetter = result[0];
   target = "HW";   
   result = removeChars( result, 1, isIn );
 
   for ( char &c : result ) 
   { 
       if ( cmap.count( c ) )
       {
           c = cmap[c]; 
       }
   }
 
   for ( int i = 1; i < result.size(); i++ ) 
   {
       if ( result[i] == result[i-1] )
       {
           result[i-1] = '*';
       }
   }
 
   target = "*"; 
   result = removeChars( result, 1, isIn );
   target = "AEIOUY";   
   result = removeChars( result, 1, isIn );
   result[0] = firstLetter;
   result += "000";
   return result.substr( 0, 4 );
}
