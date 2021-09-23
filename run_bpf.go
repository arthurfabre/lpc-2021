package main

import (
	"bytes"
	"fmt"
	"io"
	"io/ioutil"
	"os"

	"github.com/cilium/ebpf"
)

func main() {
	ret, err := run(os.Stdin)
	if err != nil {
		fmt.Fprintln(os.Stderr, "Error:", err)
		os.Exit(-1)
	}
	fmt.Println(ret)
}

func run(r io.Reader) (uint32, error) {
	elf, err := ioutil.ReadAll(r)
	if err != nil {
		return 0, err
	}

	spec, err := ebpf.LoadCollectionSpecFromReader(bytes.NewReader(elf))
	if err != nil {
		return 0, err
	}

	progSpec, ok := spec.Programs["xdp_filter"]
	if !ok {
		return 0, fmt.Errorf("missing program \"test\"")
	}

	prog, err := ebpf.NewProgramWithOptions(progSpec, ebpf.ProgramOptions{
		LogLevel: 3,
	})
	if err != nil {
		return 0, err
	}

	ret, _, err := prog.Test([]byte{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14})
	return ret, err
}
