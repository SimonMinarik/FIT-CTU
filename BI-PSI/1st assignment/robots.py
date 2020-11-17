import socket

from _thread import *

HOST = "127.0.0.1"
PORT = 1111

SERVER_MOVE = b"102 MOVE\a\b"
SERVER_TURN_LEFT = b"103 TURN LEFT\a\b"
SERVER_TURN_RIGHT = b"104 TURN RIGHT\a\b"
SERVER_PICK_UP = b"105 GET MESSAGE\a\b"
SERVER_LOGOUT = b"106 LOGOUT\a\b"
SERVER_OK = b"200 OK\a\b"
SERVER_LOGIN_FAILED = b"300 LOGIN FAILED\a\b"
SERVER_SYNTAX_ERROR = b"301 SYNTAX ERROR\a\b"
SERVER_LOGIC_ERROR = b"302 LOGIC ERROR\a\b"

CLIENT_USERNAME_MAX_LENGTH = 12
CLIENT_CONFIRMATION_MAX_LENGTH = 7
CLIENT_OK_MAX_LENGTH = 12
CLIENT_RECHARGING_MAX_LENGTH = 12
CLIENT_FULL_POWER_MAX_LENGTH = 12
CLIENT_MESSAGE_MAX_LENGTH = 100

TIMEOUT = 1
TIMEOUT_RECHARGING = 5

SERVER_KEY = 54621
CLIENT_KEY = 45328

UP = 0
DOWN = 2
LEFT = 3
RIGHT = 1


def getMessage(conn, max_length, type, buffer, sentme):
    if len(buffer) == 0 or (len(buffer) == 1 and buffer[0].find(b"\a\b") == -1):
        while True:
            message = conn.recv(1024)
            print("received: ", message, "buffer:", buffer, "sentme:", sentme)
            if message.find(b"\a\b") > max_length - 2 and message != b"RECHARGING\a\b":
                conn.sendall(SERVER_SYNTAX_ERROR)
                print("sending:", SERVER_SYNTAX_ERROR)
                conn.close()
                exit()
            if message.find(b"\a\b") == -1 and len(message) > max_length - 2:
                conn.sendall(SERVER_SYNTAX_ERROR)
                print("sending:", SERVER_SYNTAX_ERROR)
                conn.close()
                exit()
            if message.find(b"\a\b") == -1 and len(buffer):
                buffer[-1] += message
                if buffer[-1].find(b"\a\b") != -1:
                    if len(buffer[-1]) != buffer[-1].find(b"\a\b") + 2:
                        buffer = buffer[-1].split(b"\a\b")
                        buffer[0] += b"\a\b"
            elif message.find(b"\a\b") == -1 and not len(buffer):
                buffer.append(message)
            elif len(buffer) and buffer[-1].find(b"\a\b") == -1:
                if message.find(b"\a\b") != len(message) - 2:
                    buffer[-1] += message[:message.find(b"\a\b") + 2]
                    buffer.append(message[message.find(b"\a\b") + 2:])
                else:
                    buffer[-1] += message
            else:
                if message == b"\a\b":
                    buffer.append(message)
                else:
                    buffer += [e + b"\a\b" for e in message.split(b"\a\b") if e]
                if buffer[-1] == b"":
                    buffer.pop()
            if len(buffer) >= 1 and buffer[0].find(b"\a\b") != -1:
                break
    x = buffer.pop(0)
    if x.find(b"\a\b") + 2 != len(x):
        buffer.append(x[x.find(b"\a\b") + 2:])
        x = x[:x.find(b"\a\b") + 2]
    if x == b"RECHARGING\a\b":
        x, buffer = recharge(conn, max_length, type, buffer)
    if not isValid(x[:x.find(b"\a\b")], type):
        conn.sendall(SERVER_SYNTAX_ERROR)
        print("sending:", SERVER_SYNTAX_ERROR)
        conn.close()
        exit()
    message = x[:x.find(b"\a\b")]
    return message, buffer


def recharge(conn, max_length, type, buffer):
    print("recharging")
    conn.settimeout(TIMEOUT_RECHARGING)
    message, buffer = getMessage(conn, CLIENT_FULL_POWER_MAX_LENGTH, "CLIENT_FULL_POWER", buffer, "recharge")
    conn.settimeout(TIMEOUT)
    if message != b"FULL POWER":
        conn.sendall(SERVER_LOGIC_ERROR)
        print("sending:", SERVER_LOGIC_ERROR)
        conn.close()
        exit()
        return message, buffer
    message, buffer = getMessage(conn, max_length, type, buffer, "completed_recharge")
    message += b"\a\b"
    return message, buffer


def isValid(message, type):
    if type == "CLIENT_OK" and message != b"RECHARGING":
        if message.decode().count(" ") != 2:
            return 0
        x = message.decode().split(" ")
        if x[0] != "OK" or not x[1].lstrip("-").isdigit() or not x[2].lstrip("-").isdigit():
            return 0

    return 1


def getHash(message):
    username_ascii = 0
    for x in message:
        username_ascii += x
    return (username_ascii * 1000) % 65536


