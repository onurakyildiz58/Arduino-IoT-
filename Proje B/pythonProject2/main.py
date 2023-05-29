#gerekli kütüphaneler
#cvzone-> version 1.5.6
#mediapipe-> version 0.9.2.1
#serialDevice-> version 0.2
#kütüphaneler indirdikten sonra python-opencv kütüphanesinin versiyonunu 4.5.4.60 a düşürüyoruz

from cvzone.SerialModule import SerialObject
from cvzone.HandTrackingModule import HandDetector
import cv2

cap = cv2.VideoCapture(0)#görüntü yakalama
detector = HandDetector(maxHands=1, detectionCon=0.7)#el algılamaq
mySerial = SerialObject("COM3", 9600, 1)#serial port haberleşme

while True:
    success, image = cap.read()
    hands, image = detector.findHands(image)

    if hands:
        hands = hands[0]
        lmList = hands["lmList"]# el eklemlerinin listesi raporda belirtilmiştir
        bbox = hands["bbox"]# eli çevreleyen kutunun konumu, yükseklik ve genişlik bilgisi[x, y, w, h]

        fingers = detector.fingersUp(hands)
        print(fingers)
        mySerial.sendData(fingers)
        print(mySerial.sendData(fingers))



    cv2.imshow("image", image)#display
    key = cv2.waitKey(1)

    if key == ord('q') or key == ord('Q'):
        break

cap.release()
cv2.destroyAllWindows()
