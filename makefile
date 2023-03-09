f = -Iinclude
obj = bin/main.exe bin/reporter.exe bin/creator.exe
run: build
	./bin/main.exe
build: $(obj);
bin/%.exe: src/%.cpp
	g++ $(f)  $< -o $@
clean:
	rm bin/*.exe
