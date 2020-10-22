CC = g++ 


INC = ./include
SRC = ./src
OBJ = ./build

CFLAGS = -g -Wall -I${INC} -std=c++11 

# 扩展通配符，不要在$(后加空格，否则无法解析



SOURCES = $(wildcard ${SRC}/*.cpp)
MAIN_FILE = ./main.cpp
SOURCES += ${MAIN_FILE}
$(info $(SOURCES))



# patsubset 匹配的样式， 匹配的目标， 需要匹配的文件
OBJS = $(patsubst %.cpp,${OBJ}/%.o,$(notdir ${SOURCES}))

$(info $(OBJS))
TARGET = myNES

# 所有的中间文件生成目标文件
# $@目标文件 $^所有依赖文件 $< 第一个依赖文件
${TARGET}: ${OBJS}
	$(CC) ${OBJS} -o $@  

#生成中间文件

${OBJ}/%.o:${SRC}/%.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY:clean

clean:
	find $(OBJ) -name *.o -exec rm -rf {} \;
	rm -rf main.o


