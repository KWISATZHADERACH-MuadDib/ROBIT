#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h> //SetConsoleTextAttribute, ReadConsoleInput 사용

#define WALL -1
#define EMPTY 0
#define START 1
#define MAX_HISTORY 1000   //이전 기록을 저장할 배열의 최대 크기

typedef struct _Point {
    int x;
    int y;
    int day;
} Point;

typedef struct _Node {
    Point data;
    struct _Node* next;
} Node;

typedef struct _Queue {             //C언어 6일차 과제 3번을 참고함
    Node* front;
    Node* rear;
    int size;
} Queue;

int map[25][25];        //j, i (x, y) : BFS가 진행되면서 날짜(day) 값으로 덮어씀
int snapshot[25][25];   //BFS 실행 전(초기) 맵 상태를 따로 저장해둠 (출력용)
int is_wall[25][25];    //원래 벽이었는지 기억
int is_start[25][25];   //출발점이었는지 기억
int is_exit[25][25];    //출구(구멍)였는지 기억
int on_path[25][25];    //최단 경로에 포함된 칸인지 기억
int distance_from_exit[25][25];  //출구를 기준으로 BFS한 거리 (여러 최단 경로 판별용)
int visited[25][25];    //플레이어가 실제로 밟고 지나간 칸인지 기억 (초록색으로 표시할 용도)

int start_x, start_y;   //출발점 좌표
int exit_x, exit_y;     //출구 좌표

int player_x, player_y; //플레이어(사용자) 현재 좌표

HANDLE hConsole;        //콘솔 출력 핸들 (글자 색상 변경용)
WORD default_attr;      //원래 콘솔 글자 색상 (색상 변경 후 복원용)

Queue queue;

void enqueue(Point data);
void dequeue();				//queue가 비어있으면 0반환, 아니면 dequeue하고 1반환
Point front();	            //front에 위치한 값 반환
int isEmpty();				//queue에 데이터 없으면 1, 있으면 0 반환
void generate_random_map(int* m, int* n);  //테두리는 벽, 구멍 1개, 출발점 1개로 맵 생성
void copy_map(int m, int n);               //map 배열을 snapshot 배열로 복사
void run_bfs(int m, int n);                //출발점에서 BFS로 날짜(거리) 전파
void run_bfs_from_exit(int m, int n);      //출구에서 BFS로 거리 전파 (여러 최단 경로 판별용)
void mark_shortest_paths(int m, int n);    //존재하는 모든 최단 경로 위의 칸을 on_path에 표시
void print_grid(int* x, int* y, int grid[25][25]);  //벽=■, 출발점=★, 출구=□ 
void print_result(void);                   //출구까지 걸린 날짜 출력

void print_grid_with_player(int m, int n); //플레이어 위치를 포함한 현재 맵 출력 (게임 플레이용)
int play_maze(int m, int n, double* played_time_seconds);  //방향키로 미로를 직접 탐험. 반환값: 이동한 걸음 수 (ESC 종료 시 -1). played_time_seconds에 걸린 시간(초)을 저장

void init_console_color(void);   //콘솔 핸들을 가져오고 원래 색상을 저장
void set_color(WORD color);      //글자 색상을 color로 변경
void reset_color(void);          //글자 색상을 원래(기본) 색상으로 복원

int read_key(void);   //ESC/방향키를 엔터 없이 즉시 입력받는다

void save_record_to_file(double history[], int count, double current, double best);  //이전 기록 전체(배열)와 현재/최고 기록을 파일에 저장
void print_record_from_file(void);                                    //저장된 기록 파일을 읽어서 터미널에 출력

Node* create_node(Point data);

