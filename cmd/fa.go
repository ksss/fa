package main

import (
	"flag"
	"fmt"
	"os"

	"github.com/ksss/fa"
)

var list = flag.Bool("list", false, "show all id")

func main() {
	flag.Parse()
	if *list {
		for _, icon := range fa.List {
			fmt.Println(icon.Id)
		}
		os.Exit(0)
	}
	if len(os.Args) < 1 {
		fmt.Print("fa [font-awesome id] (e.g. fa github)")
		return
	}
	for _, icon := range fa.List {
		if icon.Id == os.Args[1] {
			fmt.Print(icon.Unicode)
			os.Exit(0)
		}
	}
	// not found
	os.Exit(1)
}
