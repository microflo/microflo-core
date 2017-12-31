
build: clean runtime

clean:
	rm components/*.component || echo 'already clean'

runtime:
	rm -rf build/tests
	mkdir -p build/tests
	./node_modules/.bin/microflo generate --target linux graph.fbp build/tests/runtime.cpp
	$(CXX) -std=c++0x -o build/tests/runtime build/tests/runtime.cpp -DLINUX -I./node_modules/microflo/microflo -lutil -lrt
