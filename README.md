# NandGame-VM

(Very WIP)
Messing around, trying to implement the instruction set from [NandGame](https://www.nandgame.com/).

Note: as with the site, `0x0000` is treated as a "halt" instruction, to set `A = 0` you should instead use `0xe0a0` (`A = 0&A`).

### Plans:
- Read and execute binary input from files
- A mode to step through the VM one instruction at a time
- An assembler for the site's assembly language, that produces runnable bytecode
- Possibly extend with I/O or additional instructions?