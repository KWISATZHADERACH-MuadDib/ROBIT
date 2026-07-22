#*******입력 예시가 print(compress("aaadddvv")) 형식이어서 print(compress("문자열"))을 입력해야하도록 했습니다***********

def compress(text):
    if not text:
        return ""
    compressed = ""
    current_char = text[0]    
    count = 1
    for i in range(1, len(text)):
        if text[i] == current_char:    #연속된 문자의 개수를 count에 저장
            count += 1
        else:
            compressed += current_char + str(count)
            current_char = text[i]
            count = 1
    compressed += current_char + str(count)
    if len(compressed) >= len(text):    #압축한 문자열이 기존 문자열보다 크거나 같나면 기존 문자열 반환
        return text
    return compressed                   #아니면 압축한 문자열 반환


def is_valid_code(code):
    if not code or not code[0].isalpha():           #처음이 알파벳이 아닌 경우
        return False
    i = 0
    length = len(code)
    while i < length:
        if not code[i].isalpha():
            return False
        i += 1 
        if i >= length or not code[i].isdigit():
            return False
        while i < length and code[i].isdigit():
            i += 1
    return True


def decompress(code):
    if not is_valid_code(code):
        return "ERROR"
    result = ""
    i = 0
    length = len(code)
    while i < length:
        char = code[i]
        i += 1
        num_str = ""
        while i < length and code[i].isdigit():
            num_str += code[i]
            i += 1
        count = int(num_str)
        if count < 1:                  #a0 예외처리
            return "ERROR"
        result += char * count
    return result

if __name__ == "__main__":
    while True:
        user_input = input().strip()
        
        # 아무것도 입력하지 않으면 무시
        if not user_input:
            continue
            
        try:
            # 1. 입력받은 문자열이 'print('로 시작하고 ')'로 끝나는지 확인 및 내부 알맹이 추출
            if user_input.startswith("print(") and user_input.endswith(")"):
                # "print(compress('abc'))" -> "compress('abc')"
                inner_expr = user_input[6:-1].strip()
                
                # 2. 내부 식의 마지막 괄호 ')' 위치를 기준으로 함수와 인자 분리
                if inner_expr.endswith(")"):
                    # 괄호 시작 지점 찾기
                    open_paren = inner_expr.find("(")
                    if open_paren != -1:
                        func_name = inner_expr[:open_paren].strip() # 함수 이름 ("compress" 또는 "decompress")
                        
                        # 괄호 안의 문자열 추출 후 따옴표 제거
                        # "compress('abc')" -> "'abc'" -> "abc"
                        arg_value = inner_expr[open_paren+1:-1].strip().strip("'\"")
                        
                        # 3. 함수 이름에 따라 실제 기능 연결 후 출력
                        if func_name == "compress":
                            print(compress(arg_value))
                        elif func_name == "decompress":
                            print(decompress(arg_value))
                        else:
                            print("ERROR: 알 수 없는 함수입니다.")
                    else:
                        print("ERROR: 올바른 형식이 아닙니다.")
                else:
                    print("ERROR: 올바른 형식이 아닙니다.")
            else:
                print("ERROR: print(...) 형식으로 입력해주세요.")
                
        except Exception:
            print("ERROR")
