
// ATTENTION: The arduino has limited RAM. So I have to put all the 
// constant strings into the flash-memory.

// include the library code:
#include <Wire.h>
#include "LiquidCrystal.h"
#include <avr/pgmspace.h>

// Connect via i2c, default address #0 (A0-A2 not jumpered)
LiquidCrystal lcd(0);


// 
// ALL OF THESE COMPLICATED THINGS ARE EXPLAINED IN 
// 00_learning_putting_strings_into_other_memory.txtssssssHitman 2

// ATTENTIOINN: Due to the limitations of the display the names of the 
// meals should not be longer then 32 characters.
// 12345678901234567890123456789012

// // // // // // // // // // // // // // // // // // // // // 
// // // // // // WEEKDAY MEALS DEFINITIONS  // // // // // // 
// // // // // // // // // // // // // // // // // // // // // 
const char weekdaymeal_01[] PROGMEM = "Polse pa grill";
const char weekdaymeal_02[] PROGMEM = "Hamburger Tex Mex";
const char weekdaymeal_03[] PROGMEM = "Vegetariske Hamburger";
const char weekdaymeal_04[] PROGMEM = "Laks";
const char weekdaymeal_05[] PROGMEM = "Lieblingsspaghetti";
const char weekdaymeal_06[] PROGMEM = "Makkaroni med Ost og Blomkal";
const char weekdaymeal_07[] PROGMEM = "Ertenudler";
const char weekdaymeal_08[] PROGMEM = "Fersk Pasta med Cherrytomater";
const char weekdaymeal_09[] PROGMEM = "Omelett (med Tomater)";
const char weekdaymeal_10[] PROGMEM = "Blomkalsuppe";
const char weekdaymeal_11[] PROGMEM = "Blomkalsuppe fra pose";
const char weekdaymeal_12[] PROGMEM = "Italiensk Gryte fra pose";
const char weekdaymeal_13[] PROGMEM = "Speilegg pa brod";
const char weekdaymeal_14[] PROGMEM = "Eggerore";
const char weekdaymeal_15[] PROGMEM = "Eggerore med Lok, Salami, Tomat";
const char weekdaymeal_16[] PROGMEM = "Chili sin Carne";
const char weekdaymeal_17[] PROGMEM = "Tacos";
const char weekdaymeal_18[] PROGMEM = "Melkeris";
const char weekdaymeal_19[] PROGMEM = "Pannekaker";
const char weekdaymeal_20[] PROGMEM = "Pita";
const char weekdaymeal_21[] PROGMEM = "Rocka Ris";
const char weekdaymeal_22[] PROGMEM = "Risotto med Erter";

// Define the array that contains the pointers to the meal-names.
const char* const weekday_meals[] PROGMEM = {
weekdaymeal_01, weekdaymeal_02, weekdaymeal_03, weekdaymeal_04, 
weekdaymeal_05, weekdaymeal_06, weekdaymeal_07, weekdaymeal_08, 
weekdaymeal_09, weekdaymeal_10, weekdaymeal_11, weekdaymeal_12, 
weekdaymeal_13, weekdaymeal_14, weekdaymeal_15, weekdaymeal_16, 
weekdaymeal_17, weekdaymeal_18, weekdaymeal_19, weekdaymeal_20, 
weekdaymeal_21, weekdaymeal_22
};

const int number_of_weekday_meals = 22;



// // // // // // // // // // // // // // // // // // // // // 
// // // // // // WEEKEND MEALS DEFINITIONS  // // // // // // 
// // // // // // // // // // // // // // // // // // // // // 

const char weekendmeal_01[] PROGMEM = "Kjottbrod i Gryte";
const char weekendmeal_02[] PROGMEM = "Lasagne";
const char weekendmeal_03[] PROGMEM = "Gryte med Dumplings";



const char* const weekend_meals[] PROGMEM = {
weekendmeal_01, weekendmeal_02, weekendmeal_03
};

const int number_of_weekend_meals = 3;




// Here I define the variable that shall later hold whatever I pull 
// out of the flash-memory.
// ATTENTION: This is a char array and the size must be as big as the 
// largest string I'd like to pull out of memory.
// ATTENTION: Don't make it too big because this will reserve too much memory
// in the RAM.
char buffer[200];

// I also need a variable that shall hold the pointer to the data.
// All of this is explained in the above mentioned document.
char* buffer_pointer;

