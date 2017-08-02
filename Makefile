ROOT=$(shell pwd)
SERVER=$(ROOT)/server
CLIENT=$(ROOT)/client
LOG=$(ROOT)/log
POOL=$(ROOT)/data_pool
COMM=$(ROOT)/comm
LIB=$(ROOT)/lib/lib
WINDOW=$(ROOT)/window
PLUGIN=$(ROOT)/plugin
CONF=$(ROOT)/conf

LDFLAGS=-ljson -lpthread -lncurses
##-I是编译时
INCLUDE=-I$(POOL) -I$(LOG) -I$(COMM) -I$(LIB)/include -I$(WINDOW)
#-L是链接时
LIB_PATH=-L$(LIB)

SERVER_BIN=chat_system
CLIENT_BIN=chat_client

CC=g++

SERVER_OBJ=$(shell ls $(SERVER)|grep -E '\.cpp$$'|sed 's/\.cpp/\.o/')
SERVER_OBJ+=$(shell ls $(POOL)|grep -E '\.cpp$$'|sed 's/\.cpp/\.o/')
SERVER_OBJ+=$(shell ls $(LOG)|grep -E '\.cpp$$'|sed 's/\.cpp/\.o/')
SERVER_OBJ+=$(shell ls $(COMM)|grep -E '\.cpp$$'|sed 's/\.cpp/\.o/')
CLIENT_OBJ=$(shell ls $(CLIENT)|grep -E '\.cpp$$'|sed 's/\.cpp/\.o/')
CLIENT_OBJ+=$(shell ls $(LOG)|grep -E '\.cpp$$'|sed 's/\.cpp/\.o/')
CLIENT_OBJ+=$(shell ls $(COMM)|grep -E '\.cpp$$'|sed 's/\.cpp/\.o/')
CLIENT_OBJ+=$(shell ls $(WINDOW)|grep -E '\.cpp$$'|sed 's/\.cpp/\.o/')

.PHONY:all
all:$(SERVER_BIN) $(CLIENT_BIN)

$(SERVER_BIN):$(SERVER_OBJ)
	$(CC) -o $@ $^ $(LDFLAGS) $(LIB_PATH) 
$(CLIENT_BIN):$(CLIENT_OBJ)
	$(CC) -o $@ $^ $(LDFLAGS) $(LIB_PATH) 
%.o:$(SERVER)/%.cpp
	$(CC) -c $< $(INCLUDE) 
%.o:$(CLIENT)/%.cpp
	$(CC) -c $< $(INCLUDE) 
%.o:$(POOL)/%.cpp
	$(CC) -c $< 
%.o:$(LOG)/%.cpp
	$(CC) -c $< 
%.o:$(WINDOW)/%.cpp
	$(CC) -c $< 
%.o:$(COMM)/%.cpp
	$(CC) -c $<  $(INCLUDE)

.PHONY:debug
debug:
	@echo $(SERVER_OBJ)
	@echo $(CLIENT_OBJ)

.PHONY:output
output:
	mkdir -p output/server
	mkdir -p output/server/log
	mkdir -p output/client
	cp $(SERVER_BIN) output/server/
	cp $(CLIENT_BIN) output/client/
	cp $(PLUGIN)/ctl_server.sh output/server
	cp -rf $(CONF) output/server

PHONY:clean
clean:
	rm -rf *.o $(SERVER_BIN) $(CLIENT_BIN) output

