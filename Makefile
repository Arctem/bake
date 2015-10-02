
all: CMakeLists.txt
	mkdir -p build; \
	cd build; \
	cmake ..; \
	make;

clean:
	rm -rf build
	rm -f bake
