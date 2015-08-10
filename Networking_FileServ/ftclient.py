#!/usr/bin/python
""" Usage: python ftclient.py [SERVER_HOST] [SERVER_PORT] [COMMAND] [FILENAME] [DATA_PORT]
* References: https://docs.python.org/2/howto/sockets.html
"""
import socket
import sys
import threading

BUFFER_SIZE = 1024

list_mode = 0
file_save_name = ""

def write_console_to_socket(port, handle):
    serversocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    serversocket.bind(('', port))
    serversocket.listen(5)
    while 1:
        (clientsocket, address) = serversocket.accept()
        ct = client_thread(clientsocket)
        ct.run()


def main(server_host, server_port, command, filename="", data_port=""):
    if command not in ["-l", "-g"]:
        print(__doc__)
        return
    if command == "-l":
        data_port = filename
    else:
        command += " " + filename
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((server_host, server_port))
    s.send(data_port)
    s.send(command)
    s.close()

if __name__ in "__main__":
    if len(sys.argv) < 1:
        print(__doc__)
    else:
        main(*sys.argv[1])
