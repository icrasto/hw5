#ifndef RECCHECK
// For debugging
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;

// OLD code:
// then add to current word
        // currentWord[pos] = in[pos];
        // bool decreasedCount = false;
        // int localYellowsLeft = yellowsLeft;
        // decrease occurrence from array of yellow letters **check if there is overlap??
        // if (yellowCounts[in[pos] - 'a'] > 0) {
        //     yellowCounts[in[pos]-'a'] = yellowCounts[in[pos]-'a'] - 1;
        //     localYellowsLeft--;
        //     decreasedCount = true;
        // }

        // check if this combination is possible with the såpots left
            // int spotsLeft = in.length() - (pos);
            // int yellowsLeft = 0;

            // std::map<char,int>::iterator it = yellowCounts.begin();
            // while (it != yellowCounts.end()) {
            //     yellowsLeft += it->second;
            //     it++;
            // }
        

        // go to the next position in recursion only if enough spots left for yellows
        // if (localYellowsLeft <= spotsLeft) {


        // }
        // if (decreasedCount == true) {
        //     yellowCounts[in[pos]-'a'] = yellowCounts[in[pos]-'a'] + 1;
        //     // yellowsLeft++;
        // }

        // int yellowsLeft = 0;
        // std::map<char,int>::iterator it = yellowCounts.begin();
        // while (it != yellowCounts.end()) {
        //     yellowsLeft += it->second;
        //     it++;
        // }

        // if (yellowsLeft > spotsLeft) {
            //     // not possible go to next letter
            //     if (decreasedCount == true) {
            //         yellowCounts[letter] = yellowCounts[letter] + 1;
            //         yellowsLeft++;
            //     }
            //     letter++;
            //     continue;
            // }


// Add prototypes of helper functions here
void helperFunc(size_t pos, string& currentWord, size_t yellowCounts[26], size_t yellowsLeft, const std::string& in, const std::set<std::string>& dict, std::set<std::string>& results);


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here

    std::set<std::string> results;
    // empty case
    if (in.length() == 0) {
        return results;
    }

    // using array to store counts of floating letters. 26 size for each letter
    // used map before but longer lookup
    size_t yellowCounts[26]={0};
    
    for (size_t i=0; i < floating.length(); i++) {
        char letter = floating[i];
        yellowCounts[letter - 'a']++;
    }

    

    // setting string of individual words created - set to length of in (final word length)
    std::string currentWord = in;
    int yellowsLeft = floating.length();
    helperFunc(0, currentWord, yellowCounts, yellowsLeft, in, dict, results);
    return results;

}

// Define any helper functions here
void helperFunc(size_t pos, string& currentWord, size_t yellowCounts[26], size_t yellowsLeft, const std::string& in, const std::set<std::string>& dict, std::set<std::string>& results) {
    
    if (pos == in.length()) {
        // make sure all yellow letters have been used & check if english word
        if (yellowsLeft == 0 && dict.find(currentWord) != dict.end()) {
            
          results.insert(currentWord);
        
        }
        return;
    }
    size_t spotsLeft = in.length() - (pos);
    if (yellowsLeft > spotsLeft) {
        return;
    }
    // then there is a letter (not a dash) position is predetermined
    if (in[pos] != '-'){
        
            helperFunc(pos+1, currentWord, yellowCounts, yellowsLeft, in, dict, results);
    } else {
        // is a dash

        // calculating spots left to compare inside while loop
        
    
        char letter = 'a';
        while (letter <= 'z') {
            
            currentWord[pos] = letter;
            // decrease yellow letters count if needed
            bool decreasedCount = false;
            size_t localYellowsLeft = yellowsLeft;
            if (yellowCounts[letter - 'a'] > 0) {
                yellowCounts[letter - 'a']--;
                localYellowsLeft--;
                decreasedCount = true;
            }
            // check if this combination is possible with the spots left
            
            

            // continue recursing through other letter combinations if spots left
            if (localYellowsLeft <= spotsLeft-1) {
                helperFunc(pos+1, currentWord, yellowCounts, localYellowsLeft, in, dict, results);
            }
            // backtracking
            currentWord[pos] = '-';
            if (decreasedCount == true) {
                yellowCounts[letter - 'a']++;
                // yellowsLeft++;
            }
            letter++;
        }
    }
    
}
