def remove_duplicates(nums):
    if not nums:
        return 0

    i = 0  
    for j in range(1, len(nums)):  
        if nums[j] != nums[i]: 
            i += 1 
            nums[i] = nums[j]  
    return i + 1  

# use case
nums = [int(x) for x in input("Enter sorted array elements (separate elements using one space): ").split()]
length = remove_duplicates(nums)
print("New length:", length)
print("Modified array:", nums[:length])