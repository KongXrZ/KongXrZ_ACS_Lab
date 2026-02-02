Table = ["0","1","2","3","4","5","6","7","8"] #กำหนดตาราง

#กำหนดตาราง
def displaytable(): 
    print(f"{Table[0]} | {Table[1]} | {Table[2]}")
    print("--+---+--")
    print(f"{Table[3]} | {Table[4]} | {Table[5]}")
    print("--+---+--")
    print(f"{Table[6]} | {Table[7]} | {Table[8]}")
    print("\n")

#ตรวจรูปแบบการชนะ
def check_win(board, player):
    win_conf = [(0,1,2),(3,4,5),(6,7,8),(0,3,6),(1,4,7),(2,5,8),(0,4,8),(2,4,6)]#ตารางแสดงรูปแบบการชนะ
    for a,b,c in win_conf:#เช็คค่าในตำแหน่งของ a b c
        if board[a] == board[b] == board[c] == player: #มีค่าเท่ากันตามรูปแบบซึ่งเป็นผู้เล่น
            return True #รีเทิร์นฟังก์ชั่นเป็นค่าความจริง"จริง"
    return False #รีเทิร์นฟังก์ชั่นเป็นค่าความจริง"เท็จ"

#ระบบเดินเกม(วางตำแหน่งAI)
def find_winning_move(board, player):
    for i in range(9): #ตรวจสอบทีละตำแหน่ง n-1
        if board[i] == str(i): #เช็คตำแหน่งบนกระดานกับ i
            board[i] = player #ถ้าใช่ให้แสดงตำแหน่งผู้เล่น player = "x"
            if check_win(board, player): #ตรวจสอบรูปแบบการชนะ
                board[i] = str(i) #ถ้าตำแหน่งยังไม่ถูกเปลี่ยน
                return i #แสดงค่าตำแหน่งเดิม
            board[i] = str(i) #แสดงค่าตำแหน่งเดิม
    return None #ถ้าเช็คครบทุกช่องแล้วไม่มีช่องไหนที่วางแล้วชนะเลย ให้คืนค่า None

#ระบบเดินหมากของAI
def ai_best_move(board, ai, human): 
    win_move = find_winning_move(board, ai) #เรียกใช้ระบบเดินเกม (เปลี่ยนจากplayerเป็นai)
    if win_move is not None: #เช็คว่าวางช่องนี้แล้วชนะมั้ย
        return win_move #วางเลย
    
    block_move = find_winning_move(board, human)#เรียกใช้ระบบเดินเกม ตรวจตำแหน่งผู้เล่น
    if block_move is not None:#เช็คว่าวางช่องนี้แล้วชนะมั้ย
        return block_move#วางเลย เพื่อตัดทางผู้เล่น
    if board[4] == "4": #เช็คจุทยุทธศาสตร์ ตรงกลาง ว่างมั้ย
        return 4 #ถ้าใช่ วางโลดด
    for i in [0,2,6,8]: #เช็คมุม
        if board[i] == str(i): #มุมว่างมั้ย 
            return i #ว่างก็วางโลด
    for i in range(9): #หมุดมุข เช็คช่องที่เหลือ
        if board[i] == str(i): #ว่างมั้ย
            return i #ว่างก็วาง
    return None #คืนค่านอน เบิ่ดคำสิเว่า

#ระบบเกม
def play_game():
    human = "x"
    ai = "o"
    turn_count = 0 
    current_player = human #ให้ผู้เล่นเริ่มก่อน
    
    print("Welcome to Tic-Tac-Toe Game!")
    displaytable() #เรียกใช้ตาราง

    while turn_count < 9: #เล่นได้ถ้ามีการวางไม่เกิน9ครั้ง
        if current_player == human: #ตรวจสอบผู้ที่เล่นอยู่
            pos = int(input(f"Your turn ({human}): ")) #รับค่าจากplayer
            
            if pos in range(9) and Table[pos] == str(pos):#ตรวจว่าค่าที่ใส่อยู่ในขอบเขต และ ตารางว่างมั้ย
                Table[pos] = human #วาง
                if check_win(Table, human): #ตรวจสอบรูปแบบชนะ
                    displaytable() #แสดงกระดาน
                    print("You Win!")
                    return #ออกจากwhile จบเกม
                current_player = ai #สลับฝั่ง
                turn_count += 1 #นับตา
            else:
                print("Invalid Position. Try again.")
                continue

        else:
            print(f"AI ({ai}) is thinking...")
            move = ai_best_move(Table, ai, human) #ให้AIคิด
            if move is not None: #ถ้ายังมีที่ให้วาง
                Table[move] = ai #aiวาง
                if check_win(Table, ai): #เช็คว่าชนะมั้ย
                    displaytable()#แสดงตาราง
                    print("AI Wins!")
                    return
                current_player = human #สลับฝั่ง
                turn_count += 1#นับตา
        
        displaytable()

    print("Draw!")

play_game() #เริ่มเกม