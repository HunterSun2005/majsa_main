.PHONY: all run binary clean submit git gdb

all: majsa

majsa: git
	gcc -g -O2 $(shell find ./src -name *.c) -I. -Wall -Wextra -o majsa

run: majsa
	./majsa

gdb: majsa
	gdb majsa

git:
	git add -A
	git commit --allow-empty -m "compile"

clean:
	@rm majsa

submit:
	$(eval TEMP := $(shell mktemp -d))
	$(eval BASE := $(shell basename $(CURDIR)))
	$(eval FILE := ${TEMP}/${TOKEN}.zip)
	@cd .. && zip -qr ${FILE} ${BASE}/* ${BASE}/.git
	@echo "Created submission archive ${FILE}"
	@curl -m 5 -w "\n" -X POST -F "TOKEN=${TOKEN}" -F "FILE=@${FILE}" \
		https://oj.cpl.icu/api/v2/submission/lab
	@rm -r ${TEMP}
