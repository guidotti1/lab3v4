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

all: artApp createUserAccounts userComment userVote viewUserProfile userFriends getRecent PutHTML PutCGI 

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
	$(CC) userComment.o -o userComment -L/usr/local/lib -lcgicc -lmysqlcppconn
	
userVote.o: userVote.cpp
	$(CC) -c $(CFLAGS) userVote.cpp
	
userVote: userVote.o
	$(CC) userVote.o -o userVote -L/usr/local/lib -lcgicc -lmysqlcppconn
	
viewUserProfile.o: viewUserProfile.cpp
	$(CC) -c $(CFLAGS) viewUserProfile.cpp

viewUserProfile: viewUserProfile.o artEntry.o
	$(CC) viewUserProfile.o artEntry.o -o viewUserProfile -L/usr/local/lib -lcgicc -lmysqlcppconn
	
userFriends.o: userFriends.cpp
	$(CC) -c $(CFLAGS) userFriends.cpp

userFriends: userFriends.o 
	$(CC) userFriends.o  -o userFriends -L/usr/local/lib -lcgicc -lmysqlcppconn
	
getRecent.o: getRecent.cpp
	$(CC) -c $(CFLAGS) getRecent.cpp

getRecent: getRecent.o 
	$(CC) getRecent.o  -o getRecent -L/usr/local/lib -lcgicc -lmysqlcppconn

PutCGI: artApp
	chmod 757 artApp
	chmod 757 createUserAccounts
	chmod 757 userVote
	chmod 757 userComment
	chmod 757 viewUserProfile
	chmod 757 userFriends
	chmod 757 getRecent
	cp artApp /usr/lib/cgi-bin/$(USER)_artApp.cgi 
	cp createUserAccounts /usr/lib/cgi-bin/$(USER)_createUserAccounts.cgi
	cp userComment /usr/lib/cgi-bin/$(USER)_userComment.cgi
	cp userVote /usr/lib/cgi-bin/$(USER)_userVote.cgi
	cp viewUserProfile /usr/lib/cgi-bin/$(USER)_viewUserProfile.cgi
	cp userFriends /usr/lib/cgi-bin/$(USER)_userFriends.cgi
	cp getRecent /usr/lib/cgi-bin/$(USER)_getRecent.cgi


	echo "Current contents of your cgi-bin directory: "
	ls -l /usr/lib/cgi-bin/

PutHTML:
	cp artApp.html /var/www/html/class/softdev/$(USER)/artApp3
	cp artApp.js /var/www/html/class/softdev/$(USER)/artApp3
	cp artApp.css /var/www/html/class/softdev/$(USER)/artApp3


	echo "Current contents of your HTML directory: "
	ls -l /var/www/html/class/softdev/$(USER)/artApp3

clean:
	rm -f *.o  artApp 
