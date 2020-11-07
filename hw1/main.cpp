//
//  main.cpp
//  hw1
//
//  Created by 李心怡 on 7/8/20.
//  Copyright © 2020 李心怡. All rights reserved.
//

//#include <iostream>
//using namespace std;
//void mystery (int* ptr, int& a, int& b);
//int main ()
//{
//    const int size = 10;
//    int* arr[size];
//
//    cout << arr <<endl;
//    for (int k = 0; k < size ; k++){
//        arr[k] = new int;
//    }
//
//    for (int k = 0; k < size ; k++){
//        *arr[k] = k+1;
//    }
//
//    for (int i = 0; i < size ; i++){
//        cout << *arr[i] <<endl;
//    }
//
//    delete arr[1];
//    arr[1] = arr[size - 1];
//    for (int i = 0; i < size - 1 ; i++){
//        cout << *arr[i] <<endl;
//    }
    //cout << arr[1] << endl;
    //cout << arr[9] << endl;
    
    //cout << arr[0][0] << endl;

    //arr[0] = 1;
    
    
    //int* p = arr;
    //for (int i = 0; i < 10; i++){
    //    *p = i;
    //    p++;
    //}
    //for (int j = 0; j < 10; j++){
    //    cout << arr[j] << endl;
    //}
    //p = arr;
    //delete (p+2);
    //*(p+2) = arr[9];
    
    
    
    
    //int num1 = 0, num2 = 14, num3 = 17;
    //
    //int *p = &num1;
    //cout << "1 p is " << p << endl;
    //mystery(p, num2, num3);
    //cout << "2 p is " << p << endl;
    //cout << "num1: " << num1 << " num2: " << num2
    //    << " num3: " << num3 << endl;
    //if (p == &num1) cout << " num1";
    //else if (p == &num2) cout << " num2";
    //else if (p == &num3) cout << " num3";
    //cout << endl;
    //return 0;

//}
//void mystery (int* ptr, int& a, int& b) {
//    a++;
//    b--;
//    *ptr = 1000;
//    cout << "in func 1 p is " << ptr << endl;
//    if (a > b)
//        ptr = &a;
//    else
//        ptr = &b;
//    cout << "in func 2 p is " << ptr << endl;
//    *ptr += 10;
//    return;
//}


#include <iostream>
#include "LinkedList.h"
#include <cassert>
#include <stack>
#include <string>

using namespace std;

