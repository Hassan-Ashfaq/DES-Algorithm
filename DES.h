#ifndef DES_H_
#define DES_H_

#include<iostream>
#include<string>
using namespace std;

template<class T>
T initKeyPermutation(T key)
{
    int no = 0;
    T binary = "";
    int key_len = key.length();

    for (int i = 0; i < key_len; i++)
    {
        T tmp = "";
        if (key[i] >= '0' && key[i] <= '9')
        {
            no = int(key[i]) - 48;
            while (no > 0)
            {
                tmp += char(no % 2 + 48);
                no /= 2;
            }
            while (tmp.length() != 4)
            {
                tmp += '0';
            }
            no = 0;
        }
        else {
            no = key[i] - 'A' + 10;
            while (no > 0)
            {
                tmp += char(no % 2 + 48);
                no /= 2;
            }
        }
        for (int j = 3; j >= 0; j--)
        {
            binary += tmp[j];
        }
    }
    int PC1[] = { 57,49,41,33,25,17,9,1,58,50,   // Given in Assignment 
                42,34,26,18,10,2,59,51,43,35,
                27,19,11,3,60,52,44,36,63,55,
                47,39,31,23,15,7,62,54,46,38,
                30,22,14,6,61,53,45,37,29,21,
                13,5,28,20,12,4 };

    int Key[64] = { 0 };
    int permutedKey[56] = { 0 };
    T binary_key = "";

    for (int i = 0; i < 64; i++)
    {
        Key[i] = binary[i] - '0';
    }

    for (int i = 0; i < 56; i++)
    {
        permutedKey[i] = Key[PC1[i] - 1];
        binary_key += to_string(permutedKey[i]);
    }

    return binary_key;
}

template<class T>
T halfCircularShift(T half_key, int index)
{
    for (int i = 0; index != 0; i++)
    {
        int tmp = half_key[0];
        for (int j = 0; j < half_key.size(); j++)
        {
            half_key[j] = half_key[j + 1];
        }
        half_key[half_key.size() - 1] = tmp;
        index--;
    }
    return half_key;
}

template<class T>
T roundPermutation(T key)
{
    int PC2[48] = { 14,17,11,24,1,5,3,28,15,6,21,10,23,   // Given in Assignment
                19,12,4,26,8,16,7,27,20,13,2,41,52,31,
                37,47,55,30,40,51,45,33,48,44,49,39,56,
                34,53,46,42,50,36,29,32 };

    int Key[56] = { 0 };
    int permutedKey[48] = { 0 };
    T binary_key = "";

    for (int i = 0; i < 56; i++)
    {
        Key[i] = key[i] - '0';
    }

    for (int i = 0; i < 48; i++)
    {
        permutedKey[i] = Key[PC2[i] - 1];
        binary_key += to_string(permutedKey[i]);
    }

    return binary_key;
}

template<class T>
T initTextPermutation(T text)
{
    int no = 0;
    T binary = "";
    int key_len = text.length();

    for (int i = 0; i < key_len; i++)
    {
        T tmp = "";
        if (text[i] >= '0' && text[i] <= '9')
        {
            no = int(text[i]) - 48;
            while (no > 0)
            {
                tmp += char(no % 2 + 48);
                no /= 2;
            }
            while (tmp.length() != 4)
            {
                tmp += '0';
            }
            no = 0;
        }
        else {
            no = text[i] - 'A' + 10;
            while (no > 0)
            {
                tmp += char(no % 2 + 48);
                no /= 2;
            }
        }
        for (int j = 3; j >= 0; j--)
        {
            binary += tmp[j];
        }
    }
    int PermutationTable[] = { 58,50,42,34,26,18,10,2,60,52,       //Given in Assignment
                            44,36,28,20,12,4,62,54,46,38,
                            30,22,14,6,64,56,48,40,32,24,
                            16,8,57,49,41,33,25,17,9,1,59,
                            51,43,35,27,19,11,3,61,53,45,
                            37,29,21,13,5,63,55,47,39,31,
                            23,15,7 };
    int Binary_data[64] = { 0 };
    int permutedKey[64] = { 0 };
    T binary_key = "";

    for (int i = 0; i < 64; i++)
    {
        Binary_data[i] = binary[i] - '0';
    }

    for (int i = 0; i < 64; i++)
    {
        permutedKey[i] = Binary_data[PermutationTable[i] - 1];
        binary_key += to_string(permutedKey[i]);
    }

    return binary_key;
}

