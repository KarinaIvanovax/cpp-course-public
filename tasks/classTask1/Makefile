.PHONY: test build

config:
	cmake -B ./build -DCMAKE_BUILD_TYPE=Debug

build: config
	cmake --build ./build --target classTask1 --config Debug

run: build classTask1
	./classTask1

test: build classTask1
	python3 tests.py

clean:
	rm -rf build/
	rm classTask1
