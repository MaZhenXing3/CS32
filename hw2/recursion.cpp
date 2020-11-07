//
//  recursion.cpp
//  hw2P1
//
//  Created by 李心怡 on 7/23/20.
//  Copyright © 2020 李心怡. All rights reserved.
//

#include <iostream>
#include <string>
//#include <cstdlib>
using namespace std;

// Returns the product of two non-negative integers, m and n,
// using only repeated addition.
int product(unsigned int m, unsigned int n)
{
    // base case, if one of the number is 0, then the product is 0;
    if (m == 0 || n == 0) return 0;
    // adding one m to a smaller product;
    return m + product(m,n-1);
    
    //return -1;  // This is incorrect.
}
// Returns the number of occurrences of digit in the decimal
// representation of num. digit is an int between 0 and 9
// inclusive.
//
 // Pseudocode Example:
// digitCount(18838, 8) =>3
// digitCount(55555, 3) =>0
// digitCount(0, 0) =>0 or // 1 (either if fine)
int digitCount(int num, int digit) {
    
    //base case, if the last digit is num, return 1, else return 0;
    //if (num%10 == num){
    //    if (num == digit) return 1;
    //    else return 0;
    //}
    // base case, if input num is 0, return 0;
    if (num == 0) return 0;
    
    // use of itself;
    // if the last digit of num in this func is not equal, return
    // the self func that input num omit the last digit from previous func call;
    // else if equal, +1;
    if (abs(num%10) != digit) return digitCount(num/10, digit);
    
    else{
        return 1 + digitCount(num/10, digit);
    }
}
// Returns a string where the same characters next each other in
// string n are separated by "333"
//
// Pseudocode Example:
//    terribleTriplets("goodbye") => "go333odbye"
//    terribleTriplets ("yyuu")    => "y333yu333u"
//    terribleTriplets ("aaaa")    => "a333a333a333a"
//
string terribleTriplets(string n)
{
    // base case, if the length of string is 0 or 1, then nowhere to add "333";
    if (n.size() == 0 || n.size() == 1) return n;
    string insert = "333";
    
    //if the two chars at the beginning of the string are equal, insert "333" after the 1st char;
    if (n[0] == n[1]){
        return n[0] + insert + terribleTriplets(n.substr(1,-1)); // the
    }
    else{
        // no insertion, just input the rest to itself;
        return n[0] + terribleTriplets(n.substr(1,-1));
    }
    //return "";  // This is not always correct.
}

// str contains a single pair of square brackets, return a new
// string made of only the square brackets and whatever those
// square brackets contain
//
//  Pseudocode Example:
//     hipToBeSquare("abc[ghj]789") => "[ghj]"
//     hipToBeSquare("[x]7") => "[x]"
//     hipToBeSquare("4agh[y]")=> "[y]"
//     hipToBeSquare("4agh[]")=> "[]"
//
string hipToBeSquare(string str)
{
    // base case, if string size 0, return empty;
    // if the stirng start with "[" abd end with "]", return the str;
    if (str.size() == 0) return "";
    if (str[0] == '['  && str[str.size()-1] == ']') return str;
    
    // if the beginning of the string is not "[", then
    //      call itself with inputing the substring of the string that omit the first char;
    //      else call itself with inputing the substring of the string that omit the last char;
    if (str[0] != '['){
        return hipToBeSquare(str.substr(1,-1));
    }
    else {
        return hipToBeSquare(str.substr(0,str.size()-1));
    }
    //return "*";  // This is incorrect.
}
// Return true if the total of any combination of elements in
// the array a equals the value of the target.
//
//  Pseudocode Example:
//     summerSolstice([2, 4, 8], 3, 10) => true
//     summerSolstice([2, 4, 8], 3, 6) => true
//     summerSolstice([2, 4, 8], 3, 11) => false
//     summerSolstice([2, 4, 8], 3, 0)  => true
//     summerSolstice([], 0, 0)         => true
//

// helper function for summerrSolstice;
bool if_i_is_included(const int a[], int size, int target, int i, int sumsofar)
//return true if any element add up to target
{
    //base case, if sumsofar equal to target, then return true;
    // if index pass the last index of the array, then return false;
    if (sumsofar == target) return true;
    if (i == size) return false;
    
    // withnext is to a bool to check if index i is needed to sum to target. if need index i, then return true;
    // withoutnext is a bool to check if index i is not needed to sum to target. if doesn't need index i, then return true;
    bool withnext = if_i_is_included(a, size, target , i+1, sumsofar + a[i]);
    bool withoutnext = if_i_is_included(a, size, target , i+1, sumsofar);
    //return if one of the withnext or withoutnext is true, return true; because either way will sum some numbers to target. However, if both are false, that means no summation can reach target because this number at index i is can't be included or excluded which means it's impossible.
    return (withnext || withoutnext);
}

bool summerSolstice(const int a[], int size, int target)
{
    // recursively acll if_i_is_included;
    return if_i_is_included(a, size, target, 0, 0);
}

bool isThisTheEnd(string maze[], int nRows, int nCols,
                 int sr, int sc, int er, int ec)
{
    //base case, if start at end point, return true;
    if (sr == er && sc == ec) return true;
    // mark start point to be visited;
    maze[sr][sc] = '#';
    bool north = false;
    bool south = false;
    bool west = false;
    bool east = false;
    // check at each direction, if it's the end;
    if (sr >= 1 && sr <= nRows-2 && sc >= 1 && sc <= nCols-2){
        if (maze[sr-1][sc] == '.' ){
            north = isThisTheEnd(maze, nRows, nCols, sr-1, sc, er, ec);
        }
        if (maze[sr+1][sc] == '.' ){
            south = isThisTheEnd(maze, nRows, nCols, sr+1, sc, er, ec);
        }
        if (maze[sr][sc-1] == '.' ){
            west = isThisTheEnd(maze, nRows, nCols, sr, sc-1, er, ec);
        }
        if (maze[sr][sc+1] == '.' ){
            east = isThisTheEnd(maze, nRows, nCols, sr, sc+1, er, ec);
        }
    }
    // if one of the direction can reach end point, this will return true, else if non of them can reach end point, it will return false;
    return (north || south || west || east);
}
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise

//main code to validate the functions;

int generateRandNum(){
    srand(time(0));
    return rand()%5;
}
int main() {
    // insert code here...
    std::cout << "Hello, World!\n";
    cout << generateRandNum() << endl;
    
    /*
    int prod = product(91, 100);
    cout << prod << endl;
    int count = digitCount(1,1);
    cout << "digit count "<< count << endl;
    int check = -19/10;
    int rest = -19%10;
    cout << check << ", " << rest << endl;
    
    string a = "yyuu";
    cout << "check triplets " <<terribleTriplets(a) << endl;
    
    cout << a.substr(0,a.size()-1) << endl;
    
    string hip = "here ]mad pro[";
    string result = hipToBeSquare(hip);
    cout << result << endl;
    
    int arr[5] = {1,3,5,8,-5};
    cout << "summer check " << summerSolstice(arr, 5, -6) << endl;
    
    
    string maze[10] = {
          "XXXXXXXXXX",
          "X.......@X",
          "XX@X@@X.XX",
          "X..X.X...X",
          "X..X...@.X",
          "X....XXX.X",
          "X@X....XXX",
          "XXXXXXXXXX",
          "X...X....X",
          "XXXXXXXXXX"
    };
    if (isThisTheEnd(maze, 10, 10, 8, 1, 8, 8))
       cout << "Solvable!" << endl;
    else
       cout << "Out of luck!" << endl;
     */
    return 0;
}

