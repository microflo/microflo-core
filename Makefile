
COMPONENT_SOURCES=$(shell find ./components -name *.hpp)
COMPONENT_TARGETS=$(COMPONENT_SOURCES:%.hpp=%.component)

build: clean components

# TODO: Use automatic dependency
components: $(COMPONENT_TARGETS)

components/%.component: components/%.hpp
	./node_modules/.bin/microflo component $<

clean:
	rm components/*.component || echo 'already clean'
