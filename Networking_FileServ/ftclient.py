#!/usr/bin/python
""" Usage: python ftclient.py [server to connect] [server port] [-l or -g] [filename if -g] [port for data connection]

References:
* Other chat client project
* https://docs.python.org/2/howto/sockets.html
"""
import socket
import sys
import time

BUFFER_SIZE = 1024

list_mode = False
file_save_name = ""


def write_console_to_socket(server_socket):
    (client_socket, address) = server_socket.accept()
    if list_mode:
        while 1:
            client_buffer = client_socket.recv(BUFFER_SIZE)
            if client_buffer != "":
                print(client_buffer)
            else:
                return
    else:
        with open(file_save_name, "w") as f:
            while 1:
                client_buffer = client_socket.recv(BUFFER_SIZE)
                if client_buffer != "":
                    f.write(client_buffer)
                else:
                    return


def main(server_host, server_port, command, filename="", data_port=""):
    global list_mode
    global file_save_name
    if command not in ["-l", "-g"]:
        print(__doc__)
        return
    if command == "-l":
        list_mode = True
        data_port = filename
    else:
        file_save_name = filename
        command += " " + filename

    # Start data socket
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind(('', int(data_port)))
    server_socket.listen(1)
    time.sleep(2)

    # Send command to ftserver
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((server_host, int(server_port)))
    s.sendall(data_port)
    s.sendall(command)

    write_console_to_socket(server_socket)
    try:
        print(s.recv(BUFFER_SIZE))
    except socket.timeout:
        pass
    s.close()
    server_socket.close()


if __name__ in "__main__":
    if len(sys.argv) < 3:
        print(__doc__)
    else:
        main(*sys.argv[1:])
