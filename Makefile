troll:
	g++ -Wall -g -o ./Bin/a.exe $(wildcard *.c) -ID:/_Code/include/ -LD:/_Code/ -lglew32 -lglfw3 -lopengl32
	xcopy .\Lib .\Bin /c /y
	xcopy .\Resources .\Bin /c /y
	./bin/a.exe
