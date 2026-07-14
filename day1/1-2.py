
def add_log(robot_name, battery, logs=None):
    if logs is None:   #기본 매개변수로 mutable 자료형인 빈 리스트를 사용하면 이전 데이터가 누적되게 된다. 그래서 기본값을 None으로 지정하고, 함수 내부에서 새로 생성했다.(함정 이해, mutable 자료형 이해)

        logs = []
    battery = str(battery)    #battery 변수는 자료형이 int형이므로 문자열인 "battery"와 합쳐질 수 없어 battery 변수를 문자열 변수로 바꾸었다.(type error 수정, str() 사용)
    log = robot_name + " battery: " + battery
    logs.append(log)
    return logs

print(add_log("frontbot", 80))
print(add_log("rearbot", 50))
print(add_log("armbot", 20))