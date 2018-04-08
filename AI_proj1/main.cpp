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
#include <queue>


typedef struct __stackElement {
    
    int row;
    int col;
    int dir;
    int limit;
    
}stackElement;

typedef struct __pqElement {
    
    int row;
    int col;
    int dir;
    int hu;
    bool operator<(const __pqElement & rhs) const
    {
        return hu < rhs.hu;
    }
    
}pqElement;

typedef struct __retVal {
    
    int finish_row;
    int finish_col;
    int size;
    int time;
    
}retVal;


using namespace std;
int ROW, COL;
int ** MATRIX;
int Go_Up(int &R, int &C);
int Go_Down(int &R, int &C);
int Go_Left(int &R, int &C);
int Go_Right(int &R, int &C);
int (*Go[4])(int&, int&)= { Go_Up, Go_Left, Go_Down, Go_Right};
void WHereIsStartPoint(int& R, int &C);
void WHereIsFinishPoint(vector<pair<int, int> > finishPoint);
pair<int, int> IDS (int &R, int &C);
pair<int, int> BFS (int &R, int &C);
int ** HU_MATRIX;
int ** visits;
pair<int, int> ** trace_MATRIX;

int ** A_MATRIX;


int score[5] = { 0, 1, 10, 0, 100 };

stack<pair<int, int> > trace;

int main(int argc, const char * argv[]) {
  
    int Start_R, Start_C;
    int Finish_R, Finish_C;
    int tmp_R, tmp_C;
    int tmptmp_R, tmptmp_C;
    int len = 0;
    pair<int, int> tempPair;
    vector<pair<int, int> > finishPoints;
    // 파일 입력
  //  ifstream in(argv[1]);
    ifstream in("input_ex3.txt");
    ofstream off("output_ex.txt");
    
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
    
        
        for (int i = 0; i < ROW; ++i) {
            for (int j = 0; j < COL; ++j) {
                cout << MATRIX[i][j]<<" ";
            }
            cout << endl;
        }
      
        HU_MATRIX = new int*[ROW];
        for (int i = 0; i < ROW; ++i)
            HU_MATRIX[i] = new int[COL];
        
        for(int i = 0 ; i < ROW; ++i)
            for (int j = 0; j < COL; ++j)
            {
                if (MATRIX[i][j] == 1)
                {
                    HU_MATRIX[i][j] = 0;
                }
                else if (MATRIX[i][j] == 2)
                {
                    HU_MATRIX[i][j] = 0;
                    for (int i2 = -3; i2 <= 3; ++i2)
                        for (int j2 = -3; j2 <= 3; ++j2)
                        {
                            if(i+i2 < 0 || i+i2 >= ROW || j+j2 <0 || j+j2 >=COL)
                                continue;
                            HU_MATRIX[i][j] += score[MATRIX[i + i2][j + j2]];
                        }
                }
                else if (MATRIX[i][j] == 3)
                {
                    HU_MATRIX[i][j] = 0;
                }
                else if (MATRIX[i][j] == 4)
                {
                    HU_MATRIX[i][j] = 10000;
                }
                
            }
        
        trace_MATRIX = new pair<int, int>*[ROW];
        for (int i = 0; i < ROW; ++i){
            trace_MATRIX[i] = new pair<int, int>[COL];
            for (int j = 0; j< COL; ++j) {
                trace_MATRIX[i][j] = make_pair(0, 0);
            }
        }
        
        visits = new int*[ROW];
        for(int i = 0; i < ROW; ++i){
            visits[i] = new int[COL];
            for (int j = 0; j< COL; ++j) {
                visits[i][j] = 0;
            }
        }
    
        A_MATRIX = new int*[ROW];
        for(int i = 0; i < ROW; ++i){
            A_MATRIX[i] = new int[COL];
            for (int j = 0; j< COL; ++j) {
                A_MATRIX[i][j] = 0;
            }
        }
    }
    else {
        cout << "파일을 찾을 수 없습니다!" << endl;
        return -1;
    }
    in.close();
    
    
    
   /*
    
    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COL; ++j) {
            cout << HU_MATRIX[i][j]<<" ";
        }
        cout << endl;
    }
    */
    
 
    
    //시작점 구하기
    WHereIsStartPoint(Start_R, Start_C);
    WHereIsFinishPoint(finishPoints);
    
  
    
    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COL; ++j) {
            int min = 100000;
            for(vector<pair<int, int> >::iterator iter=finishPoints.begin(); iter != finishPoints.end(); ++iter)
            {
                int tmpp1, tmpp2;
                tmpp1 = i - iter->first;
                tmpp2 = j - iter->second;
                if(min > tmpp1 * tmpp1 + tmpp2 * tmpp2){
                    min =tmpp1 * tmpp1 + tmpp2 * tmpp2;
                }
            }
            A_MATRIX[i][j] = min;
        }
       
    }
    
    Finish_R = Start_R;
    Finish_C = Start_C;
    
    //미로찾기
    tempPair = IDS(Finish_R, Finish_C);
  //  tempPair = BFS(Finish_R, Finish_C);
    
    /*
     // IDS 모드
    while(!trace.empty())
    {
        cout << "trace" << trace.top().first <<"," <<trace.top().second << endl;
        MATRIX[trace.top().first][trace.top().second] = 5;
        trace.pop();
    }
    */
    
    
    tmp_R = trace_MATRIX[Finish_R][Finish_C].first;
    tmp_C = trace_MATRIX[Finish_R][Finish_C].second;
    
    while(tmp_R != Start_R || tmp_C != Start_C)
    {
        MATRIX[tmp_R][tmp_C] = 5;
        len++;
        tmptmp_R =trace_MATRIX[tmp_R][tmp_C].first;
        tmptmp_C =trace_MATRIX[tmp_R][tmp_C].second;
        tmp_R = tmptmp_R;
        tmp_C = tmptmp_C;
        cout << tmp_R <<" " << tmp_C <<endl;
    }
    
    //output 출력
    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COL; ++j) {
             off <<MATRIX[i][j] <<" ";
        }
        off <<endl;
    }
    off << "---" << endl;
    off << "length : " << len <<endl;
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


