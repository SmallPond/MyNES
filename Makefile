CC = g++ 


INC = ./include
SFML_INC = /usr/local/Cellar/sfml/2.5.1/include
SRC = ./src
OBJ = ./build

CFLAGS = -g -Wall -I${INC} -I${SFML_INC} -std=c++11 
LDFLAGS = -L/usr/local/Cellar/sfml/2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system
# 扩展通配符，不要在$(后加空格，否则无法解析



SOURCES = $(wildcard ${SRC}/*.cpp)

# SOURCES += ${MAIN_FILE}
# $(info $(SOURCES))



# patsubset 匹配的样式， 匹配的目标， 需要匹配的文件
OBJS = $(patsubst %.cpp,${OBJ}/%.o,$(notdir ${SOURCES}))

# $(info $(OBJS))
TARGET = myNES

# 所有的中间文件生成目标文件
# $@目标文件 $^所有依赖文件 $< 第一个依赖文件
# 血的教训：$(LDFLAGS)一定要放到最后，不然在Ubuntu会链接报错
${TARGET}: ${OBJS}
	$(CC)  ${OBJS} -o $@   $(LDFLAGS)

#生成中间文件
${OBJ}/%.o:${SRC}/%.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY:clean

clean:
	find $(OBJ) -name *.o -exec rm -rf {} \;
	# rm -rf main.o
	rm -rf ${TARGET}


