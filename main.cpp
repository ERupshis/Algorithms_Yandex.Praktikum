//#include "Algorithms_Y.Praktikum_Sprint1.h"
//#include "Algorithms_Y.Praktikum_Sprint1_Exam.h"
#include "Tests_Launcher.h"

#include <fstream>

void Test() {
    sprint1_tests();
    sprint2_tests();
    sprint3_tests();
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
    //s1_problems::F_Palindrome(input_file, output_file);
    //s1_problems::G_WorkFromHome(input_file, output_file);
    //s1_problems::H_BinarySystem(input_file, output_file);
    //s1_problems::I_PowerOfFour(input_file, output_file);
    //s1_problems::J_Factorization(input_file, output_file);
    //s1_problems::K_ListForm(input_file, output_file);
    //s1_problems::L_ExtraLetter(input_file, output_file);

    //s1_exam_problems::A_NearestZero(input_file, output_file);
    //s1_exam_problems::B_SleightOfHand(input_file, output_file);

    //s2_problems::A_Monitoring(input_file, output_file);
    //s2_problems::F_StackMax(input_file, output_file);
    //s2_problems::G_StackMaxEffective(input_file, output_file);
    //s2_problems::H_BracketSequence(input_file, output_file);
    //s2_problems::I_LimitedQueue(input_file, output_file);
    //s2_problems::J_ListedQueue(input_file, output_file);
    //s2_problems::K_RecursionFibonacci(input_file, output_file);
    //s2_problems::L_RecursionFibonacciAbs(input_file, output_file);

    //s2_exam_problems::A_Deque(input_file, output_file);
    //s2_exam_problems::B_Calc(input_file, output_file);

    //s3_problems::A_BracketsGenerator(input_file, output_file);
    //s3_problems::B_Combinations(input_file, output_file);
    //s3_problems::L_TwoBikes(input_file, output_file);

    
    
}

