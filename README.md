# arduino-meal-proposer
## Problem:  
You know how to cook many things but always end up with the same stuff?

Because a usual weekday morning leaves little time to pull out the correct cooking book to figure out which ingrediences are needed.  
Because there are far too many bookmarks in said book and the meal in question is not to be found within this short moment between making lunch for the offspring and going to work.  
Because one simply forgets some of the less regularly cooked meals.  
And why does it always have to be me to come up with an idea for what to eat?  

## Solution:  
Let modern technology help you remember all the other things you can cook and take away one of these everyday struggles.

## What you'll get:  
When you have finished this project, a cool looking blue glowing LCD display will show a randomly picked meal.

If you don't like it, just press the "next"-button and another (random) meal will be displayed.

If you like it, press the "ok"-button and a list with the ingrediences will be shown.

Since one often has more time at the weekend to prepare more elaborated meals, these are distinguished from weekday meals.


## Comments:  
I used an Arduino, two buttons and a LCD display. Details of the setup can be found in "00_arduino_setup.txt"

The actual program to be uploaded to the arduino is "meal_proposer.ino" in the respective folder (you may have guessed this ;) ).

The meal names and the lists with the ingrediences need to be included in the code that will be uploaded to the arduino.
Two examples are given in the code.

The Arduino I used had a limited working memory. At the same time I have quite long strings (the lists with the ingrediences for each meal). It was is not possible to hold all this information at the same time in the working memory.  
Thus I have to swap information from the program/flash-memory into the working memory just when it is needed.  
This leads to some rather "weird constructs" in the code. Thus this challenge and the solution are described in detail in "read_from_flash_memory.ino" in the respective folder.

Some less significant things (e.g. how to get a really random number) are described as comments in the code.

One last comment: The code and the comments were written for interested people that are non-regular-C programmers. Hence many things I comment are probably quite obvious for more experienced people.