template<typename T>
T expandHalfText(T rightHalfText)
{
    int EXPANSION_TABLE[48] = { 32,1,2,3,4,5,4,5,6,7,8,9,8,9,10,11,12,13,12,13,14,15,16,
                    17,16,17,18,19,20,21,20,21,22,23, 24,25,24,25,26,27,28,29,28,29,30,
                    31,32,1 };
    int Binary_data[48] = {0};
    T binary_txt = "";

    for (int i = 0; i<rightHalfText.size(); i++)
    {
        Binary_data[i] = rightHalfText[i] - '0';
    }
    for (int i = 0; i < 48; i++)
    {
        binary_txt += to_string(Binary_data[EXPANSION_TABLE[i] - 1]);
    }

    return binary_txt;
}

template<class T>
T XOR(T text, T key)
{
    T XOR_data = "";
    for (int i = 0; i < text.size(); i++)
    {
        if (text[i] == key[i])
        {
            XOR_data += '0';
        }
        else if (text[i] != key[i]) {
            XOR_data += '1';
        }
    }
    return XOR_data;
}

template<class T>
T calcSBox(T text)
{
    int text_data[8][6] = { 0 };
    int limit = 0;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            text_data[i][j] = text[j + limit] - '0';
        }
        limit += 6;
    }

    int row_value[2] = { 0 };
    int col_value[4] = { 0 };

    int x = 0;
    int y = 0;
    int u = 0;
    int v = 1;

    int index_data[8][2] = { 0 };
    int in_i = 0;

    for (int j = 0; j < 8; j++)
    {
        for (int i = 0; i < 2; i++)
        {
            row_value[i] = text_data[x][y];
            y += 5;
            in_i = 0;
        }

        index_data[j][in_i] = row_value[0] * 2 + row_value[1] * 1;
        for (int i = 0; i < 4; i++)
        {
            col_value[i] = text_data[u][v];
            v++;
        }
        index_data[j][in_i + 1] = col_value[0] * 8 + col_value[1] * 4 + col_value[2] * 2 + col_value[3] * 1;
        x++;
        y = 0;
        u++;
        v = 1;
        in_i++;
    }

    int SBOX[8][4][16] = {
        //Box-1
        {
            14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
            0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,
            4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
            15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13
        },
        //Box-2
        {
            15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,
            3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,
            0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,
            13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9
        },
        //Box-3
        {
            10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,
            13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,
            13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,
            1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12
        },
        //Box-4
        {
            7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,
            13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,
            10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,
            3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14
        },
        //Box-5
        {
            2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,
            14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,
            4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,
            11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3
        },
        //Box-6
        {
            12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,
            10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,
            9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,
            4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13
        },
        //Box-7
        {
            4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,
            13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,
            1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,
            6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12
        },
        //Box-8
        {
            13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,
            1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,
            7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,
            2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11
        }

    };

    T calcSBox = "";
    int t = 0;
    int temp = 0;
    T temp_str = "";

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 1; j++)
        {
            temp = SBOX[t][index_data[i][j]][index_data[i][j + 1]];
            while (temp > 0)
            {
                temp_str += to_string(temp % 2);
                temp /= 2;
            }
            while (temp_str.length() != 4)
            {
                temp_str += '0';
            }
            for (int x = 3; x >= 0; x--)
            {
                calcSBox += temp_str[x];
            }
            temp = 0;
            temp_str = "";
        }
        t++;
    }
    return calcSBox;
}

#endif