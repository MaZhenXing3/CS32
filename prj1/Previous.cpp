//
//  Previous.cpp
//  zion
//
//  Created by 李心怡 on 7/2/20.
//  Copyright © 2020 李心怡. All rights reserved.
//

#include <stdio.h>
#include <iostream>

#include "globals.h"
#include "Previous.h"
using namespace std;

Previous::Previous(int nRows, int nCols):m_nRows(nRows), m_nCols(nCols)
{
    if (nRows < 1 || nCols < 1 || nRows > MAXROWS || nCols > MAXCOLS){
        cout << "***** Previous is invalid with size of  ******" << nRows <<
        " rows and " << nCols << "cols !" << endl;
        exit(1);
    }
    for (int r = 0; r < m_nRows; r++){
        for (int c = 0; c < m_nCols; c++){
            m_grid[r][c] = 0;
        }
    }
}

void Previous::showPreviousMoves() const{
    clearScreen();
    for (int r = 0; r < m_nRows; r++){
        for (int c = 0; c < m_nCols; c++){
            char mark = '.';
            int stays = m_grid[r][c];
            if (stays >= 26){
                mark = 'Z';
            }
            else if (stays > 0){
                mark = 'A' + stays-1;
            }
            cout << mark;
        }
        cout << endl;
    }
    cout << endl;
}

bool Previous::dropACrumb(int r, int c){
    if (r < 1 || c < 1 || r > MAXROWS || c > MAXCOLS)
        return false;
    m_grid[r-1][c-1]++;
    return true;
    
}
