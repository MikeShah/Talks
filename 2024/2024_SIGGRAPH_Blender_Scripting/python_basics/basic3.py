'''
	Let's now take a look at some conditional statements
	which allow us to make 'decisions' in our code. 
'''
import random

aNumber = random.randint(1,10)
myGuess = -1

# While loops have a 'condition' that will be tested
# to see if we should continue executing the loop
while(myGuess != aNumber):
	# Note: In order to make sure that our
	#       'input' is an integer value, we
	#       'cast' that value with the int() 
  #       function.
	myGuess = int(input("Pick a number: "))

	if(myGuess < aNumber):
		print("Guess higher!")

	if(myGuess > aNumber):
		print("Guess lower!")

	if(myGuess == aNumber):
		print("You guessed correctly!")
	
'''
	We can 'group' together our 'if' statements such that
	only one conditon has to be checked.
	Generally -- this is more efficient, and likely what
	we want to do.
'''

if(aNumber > 5):
	print("A number was greater than 5")
elif(aNumber==5):
	print("The number was 5")
else:
	print("The number must have been less than 5")
