TARGET = toy_project

CC = gcc
CFLAGS= -I$(SYSTEM) -I$(UI) -I$(WEB_SERVER)

SYSTEM = ./system
UI = ./ui
WEB_SERVER = ./web_server

HEADERS = $(SYSTEM)/system_server.h $(UI)/gui.h $(UI)/input.h  $(WEB_SERVER)/web_server.h

OBJS = main.o system_server.o ui.o web_server.o input.o


$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)

main.o: main.c $(HEADERS)
	$(CC) $(CFLAGS) -c -o $@ main.c

system_server.o: $(SYSTEM)/system_server.c $(HEADERS)
	$(CC) $(CFLAGS) -c -o $@ $(SYSTEM)/system_server.c

ui.o: $(UI)/gui.c $(HEADERS)
	$(CC) $(CFLAGS) -c -o $@ $(UI)/gui.c

input.o: $(UI)/input.c $(HEADERS)
	$(CC) $(CFLAGS) -c -o $@ $(UI)/input.c

web_server.o: $(WEB_SERVER)/web_server.c $(HEADERS)
	$(CC) $(CFLAGS) -c -o $@ $(WEB_SERVER)/web_server.c


clean:
	rm -rf $(OBJS) $(TARGET)
