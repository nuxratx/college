import string
import numpy


upper = string.ascii_uppercase 
lower = string.ascii_lowercase


text = input("Enter a message: ")
num = int(input ("Enter a positive number: "))


def encryption(text,num):
    cipher = ""
    shift_upper = numpy.roll(list(upper), num)
    shift_lower = numpy.roll(list(lower), num)
    #If input string and integer is given then return the exact ciphertext as outpput 
    for character in text:
        if character in upper:
            cipher += shift_upper[upper.index(character)]
        elif character in lower:
            cipher += shift_lower[lower.index(character)]
        else:
            cipher += character
    return cipher

def decryption(text,num):
    plain = ""
    shift_upper = list(numpy.roll(list(upper), num))
    shift_lower = list(numpy.roll(list(lower), num))
    #If input string and integer is given then return the exact ciphertext as outpput 
    for character in text:
        if character in upper:
            plain += upper[shift_upper.index(character)]
        elif character in lower:
            plain += lower[shift_lower.index(character)]
        else:
            plain += character
    return plain

    #This function will take the output and encryption 
    # key of the above encryption function and decode the message to give out the original plain text


print(decryption(encryption(text,num), num))