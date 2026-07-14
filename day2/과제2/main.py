import sys
import pygame

EMPTY, BLACK, WHITE = 0, 1, 2
DIRECTIONS = [(-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1), (1, 0), (1, 1)]
SIZE = 8


def new_board():
    board = [[EMPTY] * SIZE for _ in range(SIZE)]
    board[3][3] = WHITE
    board[3][4] = BLACK
    board[4][3] = BLACK
    board[4][4] = WHITE
    return board


def opponent(player):
    return WHITE if player == BLACK else BLACK


def in_bounds(r, c):
    return 0 <= r < SIZE and 0 <= c < SIZE


def flips_in_direction(board, player, r, c, dr, dc):
    """해당 방향으로 뒤집을 수 있는 상대 돌의 좌표 리스트를 반환한다."""
    opp = opponent(player)
    flips = []
    nr, nc = r + dr, c + dc
    while in_bounds(nr, nc) and board[nr][nc] == opp:
        flips.append((nr, nc))
        nr, nc = nr + dr, nc + dc
    if in_bounds(nr, nc) and board[nr][nc] == player and flips:
        return flips
    return []


def get_flips(board, player, r, c):
    if board[r][c] != EMPTY:
        return []
    all_flips = []
    for dr, dc in DIRECTIONS:
        all_flips.extend(flips_in_direction(board, player, r, c, dr, dc))
    return all_flips


def valid_moves(board, player):
    """{(row, col): [뒤집힐 좌표들]} 형태로 현재 둘 수 있는 모든 수를 반환한다."""
    moves = {}
    for r in range(SIZE):
        for c in range(SIZE):
            flips = get_flips(board, player, r, c)
            if flips:
                moves[(r, c)] = flips
    return moves


def apply_move(board, player, r, c):
    moves = valid_moves(board, player)
    if (r, c) not in moves:
        return False
    board[r][c] = player
    for fr, fc in moves[(r, c)]:
        board[fr][fc] = player
    return True


def count_stones(board):
    black = sum(row.count(BLACK) for row in board)
    white = sum(row.count(WHITE) for row in board)
    return black, white


# ---------------------------------------------------------
# pygame 화면 설정
# ---------------------------------------------------------

CELL_SIZE = 70
BOARD_PIXELS = CELL_SIZE * SIZE
TOP_BAR_HEIGHT = 60
WINDOW_WIDTH = BOARD_PIXELS
WINDOW_HEIGHT = BOARD_PIXELS + TOP_BAR_HEIGHT

COLOR_BOARD = (0, 128, 0)
COLOR_LINE = (0, 0, 0)
COLOR_BLACK = (20, 20, 20)
COLOR_WHITE = (245, 245, 245)
COLOR_TOP_BAR = (30, 30, 30)
COLOR_TEXT = (255, 255, 255)
COLOR_HINT = (0, 200, 0)


