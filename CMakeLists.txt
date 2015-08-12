cmake_minimum_required(VERSION 3.2)
project(project4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c89")

set(ENC_D_SOURCE_FILES otp_enc_d.c)
set(ENC_SOURCE_FILES otp_enc.c)
set(DEC_SOURCE_FILES otp_dec_d.c)
set(DEC_D_SOURCE_FILES otp_dec.c)
set(KEYGEN_SOURCE_FILES keygen.c)


add_executable(otp_enc_d ${ENC_D_SOURCE_FILES})
add_executable(otp_enc ${ENC_SOURCE_FILES})
add_executable(otp_dec_d ${DEC_SOURCE_FILES})
add_executable(otp_dec ${DEC_D_SOURCE_FILES})
add_executable(keygen ${KEYGEN_SOURCE_FILES})