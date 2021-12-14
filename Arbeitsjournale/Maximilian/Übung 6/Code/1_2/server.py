from socket import socket, AF_INET, SOCK_STREAM
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
from matplotlib import style

IP = '0.0.0.0' # change individually
PORT = 3419 # choose client port

BUFFER_SIZE = 30 # buffer size in bytes, should be bigger than expected data

print("Wait for client...")
sock = socket(AF_INET, SOCK_STREAM) # create TCP socket
sock.bind((IP, PORT))               # initialize socket
sock.listen(1)                      # wait for incoming connection (blocking call!)
connection, address = sock.accept() # establish connection with client
print("Connected!")

style.use('fivethirtyeight')

fig = plt.figure()
ax1 = fig.add_subplot(2,1,1)
ax2 = fig.add_subplot(2,1,2)

xs = []
ys = []
zs = []

def animate(i):
    received = connection.recv(BUFFER_SIZE) # receive data from client (format: bytes)
    data = received.decode('utf8') # decode received message from bytes to string
    data = data.split(",") # split data on comma
    temp = data[0][0:4]
    humi = data[1][0:4]

    xs.append(int(i))
    ys.append(float(temp))
    zs.append(float(humi))

    ax1.clear()
    ax2.clear()
    ax1.plot(xs, ys, 'b')
    ax2.plot(xs, zs, 'r')
    plt.xlabel('time (s)')
    ax1.set_ylabel('Temperature')
    ax2.set_ylabel('Humidity')
    


ani = FuncAnimation(fig, animate, interval=1000)

plt.tight_layout()
plt.show()