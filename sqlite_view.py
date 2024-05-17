# view_users.py

import sqlite3

def init_users(database="users.db"):
    conn = sqlite3.connect(database)
    cursor = conn.cursor()

    # Users Init
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

    conn = sqlite3.connect(database)
    cursor = conn.cursor()

    cursor.execute("SELECT * FROM Users")
    rows = cursor.fetchall()

    if rows:
        print("User Data:")
        for row in rows:
            print(f"ID: {row[0]}, Password: {row[1]}")
    else:
        print("No user data found.")

    cursor.close()
    conn.close()

if __name__ == "__main__":
    init_users()
    view_users()
