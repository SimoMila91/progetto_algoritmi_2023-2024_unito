BIN_SRC_PRIORITY = ex3
BIN_SRC_GRAPH = ex4
BIN_DIR = classes


graph:
	javac -d $(BIN_DIR) src/$(BIN_SRC_PRIORITY)/*.java src/$(BIN_SRC_GRAPH)/*.java

run:
	java -cp $(BIN_DIR) ex3_4/src/ex4/Prim $(FILE)


clean:
	rm -f $(BIN_DIR)/*