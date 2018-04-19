//        "arduino-meal-proposer" (v0.5)
//        Copyright 2018 Soren Heinze
//        soerenheinze@gmx.de
//        5B1C 1897 560A EF50 F1EB 2579 2297 FAE4 D9B5 2A35
//
//        This program is free software: you can redistribute it and/or modify
//        it under the terms of the GNU General Public License as published by
//        the Free Software Foundation, either version 3 of the License, or
//        (at your option) any later version.
//
//        This program is distributed in the hope that it will be useful,
//        but WITHOUT ANY WARRANTY; without even the implied warranty of
//        MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.    See the
//        GNU General Public License for more details.
//
//        You should have received a copy of the GNU General Public License
//        along with this program.    If not, see <http://www.gnu.org/licenses/>.

// This program uses an arduino, a LCD display and two buttons to randomly show 
// a defined meal. Pressing the "next"-button will display another (random) meal. 
// If a meal is chosen, pressing the "ok"-button will lead to a list with the
// ingrediences for it. 


// ATTENTION: The arduino has limited RAM. So I have to put all the 
// constant strings into the program/flash-memory.
// See "read_from_flash_memory.ino" for a detailed description of this problem 
// and the solution.

// include the proper libraries:
#include <Wire.h>
#include "LiquidCrystal.h"
#include <avr/pgmspace.h>

// Connect via i2c, default address #0 (A0-A2 not jumpered)
LiquidCrystal lcd(0);


// ATTENTION: Due to the limitations of the display the names of the 
// meals should not be longer then 32 characters.
// 123456789 123456789 123456789 12

// // // // // // // // // // // // // // // // // // // // // 
// // // // // // // WEEKDAY MEALS NAMES  // // // // // // // 
// // // // // // // // // // // // // // // // // // // // // 

// Name of meal not longer then this:    123456789 123456789 123456789 12
const char weekdaymeal_01[] PROGMEM = "Favorite Weekdy Meal ONE";
const char weekdaymeal_02[] PROGMEM = "Favorit Weekday Meal TWO";

// ATTENTION: 
// AFTER ADDING NEW MEALS: don't forget to update the pointer-array below.

// Define the array that contains the pointers to the meal-names.
const char* const weekday_meals[] PROGMEM = {
weekdaymeal_01, weekdaymeal_02
};


// // // // // // // // // // // // // // // // // // // // // 
// // // // // // // WEEKEND MEALS NAMES  // // // // // // // 
// // // // // // // // // // // // // // // // // // // // // 

// Name of meal not longer then this:    123456789 123456789 123456789 12
const char weekendmeal_01[] PROGMEM = "Favorit Weekday Meal ONE";
const char weekendmeal_02[] PROGMEM = "Favorit Weekday Meal TWO";

// ATTENTION: 
// AFTER ADDING NEW MEALS: don't forget to update the pointer-array below.

const char* const weekend_meals[] PROGMEM = {
weekendmeal_01, weekendmeal_02
};





// // // // // // // // // // // // // // // // // // // // // 
// // // // // // WEEKDAY MEALS INGREDIENCES // // // // // // 
// // // // // // // // // // // // // // // // // // // // // 

// ATTENTION: Limited number of characters: 200.
// (see comment below regarding the definition of the "buffer" variable)
// (
// This is to figure out the length of the string, so that it doesn't get too long:
// ------------------------------------------------1     5     10                20                30                40                50                60                70                80                90             100             110             120             130             140             150             160             170             180             190             200
const char weekdaymeal_ingredients_01[] PROGMEM = "Cookbook_1 p. 23 - INGREDIENCE_1, INGREDIENCE_2, INGREDIENCE_3, BEWARE THE LIMIT OF 200 CHARACTERS!";
const char weekdaymeal_ingredients_02[] PROGMEM = "Cookbook_2 p. 42 - INGREDIENCE_1, INGREDIENCE_2, INGREDIENCE_3, BEWARE THE LIMIT OF 200 CHARACTERS!";;

// ATTENTION: 
// AFTER ADDING NEW INGREDIENCES: don't forget to update the pointer-array below.

