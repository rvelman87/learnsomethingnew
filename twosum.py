def twoSums(nums, target):
    result = {}
    # import pdb; pdb.set_trace()
    for i, num  in enumerate(nums):
        complement = target - num
        if complement in result:
            return [result[complement], i]
        result[num] = i
    return []




print(twoSums([2,7,11,15], 9))
print(twoSums([3,2,4], 6))
print(twoSums([3,3], 6))
