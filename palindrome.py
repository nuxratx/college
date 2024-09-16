'''Create a python script that will check if a particular string is a palindrome or not'''

import argparse

# Set up argument parser
parser = argparse.ArgumentParser(description='Find out if your word is a palindrome or not')
parser.add_argument('-p', '--palindrome', type=str, required=True, help='your string goes here')
args = parser.parse_args()

# Define function to check if a string is a palindrome
def is_palindrome_or_not(palindrome):
    return palindrome == palindrome[::-1]

# Call the function with the provided argument and print the result
result = is_palindrome_or_not(args.palindrome)
print('"{}" is a palindrome: {}'.format(args.palindrome, result))
