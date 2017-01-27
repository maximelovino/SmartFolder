# SmartFolder

## What is SmartFolder
SmartFolder is a way to search files on you system and group the results. The program will interpret search queries and create a folder with symbolic links to all the found matches

## Usage
`./SmartFolder <SmartFolder> <SearchDirectory> <Search...>`

## Search Specifications

The search should be written in a [RPN format](https://en.wikipedia.org/wiki/Reverse_Polish_notation) 

### Search arguments
- `--name <name>`
- `--size [-+]<size>[K/M/G/T]`
- `--dateStatus [-+]<YYYY-MM-DD>`
- `--dateModified [-+]<YYYY-MM-DD>`
- `--dateUsed [-+]<YYYY-MM-DD>`
- `--uid <loginName>`
- `--gid <groupName>`
- `--perms <octal>`

### Search operands
- AND / and
- OR / or
- XOR / xor
- NOT / not

## Usage Example
Let's say we want all .c and .h files smaller than 1 MB to be searched from the folder `~/Documents/LauzHackWinners` in the SmartFolder `~/memory_leak`

`./SmartFolder ~/memory_leak ~/Documents/LauzHackWinners --name .c --name .h or --size -1M and`
