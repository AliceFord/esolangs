import sys

def get_exit_bracket(program, currentIndex):  # Find matching closing bracket
    n = 1
    for i in range(currentIndex + 1, len(program)):
        if program[i] == '[':
            n += 1
        elif program[i] == ']':
            n -= 1
        if n == 0:
            return i

def get_entry_bracket(program, currentIndex):
    n = 1
    for i in range(currentIndex - 1, -1, -1):
        if program[i] == ']':
            n += 1
        elif program[i] == '[':
            n -= 1
        if n == 0:
            return i


def brainfk_encode(code, index, program):
    if code == '>':
        return "T R 1"  
    elif code == '<':
        return "T L 1" 
    elif code == '+':
        return "T A 1"  
    elif code == '-':
        return "T D 1"  
    elif code == '.':
        return "O C T"
    elif code == ',':
        return "I C T"
    elif code == '[':
        return f"? (T=0) {get_exit_bracket(program, index + 1) + 1}"
    elif code == ']':
        return f"J {get_entry_bracket(program, index) + 1}"
    else:
        return ""

def main(args):
    output = []

    filename = args[1]
    with open(filename, 'r') as f:
        program = list(f.read())
    
    output.append("TAPE")

    for i, line in enumerate(program):
        output.append(brainfk_encode(line, i, program))

    with open("Brainfk_output.txt", 'w') as f:
        f.write("\n".join(output))

if __name__ == '__main__':
    main(sys.argv)