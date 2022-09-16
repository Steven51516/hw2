#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
    rawWords=trim(rawWords);
    std::set<std::string> s_set;
    int p1 = 0;
    int p2 = 0;
    for(int i = 0; i<int(rawWords.size()); i++)
    {
        if(ispunct(rawWords[p2])||isspace(rawWords[p2]))
        {
            if(p2-p1>=2) s_set.insert(rawWords.substr(p1,p2-p1));
            p1=p2+1;
        }
        else if(i==int(rawWords.size())-1)
        {
            if(p2-p1+1>=2) s_set.insert(rawWords.substr(p1,p2-p1+1));
        }
        p2++;
    }
    return s_set;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
