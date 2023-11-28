.PHONY: test build

config:
	cmake -B ./build -DCMAKE_BUILD_TYPE=Debug

build: config
	cmake --build ./build --target task5 --config Debug

run: build build/task5
	clear && build/task5

test: build build/task5
	valgrind --version || "valgrind not installed"
	valgrind \
		--leak-check=full \
		--show-leak-kinds=all \
		--error-exitcode=1 \
		--show-error-list=yes \
		./build/task5

clean:
	rm -rf build/
