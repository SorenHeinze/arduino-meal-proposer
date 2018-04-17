AT THE MOMENT I USE THIS REPOSITORY TO LEARN HOW TO USE GIT ON THE COMMAND LINE

# arduino-meal-proposer
**Problem**:  
You know how to cook many things but always end up with the same stuff?

Because a usual weekday morning does leave little time to pull out the correct cooking book to figure out which ingrediences are needed. 
Because there are far too many bookmarks in said book and the meal in question is not to be found within this short moment between making lunch for the offspring and going to work.
Because one simply forgets some of the less regularly cooked meals.
And why does it always have to be me to come up with an idea for what to eat?

**Solution**:  
Let modern technology help you remember all the other things you can cook and take away one of these everyday struggles.


**Comments**:  
I used an Arduino, two buttons and a LCD display. Details of the setup can be found in "00_arduino_setup.txt"

ATTENTION:
The Arduino I used had a limited working memory. At the same time I have quite long strings (the lists with the ingrediences for each meal). It was not possible to hold all this information at the same time in the working memory.
Thus I have to swap information from the flash-memory into the working memory just when it is needed.

This leads to some rather "weird constructs" in the code and this challenge and the solution are described in detail in "01_read_from_flash_memory.txt"

Some less significant things (e.g. how to get a really random number) are described as comments in the code.
