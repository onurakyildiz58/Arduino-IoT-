import serial
import webbrowser


#veriyi alma
uno = serial.Serial("com5", 9600)
x = 0
urlList = []

#str = "191307026         ,Onur Akyildiz     ,Kocaeli Uni       ,Teknoloji fak     ,Bil Sis Muh       }


URL = "https://script.google.com/macros/s/AKfycbw16NxQF41e3Rs5fYDBSrBsXPtYWQQ3MFgD9OYifYNYbcyyXOCasxAabQuiRgYe_LZaPA/exec?"
Key = "AKfycbw16NxQF41e3Rs5fYDBSrBsXPtYWQQ3MFgD9OYifYNYbcyyXOCasxAabQuiRgYe_LZaPA"
#?data1=191307026&data2=OnurAkyildiz&data3=KocaeliUni&data4=Teknolojifak&data5=BilSisMüh


urlPart = "data"
FullURL = ""
finalURL = []
strURL = ""
while x != 1:
    while uno.inWaiting() == 0:
        pass
    data = uno.readline()
    data = str(data, 'utf-8')
    print("gelen data : ", data)
    x += 1

#veriyi işleme
data = data.split(",")

print("ayrılmış data : ", data)

for i in range(len(data)):
    clean = data[i].replace(" ", "").replace("\"", "").replace("","").replace("}", "")
    print("data tek tek : ", clean)
    urlList.append(clean)

for i in range(len(urlList)):
    FullURL = urlPart + str(i+1) + "=" + urlList[i]
    print(FullURL)
    finalURL.append(FullURL)
print(finalURL)

for i in range(len(finalURL)):
    print(finalURL[i], end="")
    strURL = strURL + finalURL[i] + "&"

strURL = strURL.replace("_", "")
print("str : ", strURL)
URL = URL + strURL
print("final URL : ", URL)
# web browser ilw arama
webbrowser.open(URL)

