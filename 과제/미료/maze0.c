#include <stdio.h>
#include <stdbool.h>
#include "maze0.h"

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

void add(int* top, element pos) {
    //printf("add!");
    stack[*top] = pos;
    printf("%d, %d, %d, %d\n", *top, stack[*top].col, stack[*top].row, stack[*top].dir);
    *top = *top + 1;
}

element delete(int* top) {
    if (*top > 0) {
        *top = *top - 1;
    }
    element d = stack[*top];
    //printf("delete!");
    //printf("%d, %d, %d, %d", *top, d.col, d.row, d.dir);
    return d;
}

void path(void)
{	// 미로를 통과하는 경로가 존재할 경우, 이를 출력
    int  i, row, col, next_row, next_col, dir;
    int  found = false;
    element  position;

    // 미로의 입구좌표와 E 방향으로 stack 초기화
    mark[1][1] = 1;
    int top = 0;
    stack[0].row = 1;  stack[0].col = 1;  stack[0].dir = 0;
    while (top > -1 && !found) { // stack이 empty가 아니고, 아직
                           // 경로를 발견 못할 때까지 실행
        position = delete(&top);	 // top의 위치로 이동
        row = position.row;
        col = position.col;
        dir = position.dir;
        while (dir < 8 && !found) { // 8방향을 차례대로 검사
            next_row = row + move[dir].x;     // move in direction dir
            next_col = col + move[dir].y;
            if (next_row == EXIT_ROW && next_col == EXIT_COL) {
                position.row = row;
                position.col = col;
                position.dir = ++dir;
                add(&top, position);
                position.row = EXIT_ROW;
                position.col = EXIT_COL;
                position.dir = 9;
                add(&top, position);
                top--;
                found = true;	 // 출구 발견. 경로는 어디에?
            }
            else if (!maze[next_row][next_col] && !mark[next_row][next_col]) { // 아직 안 가본 길
                position.row = row;
                position.col = col;
                position.dir = ++dir;
                add(&top, position);  // 현재 좌표와 방향을 stack 저장
                row = next_row;  // 안 가본 길로 전진. 방향은 북쪽
                col = next_col;
                mark[next_row][next_col] = 1;
                dir = 0;
            }
            else  ++dir;
        }
    }
    if (found) {	// stack에 저장된 경로 출력
        printf(" The path is: \n ");
        printf("row  col \n");
        for (i = 0; i <= top; i++)
            printf(" %2d %5d \n ", stack[i].row, stack[i].col);
        //printf(" %2d %5d \n ", row, col);
        printf(" %2d %5d \n ", EXIT_ROW, EXIT_COL);
    }
    else printf(" The maze does not have a path \n ");
}

int main(void) {
    move[0].x = -1;
    move[1].x = -1;
    move[2].x = 0;
    move[3].x = 1;
    move[4].x = 1;
    move[5].x = 1;
    move[6].x = 0;
    move[7].x = -1;
    move[0].y = 0;
    move[1].y = 1;
    move[2].y = 1;
    move[3].y = 1;
    move[4].y = 0;
    move[5].y = -1;
    move[6].y = -1;
    move[7].y = -1;
    path();


    for (int i = 0; i < MAX_STACK_SIZE; i++) {
        if (stack[i].row == 0 && stack[i].col == 0)
            break;
        mark[stack[i].row][stack[i].col] = 2;
        
    }


    int path_count = 0;
    int mark_count = 0;
    printf("\n");
    for (int j = 0; j < ROWS; j++) {
        for (int k = 0; k < COLS; k++) {
            //if (j == EXIT_ROW && k == EXIT_COL)
            //    printf(" *");
            if (mark[j][k] == 1) {
                mark_count++;
                printf("^");
            }
            else if (mark[j][k] == 2) {
                path_count++;
                printf("@");
            }
            else if (maze[j][k] == 1)
                printf("|");
            else
                printf(" ");
        }
        printf("\n");
    }
    printf("방문한 노드 수 : %d\n", mark_count + path_count);
    printf("해답경로 길이 : %d\n", path_count - 1);
    return 0;
}