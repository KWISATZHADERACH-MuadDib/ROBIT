user_map = []
for _ in range(10):
    row = list(map(int, input().split()))
    user_map.append(row)


x, y = 1, 1

while True:
    user_map[y][x] = 9
    
    if user_map[y][x + 1] != 1:
        x += 1
        
    elif user_map[y + 1][x] != 1:
        y += 1
    
    else:
        break
        
    if user_map[y][x] == 2:
        user_map[y][x] = 9
        break

print()

for i in range(10):
    for j in range(10):
        print(user_map[i][j], end=" ")
    print()