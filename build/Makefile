SRC_DIR=../src
TST_DIR=../tst
INC_DIR=../include
SERVER_DIR=../src/server
EXAMPLE_DIR=../example
COMMON_DIR=../src/common
PROTOBUF_DIR=../protobuf

EXE=libnetlib.so
EXAMPLE=example
TEST=test
CXX=g++
PROTOC=protoc

PROTO_FILE=$(wildcard $(PROTOBUF_DIR)/*.proto)
PROTO_SRC=$(patsubst %.proto, %.pb.cc, $(PROTO_FILE))
PROTO_INC=$(patsubst %.proto, %.pb.h, $(PROTO_FILE))
PROTO_OBJ=$(patsubst %.cc, %.o, $(PROTO_SRC))

CPP_SRC=$(wildcard $(SRC_DIR)/*.cpp)
SRC_OBJ=$(patsubst %.cpp, %.o, $(CPP_SRC))

EXAMPLE_SRC=$(wildcard $(EXAMPLE_DIR)/*.cpp)
EXAMPLE_OBJ=$(patsubst %.cpp, %.o, $(EXAMPLE_SRC))

COMMON_SRC=$(wildcard $(COMMON_DIR)/*.cpp)
COMMON_OBJ=$(patsubst %.cpp, %.o, $(COMMON_SRC))

TST_SRC=$(wildcard $(TST_DIR)/*.cpp) 
#TST_SRC+=$(filter-out ../src/main.cpp, $(CPP_SRC)) 
TST_OBJ=$(patsubst %.cpp, %.o, $(TST_SRC)) 
TST_SRC+=$(COMMON_OBJ)
TST_SRC+=$(PROTO_OBJ)

INCLUDES =-I. -I../ -I../include -I../src -I../include/common -I../example
CXXFLAGS=-fPIC -g -std=c++11 -Wall -Werror
LD_LIBRARIES=-lpthread -lgtest -lgmock -L/opt/nokia/lib64  -lprotobuf -L. 
DOXYINPUT := Doxyfile $(shell find $$(awk -F= '/^[[:space:]]*INPUT[[:space:]]*=/ { print $$2 }' < Doxyfile) -maxdepth 1 -name '*.[ch]')
all: build install ut

build: $(EXE) $(EXAMPLE)
$(EXE):$(PROTO_OBJ) $(SRC_OBJ) $(COMMON_OBJ)
	@echo $(CPP_SRC)
	@echo $(PROTO_FILE)
	@echo $(PROTO_SRC)
	@echo $(PROTO_OBJ)
	$(CXX) -shared $(PROTO_OBJ) $(SRC_OBJ) $(COMMON_OBJ) $(LD_LIBRARIES) $(INCLUDES) -o $@


$(EXAMPLE): $(PROTO_OBJ) $(EXAMPLE_OBJ) $(COMMON_OBJ)
	@echo $(EXAMPLE_SRC)
	@echo $(EXAMPLE_OBJ)
	$(CXX) $(PROTO_OBJ) $(LD_LIBRARIES) $(INCLUDES)  ../example/Client.o -lnetlib -o client
	$(CXX) $(PROTO_OBJ) $(LD_LIBRARIES) $(INCLUDES)  ../example/listener.o -lnetlib -o listener
	$(CXX) $(PROTO_OBJ) $(LD_LIBRARIES) $(INCLUDES)  ../example/server.o -lnetlib -o server
#	$(CXX) $(EXAMPLE_OBJ) $(PROTO_OBJ) $(COMMON_OBJ) $(LD_LIBRARIES) $(INCLUDES) -lnetlib -o $@
#	./$(EXAMPLE)
	
ut: $(TEST)
$(TEST): $(TST_OBJ)
	@echo $(TST_SRC)
	$(CXX) $(TST_OBJ) $(LD_LIBRARIES) $(INCLUDES) -L../build -lnetlib -o $@
	./$(TEST)

install: 
	cp $(EXE) /usr/local/lib
#	ldconfig -v
		
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
	
#doc: html/index.html
#
#html/index.html: $(DOXYINPUT) 
#	doxygen

doc:
	doxygen Doxyfile
		
.PHONY: clean ut build 