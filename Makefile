# Created by: Nasseef Abukamail
# This Makefile will allow you to run tests for the appointment class
#
# Usage:
#    make run_tests
#    mingw32-make run_tests_win
#
#Variables
CC = g++
CFLAGS = -g -Wall -std=c++11

# Linking all the files and run the tests. Use your own header and
# object files.

a.out: appointment2.o appointment2.h appointment_main2.o
	$(CC) $(CFLAGS) _TEST/appointment2.o _TEST/appointment_main2.o -o a.out

appointment.o: appointment2.cc appointment2.h
	$(CC) -c $(CFLAGS) appointment2.cc -o _TEST/appointment2.o

appointment_main.o: appointment_main2.cc appointment2.h
	$(CC) -c $(CFLAGS) appointment_main2.cc -o _TEST/appointment_main2.o

######################################## R U N   T E S T s ##################################################
run_tests: appointment2.h appointment2.o
	head appointment2.cc
	$(CC) $(CFLAGS) _TEST/TEST_cases.cc appointment2.cc -o _TEST/run_tests ; _TEST/run_tests -sr compact

run_tests_win: appointment2.h appointment2.o
	$(CC) $(CFLAGS) _TEST/TEST_cases.cc appointment2.cc -o _TEST/run_tests
	_TEST/run_tests -sr compact
##############################################################################################################

clean:
	rm -rf _TEST/*.o _TEST/run_tests a.out _TEST/a.out

# ######################################### R U N   T E S T s ##################################################
# run_tests: appointment.h appointment.o
# 	head appointment.cc
# 	$(CC) $(CFLAGS) _TEST/TEST_cases.cc _TEST/appointment.o -o _TEST/a.out && ./_TEST/a.out -sr compact
# ##############################################################################################################