int main()
{
    int m, n;
    double best_time = -1;   //최고 기록(초). -1이면 아직 기록 없음
    double history[MAX_HISTORY];   //지금까지 완료한 판들의 기록(초)을 순서대로 저장
    int history_count = 0;         //history에 저장된 기록 개수
    int quit = 0;

    srand((unsigned int)time(NULL));
    init_console_color();   //콘솔 색상 핸들 준비 (지나온 길을 초록색으로 표시하기 위함)

    while (!quit) {
        //탈출 가능한 미로가 나올 때까지, 그리고 최단 경로가(두변 중 큰 변의 길이보다) 짧지 않을 때까지 생성 + BFS를 반복
        do {
            generate_random_map(&m, &n);          //가로(m), 세로(n) 크기와 맵 내용을 랜덤 생성
            copy_map(m, n);                        //BFS로 덮어쓰이기 전 초기 상태 저장

            run_bfs(m, n);
        } while (map[exit_x][exit_y] == EMPTY || ((map[exit_x][exit_y] - 1) < (m > n ? m : n)));       //출구에 도달 못했거나 최단 경로가 긴 변보다 짧으면 다시 생성

        int shortest = map[exit_x][exit_y] - 1;  //출발점 -> 출구까지 최단 걸음 수

        run_bfs_from_exit(m, n);    //출구를 기준으로도 거리를 구해서
        mark_shortest_paths(m, n);  //존재하는 모든 최단 경로 칸에 표시\

        system("cls");
        printf("=== 미로 탈출 게임 ===\n");
        printf("방향키로 이동하세요. (ESC: 이번 판 포기)\n");
        if (best_time >= 0)
            printf("현재 최고 기록: %.1lf 초\n", best_time);
        printf("아무 키나 누르면 시작합니다...\n");
        read_key();

        double played_time = 0;
        int steps = play_maze(m, n, &played_time);   //실제 플레이. 반환값 = 사용자가 이동한 걸음 수

        system("cls");

        if (steps == -1) {
            printf("=====================================\n");
            printf("        이번 판을 포기했습니다.\n");
            printf("=====================================\n\n");
            print_grid(&m, &n, map);   //최단 경로 칸만 숫자로 표시됨 (on_path 기준)

            save_record_to_file(history, history_count, played_time, best_time);    //최단 경로 도달 실패 -> 지금까지의 모든 이전 기록 + 현재 + 최고 기록을 파일에 저장함.
            print_record_from_file();        //파일을 다시 읽어서 출력

            if (history_count < MAX_HISTORY) {
                history[history_count++] = played_time;   //이번 기록도 목록에 추가
            }

            quit = 1;   //탈출 실패 시 결과 출력 후 바로 프로그램 종료
        }
        else if (steps == shortest) {
            if (best_time < 0 || played_time < best_time) {
                best_time = played_time;   //신기록 갱신
            }

            printf("=====================================\n");
            printf("   *** 클리어! 최단 경로로 탈출 성공! ***\n");
            printf("=====================================\n\n");
            printf("이동 횟수: %d (최단 경로: %d)\n", steps, shortest);
            printf("클리어 시간: %.1lf 초\n", played_time);
            printf("최고 기록: %.1lf 초\n\n", best_time);
            print_grid(&m, &n, map);   //참고용으로 최단 경로도 함께 표시

            if (history_count < MAX_HISTORY) {
                history[history_count++] = played_time;   //이번 기록을 "이전 기록" 목록에 추가
            }
        }
        else {
            printf("=====================================\n");
            printf("실패! 최단 경로로 탈출하지 못했습니다.\n");
            printf("=====================================\n\n");
            printf("이동 횟수: %d (최단 경로: %d)\n", steps, shortest);
            printf("소요 시간: %.1lf 초\n\n", played_time);
            printf("최단 경로는 다음과 같습니다:\n\n");
            print_grid(&m, &n, map);   //최단 경로 칸만 숫자로 표시됨 (on_path 기준)

            save_record_to_file(history, history_count, played_time, best_time);    //최단 경로 도달 실패 -> 지금까지의 모든 이전 기록 + 현재 + 최고 기록을 파일에 저장함
            print_record_from_file();       //파일을 다시 읽어서 출력함

            if (history_count < MAX_HISTORY) {
                history[history_count++] = played_time;   //이번 기록도 목록에 추가
            }

            quit = 1;   //탈출 실패 시 결과 출력 후 바로 프로그램 종료
        }

        if (!quit) {        //탈출 성공시
            printf("\n다시 도전하려면 아무 키나, 완전히 종료하려면 ESC를 누르세요...\n");
            int key = read_key();
            if (key == 27) {
                quit = 1;
            }
        }
    }

    printf("\n게임을 종료합니다.\n");
    return 0;
}

