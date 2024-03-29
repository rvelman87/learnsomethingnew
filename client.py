#! /usr/bin/python
import socket

HOST = "127.0.0.1"  # The server's hostname or IP address
PORT = 8081# The port used by the server

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    data = s.recv(255)

print(f"Received {data!r}")
