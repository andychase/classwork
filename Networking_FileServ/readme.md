# chatserv.c & chatclient.py

How to compile chatserv:

    make

How to run chatserv:

    ./chatserv [port to run chatserv on]

How to run chatclient.py

    python chatclient.py [hostname to connect to] [port to connect to]

How to use chatserv:

* This program is used through a terminal. On Mac OS X use the Terminal.app program,
  or on unix-type systems use your favorite terminal emulator like xterm
    * This software is only written for posix systems, cygwin is available if you are on windows.
* In the same directory as the software, compile and run `chatserv` (see above)
* Chatserv will wait for a client to connect to it
* Once a client is connected, you can type messages in at any time
    * Note if a message comes in while you are still typing, the first part of your
      message will still be sent when you press enter. You can still also erase with backspace
      but your screen won't display the characters erasing.
* Type \quit at the prompt at any time to close the connection with the client
* End the program with control+c

How to use chatclient.py:

* Open up a terminal (see above)
* Run: `python chatclient.py [hostname to connect to] [port to connect to]`
* Enter in your chat handle to be used to identify your messages. 
  You cannot change it except by re-connecting.
* Type in your message at the prompt
* Type \quit at the prompt to close the connection with the server and quit the program
