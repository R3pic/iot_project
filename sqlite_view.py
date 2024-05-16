# view_users.py

import sqlite3

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
    view_users()