const char* const weekday_meals_ingredients[] PROGMEM = {
weekdaymeal_ingredients_01, weekdaymeal_ingredients_02
};


// // // // // // // // // // // // // // // // // // // // // 
// // // // // // WEEKEND MEALS INGREDIENCES // // // // // // 
// // // // // // // // // // // // // // // // // // // // // 

// ------------------------------------------------1     5     10                20                30                40                50                60                70                80                90             100             110             120             130             140             150             160             170             180             190             200
const char weekendmeal_ingredients_01[] PROGMEM = "Cookbook_3 p. 5 - INGREDIENCE_1, INGREDIENCE_2, INGREDIENCE_3, BEWARE THE LIMIT OF 200 CHARACTERS!";
const char weekendmeal_ingredients_02[] PROGMEM = "Cookbook_4 p. 17 - INGREDIENCE_1, INGREDIENCE_2, INGREDIENCE_3, BEWARE THE LIMIT OF 200 CHARACTERS!";


// ATTENTION: 
// AFTER ADDING NEW INGREDIENCES: don't forget to update the pointer-array below.

const char* const weekend_meals_ingredients[] PROGMEM = {
weekendmeal_ingredients_01, weekendmeal_ingredients_02
};






// // // // // // // // // // // // // // // // // // // // // 
// // // // // // DEFINITION OF VARIABLES // // // // // // //
// // // // // // // // // // // // // // // // // // // // // 

const int number_of_weekday_meals = sizeof(weekday_meals) / sizeof(weekday_meals[0]);
const int number_of_weekend_meals = sizeof(weekend_meals) / sizeof(weekend_meals[0]);

String meal;
String chosen_ingredients;
String part_of_ingredients;
const int okPin = 3;
const int nextPin = 4;
int this_day;
int meal_number;
int this_meal_number;
int chosen_meal_number;
int meal_chosen = 2;
int counter;
int length_of_ingredients;
// When displaying the ingredients I need to read both buttons but I don't
// distinguish between those. However, read_input() returns an int so I "catch" 
// it with this variable just to be on the safe side.
int dummy;

// Here I define the variable that shall later hold whatever I pull 
// out of the program/flash-memory.
// 
// ATTENTION: This is a char array and the size must be as big as the 
// largest string I'd like to pull out of memory.
// 
// ATTENTION: Don't make it too big because this will reserve too much memory
// in the RAM. 200 is rather arbitrary but worked well for all the meals I'm able 
// to cook.
char buffer[200];

// I also need a variable that shall hold the pointer to the data.
// All of this is explained in the above mentioned file.
char* buffer_pointer;






// // // // // // // // // // // // // // // // // // // // // 
// // // // // // DEFINITION OF FUNCTIONS // // // // // // //
// // // // // // // // // // // // // // // // // // // // // 

void setup() {
    // set up the LCD's number of rows and columns: 
    lcd.begin(16, 2);
    lcd.setBacklight(HIGH);
    pinMode(okPin, INPUT);
    pinMode(nextPin, INPUT);
}



// Clear the Display and set the cursor back to the starting position.
void clearScreen(){
    // Delete everything from the display ...
    lcd.clear();
    // ... and set the cursor to column 0, line 0 (note: line 1 is the second 
    // row, since counting begins as usual at 0):
    lcd.setCursor(0, 0);
}



// This function takes care that Strings longer then 16 characters are 
// displayed over the two lines of the display.
void display_this(String this_string) {
    clearScreen();
    lcd.print(this_string.substring(0, 16));
    lcd.setCursor(0, 1);
    lcd.print(this_string.substring(16, 32));
}



// This function reads if a button is pressed and returns 1 for the one 
// (e.g. weekday or ok) or 2 for the other (e.g. weekend or next). 
int read_input() {
    while (true) {
        if (digitalRead(okPin) == HIGH) {
            return 1;
        }
        else if (digitalRead(nextPin) == HIGH) {
            return 2;
        }    
    }
}



