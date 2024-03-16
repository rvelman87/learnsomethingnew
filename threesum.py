def threeSum(nums, target) -> list[list[int]]:
    result = []
    nums.sort()
    for idx, num in enumerate(nums):
        if idx > 0 and num == nums[idx-1]:
            continue
        left = idx + 1
        right = len(nums)-1

        while(left < right):

            sum = nums[idx] + nums[left] + nums[right]
            if (sum > target):
                right = right -1
            elif (sum < target):
                left = left + 1
            else:
                result.append([nums[idx], nums[left],nums[right]])
                left = left +1
                while nums[left] == nums[left -1] and left < right:
                    left = left +1
    return result



print(threeSum([0,1,1], 0))
print(threeSum([-1,0,1,2,-1,-4], 0))
print(threeSum([0,0,0], 0))
