CC=clang

default: build
.PHONY: default

gen-list:
	ruby fa-gen-list.rb > fa-icon-list.h
.PHONY: gen-list

build:
	mkdir -p build
	CC fa.c -o build/fa
.PHONY: build

test:
	ruby test/fa.rb
.PHONY: test

all: gen-list build test
.PHONY: all
