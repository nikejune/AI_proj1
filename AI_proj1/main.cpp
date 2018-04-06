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
pair<int, int> IDS (int R, int C);

stack<pair<int, int> > trace;

int main(int argc, const char * argv[]) {
  
    int Start_R;
    int STart_C;
    pair<int, int> tempPair;
    // 파일 입력
  //  ifstream in(argv[1]);
    ifstream in("input_ex1.txt");
    ofstream off("output_ex1.txt");
    
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
    in.close();
    
    //시작점 구하기
    WHereIsStartPoint(Start_R, STart_C);
    tempPair = IDS(Start_R, STart_C);
    
    while(!trace.empty())
    {
        cout << "trace" << trace.top().first <<"," <<trace.top().second << endl;
        MATRIX[trace.top().first][trace.top().second] = 5;
        trace.pop();
    }
    
    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COL; ++j) {
             off <<MATRIX[i][j] <<" ";
        }
        off <<endl;
    }
    off << "---" << endl;
    off << "length : " << tempPair.first <<endl;
     off << "time : " << tempPair.second <<endl;
    off.close();
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

pair<int, int> IDS (int R, int C)
{
    int cur_R, cur_C, cur_dir, cur_limit;
    int tmp_R, tmp_C;
    int limit = 0;
    int time =0;
    int ex_limit;
    
    stack<stackElement> S;
    stackElement tmpStackElement;

    
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
//        tmpStackElement ={cur_R, cur_C, 0, limit};
//      S.push(tmpStackElement);
        for (int i = 0; i < 4 ; ++i) {
            tmp_R = cur_R;
            tmp_C = cur_C;
            if(Go[i](tmp_R,tmp_C)){
                tmpStackElement = {tmp_R, tmp_C, i, cur_limit-1};
                S.push(tmpStackElement);
                
            }
        }

        while(!S.empty()){
         
            
            //pop 과정
            cur_R = S.top().row;
            cur_C = S.top().col;
            cur_dir = S.top().dir;
            cur_limit = S.top().limit;
            
            // 길이 막혀서 돌아오게 되었을 떄
            // (전단계의 limit값과 현재 limit값의 차이가 1이 아니라면)
            if(ex_limit - cur_limit != 1)
            {
                for(int i =0; i<= cur_limit - ex_limit ; i++){
                    cout << "pop" << trace.top().first <<"," <<trace.top().second << endl;
                    trace.pop();
                    
                }
            }
            ex_limit = cur_limit;
            S.pop();
            
            //도착확인
            if(MATRIX[cur_R][cur_C] == 4)
            {
                cout << "find !! " << cur_R << "," << cur_C <<endl;
                return make_pair(trace.size() , time);
            }
            
            // 자취 남기기
            trace.push(make_pair(cur_R, cur_C));
            cout << "push" << trace.top().first <<"," <<trace.top().second << endl;
            
            //시도(time)증가
            time++;
            
            // 스텍에 가능한 이동 집어넣기
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
                
            

        }
     
        while(!trace.empty()){
            cout << "pop" << trace.top().first <<"," <<trace.top().second << endl;
            trace.pop();
            
        }
        
    }
    
}

