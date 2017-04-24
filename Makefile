
COMPONENT_SOURCES=$(shell find ./components -name *.hpp)
COMPONENT_TARGETS=$(COMPONENT_SOURCES:%.hpp=%.component)

build: clean components runtime

# TODO: Use automatic dependency
components:
	echo '.component generation disabled'

components/%.component: components/%.hpp
	./node_modules/.bin/microflo component $<

clean:
	rm components/*.component || echo 'already clean'

runtime:
	rm -rf build/tests
	mkdir -p build/tests
	./node_modules/.bin/microflo generate --target linux --library ./components/linux-standard.json graph.fbp build/tests/runtime.cpp
	$(CXX) -std=c++0x -o build/tests/runtime build/tests/runtime.cpp -DLINUX -I./node_modules/microflo/microflo -lutil -lrt
