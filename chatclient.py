#!/usr/bin/python
""" Usage: python chatclient.py [hostname] [port]
    References: Python's telnetlib implementation
"""
import socket
import sys
import threading


BUFFER_SIZE = 1024


def query_for_handle():
    # sys.stdin is used for python 2/3 compatibility
    sys.stdout.write("Choose your handle?> ")
    sys.stdout.flush()
    return sys.stdin.readline().strip() + "> "


def write_console_to_socket(connection, handle):
    while True:
        sys.stdout.write(handle)
        sys.stdout.flush()
        msg = sys.stdin.readline()
        if msg == "\\quit\n":
            connection.close()
            return
        msg = handle + msg
        connection.sendall(msg.encode('utf-8'))


def read_socket_to_console(connection, handle):
    while True:
        try:
            data = connection.recv(BUFFER_SIZE)
        except (EOFError, ValueError):
            print('*** Connection closed ***')
            return
        else:
            if data:
                sys.stdout.write("\n" + data.decode('utf-8') + handle)
            else:
                sys.stdout.flush()


def main(hostname, port):
    handle = query_for_handle()
    connection = socket.create_connection((hostname, port))
    connection.sendall(b"\n")
    read_thread = threading.Thread(group=None, target=write_console_to_socket, args=(connection, handle))
    read_thread.daemon = True
    read_thread.start()
    read_socket_to_console(connection, handle)


if __name__ in "__main__":
    if len(sys.argv) < 3:
        print(__doc__)
    else:
        main(sys.argv[1], sys.argv[2])
