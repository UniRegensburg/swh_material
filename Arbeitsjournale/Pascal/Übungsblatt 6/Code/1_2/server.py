from socket import socket, AF_INET, SOCK_STREAM
from win10toast import ToastNotifier
toaster = ToastNotifier()

IP = '0.0.0.0' # IP address has to be changed
PORT = 1515 # Port has to be the same as for the client

BUFFER_SIZE = 30 # buffer size in bytes, should be bigger than expected data

print("Wait for client...")
sock = socket(AF_INET, SOCK_STREAM) # create TCP socket
sock.bind((IP, PORT))               # initialize socket
sock.listen(1)                      # wait for incoming connection (blocking call!)
connection, address = sock.accept() # establish connection with client
print("Connected!")
isHot = False
isHumid = False

while(True):
    received = connection.recv(BUFFER_SIZE) # receive data from client (format: bytes)
    data = received.decode('utf8') # decode received message from bytes to string
    data = data.split() # split data on whitespace
    temp = float(data[0])
    humid = float(data[1])
    print(temp, " ", humid)
    if temp >= 25 and not isHot:
        isHot = True
        # show toast message on windows
        toaster.show_toast("Trinken nicht vergessen!", "Es scheint sehr warm in deinem Zimmer zu sein (über 26°C). Denke daran, immer genug zu trinken bei dieser Hitze!", duration=5,threaded=True)
    elif temp < 25:
        isHot = False
    if humid >= 60 and not isHumid:
        isHumid = True
        toaster.show_toast("Bitte lüften!", "In deinem Zimmer ist eine sehr hohe Luftfeuchtigkeit. Wird zeit zu lüften", duration=5,threaded=True)
    elif humid < 60:
        isHumid = False

