SRC += src/*.c
FLG += -std=c99
FLG += -Wall
LNK += -lraylib
LNK += -lmodbus
BIN += rl_mb_viewer

build:
	gcc $(SRC) $(FLG) $(LNK) -o $(BIN)

run:
	./$(BIN)

