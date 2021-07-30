#!/usr/bin/python

"""
interview bit permutation question or 
leetcode 438 """

class solution:
    def __init__(self, r1, r2):
        self.output = []
        self.number = int (r1)
        self.string = r2

    def printelements(self):
        print(self.number)
        print(self.string)
        print(type(self.number))
        print(type(self.string))

    def constraint(self):
        if((self.number - len(self.string)) == 1):
            print("Entered valid string and number")
            print(f"Number of elements is n = {self.number}")
            print(f"Input string {self.string}")
        else:
            print("Please enter number of size 1 greater than length of string")
            exit()
        if(len(self.string) != self.string.count('I') + self.string.count('D')):
            print("Pattern not matching")
            exit()
    def solve(self):
        gen = list (range(1, self.number +1))
        res = []
        #print("elements",gen)
        for i in self.string:
            if i == 'I':
                res.append(min(gen))
                gen.remove(min(gen))
            elif i == 'D':
                res.append(max(gen))
                gen.remove(max(gen))

        res.extend(gen)
        return res    

r1,r2 = input("Enter the number and string  :").split() #getting multiple input in python
s1 = solution(r1,r2)
s1.constraint()
s1.printelements()
s1.solve()
print("Output ",s1.solve())
