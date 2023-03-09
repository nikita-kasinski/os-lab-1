f = -Iinclude
obj = bin/Main.exe bin/Reporter.exe bin/Creator.exe
run: build
	./bin/Main.exe
build: $(obj);
bin/%.exe: src/%.cpp
	g++ $(f)  $< -o $@
clean:
	rm bin/*.exe
