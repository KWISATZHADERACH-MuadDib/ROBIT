my_list = []

while True:
    user_input = input().split()

    if not user_input:
        continue

    command = user_input[0]

    if command == "append":               #리스트의 매서드 구현
        my_list.append(user_input[1])     #리스트의 메서드 이해

    elif command == "insert":
        idx = int(user_input[1])
        value = user_input[2]
        
        if idx > len(my_list) or idx < 0:
            print("인덱스 범위를 벗어났습니다.") #예외 처리
            continue 
            
        my_list.insert(idx, value)

    elif command == "remove":
  
        if user_input[1] in my_list:
            my_list.remove(user_input[1])
        else:
            print("존재하지 않는 값입니다.")#예외 처리
    
    elif command == "pop":
        if len(my_list) == 0:
            print("리스트가 비어있습니다.")#예외 처리
            continue
        else:
            idx = int(user_input[1])
            

            if idx < 0 or idx >= len(my_list):
                print("인덱스 범위를 벗어났습니다.")
                continue
                
            my_list.pop(idx)

    elif command == "len":
        print(len(my_list))

    elif command == "print":
        print(my_list)
    
    elif command == "clear":
        my_list.clear()
