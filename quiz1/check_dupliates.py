def contains_duplicate(nums):
    seen = set()
    for num in nums:
        if num in seen:
            return True
        seen.add(num)
    return False

# use case
nums = [int(x) for x in input("Enter array elements (separate elements using one space): ").split()]
print("Contains duplicate:", contains_duplicate(nums))