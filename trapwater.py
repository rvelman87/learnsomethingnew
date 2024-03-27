def twoPointers(array): #o(n)

    #check the start and end indexes are within limit
    # assuming they are

    left = 0
    right = len(array) -1
    print("right" , right)
    maximum = 0
    while (left < right):
        area = min(array[left], array[right]) * (right - left)
        maximum  = max (area, maximum)
        if (array[left] > array [right]):
            right -= 1
        else:
            left += 1
    return maximum

def brute_force(array, start, end):

    #check the start and end indexes are within limit
    # assuming they are

    first = array[start]
    last = array[end]

    return min(first, last ) * (end-start)

def max_area(array):
    if not array or len(array) == 1:
        return 0
    maximum = 0
    for i in range(len(array)): # N times
        for j in range(i+1, len(array)): # n times ==> N^2 , space o(1)
            result = brute_force(array, i, j)
            # print("loop i=", i, " j=", j, "result =", result)
            maximum = max(result, maximum) if result else 0
            # print("max = ", maximum)
    return maximum
print("area between index 0 and 1 ", brute_force([5,9,2,1,4], 0, 1))
print("area between index 0 and 0 ", brute_force([5,9,2,1,4], 0, 0))
print("area between index 0 and 4 ", brute_force([5,9,2,1,4], 0, 4))

print("max area brute force ", max_area([5,9,2,1,4]))
print("max area two pointers ", twoPointers([5,9,2,1,4]))
