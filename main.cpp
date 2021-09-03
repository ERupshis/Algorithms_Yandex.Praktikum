#include "Algorithms_Y.Praktikum_Sprint1.h"
#include "Tests_Launcher.h"

#include <iostream>
#include <fstream>

void Test() {
    sprint1_tests();
}

int main()
{
    Test();
    std::ifstream input_file("input.txt");
    std::ofstream output_file("output.txt");
    //s1_problems::A_FunctionValues(input_file, output_file);
    //s1_problems::B_EvenAndOddNumbers(input_file, output_file);
    //s1_problems::C_Neighbours(input_file, output_file);
    //s1_problems::D_WeatherRandomness(input_file, output_file);
    //s1_problems::E_LongestWord(input_file, output_file);
    s1_problems::F_Palindrome(input_file, output_file);
}
