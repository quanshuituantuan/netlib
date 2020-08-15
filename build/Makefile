.PHONY: clean ut build 

INCLUDES =-I../include
CXXFLAGS=-std=c++11 -Wall -Werror
LD_LIBRARIES=-lpthread -lgtest

SRC_DIR=../src
TST_DIR=../tst
INC_DIR=../include
SERVER_DIR=../src/server
EXAMPLE_DIR=../example
PROTOBUF_DIR=../protobuf

EXE=libnetlib.a
EXAMPLE=example
TEST=test
CXX=g++
PROTOC=protoc

PROTO_FILE=$(wildcard $(PROTOBUF_DIR)/*.proto)
PROTO_SRC=$(patsubst %.proto, %.pb.cc, $(PROTO_FILE))
PROTO_INC=$(patsubst %.proto, %.pb.h, $(PROTO_FILE))
PROTO_OBJ=
#PROTO_OBJ=$(patsubst %.cc, %.o, $(PROTO_SRC))

CPP_SRC=$(wildcard $(SRC_DIR)/*.cpp)
SRC_OBJ=$(patsubst %.cpp, %.o, $(CPP_SRC))

EXAMPLE_SRC=$(wildcard $(EXAMPLE_DIR)/*.cpp)
EXAMPLE_OBJ=$(patsubst %.cpp, %.o, $(EXAMPLE_SRC))

TST_SRC=$(wildcard $(TST_DIR)/*.cpp) 
TST_OBJ=$(patsubst %.cpp, %.o, $(TST_SRC)) 
TST_SRC+=$(PROTO_OBJ)

all: build ut

build: $(EXE) $(EXAMPLE)
$(EXE):$(PROTO_OBJ) $(SRC_OBJ)
	#$(CXX) -shared $(PROTO_OBJ) $(SRC_OBJ) $(LD_LIBRARIES) $(INCLUDES) -o $@
	ar rcs $@ $^

$(EXAMPLE): $(PROTO_OBJ) $(EXAMPLE_OBJ) 
	@echo $(EXAMPLE_SRC)
	@echo $(EXAMPLE_OBJ)
	#$(CXX) $(PROTO_OBJ) $(LD_LIBRARIES) $(INCLUDES)  ../example/Client.o -lnetlib -o client
	#$(CXX) $(PROTO_OBJ) $(LD_LIBRARIES) $(INCLUDES)  ../example/listener.o -lnetlib -o listener
	#$(CXX) $(PROTO_OBJ) $(LD_LIBRARIES) $(INCLUDES)  ../example/server.o -lnetlib -o server
	#$(CXX) $(EXAMPLE_OBJ) $(PROTO_OBJ) $(LD_LIBRARIES) $(INCLUDES) -lnetlib -o $@
#	./$(EXAMPLE)
	
ut: $(TEST)
$(TEST): $(TST_OBJ)
	@echo $(TST_SRC)
	$(CXX) $(TST_OBJ) $(LD_LIBRARIES) $(INCLUDES) $(EXE) -o $@
	./$(TEST)

install: 
	cp $(EXE) /usr/local/lib
		
%.o:%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<
%.pb.o: %.pb.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES)  -c -o $@ $<
%.pb.cc: $(PROTO_FILE)
	$(PROTOC) --proto_path=$(PROTOBUF_DIR) $(PROTO_FILE) --cpp_out=$(PROTOBUF_DIR)

clean:
	rm $(EXE) $(EXAMPLE) $(TEST) $(SRC_OBJ) $(EXAMPLE_OBJ) $(PROTO_OBJ) $(TST_OBJ) ./html -fr
	rm -fr $(PROTO_SRC)
	rm -fr $(PROTO_INC)
	rm -fr core
	rm -fr client 
	rm -fr listener server

DOXYINPUT := Doxyfile $(shell find $$(awk -F= '/^[[:space:]]*INPUT[[:space:]]*=/ { print $$2 }' < Doxyfile) -maxdepth 1 -name '*.[ch]')

#doc: html/index.html
#
#html/index.html: $(DOXYINPUT) 
#	doxygen

doc:
	doxygen Doxyfile
		
