''' 
	For functions or data structures not provided in
	the Python language we can 'import' that functionality.
	These imports may be from ourselves, or other users who
	are sharing their libraries of code.
'''
import random
# In this example we can generate any random
# number between 1 and 10
random_number = random.uniform(1,10)
print(random_number)
# Note: It's okay to re-assign variables
# 		  This time, we just pick a random integer value
random_number = random.randint(1,10)
print(random_number)

# More features of the 'random' library
# Try typing: 'help(random)' or 'dir(random)'
# for more ideas
pick_a_value = random.choice([1,3,5,7,9])
print(pick_a_value)

# Now you've seen numbers between []'s a few times.
# This is known as a fundamental data structure known
# as a 'list' in Python.
myList = list()
myList.append(1)
myList.append(2)
myList.append(3)
print(myList)
# or alternatively, you can directly assign the list.
myList = [1,2,3]

# Here are some other operations on lists
aList = [1,2,3,4]
bList = [5,6,7,8]
aList.append(bList)
print(aList)
aList.remove(2)
print("length of aList",len(aList))