//새로운 노드 생성 함수
Node* create_node(Point data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void enqueue(Point data) {

    Node* newNode = create_node(data);

    if (queue.rear == NULL) {	//queue가 비어있으면 front도 새노드로 추가
        queue.front = newNode;
        queue.rear = newNode;
    }
    else {
        queue.rear->next = newNode;	//아니면 기존 node에 추가
    }
    queue.rear = newNode;

    queue.size++;
    return;
}

void dequeue() {
    if (queue.front == NULL) {
        return;
    }
    else {
        Node* cur = queue.front;
        Node* nextNode = cur->next;					//rear을 이전 노드로 바꾸기 위해 next값을 미리 저장한다. free()하면 rear의 데이터가 없어지기 때문
        free(queue.front);
        queue.front = nextNode;						//rear이 기존 rear의 직전 node가 된다.	
        if (queue.front == NULL)
            queue.rear = NULL;
    }

    queue.size--;
    return;
}

Point front() {
    return queue.front->data;		//front 값 반환
}

//queue에 데이터가 없으면 1, 있으면 0 반환
int isEmpty() {
    if (queue.size != 0)
        return 0;
    else
        return 1;
}

//테두리는 전부 벽으로, 테두리 중 한 곳(모서리 제외)에 구멍을 뚫고, 내부에서 출발점을 정하고. 나머지 내부는 랜덤하게 벽을 배치하는 함수
void generate_random_map(int* x, int* y) {
    int m, n;
    int wall_percent = 20;   //내부 칸의 벽 생성 확률 (%)

    m = rand() % 6 + 10;   //가로 크기: 10 ~ 15
    n = rand() % 6 + 10;   //세로 크기: 10 ~ 15
    *x = m;
    *y = n;

    //모서리는 전부 벽, 내부는 랜덤하게 벽을 생성
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            is_wall[j][i] = 0;
            is_start[j][i] = 0;
            is_exit[j][i] = 0;
            on_path[j][i] = 0;
            visited[j][i] = 0;

            if (i == 0 || i == n - 1 || j == 0 || j == m - 1) {
                map[j][i] = WALL;
                is_wall[j][i] = 1;                                  //테두리를 벽으로 만듦
            }
            else if (rand() % 100 < wall_percent) {
                map[j][i] = WALL;
                is_wall[j][i] = 1;                                  //빈 공간을 랜덤하게 벽으로 만듦
            }
            else {
                map[j][i] = EMPTY;
            }
        }
    }

    //모서리 중 한 변을 골라, 꼭짓점를 제외한 위치에 구멍을 뚫는다 (꼭짓점을 뚫으면 미로 탈출이 불가능하기 때문)
    int side = rand() % 4;   //0:위, 1:아래, 2:왼쪽, 3:오른쪽
    int i, j;

    switch (side) {
    case 0:
        j = rand() % (m - 2) + 1;
        i = 0;
        break; //윗변
    case 1:
        j = rand() % (m - 2) + 1;
        i = n - 1;
        break; //아랫변
    case 2:
        i = rand() % (n - 2) + 1;
        j = 0;
        break; //왼쪽변
    default:
        i = rand() % (n - 2) + 1;
        j = m - 1;
        break; //오른쪽변
    }

    map[j][i] = EMPTY;
    is_wall[j][i] = 0;
    is_exit[j][i] = 1;
    exit_x = j;
    exit_y = i;

    //모서리가 아닌 내부 칸 중 벽이 아닌 곳을 골라 출발점으로 지정
    int placed = 0, attempts = 0;
    while (!placed && attempts < 2000) {
        int j = rand() % (m - 2) + 1;
        int i = rand() % (n - 2) + 1;
        attempts++;

        if (map[j][i] == EMPTY) {
            map[j][i] = START;
            is_start[j][i] = 1;
            start_x = j;
            start_y = i;
            enqueue((Point) { j, i, 1 });
            placed = 1;
        }
    }

    return;
}