def draw_board(screen, board, player, moves, font, game_over, winner_text):
    # 상단 정보 바
    screen.fill(COLOR_TOP_BAR, (0, 0, WINDOW_WIDTH, TOP_BAR_HEIGHT))

    black_count, white_count = count_stones(board)

    if game_over:
        status = f"게임 종료! {winner_text}"
    else:
        turn_name = "흑(Black)" if player == BLACK else "백(White)"
        status = f"현재 차례: {turn_name}"

    status_surf = font.render(status, True, COLOR_TEXT)
    screen.blit(status_surf, (10, 15))

    score_text = f"흑 {black_count} : 백 {white_count}"
    score_surf = font.render(score_text, True, COLOR_TEXT)
    score_rect = score_surf.get_rect(right=WINDOW_WIDTH - 10, centery=TOP_BAR_HEIGHT // 2)
    screen.blit(score_surf, score_rect)

    # 보드 배경
    screen.fill(COLOR_BOARD, (0, TOP_BAR_HEIGHT, BOARD_PIXELS, BOARD_PIXELS))

    # 격자 선
    for i in range(SIZE + 1):
        y = TOP_BAR_HEIGHT + i * CELL_SIZE
        pygame.draw.line(screen, COLOR_LINE, (0, y), (BOARD_PIXELS, y), 2)
        x = i * CELL_SIZE
        pygame.draw.line(screen, COLOR_LINE, (x, TOP_BAR_HEIGHT), (x, TOP_BAR_HEIGHT + BOARD_PIXELS), 2)

    # 돌 그리기
    radius = CELL_SIZE // 2 - 6
    for r in range(SIZE):
        for c in range(SIZE):
            piece = board[r][c]
            cx = c * CELL_SIZE + CELL_SIZE // 2
            cy = TOP_BAR_HEIGHT + r * CELL_SIZE + CELL_SIZE // 2

            if piece == BLACK:
                pygame.draw.circle(screen, COLOR_BLACK, (cx, cy), radius)
            elif piece == WHITE:
                pygame.draw.circle(screen, COLOR_WHITE, (cx, cy), radius)
            elif (r, c) in moves and not game_over:
                # 둘 수 있는 칸은 작은 초록 점으로 힌트 표시
                pygame.draw.circle(screen, COLOR_HINT, (cx, cy), 6)


def pixel_to_cell(pos):
    x, y = pos
    y -= TOP_BAR_HEIGHT
    if y < 0:
        return None
    col = x // CELL_SIZE
    row = y // CELL_SIZE
    if 0 <= row < SIZE and 0 <= col < SIZE:
        return row, col
    return None


def main():
    print("=== pygame 버전:", pygame.version.ver, "===\n")

    pygame.init()
    screen = pygame.display.set_mode((WINDOW_WIDTH, WINDOW_HEIGHT))
    pygame.display.set_caption("오셀로 (Othello) - pygame")
    clock = pygame.time.Clock()
    pygame.font.init()
    # 한글이 깨지지 않도록 시스템에 설치된 한글 폰트를 후보 순서대로 시도한다
    # (Windows: 맑은 고딕 / Mac: Apple SD Gothic Neo / Linux: NanumGothic)
    korean_font_candidates = ["malgungothic", "applesdgothicneo", "nanumgothic", "notosanscjkkr"]
    available_fonts = pygame.font.get_fonts()
    chosen_font_name = next((name for name in korean_font_candidates if name in available_fonts), None)

    if chosen_font_name:
        font = pygame.font.SysFont(chosen_font_name, 22)
    else:
        # 한글 폰트를 찾지 못하면 기본 폰트로 대체한다 (이 경우 한글이 깨질 수 있음)
        font = pygame.font.SysFont(None, 24)
        print("경고: 한글 폰트를 찾지 못했습니다. 화면의 한글이 깨져 보일 수 있습니다.")

    board = new_board()
    player = BLACK
    game_over = False
    winner_text = ""

    moves = valid_moves(board, player)

    running = True
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

            elif event.type == pygame.MOUSEBUTTONDOWN and not game_over:
                cell = pixel_to_cell(event.pos)
                if cell is not None:
                    r, c = cell
                    if apply_move(board, player, r, c):
                        # 다음 차례로 전환, 상대가 둘 곳이 없으면 패스
                        next_player = opponent(player)
                        next_moves = valid_moves(board, next_player)

                        if next_moves:
                            player = next_player
                            moves = next_moves
                        else:
                            # 상대는 패스, 내가 계속 둘 수 있는지 확인
                            my_moves = valid_moves(board, player)
                            if my_moves:
                                moves = my_moves
                                print(f"{'백' if next_player == WHITE else '흑'} 차례는 둘 곳이 없어 패스합니다.")
                            else:
                                game_over = True

            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_r:
                    # R 키로 새 게임 시작
                    board = new_board()
                    player = BLACK
                    game_over = False
                    moves = valid_moves(board, player)

        if game_over and not winner_text:
            black_count, white_count = count_stones(board)
            if black_count > white_count:
                winner_text = f"흑 승리! ({black_count}:{white_count})  [R키: 다시하기]"
            elif white_count > black_count:
                winner_text = f"백 승리! ({black_count}:{white_count})  [R키: 다시하기]"
            else:
                winner_text = f"무승부! ({black_count}:{white_count})  [R키: 다시하기]"

        draw_board(screen, board, player, moves, font, game_over, winner_text)
        pygame.display.flip()
        clock.tick(30)

    pygame.quit()
    sys.exit()


if __name__ == "__main__":
    main()
