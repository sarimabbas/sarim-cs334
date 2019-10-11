import socket

LOCAL_UDP_IP = "192.168.1.2"
SHARED_UDP_PORT = 5005

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)  # Internet  # UDP
sock.bind((LOCAL_UDP_IP, SHARED_UDP_PORT))

while True:
    print("jwehfgioewrh")
    data, addr = sock.recvfrom(2048)  # buffer size is 1024 byte
    print("received message:", data)

