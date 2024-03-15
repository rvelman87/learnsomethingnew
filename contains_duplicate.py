def containsduplicate(nums):
    result = set()
    for i in nums:
        if i in result:
            return True
        result.add(i)
    return False

print(containsduplicate( [1,2,3,1]))
print(containsduplicate( [1,2,3,4]))
print(containsduplicate( [1,1,1,3,3,4,3,2,4,2]))
