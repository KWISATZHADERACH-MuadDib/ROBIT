"""
도서 대출 관리 프로그램

명령어:
    add 책이름 수량      - 책 등록, 이미 있으면 수량 추가
    borrow 사용자 책이름  - 대출
    return 사용자 책이름  - 반납
    status 책이름        - 남은 수량 출력
    user 사용자          - 사용자의 대출 목록 출력
    list                - 전체 책 목록을 등록 순서대로 출력
    Exit                - 종료

조건:
    - 책과 사용자 이름에는 공백 없음
    - 수량은 0 이상의 정수
    - 잘못된 명령어 형식은 ERROR
    - eval() 사용 금지
    - 함수로 기능 분리
"""

# 책 이름 -> 남은(보관 중인) 수량 (등록 순서 유지)
books = {}

# 책 이름 -> 등록된 전체 수량 (대출 중인 수량 계산에 사용)
total_books = {}

# 사용자 이름 -> 현재 대출 중인 책 이름 목록 (대출 순서 유지)
user_loans = {}


def is_valid_name(name):
    """이름에 공백이 없는지 확인

    현재 process_command()가 line.split()으로 인자를 나누기 때문에,
    이 함수로 들어오는 name에는 사실 공백이 포함될 수 없다.
    (split()은 공백 자체를 구분자로 써서 토큰을 만들기 때문)

    다만 나중에 shlex.split() 등으로 파싱 방식이 바뀌어
    따옴표로 묶인 인자(예: "긴 이름")를 허용하게 되면
    공백 포함 이름이 실제로 들어올 수 있으므로,
    그런 변경에 대비해 검증 로직을 그대로 남겨둔다.
    """
    return len(name) > 0 and not any(ch.isspace() for ch in name)


def is_valid_quantity(text):
    """0 이상의 정수인지 확인"""
    if not text.isdigit():
        return False
    return int(text) >= 1


def add_book(args):
    """add 책이름 수량"""
    if len(args) != 2:
        print("ERROR: add 명령어 형식이 올바르지 않습니다")
        return

    name, qty_text = args

    if not is_valid_name(name):
        print("ERROR: 책 이름 형식이 올바르지 않습니다")
        return

    if not is_valid_quantity(qty_text):
        print("ERROR: 수량은 1 이상의 정수여야 합니다")
        return

    qty = int(qty_text)

    if name in books:
        books[name] += qty
        total_books[name] += qty
    else:
        books[name] = qty
        total_books[name] = qty

    print(f"{name} 등록 완료 (현재 수량: {books[name]})")


def borrow_book(args):
    """borrow 사용자 책이름"""
    if len(args) != 2:
        print("ERROR: borrow 명령어 형식이 올바르지 않습니다")
        return

    user, name = args

    if not is_valid_name(user) or not is_valid_name(name):
        print("ERROR: 이름 형식이 올바르지 않습니다")
        return

    if name not in books:
        print(f"ERROR: {name} 책이 존재하지 않습니다")
        return

    if books[name] <= 0:
        print(f"ERROR: {name} 책의 남은 수량이 없습니다")
        return

    if name in user_loans.get(user, []):
        print(f"ERROR: {user}님은 이미 {name} 책을 대출 중입니다")
        return

    books[name] -= 1
    user_loans.setdefault(user, []).append(name)
    print(f"{user}님이 {name} 책을 대출했습니다 (남은 수량: {books[name]})")


def return_book(args):
    """return 사용자 책이름"""
    if len(args) != 2:
        print("ERROR: return 명령어 형식이 올바르지 않습니다")
        return

    user, name = args

    if not is_valid_name(user) or not is_valid_name(name):
        print("ERROR: 이름 형식이 올바르지 않습니다")
        return

    if name not in user_loans.get(user, []):
        print(f"ERROR: {user}님은 {name} 책을 대출 중이지 않습니다")
        return

    user_loans[user].remove(name)
    books[name] += 1
    print(f"{user}님이 {name} 책을 반납했습니다 (남은 수량: {books[name]})")


def print_status(args):
    """status 책이름"""
    if len(args) != 1:
        print("ERROR: status 명령어 형식이 올바르지 않습니다")
        return

    name = args[0]

    if name not in books:
        print("ERROR")
        return

    print(books[name])


def print_user(args):
    """user 사용자"""
    if len(args) != 1:
        print("ERROR: user 명령어 형식이 올바르지 않습니다")
        return

    user = args[0]
    loans = user_loans.get(user, [])

    if not loans:
        print("EMPTY")
        return

    for book_name in loans:
        print(book_name)


def print_list(args):
    """list - 책이름, 대출중 수량, 보관중 수량을 함께 출력"""
    if len(args) != 0:
        print("ERROR: list 명령어 형식이 올바르지 않습니다")
        return

    if not books:
        print("EMPTY")
        return

    for name in books:
        stored = books[name]
        borrowed = total_books[name] - stored
        print(f"{name}, 대출중: {borrowed}권, 보관중: {stored}권")


def process_command(line):
    """입력 한 줄을 파싱하여 알맞은 함수 호출. 종료 명령이면 False 반환"""
    tokens = line.split()

    if not tokens:
        print("ERROR: 명령어가 비어 있습니다")
        return True

    command, args = tokens[0], tokens[1:]

    if command == "add":
        add_book(args)
    elif command == "borrow":
        borrow_book(args)
    elif command == "return":
        return_book(args)
    elif command == "status":
        print_status(args)
    elif command == "user":
        print_user(args)
    elif command == "list":
        print_list(args)
    elif command == "Exit":
        return False
    else:
        print("ERROR: 알 수 없는 명령어입니다")

    return True


def main():
    print("도서 대출 관리 프로그램을 시작합니다. (종료: Exit)")
    while True:
        try:
            line = input("> ")
        except EOFError:
            break

        if not process_command(line):
            print("프로그램을 종료합니다.")
            break


if __name__ == "__main__":
    main()
