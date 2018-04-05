//
//  main.cpp
//  AI_proj1
//
//  Created by nikejune on 2018. 4. 5..
//  Copyright © 2018년 nikejune. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <utility>

typedef struct __stackElement {
    
    int row;
    int col;
    int dir;
    int limit;
    
}stackElement;

using namespace std;
int ROW, COL;
int ** MATRIX;
int Go_Up(int &R, int &C);
int Go_Down(int &R, int &C);
int Go_Left(int &R, int &C);
int Go_Right(int &R, int &C);
int (*Go[4])(int&, int&)= { Go_Up, Go_Left, Go_Down, Go_Right};
void WHereIsStartPoint(int& R, int &C);
void IDS (int R, int C);

stack<pair<int, int> > trace;

int main(int argc, const char * argv[]) {
  
    int Start_R;
    int STart_C;
    // 파일 입력
  //  ifstream in(argv[1]);
    ifstream in("input_ex1.txt");
    
    if (in.is_open()) {
        in >> ROW;
        in >> COL;
        MATRIX = new int*[ROW];
        for(int i = 0; i < ROW; ++i)
            MATRIX[i] = new int[COL];

        while (!in.eof()) {
            for (int i = 0; i < ROW; ++i) {
                for (int j = 0; j < COL; ++j) {
                    in >> MATRIX[i][j];
                }
            }
        }
        
    }
    else {
        cout << "파일을 찾을 수 없습니다!" << endl;
        return -1;
    }
    
    //시작점 구하기
    WHereIsStartPoint(Start_R, STart_C);
    IDS(Start_R, STart_C);
    
    while(!trace.empty())
    {
        cout << "trace" << trace.top().first <<"," <<trace.top().second << endl;
        MATRIX[trace.top().first][trace.top().second] = 5;
        trace.pop();
    }
    MATRIX[Start_R][STart_C] = 3;
    
    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COL; ++j) {
             cout <<MATRIX[i][j] <<" ";
        }
        cout <<endl;
    }
    return 0;
}

void WHereIsStartPoint(int& R, int &C)
{
    pair<int, int> ret;
    for (int i = 0; i < ROW; ++i)
        for (int j = 0; j < COL; ++j)
            if(MATRIX[i][j] == 3)
            {
                R = i;
                C = j;
                break;
            }
}
int Go_Up(int &R, int &C)
{
    if(R - 1 < 0)
        return 0;
    R--;
    
    if(MATRIX[R][C] != 2 && MATRIX[R][C] != 4)
        return 0;
    else
        return 1;
}
int Go_Down(int &R, int &C)
{
    if(R + 1 == ROW)
        return 0;
    R++;
    
    if(MATRIX[R][C] != 2 && MATRIX[R][C] != 4)
        return 0;
    else
        return 1;
}
int Go_Left(int &R, int &C)
{
    if(C - 1 < 0)
        return 0;
    C--;
    
    if(MATRIX[R][C] != 2 && MATRIX[R][C] != 4)
        return 0;
    else
        return 1;
}
int Go_Right(int &R, int &C)
{
    if(C + 1 == COL)
        return 0;
    C++;
    
    if(MATRIX[R][C] != 2 && MATRIX[R][C] != 4)
        return 0;
    else
        return 1;
}

void IDS (int R, int C)
{
    int cur_R, cur_C, cur_dir, cur_limit;
    int tmp_R, tmp_C;
    int limit = 0;
    
    int ex_limit;
    
    stack<stackElement> S;
    stackElement tmpStackElement;

    trace.push(make_pair(cur_R, cur_C));
    while(true)
    {
        limit++;
        cur_limit = limit;
        ex_limit = cur_limit;
        cout << limit << "'s trial"<< endl;
        cur_R = R;
        cur_C = C;
        cur_dir = -1;
        
        
        //시작점 집어넣기
        tmpStackElement ={cur_R, cur_C, 0, limit};
        S.push(tmpStackElement);
        
      
        do{
            if(cur_limit != 0){
                for (int i = 0; i < 4 ; ++i) {
                    if(cur_dir  == (i +2 )%4)
                        continue;
                    tmp_R = cur_R;
                    tmp_C = cur_C;
                    if(Go[i](tmp_R,tmp_C)){
                        tmpStackElement = {tmp_R, tmp_C, i, cur_limit-1};
                        S.push(tmpStackElement);
                        
                    }
                }
            }
                
        
            cur_R = S.top().row;
            cur_C = S.top().col;
            cur_dir = S.top().dir;
            cur_limit = S.top().limit;
            if(ex_limit - cur_limit != 1)
            {
                for(int i =0; i<= cur_limit - ex_limit ; i++){
                    cout << "pop" << trace.top().first <<"," <<trace.top().second << endl;
                    trace.pop();
                    
                }
            }
            ex_limit = cur_limit;
            
            trace.push(make_pair(cur_R, cur_C));
            cout << "push" << trace.top().first <<"," <<trace.top().second << endl;

            if(MATRIX[cur_R][cur_C] == 4)
            {
                cout << "find !! " << cur_R << "," << cur_C <<endl;
                return;
            }
            else if (MATRIX[cur_R][cur_C] == 2)
            {
                cout << cur_R << "," << cur_C <<endl;
                
            }

            

            S.pop();

        }while(!S.empty());
        
        
    }
    
}