def login(conn, buffer):
    username, buffer = getMessage(conn, CLIENT_USERNAME_MAX_LENGTH, "CLIENT_USERNAME", buffer, "getting_username")
    saved_hash = getHash(username)
    server_confirm_code = (saved_hash + SERVER_KEY) % 65536
    client_confirm_code = (saved_hash + CLIENT_KEY) % 65536
    conn.sendall((str(server_confirm_code) + "\a\b").encode())
    print("sending:", (str(server_confirm_code) + "\a\b").encode())
    received_confirm_code, buffer = getMessage(conn, CLIENT_CONFIRMATION_MAX_LENGTH, "CLIENT_CONFIRMATION", buffer, "getting_confirm_code")
    received_confirm_code = received_confirm_code.decode()
    if received_confirm_code.isdigit():
        if client_confirm_code == int(received_confirm_code):
            conn.sendall(SERVER_OK)
            print("sending:", SERVER_OK)
            return 1, buffer
        else:
            conn.sendall(SERVER_LOGIN_FAILED)
            print("sending:", SERVER_LOGIN_FAILED)
            conn.close()
            exit()
            return 0, buffer
    else:
        conn.sendall(SERVER_SYNTAX_ERROR)
        print("sending:", SERVER_SYNTAX_ERROR)
        conn.close()
        exit()


def getDirection(conn, buffer):
    direction = None
    conn.sendall(SERVER_MOVE)
    print("sending:", SERVER_MOVE)
    moved, buffer = getMessage(conn, CLIENT_OK_MAX_LENGTH, "CLIENT_OK", buffer, "getting dir 1 move")
    moved = moved.decode().split(" ")
    x = moved[1]
    y = moved[2]
    x_tmp = x
    y_tmp = y
    while x_tmp == x and y == y_tmp:
        conn.sendall(SERVER_MOVE)
        print("sending:", SERVER_MOVE)
        moved, buffer = getMessage(conn, CLIENT_OK_MAX_LENGTH, "CLIENT_OK", buffer, "getting dir 2 move")
        moved = moved.decode().split(" ")
        x_tmp = moved[1]
        y_tmp = moved[2]
    if int(moved[1]) < int(x):
        direction = LEFT
    if int(moved[1]) > int(x):
        direction = RIGHT
    if int(moved[2]) < int(y):
        direction = DOWN
    if int(moved[2]) > int(y):
        direction = UP
    x = int(moved[1])
    y = int(moved[2])
    return direction, x, y, buffer


def changeDirection(conn, fr0m, to, buffer):
    while fr0m != to:
        conn.sendall(SERVER_TURN_RIGHT)
        print("sending:", SERVER_TURN_RIGHT)
        x, buffer = getMessage(conn, CLIENT_OK_MAX_LENGTH, "CLIENT_OK", buffer, "changedirection")
        fr0m = (fr0m + 1) % 4
    return fr0m, buffer


def moveForward(conn, buffer):
    conn.sendall(SERVER_MOVE)
    print("sending:", SERVER_MOVE)
    moved, buffer = getMessage(conn, CLIENT_OK_MAX_LENGTH, "CLIENT_OK", buffer, "moveforward")
    moved = moved.decode().split(" ")
    return int(moved[1]), int(moved[2]), buffer


def pickUp(conn, buffer):
    conn.sendall(SERVER_PICK_UP)
    print("sending:", SERVER_PICK_UP)
    message, buffer = getMessage(conn, CLIENT_MESSAGE_MAX_LENGTH, "CLIENT_MESSAGE", buffer, "pickup")
    if message != b"":
        return True, buffer
    else:
        return False, buffer


