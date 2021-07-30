!/usr/bin/python

class Stack:
    def __init__(self, capacity):
        self.capacity = capacity
        self.top  = -1
        self.elements = []

    def push (self, value):
        if(self.top == self.capacity):
            print("Stack Overflow")
            return
        else:
            self.top = self.top +1
            self.elements.append(value)

    def display(self):
        if(self.top == -1):
            print("Stack Underflow")
        else:
            print(self.elements[self.top])

    def pop(self):
        if(self.top == -1):
            print("Stack Underflow")
        else:
            print(self.elements[self.top])
            self.top = self.top -1

s1 = Stack(5)
s1.display()
s1.pop()
s1.push(1)
s1.display()
s1.push(2)
s1.display()
s1.push(3)
s1.push(4)
s1.push(5)
s1.display()
