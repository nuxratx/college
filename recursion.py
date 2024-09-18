#Without using the max() function in python, create a function that returns the max value using:
#recursion
#a pivot that splits the list in half

#given a string of number 
lst = input("Enter a list of positive number separated by comas : ").split(",")
print(lst)

def split_input(user_input):
    half = len(user_input)//2
    return user_input [:half], user_input[half:]

def maximum_num(a):
    if not a:
        return -1

    if len(a) == 1:
        return a[0]
    
    if len(a) == 2:
        b = a[0]
        c = a[1]
    else:
        x,y=split_input(a)
        b = maximum_num(x)
        c = maximum_num(y)

    return b if b > c else c

print(maximum_num(lst))