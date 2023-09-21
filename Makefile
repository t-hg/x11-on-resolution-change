BIN=x11-on-resolution-change
INSTALL_DIR=/usr/local/bin


.PHONY: default
default:
	@echo "Please specify target:"
	@echo "  build"
	@echo "  install"
	@echo "  uninstall"
	@echo "  clean"


.PHONY: build
build:
	clang -Wall -o $(BIN) -lX11 main.c


.PHONY: install
install:
	mv $(BIN) $(INSTALL_DIR)


.PHONY: uninstall
uninstall:
	rm -f $(INSTALL_DIR)/$(BIN)


.PHONY: clean
clean:
	rm -f $(BIN)