int main() {
    
    string a, b, c;
    a = "c";
    b = "a";
    c = "Zoo";
    
    cout << (a <= b) << endl;
    
    
    //const int size = 10;
    //int arr[size] = {1,2,3,4,4,2,10,2};
    //const int targ = 2;
    //for (int i = 0; i < 10 ; i++){
    //    cout << arr[i] << endl;
    //}
    //
    //
    //for (int e = 0; e < size; e++){
    //    // delete one element
    //    int mark = -1;
    //    for (int i = 0; i < size ; i++){
    //        if (arr[i] == targ){
    //            mark = 1;
    //        }
    //        if (mark >= 0 ){
    //            arr[i] = arr[i + 1];
    //        }
    //
    //        if (mark >= 0 && i == 9){
    //            arr[i] = 0;
    //        }
    //    }
    //}
    
    //cout << "---------" << endl;
    //for (int i = 0; i < 10 ; i++){
    //    cout << arr[i] << endl;
    //}
    
    
    //int n1 = 0;
    //int* p = &n1;
    //*p = 10;
    //cout << "p is " << *p << endl;
    //cout << "n1 is " << n1 << endl;
    
    
    //cout << "let's begin" << endl;
    //LinkedList e1;
    //LinkedList e2;
    //e2.insertToFront("X");
    //e2.insertToFront("Y");
    //e2.insertToFront("Z");
    //e1.append(e2);
    //stack<string> smoke;
    //
    //smoke.push("p");
    //smoke.push("n");
    //smoke.push("a");
    //smoke.push("d");
    //smoke.push("l");
    //
    //string temp;
    //temp = smoke.top();
    //cout << temp << endl;
    
    //e1.printList();
    //e2.printList();
    //e1.swap(e2); // exchange contents of e1 and e2
    //string s;
    //assert(e1.size() == 3 && e1.get(0, s) && s == "Z");
    //assert(e2.size() == 4 && e2.get(2, s) && s == "B");
    
    
    //LinkedList e1;
    //e1.insertToFront("Jim");
    //e1.insertToFront("Oz");
    //e1.insertToFront("Paul");
    //e1.insertToFront("Kevin");
    //e1.reverseList(); // reverses the contents of e1
    //string s;
    //assert(e1.size() == 4 && e1.get(0, s) && s == "Jim");

    //LinkedList e1;
    //e1.insertToFront("Athos");
    //e1.insertToFront("Porthos");
    //e1.insertToFront("Aramis");
    //LinkedList e2;
    //e2.insertToFront("Robin");
    //e2.insertToFront("Batman");
    //e1.append(e2); // adds contents of e2 to the end of e1
    //string s;
    //assert(e1.size() == 5 && e1.get(3, s) && s == "Batman");
    //assert(e2.size() == 2 && e2.get(1, s) && s == "Robin");
    
    //LinkedList ls;
    //ls.insertToFront("The Mandalorian");
    //ls.insertToFront("Baby Yoda");
    //ls.insertToFront("Cara Dune");
    //ls.insertToFront("Greef Karga");
    //ls.printList();
    //LinkedList ls1(ls);
    //ls.printReverse();
    //ls.reverseList();
    
    
    //LinkedList ls;
    //ls.insertToFront("Hawkeye");
    //ls.insertToFront("Thor");
    //ls.insertToFront("Hulk");
    //ls.insertToFront("Black Widow");
    //ls.insertToFront("Iron Man");
    //ls.insertToFront("Captain America");
    //for (int k = 0; k < ls.size(); k++)
    //{
    //    string x;
    //    ls.get(k, x);
    //    cout << x << endl;
    //}
    
    // insert code here...
    //std::cout << "Hello, World!\n";
    //ItemType a;
    //a = "mad";
    //cout << a << endl;
    //
    //LinkedList l1;
    //l1.insertToFront("1st");
    //l1.insertToFront("2nd");
    //l1.insertToFront("3rd");
    //l1.insertToFront("4th");
    //l1.printList();
    //
    //LinkedList l2(l1);
    //cout << "-------" << endl;
    //l2.printList();
    //l2.insertToFront("for l2 only");
    //
    //cout << "after inserting l2 "<< endl;
    //l1.printList();
    //cout << "-------" << endl;
    //l2.printList();
    //
    //LinkedList l3;
    //l3.insertToFront("this is l3");
    //cout << "-------" << endl;
    //l3.printList();
    //l3 = l2;
    //l3.printList();
    //l3 = l1;
    //l3.printList();
    //
    //cout << "-------" << endl;
    //
    //l3.get(1, a);
    //l3.printList();
    //
    //cout << "-------" << endl;
    //l3.reverseList();
    //l3.printList();
    //cout << "now print reversed" << endl;
    //l3.printReverse();
    //cout << "check on the list after print, now forward order------" << endl;
    //l3.printList();
    //
    //cout << "check what l2 is----- " << endl;
    //l2.printList();
    //cout << "the append l2 to l3 is -----------" << endl;
    //l3.append(l2);
    //l3.printList();
    //cout << "now end append l2 to l3 -----------" << endl;
    //
    //int siz;
    //siz = l3.size();
    //cout << "the size of appended l3 is " << siz << endl;
    //
    //l3.swap(l1);
    //cout << "----------" << endl;
    //l3.printList();
    //cout << "----------" << endl;
    //l1.printList();
    
    return 0;
}