void WHereIsFinishPoint(vector<pair<int, int> > finishPoint)
{
    pair<int, int> tmp_pair;
    for (int i = 0; i < ROW; ++i)
        for (int j = 0; j < COL; ++j)
            if(MATRIX[i][j] == 4)
            {
                tmp_pair.first = i;
                tmp_pair.second =j;
                finishPoint.push_back(tmp_pair);
            }
}

int Go_Up(int &R, int &C)
{
    if(R - 1 < 0)
        return 0;
    R--;
    if(visits[R][C])
        return 0;
    
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
    if(visits[R][C])
        return 0;
    
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
    
    if(visits[R][C])
        return 0;
    
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
    
    if(visits[R][C])
        return 0;
    
    if(MATRIX[R][C] != 2 && MATRIX[R][C] != 4)
        return 0;
    else
        return 1;
}

pair<int, int> IDS (int& R, int& C)
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
                 trace_MATRIX[tmp_R][tmp_C] = make_pair(R,C);
                
            }
        }

        while(!S.empty()){
         
            
            //pop 과정
            cur_R = S.top().row;
            cur_C = S.top().col;
            cur_dir = S.top().dir;
            cur_limit = S.top().limit;
    /*
            // 길이 막혀서 돌아오게 되었을 떄
            // (전단계의 limit값과 현재 limit값의 차이가 1이 아니라면)
            if(ex_limit - cur_limit != 1)
            {
                for(int i =0; i<= cur_limit - ex_limit ; i++){
                    cout << "pop" << trace.top().first <<"," <<trace.top().second << endl;
                    trace.pop();
                    
                }
            }
            ex_limit = cur_limit;*/
            S.pop();
            
            //도착확인
            if(MATRIX[cur_R][cur_C] == 4)
            {
                R =cur_R;
                C = cur_C;
                cout << "find !! " << cur_R << "," << cur_C <<endl;
                return make_pair(trace.size() , time);
            }
     /*
            // 자취 남기기
            trace.push(make_pair(cur_R, cur_C));
            cout << "push" << trace.top().first <<"," <<trace.top().second << endl;
       */
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
                        trace_MATRIX[tmp_R][tmp_C] = make_pair(cur_R,cur_C);
                        
                    }
                }
            }
                
            

        }
  /*
        while(!trace.empty()){
            cout << "pop" << trace.top().first <<"," <<trace.top().second << endl;
            trace.pop();
            
        }
    */
    }
    
}

pair<int, int> BFS (int &R, int &C)
{
    int cur_R, cur_C, cur_dir;
    int tmp_R, tmp_C;

    int time =0;
   
    priority_queue<pqElement> PQ;
    
    pqElement tmp_pqElement;

    
  for (int i = 0; i < 4 ; ++i) {
        tmp_R = R;
        tmp_C = C;
        if(Go[i](tmp_R,tmp_C)){

            tmp_pqElement = {tmp_R, tmp_C, i, HU_MATRIX[tmp_R][tmp_C]};
            PQ.push(tmp_pqElement);
            trace_MATRIX[tmp_R][tmp_C] = make_pair(R,C);
        }
    }
    
    while(!PQ.empty()){
        
        
        //pop 과정
        cur_R = PQ.top().row;
        cur_C = PQ.top().col;
        cur_dir = PQ.top().dir;
        visits[cur_R][cur_C] = 1;
  
        PQ.pop();
        cout << cur_R <<" "<< cur_C << endl;
        //도착확인
        if(MATRIX[cur_R][cur_C] == 4)
        {
            cout << "find !! " << cur_R << "," << cur_C <<endl;
            // 끝점 반환
            R = cur_R;
            C = cur_C;
            return make_pair(trace.size() , time);
        }
       /*
        // 자취 남기기
        trace.push(make_pair(cur_R, cur_C));
        cout << "push" << trace.top().first <<"," <<trace.top().second << endl;
        */
        //시도(time)증가
        time++;
        
        // 스텍에 가능한 이동 집어넣기
        for (int i = 0; i < 4 ; ++i) {
            if(cur_dir  == (i +2 )%4)
                continue;
            tmp_R = cur_R;
            tmp_C = cur_C;
            if(Go[i](tmp_R,tmp_C)){
                tmp_pqElement = {tmp_R, tmp_C, i, HU_MATRIX[tmp_R][tmp_C]};
                PQ.push(tmp_pqElement);
                trace_MATRIX[tmp_R][tmp_C] = make_pair(cur_R,cur_C);
            }
        }

    }
    return make_pair(0,0);
}