//초기 맵을 저장하는 함수
void copy_map(int m, int n) {
    for (int i = 0; i < n; i++) {   //map 배열의 내용을 snapshot 배열로 복사
        for (int j = 0; j < m; j++) {
            snapshot[j][i] = map[j][i];
        }
    }
    return;
}

//출발점에서 시작해 BFS로 각 칸까지 걸린 거리를 map에 기록하는 함수
void run_bfs(int m, int n) {        //x, y
    int x, y, day;
    Point result;

    while (isEmpty() == 0) {
        result = front();
        x = result.x;
        y = result.y;
        day = result.day;

        dequeue();

        if (x + 1 != m && map[x + 1][y] == EMPTY)       //오른쪽이 비어있을 때
        {
            enqueue((Point) { x + 1, y, day + 1 });
            map[x + 1][y] = day + 1;
        }
        if (x - 1 != -1 && map[x - 1][y] == EMPTY)      //왼쪽이 비어있을 때
        {
            enqueue((Point) { x - 1, y, day + 1 });
            map[x - 1][y] = day + 1;
        }
        if (y + 1 != n && map[x][y + 1] == EMPTY)       //아래쪽이 비어있을 때
        {
            enqueue((Point) { x, y + 1, day + 1 });
            map[x][y + 1] = day + 1;
        }
        if (y - 1 != -1 && map[x][y - 1] == EMPTY)      //위쪽이 비어있을 때
        {
            enqueue((Point) { x, y - 1, day + 1 });
            map[x][y - 1] = day + 1;
        }
    }

    return;
}

//출구를 기준으로 BFS를 돌려서, 각 칸이 출구로부터 몇 걸음 떨어져 있는지 구한다
//(distance_from_exit는 map처럼 1부터 시작하는 걸음 수. 0이면 아직 미방문, -1이면 벽)
void run_bfs_from_exit(int m, int n) {      //x, y
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (is_wall[j][i]) {
                distance_from_exit[j][i] = -1;
            }
            else {
                distance_from_exit[j][i] = 0;
            }
        }
    }

    distance_from_exit[exit_x][exit_y] = 1;
    enqueue((Point) { exit_x, exit_y, 1 });

    while (isEmpty() == 0) {
        Point result = front();
        int x = result.x;
        int y = result.y;
        int day = result.day;
        dequeue();

        if (x + 1 != m && distance_from_exit[x + 1][y] == 0) {
            distance_from_exit[x + 1][y] = day + 1;
            enqueue((Point) { x + 1, y, day + 1 });
        }
        if (x - 1 != -1 && distance_from_exit[x - 1][y] == 0) {
            distance_from_exit[x - 1][y] = day + 1;
            enqueue((Point) { x - 1, y, day + 1 });
        }
        if (y + 1 != n && distance_from_exit[x][y + 1] == 0) {
            distance_from_exit[x][y + 1] = day + 1;
            enqueue((Point) { x, y + 1, day + 1 });
        }
        if (y - 1 != -1 && distance_from_exit[x][y - 1] == 0) {
            distance_from_exit[x][y - 1] = day + 1;
            enqueue((Point) { x, y - 1, day + 1 });
        }
    }

    return;
}

//출발점 기준 거리와 출구 기준 거리를 더했을 때 최단 거리와 같으면, 그 칸은 최단 경로에 포함되는 칸이다.
//최단 경로가 여러 개면 그 경로들이 전부 함께 표시한다. : 이를 위해 bfs_from_exit를 만듦
void mark_shortest_paths(int m, int n) {
    int shortest = map[exit_x][exit_y];   //출발점 기준으로 잰 출구까지의 걸음 수(1부터 세는 값)

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (is_wall[j][i] == 1)
                continue;
            if (map[j][i] == EMPTY || distance_from_exit[j][i] == 0)
                continue;  //둘 중 하나라도 도달 못했으면 제외

            if (map[j][i] + distance_from_exit[j][i] - 1 == shortest) {
                on_path[j][i] = 1;
            }
        }
    }

    return;
}

