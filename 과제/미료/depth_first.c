#include<stdio.h>
#include <stdbool.h>
#include "maze0.h"

#define MAX_SIZE 100

typedef struct {
	short int 	x;
	short int	y;
} offsets;
offsets move[8];

#define MAX_STACK_SIZE 100 // = m  p 
typedef struct {
	short int 	row;
	short int 	col;
	short int 	dir;
} element;
element stack[MAX_STACK_SIZE];

typedef struct _ArrayStack {
    int top; //스택 맨 위의 인덱스
    element xy[MAX_SIZE];
}ArrayStack;
 
typedef ArrayStack Stack;

int isFull(Stack* s) {  //스택이 꽉 찼나?
    return s->top == MAX_SIZE - 1;
}

void add(Stack* s, element item) { //스택의 맨 위에 데이터 삽입
    if (isFull(s)) printf("stack empty die");
    else {
        s->top++;
        s->xy[s->top] = item;
    }
}

element Peek(Stack* s) { //스택 최상단의 데이터 검색, 찾은 데이터 반환
    element d;
    if (isEmpty(s)) {
        printf("stack full dis");
        return;
    }
    else {
        d = s->xy[s->top];
        return d;
    }
}

element delete(Stack* s) { //스택 최상단의 데이터 삭제, 삭제되는 데이터 반환
    element t = Peek(s);
    s->top--;
    return t;
}

void path(void) 
{	// 미로를 통과하는 경로가 존재할 경우, 이를 출력
	int  i,  row,  col,  next_row,  next_col,  dir;
	int found = false;
   	element position;

	// 미로의 입구좌표와 E 방향으로 stack 초기화
   	mark[1][1] = 1;  
    int top = 0;
   	stack[0].row = 1;  
    stack[0].col = 1;  
    stack[0].dir = 0;
   	while ( top > -1  &&  !found )    { // stack이 empty가 아니고, 아직
					       // 경로를 발견 못할 때까지 실행
      	position = delete(&top);	 // top의 위치로 이동
      	row = position.row;
		col = position.col;
      	dir = position.dir;
     	while ( dir < 8  &&  !found )    { // 8방향을 차례대로 검사
         	next_row = row + move[dir].x;     // move in direction dir
         	next_col = col + move[dir].y;
         	if ( next_row  ==  EXIT_ROW  &&  next_col  ==  EXIT_COL )
         	   	found = true;	 // 출구 발견. 경로는 어디에?
         	else if ( !maze[next_row][next_col]  &&  
						!mark[next_row][next_col] )  	{ // 아직 안 가본 길
				position.row = row;  
				position.col = col; 
				position.dir = ++dir;  
            		add( &top,  position );  // 현재 좌표와 방향을 stack 저장
            		row = next_row;  // 안 가본 길로 전진. 방향은 북쪽
				col = next_col;  
		 		mark[next_row][next_col] = 1;
				dir = 0;
         	}
         	else  ++dir;
    }	
    if (found)    {	// stack에 저장된 경로 출력
      	printf( " The path is: \n " );
     	printf ( "row  col \n" );
      	for ( i=0;  i <= top;  i++ )
         		printf( " %2d %5d ",  stack[i].row, stack[i].col );
      	printf( " %2d %5d \n ", row, col );
      	printf( " %2d %5d \n ", EXIT_ROW, EXIT_COL );
   	}
   	else printf( " The maze does not have a path \n " );
}

int main(void){
    path();
    return 0;
}