robot_status = [
    {"name":"mobilebot", "battery":82, "position":(1.2,0.5), "distance":0.8},
    {"name":"drone", "battery":18, "position":(0.3,1.5), "distance":0.4},
    {"name":"manipulator", "battery":45, "position":(2.0,1.0), "distance":1.2},
]

#함수를 이용하여 기능별로 나눔
def print_name(name):    #이름 출력하는 함수
    print(f"[{name}]")

def print_battery(battery_state):    #배터리 상태 출력하는 함수
    if(battery_state >= 60):    #조건문으로 상태 분류
        print("배터리 충분")
    elif(20 <= battery_state < 60):
        print("배터리 부족")
    else:
        print("충전 필요")

def print_position(x, y):    #위치 출력하는 함수
    print(f"위치: x={x}, y={y}")

def print_state(distance):    #상태 출력하는 함수
    if(distance < 0.5): 
        print("장애물 감지")
    elif(distance >= 0.5):
        print("전진 가능")

for i in range(3) :    #반복문으로 여러 데이터 처리
    name = robot_status[i]["name"]    #딕셔너리 사용
    battery_state = robot_status[i]["battery"]    
    pos_x = robot_status[i]["position"][0] #튜플 언패킹
    pos_y = robot_status[i]["position"][1]
    distance = robot_status[i]["distance"]

    print_name(name)
    print_battery(battery_state)
    print_position(pos_x, pos_y)
    print_state(distance)
    print("\n")
     
    