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

# 책 이름 -> 남은 수량 (등록 순서 유지)
books = {}

# 사용자 이름 -> 현재 대출 중인 책 이름 목록 (대출 순서 유지)
user_loans = {}


def is_valid_name(name):
    """이름에 공백이 없는지 확인"""
    return len(name) > 0 and not any(ch.isspace() for ch in name)


def is_valid_quantity(text):
    """0 이상의 정수인지 확인"""
    if not text.isdigit():
        return False
    return int(text) >= 0


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
        print("ERROR: 수량은 0 이상의 정수여야 합니다")
        return

    qty = int(qty_text)

    if name in books:
        books[name] += qty
    else:
        books[name] = qty

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
    """list"""
    if len(args) != 0:
        print("ERROR: list 명령어 형식이 올바르지 않습니다")
        return

    if not books:
        print("EMPTY")
        return

    for name in books:
        print(name)


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
