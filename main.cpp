#include<iostream>
#include<string>
#include "DES.h"
using namespace std;

int main()
{
    string key = "";
    cout << "Enter Key in Hexa_decimal : ";
    cin >> key;

    string txt = "";
    cout << "Enter text in Hexa_decimal : ";
    cin >> txt;

    cout << endl;
    string binary_key = initKeyPermutation(key);
    string binary_txt = initTextPermutation(txt);

    string key_left_half = "";
    string key_right_half = "";

    for (int i = 0; i < 28; i++)
    {
        key_left_half += binary_key[i];
        key_right_half += binary_key[i + 28];
    }

    string txt_left_half = "";
    string txt_right_half = "";

    for (int i = 0; i < 32; i++)
    {
        txt_left_half += binary_txt[i];
        txt_right_half += binary_txt[i + 32];
    }

    string new_left_half = "";
    string new_right_half = "";
    string new_key = "";
    string new_permutated_key = "";
    string new_txt_right_half = "";
    string SBOX_calc = "";
    string XOR_output = "";
    string Last = "";

    int round_shifts[16] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };

    for (int i = 0; i < 16; i++)
    {
        new_left_half = halfCircularShift(key_left_half, round_shifts[i]);
        new_right_half = halfCircularShift(key_right_half, round_shifts[i]);

        new_key = new_left_half;
        for (int j = 0; j < 28; j++)
        {
            new_key += new_right_half[j];
        }

        new_permutated_key = roundPermutation(new_key);
        new_txt_right_half = expandHalfText(txt_right_half);
        XOR_output = XOR(new_txt_right_half, new_permutated_key);
        SBOX_calc = calcSBox(XOR_output);
        Last = XOR(txt_left_half, SBOX_calc);        
        key_left_half = new_left_half;
        key_right_half = new_right_half;
        txt_left_half = txt_right_half;
        txt_right_half = Last;
    }

    string final_Step = txt_left_half;
    for (int i = 0; i < 32; i++)
    {
        final_Step += txt_right_half[i];
    }

    int INVERSE_PERMUTATION_TABLE[] = { 40 , 8 , 48 , 16 , 56 , 24 , 64 , 32,
    39 , 7 , 47 , 15 , 55 , 23 , 63 , 31, 38 , 6 , 46, 14 , 54 , 22 , 62 , 30,
    37 , 5 , 45 , 13 , 53 , 21 , 61 , 29, 36 , 4 , 44 , 12 , 52, 20, 60 , 28 ,
    35 , 3 , 43 , 11 , 51 , 19 , 59 , 27, 34 , 2 , 42 , 10 , 50 , 18 , 58 , 26 ,
    33 , 1 , 41 , 9 , 49 , 17 , 57 , 25 };

    string result = "";
    for (int i = 0; i < 64; i++)
    {
        result += final_Step[INVERSE_PERMUTATION_TABLE[i] - 1];
    }
    cout << "Encrypted Message in Binary : " << result << endl;

    int Data[16][4] = { 0 };
    int limit = 0;
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            Data[i][j] = result[j + limit] - '0';
        }
        limit += 4;
    }

    string Encrypted = "";
    int temp = 0;
    for (int i = 0; i < 16; i++)
    {
        temp = Data[i][0] * 8 + Data[i][1] * 4 + Data[i][2] * 2 + Data[i][3] * 1;
        if (temp > 9)
        {
            Encrypted += char(temp + 55);
        }
        else
        {
            Encrypted += to_string(temp);
        }
    }
    cout << "Encrypted Message in Hexa_decimal : " << Encrypted << endl;

    return 0;
}