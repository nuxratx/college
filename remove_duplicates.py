#In this program I will use different methods to remove duplictes from a list 
#Sort then duplicate 

import pandas as pd 


sample_list = [1, 5, 3, 6, 3, 5, 6, 1, 2,7,7,9,0,0,11,-5,-3]
#sample_list_sorted = sorted(sample_list)

#print(sample_list_sorted)

def remove_set(sample_list):
    final_list = list(set(sample_list))

    return sorted(final_list)

print(remove_set(sample_list))



def remove_duplicates(sample_list):
    df= pd.DataFrame({'col': sample_list})
    df.drop_duplicates(inplace=True)
    removed_dup = df['col'].tolist()

    return sorted(removed_dup)

print(remove_duplicates(sample_list))








#print_list(remove_naive(sample_list))
#print_list(remove_conds(sample_list))
#print_list(remove_set(sample_list))
#print_list(remove_enum(sample_list))
#print_list(remove_coll(sample_list)) 

#uses OrderedDict

#output expected

#[-5, -3, 0, 1, 2, 3, 5, 6, 7, 9, 11]
#[-5, -3, 0, 1, 2, 3, 5, 6, 7, 9, 11]
#[-5, -3, 0, 1, 2, 3, 5, 6, 7, 9, 11]
#[-5, -3, 0, 1, 2, 3, 5, 6, 7, 9, 11]
#[-5, -3, 0, 1, 2, 3, 5, 6, 7, 9, 11]