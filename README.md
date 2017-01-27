# SmartFolder

## What is SmartFolder
SmartFolder is a way to search files on your system and group the results. The program will interpret search queries and create a folder with symbolic links to all the found matches. This is based on the concept of [Virtual Folders](https://en.wikipedia.org/wiki/Virtual_folder) and is for example used in a feature called Smart Folder in OS X.

This implementation only runs on Linux, and can be tweaked to work in OS X.

## Usage
### Build
You can build the project from the `src` directory using `make`
### Creation
`./SmartFolder <SmartFolderPath> <SearchDirectory> <Search...>`
### Deletion
`./SmartFolder - <SmartFolderName>`

## Search Specifications

The search should be written in a [RPN format](https://en.wikipedia.org/wiki/Reverse_Polish_notation) to combine multiple search terms with logical operands.

### Search arguments
- `--name <name>`
- `--size [-+]<size>[K/M/G/T]`
- `--dateStatus [-+]<YYYY-MM-DD>`
- `--dateModified [-+]<YYYY-MM-DD>`
- `--dateUsed [-+]<YYYY-MM-DD>`
- `--uid <loginName>`
- `--gid <groupName>`
- `--perms <octal>`

Symbols written in brackets are optional.

### Search operands
- AND / and
- OR / or
- XOR / xor
- NOT / not

## Usage Example
Let's say we want all .c and .h files smaller than 1 MB to be searched from the folder `~/Documents/LauzHackWinners` and referenced in the SmartFolder `~/Desktop/memory_leak`, we would invoke our program with the command

`./SmartFolder ~/Desktop/memory_leak ~/Documents/LauzHackWinners --name .c --name .h or --size -1M and`

Then to delete this SmartFolder, you would use the command

`./SmartFolder -d memory_leak`

## Documentation
Documentation for the code is available [here](https://maximelovino.github.io/SmartFolder/)
