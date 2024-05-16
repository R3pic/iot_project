# view_users.py

import sqlite3

def init_users(database="users.db"):
    conn = sqlite3.connect(database)
    cursor = conn.cursor()

    # Users 테이블 생성
    cursor.execute("CREATE TABLE IF NOT EXISTS Users (ID VARCHAR(6) PRIMARY KEY, Password VARCHAR(6) NOT NULL)")
    cursor.execute("INSERT INTO Users (ID, Password) VALUES ('1', '1234')")
    cursor.execute("INSERT INTO Users (ID, Password) VALUES ('2', '5678')")
    cursor.execute("INSERT INTO Users (ID, Password) VALUES ('3', '0')")
    cursor.execute("INSERT INTO Users (ID, Password) VALUES ('7', '770700')")
    cursor.execute("INSERT INTO Users (ID, Password) VALUES ('222', '222222')")

    conn.commit()

    cursor.close()
    conn.close()
    

def view_users(database="users.db"):
    # 데이터베이스 연결
    conn = sqlite3.connect(database)
    cursor = conn.cursor()

    # Users 테이블 내용 조회
    cursor.execute("SELECT * FROM Users")
    rows = cursor.fetchall()

    # 결과 출력
    if rows:
        print("User Data:")
        for row in rows:
            print(f"ID: {row[0]}, Password: {row[1]}")
    else:
        print("No user data found.")

    # 연결 닫기
    cursor.close()
    conn.close()

if __name__ == "__main__":
    init_users()
    view_users()
