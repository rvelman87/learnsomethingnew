#!/bin/python3

import math
import os
import random
import re
import sys

def process(matrix, n, m):
    if not matrix:
        return ""
    line = ""
    for j in range(0,m):
        for i in range (0, n):
            # print("i=", i, "j=", j, matrix[i][j])
            line +=matrix[i][j]
            #     line +=matrix[i][j]
    newline = ""
    for i, value in enumerate(line):
        chars  = re.search("[A-Za-z0-9]", line[i:])
        if chars:
            # print(chars.span()[0], line[i])
            if chars.span()[0] != 0 and value !=" ":
                newline += " "
            else:
                newline += value
            newline = newline.replace("  ", " ")
        else:
            newline += value
            #line[i] = ' ' if chars.span()[0] !=0 else line[i] 
    
    print(newline)

first_multiple_input = input().rstrip().split()

n = int(first_multiple_input[0])

m = int(first_multiple_input[1])

matrix = []

for _ in range(n):
    matrix_item = input()
    matrix.append(matrix_item)

process(matrix, n, m)

#print("Contents" ,matrix)
