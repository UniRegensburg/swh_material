from socket import socket, AF_INET, SOCK_STREAM
from time import sleep

IP = '1.2.3.4'
PORT = 5555

sock = socket(AF_INET, SOCK_STREAM) # create TCP socket
sock.connect((IP, PORT))            # connect to the server

counter = 0 # this one is just to show you how to use variables

while(True):
    counter += 1
    
    # create a message
    message = 'Hello World! {}\r'.format(counter)
    message = message.encode('utf8') # we can only send byte sequences -> encode it!
    print(message)
    sock.send(message) # send message to the server
    sleep(0.1) # wait for 100 ms