// I my god! It looks like I have to hardcode everything.
// This is to figure out how long the buffer must be:
// ------------------------------------------------1   5   10        20        30        40        50        60        70        80        90       100       110       120       130       140       150       160       170       180       190       200
const char weekdaymeal_ingredients_01[] PROGMEM = "Polse (kjott- og vanlig), Sprolok, Ketchup, Mayonaise, Lumpe/Polsebrod/Rundstykker, Grillkull, Tennvaeske";
const char weekdaymeal_ingredients_02[] PROGMEM = "Familiekokeboka S. 163 - Svinekjottdeig (400g), Hvitlok, Spisskummen, Rod Chili, Sprolok, Cherrytomater, Ketchup, Mayonaise, Grove Rundstykker, Grillkull, Tennvaeske";
const char weekdaymeal_ingredients_03[] PROGMEM = "Vegetarisk Hamburgerblanding, Sprolok, Cherrytomater, Ketchup, Mayonaise, Rundstykker, Grillkull, Tennvaeske";
const char weekdaymeal_ingredients_04[] PROGMEM = "Laks (1 eller 2 pakker), Tacolefse, Lettromme, Honning, Grillkull, Tennvaeske";
const char weekdaymeal_ingredients_05[] PROGMEM = "1 medium Flaske HEINZ (!!!) Ketchup, Svinekjottdeig (400g), Spaghetti, Hvit Jaevner, Tomatpurre, 1 Lok, Hvitlok, Smor";
const char weekdaymeal_ingredients_06[] PROGMEM = "Laere Lage Mat S.49 - 1 Blomkal, Cheddar (200g), Parmesan (100g), 1 bunt Bladpersille, Creme Fraiche, Makkaroni";
const char weekdaymeal_ingredients_07[] PROGMEM = "Laere Lage Mat S.52 - Frosne Erter, Makkaroni, Parmesan (100g), Creme Fraiche, Smor";
const char weekdaymeal_ingredients_08[] PROGMEM = "Laere Lage Mat S.55 - Cherrytomater (500g), Hvitlok, Fersk Basilikum, Fersk Lasagne (750g), Parmesan (100g), Balsamicoeddik, Smor";
const char weekdaymeal_ingredients_09[] PROGMEM = "Laere Lage Mat S.313 - Egg, Cheddar, Smor, Cherryomater, (Basilikum)";
const char weekdaymeal_ingredients_10[] PROGMEM = "Laere Lage Mat S.136 - 2 Blomkal, 2 Gulrotter, 2 Selleri, 2 Lok, Hvitlok, Cheddar (200g), Gronnsaksbuljong, Sennep";
const char weekdaymeal_ingredients_11[] PROGMEM = "Poseblomkalsuppe, 1 Blomkal, Melk eller Flote, See på posen!";
const char weekdaymeal_ingredients_12[] PROGMEM = "Pose med italiensk Gryte, Svinekjottdeig (400g), See på posen!";
const char weekdaymeal_ingredients_13[] PROGMEM = "Egg, Ketchup, Smor, Brod";
const char weekdaymeal_ingredients_14[] PROGMEM = "Egg, Ketchup, Smor, Brod";
const char weekdaymeal_ingredients_15[] PROGMEM = "6 Egg, 1 Pakke Salami, 1 (2?) Lok, Cherrytomater";
const char weekdaymeal_ingredients_16[] PROGMEM = "Laere Lage Mat S.172 - 2 Lok, Hvitlok, 2 Gulrotter, 2 Selleri, 2 rode Paprika, Kikerter (ca. 1000g), Rode Bonner (1000g), 2 bokser hakkede Tomater, Balsamicoeddik, Chilipulver, Paprikapulver";
const char weekdaymeal_ingredients_17[] PROGMEM = "Svinekjottdeig (400g), Cherrytomater, Agurk, Mais, Sterk Saus, Romme, Tacolefse, Avocado, Tacokrydder, Ost";
const char weekdaymeal_ingredients_18[] PROGMEM = "Melk (1 Liter), Melkeris, Sukker, Tryllestov, (Kirsebaer)";
const char weekdaymeal_ingredients_19[] PROGMEM = "Hugos Kokebok S. 40 - Hvetemel (320g), Melk (1 Liter), Sukker, Tryllestov";
const char weekdaymeal_ingredients_20[] PROGMEM = "Hugos Kokebok S. 14 - 4 Store Pitabrod, Tunfisk i Boks eller Stekt Kyllingsnadder, 4 Varlok, Mais (200g), Majones, 4 Egg, Romano- eller Issalat";
const char weekdaymeal_ingredients_21[] PROGMEM = "Hugos Kokebok S. 30 - Ris, Gronnsaksbuljong, 1 Lok, 1 Rod Paprika, Sjampinjong (100g), Frosne Erter, Mais, Persille";
const char weekdaymeal_ingredients_22[] PROGMEM = "Jamie i Spania S. 84 - Risottoris, Gronnsaksbuljong, 1 Lok, 1 Selleri, Eplejuice, Smor, Parmesan, Persille, Frosne Erter";

