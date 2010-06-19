import _buffer

def Buffer():
    """
        Slight hack, noticing that all buffer methods take
        a buffer as the first argument, just like a class.
    """
    a = _buffer.new_buffer()
    a.__class__ = _buffer
    return a
