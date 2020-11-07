//
//  Previous.h
//  zion
//
//  Created by 李心怡 on 7/2/20.
//  Copyright © 2020 李心怡. All rights reserved.
//

#ifndef Previous_h
#define Previous_h

class Previous{
public:
    //constructor
    Previous(int nRows, int nCols);
    //mutators
    bool dropACrumb(int r, int c);
    //accessor
    void showPreviousMoves() const;
    
private:
    int m_nRows;
    int m_nCols;
    int m_grid[MAXROWS][MAXCOLS];
    
};


#endif /* Previous_h */
