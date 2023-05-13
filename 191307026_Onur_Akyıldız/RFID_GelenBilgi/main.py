import serial
from datetime import datetime
import webbrowser
import requests

Token = '6022870664:AAF1gV_L1CRRrZLvk8sLyzlrPvgbhiVHyvY'
group_id = "BulutBilisim01"

def send_message(msg):
   telegram_api_url = f"https://api.telegram.org/bot{Token}/sendMessage?chat_id=@{group_id}&text={msg}"
   tel_resp = requests.get(telegram_api_url)
   if tel_resp.status_code == 200:
       print("Notification sent to telegram..")
   else:
       print("Could`nt send message!!")

#https://script.google.com/macros/s/AKfycbyHBhk896lTnrA6NavwqZyYasX-IDDeAk0EnGEdWG1yhAwaCcYSZGIl6W9es59bI-ulSQ/exec?
#https://script.google.com/macros/s/AKfycbyHBhk896lTnrA6NavwqZyYasX-IDDeAk0EnGEdWG1yhAwaCcYSZGIl6W9es59bI-ulSQ/exec?data1=191307022&data2=06/03/2023

now = datetime.now()
now = now.strftime("%d/%m/%Y")

urlBase = 'https://script.google.com/macros/s/AKfycbyHBhk896lTnrA6NavwqZyYasX-IDDeAk0EnGEdWG1yhAwaCcYSZGIl6W9es59bI-ulSQ/exec?'
a = 1

uno = serial.Serial("com3", 9600)

while uno.inWaiting() == 0:
    pass
data = uno.readline()
data = str(data, 'utf-8')
data = data.replace(" ", "").replace("\"", "").replace(",", "").replace("\r\n", "")
print("gelen data :", data)

#https://script.google.com/macros/s/AKfycbyHBhk896lTnrA6NavwqZyYasX-IDDeAk0EnGEdWG1yhAwaCcYSZGIl6W9es59bI-ulSQ/exec?
#https://script.google.com/macros/s/AKfycbyHBhk896lTnrA6NavwqZyYasX-IDDeAk0EnGEdWG1yhAwaCcYSZGIl6W9es59bI-ulSQ/exec?data1=191307022&data2=06/03/2023
value = "data1=" + data + "&data2=" + now
print(value)
URL = urlBase + value
print(URL)
webbrowser.open(URL)

html = requests.get(URL)
if html.text == 'Başarılı':
    msg = data + ' numaralı öğrencinin yoklaması başarılı'
    send_message(msg)
else:
    msg = data + ' numaralı öğrencinin yoklaması başarısız'
    send_message(msg)