def searchTheGrid(conn, direction, corner, x, y, buffer):
    found_message = False
    if corner == "lower_left":
        direction, buffer = changeDirection(conn, direction, UP, buffer)
        for _ in range(5):
            moves = 0
            while moves < 4:
                found_message, buffer = pickUp(conn, buffer)
                if found_message:
                    break
                x_tmp, y_tmp, buffer = moveForward(conn, buffer)
                if not (x_tmp == x and y_tmp == y):
                    x = x_tmp
                    y = y_tmp
                    moves += 1
            moves = 0
            if found_message:
                break
            direction, buffer = changeDirection(conn, direction, RIGHT, buffer)
            found_message, buffer = pickUp(conn, buffer)
            if found_message:
                break
            while moves < 1:
                x_tmp, y_tmp, buffer = moveForward(conn, buffer)
                if not (x_tmp == x and y_tmp == y):
                    x = x_tmp
                    y = y_tmp
                    moves += 1
            if y == 2:
                direction, buffer = changeDirection(conn, direction, DOWN, buffer)
            elif y == -2:
                direction, buffer = changeDirection(conn, direction, UP, buffer)
    if corner == "lower_right":
        direction, buffer = changeDirection(conn, direction, UP, buffer)
        for _ in range(5):
            moves = 0
            while moves < 4:
                found_message, buffer = pickUp(conn, buffer)
                if found_message:
                    break
                x_tmp, y_tmp, buffer = moveForward(conn, buffer)
                if not (x_tmp == x and y_tmp == y):
                    x = x_tmp
                    y = y_tmp
                    moves += 1
            moves = 0
            if found_message:
                break
            direction, buffer = changeDirection(conn, direction, LEFT, buffer)
            found_message, buffer = pickUp(conn, buffer)
            if found_message:
                break
            while moves < 1:
                x_tmp, y_tmp, buffer = moveForward(conn, buffer)
                if not (x_tmp == x and y_tmp == y):
                    x = x_tmp
                    y = y_tmp
                    moves += 1
            if y == 2:
                direction, buffer = changeDirection(conn, direction, DOWN, buffer)
            elif y == -2:
                direction, buffer = changeDirection(conn, direction, UP, buffer)
    if corner == "upper_left":
        direction, buffer = changeDirection(conn, direction, DOWN, buffer)
        for _ in range(5):
            moves = 0
            while moves < 4:
                found_message, buffer = pickUp(conn, buffer)
                if found_message:
                    break
                x_tmp, y_tmp, buffer = moveForward(conn, buffer)
                if not (x_tmp == x and y_tmp == y):
                    x = x_tmp
                    y = y_tmp
                    moves += 1
            moves = 0
            if found_message:
                break
            direction, buffer = changeDirection(conn, direction, RIGHT, buffer)
            found_message, buffer = pickUp(conn, buffer)
            if found_message:
                break
            while moves < 1:
                x_tmp, y_tmp, buffer = moveForward(conn, buffer)
                if not (x_tmp == x and y_tmp == y):
                    x = x_tmp
                    y = y_tmp
                    moves += 1
            if y == 2:
                direction, buffer = changeDirection(conn, direction, DOWN, buffer)
            elif y == -2:
                direction, buffer = changeDirection(conn, direction, UP, buffer)
    if corner == "upper_right":
        direction, buffer = changeDirection(conn, direction, DOWN, buffer)
        for _ in range(5):
            moves = 0
            while moves < 4:
                found_message, buffer = pickUp(conn, buffer)
                if found_message:
                    break
                x_tmp, y_tmp, buffer = moveForward(conn, buffer)
                if not (x_tmp == x and y_tmp == y):
                    x = x_tmp
                    y = y_tmp
                    moves += 1
            moves = 0
            if found_message:
                break
            direction, buffer = changeDirection(conn, direction, LEFT, buffer)
            found_message, buffer = pickUp(conn, buffer)
            if found_message:
                break
            while moves < 1:
                x_tmp, y_tmp, buffer = moveForward(conn, buffer)
                if not (x_tmp == x and y_tmp == y):
                    x = x_tmp
                    y = y_tmp
                    moves += 1
            if y == 2:
                direction, buffer = changeDirection(conn, direction, DOWN, buffer)
            elif y == -2:
                direction, buffer = changeDirection(conn, direction, UP, buffer)
    conn.sendall(SERVER_LOGOUT)
    print("sending:", SERVER_LOGOUT)
    conn.close()
    exit()


def move(conn, buffer):
    direction, x, y, buffer = getDirection(conn, buffer)
    in_the_square = False
    done_with_y = False
    while not (x == 2 or x == -2) or not (y == 2 or y == -2):
        if not in_the_square:
            if not done_with_y:
                if y > 2:
                    if direction != DOWN:
                        direction, buffer = changeDirection(conn, direction, DOWN, buffer)
                    x, y, buffer = moveForward(conn, buffer)
                elif y < -2:
                    if direction != UP:
                        direction, buffer = changeDirection(conn, direction, UP, buffer)
                    x, y, buffer = moveForward(conn, buffer)
                else:
                    if direction != UP:
                        direction, buffer = changeDirection(conn, direction, UP, buffer)
                    x, y, buffer = moveForward(conn, buffer)
                if y == 2 or y == -2:
                    done_with_y = True
            else:
                if x > 2:
                    if direction != LEFT:
                        direction, buffer = changeDirection(conn, direction, LEFT, buffer)
                    x, y, buffer = moveForward(conn, buffer)
                elif x < 2:
                    if direction != RIGHT:
                        direction, buffer = changeDirection(conn, direction, RIGHT, buffer)
                    x, y, buffer = moveForward(conn, buffer)
                else:
                    if direction != RIGHT:
                        direction, buffer = changeDirection(conn, direction, RIGHT, buffer)
                    x, y, buffer = moveForward(conn, buffer)
                if x == 2 or x == -2:
                    in_the_square = True
    if x == 2:
        if y == 2:
            corner = "upper_right"
        else:
            corner = "lower_right"
    else:
        if y == 2:
            corner = "upper_left"
        else:
            corner = "lower_left"
    searchTheGrid(conn, direction, corner, x, y, buffer)


def magic(conn):
    try:
        buffer = []
        conn.settimeout(TIMEOUT)
        successful_login, buffer = login(conn, buffer)
        if not successful_login:
            return
        else:
            move(conn, buffer)
    finally:
        conn.close()


def main():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as mysocket:
        mysocket.bind((HOST, PORT))
        mysocket.listen(1)

        while True:
            conn, addr = mysocket.accept()
            start_new_thread(magic, (conn,))


if __name__ == "__main__":
    main()
