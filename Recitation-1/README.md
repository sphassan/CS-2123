# CS-2123-Recit1

/*******************************************************************************************************************
* Sean Hassan                                                                                                      *
* CS 2123 - Spring 2016                                                                                            *
* Doctor Ali Saman Tosun                                                                                           *
* Recitation 1 - Jan 29                                                                                            *
*                                                                                                                  *
* This program takes in as input a series of positive integers. It then calculates all combinations of integers,   *
* starting from 1, that may be constructed by individual members of the input being added together. For example, 1 *
* is 1, 5 is 3 + 2, 10 is 5 + 4 + 1. The algorithm used to accomplish this makes use of a profound mathematical    *
* truth, that when there is an arithmetic series that begins with 1 and continues such that no number in series is *
* larger than all prior members  added together plus 1 one may add together all numbers less than the sum of all   *
* numbers in series using only the numbers themselves. An example of this phenomena is binary counting, all        *
* positive integers may be formed by numbers in the series {1, 2, 4, 8, 16, 32, 64, ...} without exception.        *
* Utilizing this truth, the program first calculates the largest constructable number, the sum of all given        *
* numbers that do not violate the rule of the series, and then works backwards. All numbers less than the sum of   *
* all numbers may be made by removing members of the series from the sum.                                          *
*                                                                                                                  *
* This recitation was written solely by myself.                                                                    *
*******************************************************************************************************************/
