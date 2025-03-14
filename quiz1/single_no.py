def single_number(nums):
    result = 0
    for num in nums:
        result ^= num
    return result

#Example case
nums = [int(x) for x in input("Enter array elements (separate elements using one space): ").split()]
print("Single number:", single_number(nums))