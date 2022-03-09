# Stolen from https://stackoverflow.com/questions/43110398/what-is-the-most-efficient-way-to-represent-the-infinite-tape-of-a-turing-machin
# GrowingList modified by copilot

class GrowingList(list):
    def __getitem__(self, index):
        if index >= len(self):
            self.extend([0]*(index + 1 - len(self)))
        return list.__getitem__(self, index)

    def __setitem__(self, index, value):
        if index >= len(self):
            self.extend([0]*(index + 1 - len(self)))
        list.__setitem__(self, index, value)

class Tape:
    def __init__(self):
        self.pos_range=GrowingList()
        self.neg_range=GrowingList()

    def __getitem__(self, i):
        if i >= 0:
            return self.pos_range[i]
        else:
            return self.neg_range[-i-1]

    def __setitem__(self, i, v):
        if i >= 0:
            self.pos_range[i]=v
        else:
            self.neg_range[-i-1]=v

    def __repr__(self):
        start = -len(self.neg_range)
        end = len(self.pos_range)
        data = list(reversed(self.neg_range)) + self.pos_range
        return "Tape(range=[{}, {}), data={})".format(start, end, data)
