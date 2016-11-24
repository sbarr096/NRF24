import sys
import time
########################Modules Path Information################################
sys.path.append(“/home/pi/Desktop/ICBP_NRF24/modules”)
########################Modules Path Information################################
from warnings import filterwarnings
import pymysql.cursors
import MySQLdb as db
filterwarnings('ignore', category = db.Warning)

def mysql_func(rID= "", volts= "", current= "", watts= "", status= ""):

    #print("")
    #print("Starting Sql module for radio: " + rID)
    
    conn = pymysql.connect(host='localhost',
    user='root',
    password='root',
    db='ICBP',
    charset='utf8mb4',
    cursorclass=pymysql.cursors.DictCursor)
    time.sleep(1/10)

    
    cursor = conn.cursor()

    cursor.execute ("""CREATE TABLE IF NOT EXISTS """ +rID+"""(Guid int(11) NOT NULL AUTO_INCREMENT,
    Time timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
    Volts float(10,2) NOT NULL,
    Current float(10,2) NOT NULL,
    Watts float(10,2) NOT NULL,
    Status int(1) NOT NULL,
    PRIMARY KEY(Guid))""")

    time.sleep(1/10)


    
    sql = "INSERT INTO " +rID+ "(Volts, Current, Watts, Status) VALUES (%s, %s, %s, %s)"
    cursor.execute(sql, (volts, current, watts, status))
    conn.commit()
    cursor.close()

    time.sleep(8/10)


