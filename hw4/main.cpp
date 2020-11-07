//
//  main.cpp
//  hw4
//
//  Created by 李心怡 on 8/8/20.
//  Copyright © 2020 李心怡. All rights reserved.
//

#include <fstream>
#include <iostream>
#include <cctype>
#include <string>
#include "WordTree.h"
using namespace std;

int main() {
    int f[10][10];
    for (int i = 0; i <= 10; i++){
        for (int j = 0; j <= 10; j++){
            cout << f[i][i] << ", ";
        }
        cout << endl;
    }
    return 0;
}

