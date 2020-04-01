ifeq ($(OS),Windows_NT)     # is Windows_NT on XP, 2000, 7, Vista, 10...
    TARGET = strptime-core.dll
else
    TARGET = strptime-core.so
endif

${TARGET}: strptime-core.c
	cc -shared -fpic strptime-core.c -o ${TARGET}
