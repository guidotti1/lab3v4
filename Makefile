#MakeFile to build and deploy the Sample US CENSUS Name Data using ajax
# For CSC3004 Software Development

# Put your user name below:
USER= guidotti1

CC= g++

#For Optimization
#CFLAGS= -O2
#For debugging
CFLAGS= -std=c++14  -Wno-deprecated-declarations

RM= /bin/rm -f

all: artApp createUserAccounts userComment PutHTML PutCGI 

artEntry.o: artEntry.cpp artEntry.h
	$(CC) -c $(CFLAGS) artEntry.cpp

artBook.o: artBook.cpp artBook.h
	$(CC) -c $(CFLAGS) -I/usr/include/cppconn artBook.cpp

artApp.o: artApp.cpp 
	$(CC) -c $(CFLAGS) artApp.cpp

artApp: artApp.o artBook.o artEntry.o
	$(CC) artApp.o artBook.o artEntry.o -o artApp -L/usr/local/lib -lcgicc -lmysqlcppconn
	
createUserAccounts.o: createUserAccounts.cpp
	$(CC) -c $(CFLAGS) createUserAccounts.cpp

createUserAccounts: createUserAccounts.o
	$(CC) createUserAccounts.o -o createUserAccounts -L/usr/local/lib -lcgicc -lmysqlcppconn

userComment.o: userComment.cpp
	$(CC) -c $(CFLAGS) userComment.cpp
	
userComment: userComment.o
	$(CC) userComment.o -o userComment -L/usr/local/lib -lgicc =lmysqlcppconn

PutCGI: artApp
	chmod 757 artApp
	chmod 757 createUserAccounts
	cp artApp /usr/lib/cgi-bin/$(USER)_artApp.cgi 
	cp createUserAccounts /usr/lib/cgi-bin/$(USER)_createUserAccounts.cgi
	cp userComment /usr/lib/cgi-bin/$(USER)_userComment.cgi

	echo "Current contents of your cgi-bin directory: "
	ls -l /usr/lib/cgi-bin/

PutHTML:
	cp artApp.html /var/www/html/class/softdev/$(USER)/artApp
	cp artAppV2.js /var/www/html/class/softdev/$(USER)/artApp
	cp artApp.css /var/www/html/class/softdev/$(USER)/artApp


	echo "Current contents of your HTML directory: "
	ls -l /var/www/html/class/softdev/$(USER)/artApp

clean:
	rm -f *.o  artApp 
