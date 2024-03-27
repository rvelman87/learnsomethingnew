def ismountain(array): # Time o(n), space no extra mem, so o(1)
    i = 1
    print("len of array", len(array))
    while (i<len(array) and array[i] > array[i-1]) :
        print("i =", i)
        i +=1
    if (i==1 or i==len(array)): #make sure, list has at least 3 elements
        return False
    while (i<len(array) and array[i] < array[i-1]):
        print("d i =", i)
        i +=1
    return i == len(array)

# print(ismountain([0,2,3,4,5,2,1]))
# print(ismountain([0,2,3]))
print(ismountain([0]))
# print(ismountain([0,2,3,1]))
