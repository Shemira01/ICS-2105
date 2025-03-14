def rotate_array(nums, k):
    n = len(nums)
    k = k % n  

    nums.reverse()

    nums[:k] = reversed(nums[:k])

    nums[k:] = reversed(nums[k:])

#use case
nums = [int(x) for x in input("Enter array elements (separate elements using one space): ").split()]
k = int(input("Enter the number of steps to rotate (k): "))

rotate_array(nums, k)
print("Rotated array:", nums)