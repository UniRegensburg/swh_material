from websocket_server import WebsocketServer

# Called for every client connecting (after handshake)
def new_client(client):
	print("New client connected")

# Called when a client sends a message
def message_received(client, server, message):
    server.send_message_to_all("on")
    print("Client(%d) said: %s" % (client['id'], message))


PORT=9001
server = WebsocketServer(PORT)
server.set_fn_new_client(new_client)
server.set_fn_message_received(message_received)
server.run_forever()