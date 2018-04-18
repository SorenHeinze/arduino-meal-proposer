#    "read_from_flash_memory" (v0.1)
#    Copyright 2018 Soren Heinze
#    soerenheinze@gmx.de
#    5B1C 1897 560A EF50 F1EB 2579 2297 FAE4 D9B5 2A35
#
#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program.  If not, see <http://www.gnu.org/licenses/>.

// // // // // // // // // // // // // // // // 
// // // // // // THE PROBLEM // // // // // // 
// // // // // // // // // // // // // // // // 

// The arduino has just a VERY limited RAM (ca. 2kB). 
// But all data (e.g. strings) I define are put into RAM at once.
// This will NOT lead to compiling errors but the arduino will not function 
// since the RAM is full!
// 
// Solution: The arduino has another memory which is MUCH larger (ca. 30 kB).
// It contains the program itself and is either thus called program memory
// or also flash memory. But this memory is read-only.
// 
// The disadvantage does not matter for all the data that shall just be read, 
// so all of the aboved mentioned strings can be moved there.
// 
// However, if I have an array that contains strings, things become complicated
// to retrieve the strings in a way readable for humans.
// 
// This is what this small program is about.


// // // // // // // // // // // // // // // // 
// // // // // // A SIDENOTE  // // // // // // 
// // // // // // // // // // // // // // // // 

// How much memory is used can be checked by running "avr-size" on the .elf-file
// of the arduino program. 
// The .elf-file is created when the program is verified or uploaded. 
// On my (linux) system it can be found under /tmp/build.../
// 
// More about this can be found here:
// https://playground.arduino.cc/Main/CorruptArrayVariablesAndMemory
// 
// The output of avr-size is sth. like the following:
// >>>   text    data     bss     dec     hex filename
// >>>   6554     128     656    7338    1caa  <filename>
// 
// '''text''' = code (flash) memory
// '''data''' = initialised data (in RAM - includes strings etc)
// '''bss''' = non-initialised data (actually normally set to 0x00) also in RAM.
//
// So total RAM usage = (data + bss)
// We also must store all initialised data in flash so:
// FLASH = text + data 
// RAM = data + bss 
// 
// So as described ALL the data is in RAM unless it "lives" just in the flash memory.


// // // // // // // // // // // // // // // // 
// // // // // // MORE COMMENTS  // // // // // 
// // // // // // // // // // // // // // // // 

// Due to the actual project but also because I don't want to always open the 
// serial monitor I use an lcd-display to print the strings.
// Thus <Wire.h> and "LiquidCrystal.h" need to be included.
// Since I assume this is one of the arduino basic things, I think that the 
// user can figure out by herself how to connect and use a LCD display.
// 
// <avr/pgmspace.h> is needed to do all the stuff for putting data into 
// the program/flash memory.
// 
// Mainly of help with this has been the above mentioned webpage to initially 
// learn about this issue.
// To find a solution the following pages have been of help:
// - http://www.avrfreaks.net/comment/194871
// - https://www.arduino.cc/en/Reference/PROGMEM
// - and mainly: http://www.gammon.com.au/progmem (ignore the free memory stuff, 
// since this can be checked with avr-size.


// // // // // // // // // // // // // // // // 
// // // // // // THE PROGRAM // // // // // // 
// // // // // // // // // // // // // // // // 


#include <Wire.h>
#include "LiquidCrystal.h"
#include <avr/pgmspace.h>

// Initialize the lcd-display.
LiquidCrystal lcd(0);

