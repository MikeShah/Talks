'''
 A comment to ourselves in our code for 'why' we did something
 or some other important instructions
'''
# A single-line comment begins with a '#'

# Print is a function that outputs 
print("Hello Blender 3D!")

# 'name' is a variable storing (in some fashion) the value "Mike"
name = "Mike"
print("Hello", name)

# 'pi' is a variable storing a numeric value'
pi = 3.14
print("pi is: ",pi)

# We can create our own functions which take an arbitrary number
# (0 or more) number of parameters. 
def myFunction(param1, param2):
	print("param1 is:",param1)
	print("param2 is:",param2)

# When we provide different 'arguments' into a function, the
# function acts on the inputs to generate a new output.
myFunction("testing", 123)
myFunction("hello", "everyone!")

# If we want to repeat work, we can do so using 'loops'
# Here is an example of a 'for-loop'
for i in [1,2,3,4,5]:
	print(i)

# Here is another example with a 'while-loop'
count=10
while(count > -1):
	print(count,"...")
	count = count -1