const char* const weekday_meals_ingredients[] PROGMEM = {
weekdaymeal_ingredients_01, weekdaymeal_ingredients_02, 
weekdaymeal_ingredients_03, weekdaymeal_ingredients_04, 
weekdaymeal_ingredients_05, weekdaymeal_ingredients_06, 
weekdaymeal_ingredients_07, weekdaymeal_ingredients_08, 
weekdaymeal_ingredients_09, weekdaymeal_ingredients_10, 
weekdaymeal_ingredients_11, weekdaymeal_ingredients_12, 
weekdaymeal_ingredients_13, weekdaymeal_ingredients_14, 
weekdaymeal_ingredients_15, weekdaymeal_ingredients_16, 
weekdaymeal_ingredients_17, weekdaymeal_ingredients_18, 
weekdaymeal_ingredients_19, weekdaymeal_ingredients_20, 
weekdaymeal_ingredients_21, weekdaymeal_ingredients_22

};


// This is to figure out how long the buffer must be:
// ------------------------------------------------1   5   10        20        30        40        50        60        70        80        90       100       110       120       130       140       150       160       170       180       190       200
const char weekendmeal_ingredients_01[] PROGMEM = "Laere Lage Mat S. 161 - 2 Lok, Kapteinkjeks, Sennep, Svinekjottdeig (500g), 1 Egg, Hvitlok, 1 Rod Chili, Paprikapulver, Kikerter (400g), Hakkede Tomater (800g), Balsamicoeddik, Sitron, Worcestersaus";
const char weekendmeal_ingredients_02[] PROGMEM = "Laere Lage Mat S. 169 - 2 Lok, Hvitlok, 2 Gulrotter, 2 Selleri, Svinekjottdeig (500g), Hakkede Tomater (800g), Basilikum, Parmesan (150g), Lasagneplater (250g), Creme Fraice (2 Bokser), 1 Tomat";
const char weekendmeal_ingredients_03[] PROGMEM = "Laere Lage Mat S. 180 + 185 - 2 Lok, 2 Gulrotter, 2 Selleri, Hakkede Tomater (400g), Kyllinglår (500g), Eplejuice, SEE BOK FOR KJOTTVARIANTER!, Hvetemel, Bakepulver, Smor";


const char* const weekend_meals_ingredients[] PROGMEM = {
weekendmeal_ingredients_01, weekendmeal_ingredients_02, 
weekendmeal_ingredients_03
};








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
// distinguish between those. Unfortunately read_input() returns an int.
// So before messing sth. up I rather use a dummy variable.
int dummy;




void setup() {
  // set up the LCD's number of rows and columns: 
  lcd.begin(16, 2);
  lcd.setBacklight(HIGH);
  pinMode(okPin, INPUT);
  pinMode(nextPin, INPUT);
}



// Clear the Display and set the cursor back to the starting position. The 
// latter is probably not necessary and will make this whole function not 
// necessary.
// TO BE CHECKED!!!
void clearScreen(){
  // Delete everything from the display ...
  lcd.clear();
  // ... and set the cursor to column 0, line 0 (note: line 1 is the second 
  // row, since counting begins with 0):
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
  // It turned out that random() puts out random numbers but always in the 
  // same sequence. 
  // randomSeed() can solve this problem a bit by changing the (internal) 
  // parameters of random() (as I understand it), but it also puts out the 
  // same seed depending on the input.
  // A not used pin has somewhat random voltages. However, the entropy is not 
  // really good. 
  // micros() gives the time since the program started in microseconds. This 
  // way I mix some randomness with some other randomness (since the value of 
  // micros() is determined in this case when the user presses the button) and 
  // will get better entropy. 
  // " ^ " is the XOR operator which will make the entropy even better.
  // I've got this idea from here:
  // https://arduino.stackexchange.com/questions/22070/ ...
  // ... powering-from-3v-coin-cell-to-vcc-using-i-o-pin-as-supply-gnd/22081#22081 
  randomSeed(analogRead(0)^micros());
  return random(number_of_meals);
}



// This function gets the meal number according to the time of the week
// and displays the meal that belongs to it.
int get_meal(int this_day) {
  clearScreen();
  if (this_day == 1) {
    meal_number = get_meal_number(number_of_weekday_meals);
    // This is how I get a string I can work with from memory.
    // What's going on here is explained in the above mentioned document.
    buffer_pointer = (char *)pgm_read_word(&weekday_meals[meal_number]);
    strcpy_P(buffer, buffer_pointer);
    display_this(buffer);
  }
  else if (this_day == 2) {
    meal_number = get_meal_number(number_of_weekend_meals);
    buffer_pointer = (char *)pgm_read_word(&weekend_meals[meal_number]);
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
    buffer_pointer = (char*)pgm_read_word(&weekday_meals_ingredients[chosen_meal_number]);
    strcpy_P(buffer, buffer_pointer);

    return buffer;
  }
  else if (this_day == 2) {
    buffer_pointer = (char*)pgm_read_word(&weekend_meals_ingredients[chosen_meal_number]);
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
  // can always come back to this.
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
  display_this("HVERDAG    HELG  (OK)     (NEXT)");
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









