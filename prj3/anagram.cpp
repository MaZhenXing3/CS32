//
//  main.cpp
//  anagrams
//
//  Created by 李心怡 on 7/24/20.
//  Copyright © 2020 李心怡. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <istream>
#include <cstring>
using namespace std;

const int MAXRESULTS   = 20;    // Max matches that can be found
const int MAXDICTWORDS = 30000; // Max words that can be read in


int createDict(istream &dictfile, string dict[])
{
    if (getline(dictfile, dict[0])){
        int count =createDict(dictfile, dict+1);
        return  count + 1;
    }
    else{
        return 0;
    }
}

//helper function for characterMixer
bool wordCompare(string word, string dictword, int size, int i)
{
    if (word.size() != dictword.size()) return false;
    if (word == dictword) return true;
    if (i == size) return false;  // may need change to size;
    if (word[0] == dictword[i])
    {
        return wordCompare(word.substr(1,size-1), dictword.substr(0,i) + dictword.substr(i+1, size -1), size - 1, 0);
    }
    else{
        return wordCompare(word, dictword, size, i+1);
    }
}

int characterMixer(string word, const string dict[], int size, string results[])
{
    if (size == 0) return 0;
    int sizein = int(word.size());
    if (wordCompare(word, dict[0], sizein, 0))
    {
        int count = 1 + characterMixer(word, dict+1, size - 1, results);
        results[count - 1] = dict[0];
        return count;
    }
    else{
        return characterMixer(word, dict+1, size - 1, results);
    }
}

void viewAnswers(const string results[], int size)
{
    if (size == 0) return;
    viewAnswers(results + 1, size - 1);
    cout << "Matching word " << results[0] << endl;
}
/*
int countLines(istream& inf) // inf is a name of our choosing
{
    int lineCount = 0;
    string line;
    while (getline(inf, line))
        lineCount++;
    return lineCount;
}
 */

int main()
{
    
    string results[MAXRESULTS];
    string dict[MAXDICTWORDS];
    ifstream dictfile;         // file containing the list of words
    int nwords;                // number of words read from dictionary
    string word;
    
    dictfile.open("words.txt");
    if (!dictfile) {
        cout << "File not found!" << endl;
        return (1);
    }
    
    nwords = createDict(dictfile, dict);
    cout << "count check " << nwords << endl;
    
    cout << dict[nwords-1] << endl;
    
    string str = "abcdefg";
    int i = 0;
    string sub = str.substr(0,i) + str.substr(i+1, str.size()-1);// get rid of a;
    cout << sub << endl;
    cout << i+1 << endl;
     
    //viewAnswers(dict, 8);
    
    cout << "Please enter a string for an anagram: ";
    cin >> word;

    int numMatches = characterMixer(word, dict, nwords, results);
    if (!numMatches)
        cout << "No matches found" << endl;
    else
        viewAnswers(results, numMatches);
     
    return 0;
}