// If everything is just living in RAM an array of strings is defined like this:
// char* string_array[] = {"foo", "bar", "oof"}
// and I can access the elements the usual way with e.g. string_array[1].
// 
// As we can see below, by simply putting PROGMEM behind the identifier
// we can push it into the program memory.
// 
// Problem: if I want to access one element of the array in the loop(), 
// the WHOLE array is loaded into RAM again.
// 
// Solution: Leave the data in the program memory and store just the pointers
// to the data in the array.
// 
// 
// So here I first "put" the data into the flash memory.
// ATTENTION: DON'T do char* (so DON'T use the star) and DON'T use " { } " around the 
// string.
// 
// The size of the array should be left free to use (more or less) arbitrary length
// strings 
// 
// foo_1 and foo_2 are just pointers to the respective string. This is important 
// to remember to understand things below.
const char foo_1[] PROGMEM = "foo_1 foo_1 foo_1 foo_1 foo_1 foo_1 foo_1 foo_1 foo_1 foo_1 foo_1 foo_1 foo_1 foo_1 foo_1 foo_1 foo_1 foo_1 foo_1 foo_1 foo_1 foo_1 foo_1 foo_1 foo_1 foo_1 foo_1 foo_1 foo_1 foo_1"; 
const char foo_2[] PROGMEM = "foo_2foo_2foo_2foo_2foo_2foo_2foo_2foo_2foo_2foo_2foo_2foo_2foo_2foo_2foo_2foo_2foo_2foo_2foo_2foo_2foo_2foo_2foo_2foo_2foo_2foo_2foo_2foo_2foo_2foo_2";


// Secondly I "put" the pointers to the above strings into an array.
// ATTENTION: Here it is important to use char* (with the star) since 
// these are pointers.
// 
// "const" appears twice for a reason.
// See here https://github.com/arduino/Arduino/wiki/1.6-Frequently-Asked-Questions
const char* const bar[] PROGMEM = {foo_1, foo_2};

// Now define a "string" that is big enough to hold the longest string in the
// data.
// ATTENTION: Don't make it too big, because memory is allocated in the RAM
// for this string. And memory is sparse.
// ATTENTION: If the above strings are longer then the memory allocated for
// this string here that will probably lead to problems! 
// This can be taken care of, but since this is not meant for critical infrastructure
// I leave just the comment.
char buffer[200];

// The "bar"-array above actually contains just the pointers to the data. 
// So when I want to "pull out" the data from the array to store 
// it in "buffer" I'm just pulling out the pointer to the data. Hence, "buffer"
// can not be used (yet).
// Below I explain the whole "pulling the data out of program memory"-shebang.
// To remember here: I don't just need a buffer-variable for the data but also
// another char-pointer.
char* buffer_pointer;

// The setup is just for the lcd-display.
void setup() {
  // The lcd-display has 2 rows a 16 characters.
  lcd.begin(16, 2);
  lcd.setBacklight(HIGH);
}


void loop() {
  // The for-loop is here just because I have two strings in the array.
  for (int i = 0; i < 2; i++){
    // Always clear the lcd-display.
    lcd.clear();
    
    // And now it gets interesting (and complicated when I did it for the
    // first time):
    // pgm_read_word(POSITION) reads everything at "POSITION" in the 
    // program/flash memory.
    // See here for details:
    // https://www.nongnu.org/avr-libc/user-manual/ ...
    // ... group__avr__pgmspace.html#ga6e58e62e197da722b973c33ba3e1fa07
    // 
    // ATTENTION: "POSITION" needs to by a byte-address and that is waht 
    // the " & " does.
    // 
    // BUT since the data-array actually contains just pointers to the
    // real data, we need to "[...] instruct the compiler that we really do 
    // want to use that 16-bit return value of pgm_read_word as a pointer to 
    // a const char in flash memory, [so] we need to typecast it to a pointer 
    // in the form of char*." 
    // 
    // This is the what the " (char*) " in front of the pgm_read_word() does.
    // 
    // Now I have the pointer to the data but not the string itself ...
    buffer_pointer = (char*) pgm_read_word(&bar[i]);

    // ... I take care of this by using strcpy_P() which will copy the string
    // at the position the pointer points to into the buffer. 
    // 
    // ATTENTION: The " _P " is a modification of the original strcpy()-function
    // to handle the fact that the data is coming NOT from RAM but another 
    // memory.
    strcpy_P(buffer, buffer_pointer); 
    
    // Finally I can print the data.
    lcd.print(buffer);

    // The delay is just to make it recognizable by a human.
    delay(1000);
  }
}