// This function shall return just a random number in the range of the number 
// of meals. However, it turned out that randomness is a bit more complicated 
// with an arduino.
int get_meal_number(int number_of_meals) {
    // random() puts out random numbers but always in the same sequence. 
    // 
    // randomSeed() can solve this problem a bit by changing the (internal) 
    // parameters of random() (as I understand it), but it also puts out the 
    // same seed depending on the input.
    // 
    // A not used pin has somewhat random voltages. However, the entropy is not 
    // really good. 
    // 
    // micros() gives the time since the program started in microseconds. This 
    // way I mix some randomness with some other randomness (since the value of 
    // micros() is determined in this case when the user presses the button) and 
    // will get better entropy. 
    // 
    // " ^ " is the XOR operator which will make the entropy even better.
    // I've got this idea from here:
    // https://arduino.stackexchange.com/questions/22070/ ...
    // ... powering-from-3v-coin-cell-to-vcc-using-i-o-pin-as-supply-gnd/22081#22081 
    randomSeed(analogRead(0)^micros());

    return random(number_of_meals);
}



// This function gets the meal number according to the day of the week
// and displays the meal-name that belongs to it.
int get_meal(int this_day) {
    clearScreen();
    if (this_day == 1) {
        meal_number = get_meal_number(number_of_weekday_meals);
        // This is how I get a string I can work with from memory.
        // What's going on here is explained in the above mentioned file.
        buffer_pointer = (char*) pgm_read_word(&weekday_meals[meal_number]);
        strcpy_P(buffer, buffer_pointer);
        display_this(buffer);
    } else if (this_day == 2) {
        meal_number = get_meal_number(number_of_weekend_meals);
        buffer_pointer = (char*) pgm_read_word(&weekend_meals[meal_number]);
        strcpy_P(buffer, buffer_pointer);
        display_this(buffer);
    }

    return meal_number;
}



// This function waits for the user if she or he likes the meal or not.
// If not, another meal will be chosen.
// The meal number is returned since it is needed for the display of the
// proper ingredients.
int chose_meal(int this_day) {
    // read_input() returns " 2 " for the "next"-button and " 1 " for the
    // "OK"-button. Also, meal_chosen is initialized as " 2 " above, 
    // so this loop will run until the "OK"-button is pressed.
    while (meal_chosen == 2) {
        this_meal_number = get_meal(this_day);
        meal_chosen = read_input();
        delay(500);
    }

    return this_meal_number;
}



// This function choses the ingredients according to the day and meal.
String these_ingredients(int this_day, int chosen_meal_number) {
    if (this_day == 1) {
        buffer_pointer = (char*) pgm_read_word(&weekday_meals_ingredients[chosen_meal_number]);
        strcpy_P(buffer, buffer_pointer);

        return buffer;
    }
    else if (this_day == 2) {
        buffer_pointer = (char*) pgm_read_word(&weekend_meals_ingredients[chosen_meal_number]);
        strcpy_P(buffer, buffer_pointer);

        return buffer;    
    }
}



// Finally this function shows the ingredients of the chosen meal.
void show_ingredients(int this_day, int chosen_meal_number) {
    chosen_ingredients = these_ingredients(this_day, chosen_meal_number);
    // .length() is another nice method for strings. 
    length_of_ingredients = chosen_ingredients.length();
    // Loop forever, in case the button is pressed too fast so that the user 
    // can always come back to a previous ingredient.
    while (true) {
        counter = 0;
        while (counter <= length_of_ingredients) {
            part_of_ingredients = chosen_ingredients.substring(counter);
            display_this(part_of_ingredients);
            // See the comment in the variable decalaration section why I use
            // a dummy here.
            dummy = read_input();
            counter = counter + 32;
            delay(500);
            clearScreen();
        }
    }
}




void loop() {
    // First figure out what day it is ...
    display_this("WEEKDAY WEEKEND    (OK)   (NEXT)");
    this_day = read_input();
    // Delays are used to avoid "slow" users to already trigger the next action 
    // by pushing too long on the button.
    delay(500);
    clearScreen();
    // ... then figure out the meal ...
    chosen_meal_number = chose_meal(this_day);
    delay(500);
    // ... and finally display the ingredients.
    show_ingredients(this_day, chosen_meal_number);
    
    lcd.clear();
}










