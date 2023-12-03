.PHONY: test build

config:
	cmake -B ./build -DCMAKE_BUILD_TYPE=Debug

build: config
	cmake --build ./build --target additionalTask --config Debug

run: build additionalTask
	./additionalTask

test: build additionalTask
	python3 tests.py

clean:
	rm -rf build/
	rm additionalTask
