.PHONY: clean build all
build:
	mkdir -p build
	cmake -B`pwd`/build -H`pwd`

all: build
	+make -C build

clean:
	rm -rf build/*
