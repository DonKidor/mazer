APP_NAME = maze

LIBS     =  -L"src/SFM_2.4.0/lib" -lsfml-graphics -lsfml-window -lsfml-system -m32 -pg -g3

CXXINCS  = -I"src" -I"src/SFM_2.4.0/include"

CPPFLAGS = $(CXXINCS) -m32 -pg -g3 -std=c++11 -MMD
CC = g++.exe -D__DEBUG__
RM = rm.exe

SRC_DIR=src
OBJ_DIR=obj
APP_DIR=bin

APP_PATH=$(APP_DIR)/$(APP_NAME).exe

APP_SOURCES = $(wildcard $(SRC_DIR)/$(APP_NAME)/*.cpp)
APP_OBJECTS = $(APP_SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/$(SRC_DIR)/%.o)

DEPS = $(APP_OBJECTS:.o=.d)

.PHONY: all
all: $(APP_PATH)

-include $(DEPS)

$(APP_PATH) : $(APP_OBJECTS)
	$(CC) $^ -o $@ $(LIBS)

$(OBJ_DIR)/%.o : %.cpp
	$(CC) -c $< -o $@ $(CPPFLAGS)
	
.PHONY: clean
clean:
	$(RM) -rf $(OBJ_DIR)/$(SRC_DIR)/$(APP_NAME)/*.o
	$(RM) -rf $(OBJ_DIR)/$(SRC_DIR)/$(APP_NAME)/*.d
	$(RM) -rf $(APP_DIR)/$(APP_NAME).exe