
build: clean components

# TODO: Use automatic dependency
components: components/DigitalWrite.component components/DigitalRead.component components/Forward.component

components/%.component: components/%.hpp
	./node_modules/.bin/microflo component $<

clean:
	rm components/*.hpp.* || echo 'already clean'