//벽=■, 출발점=★, 출구=□, 그 외는 grid 값(빈칸 또는 전파된 날짜)을 출력
//initial/final 두 상태를 모두 출력해야 해서 어떤 배열을 볼지 인자로 받는다
void print_grid(int* x, int* y, int grid[25][25]) {
    for (int i = 0; i < *y; i++) {
        for (int j = 0; j < *x; j++) {
            if (is_exit[j][i]) {
                printf("%-3s ", "□");
            }
            else if (is_wall[j][i]) {
                printf("%-3s ", "■");
            }
            else if (is_start[j][i]) {
                printf("%-3s ", "★");
            }
            else if (grid[j][i] == EMPTY || !on_path[j][i]) {    //최단 경로에 포함되지 않은 칸은 값이 있어도 그냥 빈칸으로 표시
                printf("%-3s", " ");
            }
            else {
                printf("%-2d ", grid[j][i]);
            }
        }
        printf("\n");
    }
}

//출구 칸에 적힌 날짜 값으로 최단 경로 길이를 계산해서 출력
void print_result(void) {
    printf("%d", map[exit_x][exit_y] - 1);
}

//콘솔 핸들을 가져오고, 나중에 복원할 수 있도록 원래 글자 색상을 저장해둠
void init_console_color(void) {
    CONSOLE_SCREEN_BUFFER_INFO info;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsole, &info);
    default_attr = info.wAttributes;
}

//글자 색상을 color로 변경
void set_color(WORD color) {
    SetConsoleTextAttribute(hConsole, color);
}

//글자 색상을 원래(기본) 색상으로 복원
void reset_color(void) {
    SetConsoleTextAttribute(hConsole, default_attr);
}

//72(위) / 80(아래) / 75(왼쪽) / 77(오른쪽)으로, ESC는 27로 반환한다.
int read_key(void) {
    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    INPUT_RECORD ir;
    DWORD readCount;

    while (1) {
        ReadConsoleInputW(hIn, &ir, 1, &readCount);

        if (ir.EventType != KEY_EVENT || !ir.Event.KeyEvent.bKeyDown)
            continue;   //키를 뗄 때(KeyUp)나 마우스/창크기 등 다른 이벤트는 무시

        switch (ir.Event.KeyEvent.wVirtualKeyCode) {
        case VK_UP:             //위쪽 방향키
            return 72;
        case VK_DOWN:           //아래쪽 방향키
            return 80;
        case VK_LEFT:           //왼쪽 방향키
            return 75;
        case VK_RIGHT:          //오른쪽 방향키
            return 77;
        case VK_ESCAPE:         //esc
            return 27;
        default:
            if (ir.Event.KeyEvent.uChar.UnicodeChar != 0)
                return ir.Event.KeyEvent.uChar.UnicodeChar;   //일반 문자 키
            break;   //Shift/Ctrl 단독 입력 등은 무시하고 다음 이벤트 대기
        }
    }
}

//현재 플레이어 위치를 포함해 미로 상태를 출력
//벽=■(흰색), 출발점=★, 출구=□, 플레이어=●, 지나온 자리=■(초록)
void print_grid_with_player(int m, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (j == player_x && i == player_y) {
                set_color(FOREGROUND_GREEN | FOREGROUND_INTENSITY);   //초록색 동그라미
                printf("%-3s ", "●");       //특수 도형이 2칸을 차지해왼쪽 정렬을 해주어야 재대로 출력된다.
                reset_color();
            }
            else if (is_exit[j][i]) {
                set_color(FOREGROUND_GREEN | FOREGROUND_INTENSITY);   //초록색 네모
                printf("%-3s ", "□");
                reset_color();
            }
            else if (is_wall[j][i]) {
                printf("%-3s ", "■");
            }
            else if (is_start[j][i]) {
                set_color(FOREGROUND_GREEN | FOREGROUND_INTENSITY);   //초록색 별
                printf("%-3s ", "★");
                reset_color();
            }
            else if (visited[j][i]) {
                set_color(FOREGROUND_GREEN | FOREGROUND_INTENSITY);   //초록색 네모(지나온 자리)
                printf("%-3s ", "■");
                reset_color();
            }
            else {
                printf("%-3s", " ");
            }
        }
        printf("\n");
    }
}

