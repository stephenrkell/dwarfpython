import buffer

def main():
    """
        Test functions and properties of Buffers.

        The expected output is:
        Hello 5
        World
    """
    a = buffer.Buffer()
    a.bputs("Hello")
    print a.string, a.used
    a.string = "world"
    a.putb()

main()
