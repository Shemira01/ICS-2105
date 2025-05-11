def summation(arr):
    return sum(arr)

def maximum(arr):
    if len(arr) == 0:
        return None  
    return max(arr)

def main():
    # Get the length of the array from  user
    n = int(input("Enter the number of integers (n): "))
    
    # Declare an array of length n
    arr = []
    
    # User enters the array elements
    for i in range(n):
        num = int(input(f"Enter integer {i + 1}: "))
        arr.append(num)
    
    total_sum = summation(arr)
    print(f"The sum of the integers is: {total_sum}")
    
    max_value = maximum(arr)
    print(f"The maximum integer is: {max_value}")

if __name__ == "__main__":
    main()
