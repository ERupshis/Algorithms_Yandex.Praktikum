#pragma once

#include "Algorithms_Y.Praktikum_Sprint1.h"
#include "Algorithms_Y.Praktikum_Sprint1_Exam.h"

#include "Algorithms_Y.Praktikum_Sprint2.h"
#include "Algorithms_Y.Praktikum_Sprint2_Exam.h"

#include "Algorithms_Y.Praktikum_Sprint3.h"
#include "Algorithms_Y.Praktikum_Sprint3_Exam.h"

void sprint1_tests() {
    s1_tests::A_FunctionValues_test();
    s1_tests::B_EvenAndOddNumbers_test();
    s1_tests::C_Neighbours_test();
    s1_tests::D_WeatherRandomness_test();
    s1_tests::E_LongestWord_test();
    s1_tests::F_Palindrome_test();
    s1_tests::G_WorkFromHome_test();
    s1_tests::H_BinarySystem_test();
    s1_tests::I_PowerOfFour_test();
    s1_tests::J_Factorization_test();
    s1_tests::J_K_ListForm_test();
    s1_tests::L_ExtraLetter_test();

    s1_exam_tests::A_NearestZero();
    s1_exam_tests::B_SleightOfHand();
}

void sprint2_tests() {
    s2_tests::A_Monitoring();
    s2_tests::F_StackMax();
    s2_tests::G_StackMaxEffective();
    s2_tests::H_BracketSequence();
    s2_tests::I_LimitedQueue();
    s2_tests::J_ListedQueue();
    s2_tests::K_RecursionFibonacci();
    s2_tests::L_RecursionFibonacciAbs();

    s2_exam_tests::A_Deque();
    s2_exam_tests::B_Calc();
}

void sprint3_tests() {
    s3_tests::A_BracketsGenerator();
    s3_tests::B_Combinations();
    s3_tests::C_Subsequence();
    s3_tests::D_Cookies();
    s3_tests::E_HousesBuying();
    s3_tests::F_TrianglePerimiter();
    s3_tests::G_Wardrobe();
    s3_tests::I_ConferenceLovers();
    s3_tests::H_BigNumber();
    s3_tests::J_Bubble();
    s3_tests::K_MergeSort();
    s3_tests::L_TwoBikes();
    s3_tests::M_GoldMiddle();
    s3_tests::N_FlowerBeds();
    //s3_tests::O_TrashIndexesDifference();
    s3_tests::P_PartialSorting();

    s3_exam_tests::A_BrokenSearch();
    
}
