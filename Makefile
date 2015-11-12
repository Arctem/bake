all: CMakeLists.txt lib/googletest-release-1.7.0
	mkdir -p build
	cd build &&\
	cmake -GNinja .. &&\
	ninja


test: all
	cd build && ninja test


lib/googletest-release-1.7.0: release-1.7.0.zip
	mkdir -p lib
	unzip release-1.7.0 -d lib/
	touch lib/CMakeLists.txt
	cd lib/googletest-release-1.7.0 && cmake -GNinja . && ninja

release-1.7.0.zip:
	wget https://github.com/google/googletest/archive/release-1.7.0.zip

clean:
	rm -rf build
	rm -rf bin
	rm -f bake
	rm -rf lib/googletest-release-1.7.0
	rm -f release-1.7.0.zip
