VPATH = src
OBJS_PATH = objects/
OBJS = $(OBJS_PATH)sumplete.o $(OBJS_PATH)sumpletelib.o $(OBJS_PATH)board.o $(OBJS_PATH)commands.o $(OBJS_PATH)interfaces.o $(OBJS_PATH)osManager.o $(OBJS_PATH)ranking.o $(OBJS_PATH)solver.o $(OBJS_PATH)tools.o
SOURCE = sumplete.c sumpletelib.c board.c commands.c interfaces.c osManager.c ranking.c solver.c tools.c
OUT	= sumplete
CC = gcc
FLAGS = -g -c -Wall
LFLAGS = -lm

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

$(OBJS_PATH)sumplete.o: game/sumplete.c
	$(CC) $(FLAGS) game/sumplete.c -o $(OBJS_PATH)sumplete.o

$(OBJS_PATH)sumpletelib.o: game/sumpletelib.c
	$(CC) $(FLAGS) game/sumpletelib.c -o $(OBJS_PATH)sumpletelib.o

$(OBJS_PATH)board.o: board/board.c
	$(CC) $(FLAGS) board/board.c -o $(OBJS_PATH)board.o

$(OBJS_PATH)commands.o: commands/commands.c
	$(CC) $(FLAGS) commands/commands.c -o $(OBJS_PATH)commands.o

$(OBJS_PATH)interfaces.o: interface/interfaces.c
	$(CC) $(FLAGS) interface/interfaces.c -o $(OBJS_PATH)interfaces.o 

$(OBJS_PATH)osManager.o: os_manager/osManager.c
	$(CC) $(FLAGS) os_manager/osManager.c -o $(OBJS_PATH)osManager.o

$(OBJS_PATH)ranking.o: ranking/ranking.c
	$(CC) $(FLAGS) ranking/ranking.c -o $(OBJS_PATH)ranking.o

$(OBJS_PATH)solver.o: solver/solver.c
	$(CC) $(FLAGS) solver/solver.c -o $(OBJS_PATH)solver.o

$(OBJS_PATH)tools.o: tools/tools.c
	$(CC) $(FLAGS) tools/tools.c -o $(OBJS_PATH)tools.o

clean:
	rm -f $(OBJS)

run: $(OUT)
	./$(OUT)