//게임 플레이 함수(방향키로 제어)
int play_maze(int m, int n, double* played_time_seconds) {
    player_x = start_x;
    player_y = start_y;
    visited[player_x][player_y] = 1;   //출발점도 지나온 자리로 표시
    int steps = 0;
    int key;

    clock_t start_tick = clock();   //플레이 시작 시각 기록
    *played_time_seconds = 0;

    while (1) {
        system("cls");              //전체 화면 지움
        printf("=== 미로 탈출 게임 (방향키 이동 / ESC 종료) ===\n\n");
        print_grid_with_player(m, n);
        printf("\n이동 횟수: %d\n", steps);

        key = read_key();   //방향키는 72/80/75/77, ESC는 27로 반환됨

        int nx = player_x;
        int ny = player_y;

        switch (key) {
        case 72:        //위쪽 화살표
            ny = player_y - 1;
            break;  
        case 80:        //아래쪽 화살표
            ny = player_y + 1;
            break;  
        case 75:        //왼쪽 화살표
            nx = player_x - 1;
            break;
        case 77:        //오른쪽 화살표
            nx = player_x + 1;
            break;  
        case 27: 
            return -1;                 //ESC
        default: 
            continue;                  //방향키/ESC가 아니면 무시하고 다시 입력받기
        }

        if (nx < 0 || nx >= m || ny < 0 || ny >= n)
            continue;          //맵 범위를 벗어나면 무시 (걸음수 증가 없음)
        if (is_wall[nx][ny])
            continue;          //벽이면 이동 불가 (걸음수 증가 없음)

        player_x = nx;
        player_y = ny;
        visited[player_x][player_y] = 1;   //방금 이동한 칸을 지나온 자리로 표시
        steps++;

        if (is_exit[player_x][player_y]) {
            clock_t end_tick = clock();
            *played_time_seconds = (double)(end_tick - start_tick) / CLOCKS_PER_SEC;   //걸린 시간(초) 계산
            return steps;    //출구에 도착하면 종료,출구에 도착할 때까지 이동한 걸음 수 반환
        }
    }
}

//지금까지의 모든 이전 기록(history 배열), 이번 판 기록(current), 최고 기록(best)을 텍스트 파일에 저장
//이전 기록이 하나도 없으면 "없음"으로 표시
void save_record_to_file(double history[], int count, double current, double best) {
    FILE* fp = fopen("maze_record.txt", "w");

    if (fp == NULL) {
        printf("기록 파일을 저장하는데 실패했습니다.\n");
        return;
    }

    fprintf(fp, "===== 미로 탈출 기록 =====\n");

    if (count == 0) {
        fprintf(fp, "이전 기록 : 없음\n");
    }
    else {
        fprintf(fp, "이전 기록 (%d판) :\n", count);
        for (int i = 0; i < count; i++) {
            fprintf(fp, "  %d판째 : %.1lf 초\n", i + 1, history[i]);
        }
    }

    fprintf(fp, "현재 기록 : %.1lf 초\n", current);

    if (best < 0)
        fprintf(fp, "최고 기록 : 없음\n");
    else
        fprintf(fp, "최고 기록 : %.1lf 초\n", best);

    fclose(fp);
    return;
}

//저장된 기록 파일(maze_record.txt)을 읽어서 한 줄씩 터미널에 그대로 출력
void print_record_from_file(void) {
    FILE* fp = fopen("maze_record.txt", "r");
    char line[100];

    if (fp == NULL) {
        printf("기록 파일을 읽을 수 없습니다.\n");
        return;
    }

    printf("[ 기록 파일(maze_record.txt) 내용 ]\n");
    while (fgets(line, sizeof(line), fp) != NULL) {
        printf("%s", line);
    }

    fclose(fp);
    return;
}