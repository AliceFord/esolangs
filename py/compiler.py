import sys
from util_eso import Tape
import re

def tape_add(tape, ptr, value):
    tape[ptr] = tape[ptr] + value

def main(args):
    filename = args[1]
    with open(filename, 'r') as f:
        program = f.read().split("\n")
    
    programArgs = {}
    programOffset = 0

    ir = 0
    while (ir < len(program)):
        line = program[ir]

        commands = line.split(" ")
        
        if commands[0] == "TAPE":
            programArgs['T'] = Tape()
            programArgs['T_ptr'] = 0
            programOffset += 1
        
        if commands[0] == 'T':
            if commands[1] == 'R':
                programArgs['T_ptr'] += int(commands[2])
            elif commands[1] == 'L':
                programArgs['T_ptr'] -= int(commands[2])
            elif commands[1] == 'A':
                tape_add(programArgs['T'], programArgs['T_ptr'], int(commands[2]))
            elif commands[1] == 'D':
                tape_add(programArgs['T'], programArgs['T_ptr'], -int(commands[2]))
        elif commands[0] == 'O':
            if commands[1] == 'C':
                print(chr(programArgs['T'][programArgs['T_ptr']]), end="")
        elif commands[0] == 'I':
            if commands[1] == 'C':
                programArgs['T'][programArgs['T_ptr']] = ord(input())
        elif commands[0] == 'J':
            ir = programOffset + int(commands[1]) - 2
        elif commands[0] == '?':
            comparative = commands[1].replace("(", "").replace(")", "")
            match = re.match(r'([A-Za-z])([!<>=]*)([0-9]*)', comparative)
            if match[1] == 'T':
                if match[2] == '=':
                    if programArgs['T'][programArgs['T_ptr']] == int(match[3]):
                        ir = programOffset + int(commands[2]) - 1
                elif match[2] == '!=':
                    if programArgs['T'][programArgs['T_ptr']] != int(match[3]):
                        ir = programOffset + int(commands[2]) - 1
                
        
        ir += 1
        
        
    print("\n", programArgs, sep='')

if __name__ == '__main__':
    main(sys.argv)