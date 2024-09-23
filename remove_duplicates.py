'''Often working with a duplicate list of things can be annoying, 
sometimes I want to only find the unique list. 
This program explores different methods to remove duplictes from a list,
this is my 4th python lab in my master's program'''


import pandas as pd 

#Initializing a list 
sample_list = [1, 5, 3, 6, 3, 5, 6, 1, 2,7,7,9,0,0,11,-5,-3]


#Function one using set method to remove duplicates values 
def remove_set(sample_list):
    final_list = list(set(sample_list))

    return sorted(final_list)

print(remove_set(sample_list))


#Function two using pandas library from python 
def remove_duplicates(sample_list):
    df= pd.DataFrame({'col': sample_list})
    df.drop_duplicates(inplace=True)
    removed_dup = df['col'].tolist()

    return sorted(removed_dup)

print(remove_duplicates(sample_list))

#Function three using list comprehension to remove duplicates 
def remove_dup(sample_list):
    #creating an empty list 
    res = []
    [res.append(x) for x in sample_list if x not in res]

    return sorted(res)

print(remove_dup(sample_list))



#Epected Outpput 
#[-5, -3, 0, 1, 2, 3, 5, 6, 7, 9, 11]
#[-5, -3, 0, 1, 2, 3, 5, 6, 7, 9, 11]
#[-5, -3, 0, 1, 2, 3, 5, 6, 7, 9, 11]





