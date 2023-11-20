import socket

HEADER = 64
PORT = 5050
SERVER = '192.168.0.101'
ADDRESS = (SERVER, PORT)
FORMAT = 'utf-8'
DISCONNECT_MSG = '!DISCONNECT'

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(ADDRESS)

def send(msg):
    message  = msg.encode(FORMAT)
    msg_len = len(message)
    send_leng = str(msg_len).encode(FORMAT)
    send_leng += b' '*(HEADER- len(send_leng))
    client.send(send_leng)
    client.send(message)
    

send("Hello World")
