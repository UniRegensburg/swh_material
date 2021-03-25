from socket import socket, AF_INET, SOCK_STREAM

IP = '1.2.3.4'
PORT = 5555

BUFFER_SIZE = 20 # buffer size in bytes, should be bigger than expected data

sock = socket(AF_INET, SOCK_STREAM) # create TCP socket
sock.bind((IP, PORT))               # initialize socket
sock.listen(1)                      # wait for incoming connection (blocking call!)
connection, address = sock.accept() # establish connection with client

while(True):
    received = connection.recv(BUFFER_SIZE) # receive data from client (format: bytes)
    data = received.decode('utf8') # decode received message from bytes to string
    print(data)
