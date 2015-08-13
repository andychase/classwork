This is the final project for CS 344. The objective here is to play with daemons, sockets, and files.

	CMakeLists.txt  -- cmake build file 
	cipher_lib.c    -- cipher helper functions
	cipher_lib.h    -- ^
	compileall      -- compile script, run this to compile the programs
	keygen.c        -- this program will generate non-secure random key material
	otp_dec.c       -- decryption, this program serves as a client to the _d version
	otp_dec_d.c     -- decryption, this is the decryption server
	otp_enc.c       -- encryption, client
	otp_enc_d.c     -- encryption, server
	p4gradingscript -- bash grading script
	plaintext1      -- Test plaintext Files
	plaintext2      -- ^
	plaintext3      -- ^
	plaintext4      -- ^
	plaintext5      -- ^
	server_lib.c    -- server helper functions
	server_lib.h    -- ^

How to compile:

  ./compileall

How to run:

  ./p4gradingscript

Porgram usages:

	keygen
	USAGE: keygen keylength

	otp_dec
	Usage: otd_dec msg key [enc port #]
	otp_dec_d
	Usage: otd_dec_d [port #]

	otp_enc
	Usage: otd_enc msg key [enc port #]

	otp_enc_d
	Usage: otd_enc_d [port #]
