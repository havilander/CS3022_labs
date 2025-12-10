'''
Author: LT Ethan Haviland

This program inputs a birthday (MM DD YYYY) to find the Fibonacci
Birthday Constant (FBC) = [Fibo(YB[0])Fibo(YB[1])], the Collatz-Fibo
Birthday (CFB) = [Collatz(FBC[0]) Collatz(FBC[1]) Collatz(YB[2]), and
the Pease constant = CFB[0] + CFB[1] + CFB[2].

Extra: Monadic Chaining Operation and Mimic Closure Pattern
'''
# creates a lookup table of Fibonacci numbers
fibo_table = {0:0, 1:1}
collatz_table = {1:0}


def fibo(index):
    # returns the Fibonacci number associated with the input
    if index in fibo_table:
        return fibo_table[index]
    
    fibo_table[index] = fibo(index - 1) + fibo(index - 2)
    return fibo_table[index]
        
def collatz(num):
    # uses recursion and returns the Collatz number associated with the input
    if num in collatz_table:
        return collatz_table[num]
    if num % 2 == 0:
        collatz_table[num] = 1 + collatz(num//2)
        return collatz_table[num]
    else:
        collatz_table[num] = 1 + collatz(3 * num + 1)
        return collatz_table[num]
    
def pease_number(cfb):
    # returns the Pease number for the associated Collatz number
    return cfb[0] + cfb[1] + cfb[2]

# Result class used for Monadic chaining operation
class Result:
    def __init__(self, value=None):
        self.value = value
    
    def bind(self, func):
        return Result(value=func(self.value))
    
    def unwrap(self):
        return self.value

# Closure pattern mimic
def make_fbc_evaluate():
    def evaluate(d):
        return [fibo(d[0]), fibo(d[1])]
    return evaluate

def make_cfb_evaluate():
    def evaluate(fbc):
        return [collatz(fbc[0]), collatz(fbc[1]), collatz(yb[2])]
    return evaluate

def make_pease_evaluate():
    def evaluate(cfb):
        return pease_number(cfb)
    return evaluate

# take inputs from user for birth month number, birth day, and birth year (MM DD YYYY)
month = int(input ("\nInput your birth month number:"))
day   = int(input ("\nInput your birth day:"))
year  = int(input ("\nInput your birth year:"))
yb = [month, day, year]

fbc_evaluate = make_fbc_evaluate()
cfb_evaluate = make_cfb_evaluate()
pease_evaluate = make_pease_evaluate()

result = (
    Result(value=yb)
    .bind(fbc_evaluate)
    .bind(cfb_evaluate)
    .bind(pease_evaluate)
)

print("\nYour Pease Birthday:", result.unwrap())