/*
**terminal command to compile:**
    g++ DES.cpp
**terminal command to run:**
    ./a.out
make sure the file "DES.h" is in the same directory as DES.cpp

Submitted by:
Name: Saad Sakib Noor
Roll: BSSE1122
*/

#include<iostream>
#include<vector>
#include<algorithm>
#include "DES.h"

#define vstring vector<string>

using namespace std;

void rounds(string &left, string &right, vstring rkb, vstring rkh);
string encrypt(string plainText, vstring rkb, vstring rkh);
vstring key_process(string key);

int main()
{
    string msg = "123456ABCD132536";
    string key = "ACBB091A2736CCDC";
    cout<< "Plain Text: "<< msg<< "\n\n";
    vstring rkb= key_process(key);
    vstring rkh;
    for(int i=0; i<16; i++)
    {    
        // cout<< bin2hex(rkb[i])<< endl;
        rkh.push_back(bin2hex(rkb[i]));
    }

    cout<< "Encrypting:\n\n";
    string cipher= encrypt(msg, rkb, rkh);
    cout<< "\nCipher Text: "<< cipher<< endl;

    cout<< "\nDecrypting:\n\n";
    reverse(rkb.begin(), rkb.end());
    reverse(rkh.begin(), rkh.end());

    string original_text= encrypt(cipher, rkb, rkh);
    cout<< "\nPlain Text: "<< original_text<< endl;
}

void rounds(string &left, string &right, vstring rkb, vstring rkh)
{
    for(int i=0; i<16; i++)
    {
        //expanding right partition to 48 bits
        string right_expanded = permute(right, exp_d, 48);
 
        // XOR RoundKey[i] and right_expanded
        string x = XOR(rkb[i], right_expanded);
 
        // S-boxes
        string op = "";
        for (int i = 0; i < 8; i++) {
            int row = 2 * int(x[i * 6] - '0') + int(x[i * 6 + 5] - '0');
            int col = 8 * int(x[i * 6 + 1] - '0') + 4 * int(x[i * 6 + 2] - '0') + 2 * int(x[i * 6 + 3] - '0') + int(x[i * 6 + 4] - '0');
            int val = s[i][row][col];
            op += char(val / 8 + '0');
            val = val % 8;
            op += char(val / 4 + '0');
            val = val % 4;
            op += char(val / 2 + '0');
            val = val % 2;
            op += char(val + '0');
        }
        // Straight D-box
        op = permute(op, straight_perm, 32);
 
        // XOR left and op
        x = XOR(op, left);
 
        left = x;

        if(i!=15) 
            swap(left, right);

        cout<< "Round "<< i+1<< ": "<< bin2hex(left)<< " "<< bin2hex(right)<< " "<< rkh[i]<< endl;
    }
}


string encrypt(string plainText, vstring rkb, vstring rkh)
{
    plainText= hex2bin(plainText);  //convert plain text to binary
    plainText= permute(plainText, initialPerm_Table, 64);   //initial permutation on plain text
    cout<< "Plaintext after initial permutation: "<< bin2hex(plainText)<< endl;

    // partitioning plaintext
    string left_part= plainText.substr(0, 32);
    string right_part= plainText.substr(32, 32);
    cout<< "Plaintext after partitioning: left="<< bin2hex(left_part)
        << " , right="<< bin2hex(right_part)<< endl;

    rounds(left_part, right_part, rkb, rkh);
    string cipher= left_part+right_part;

    cipher= bin2hex(permute(cipher, finalPerm_table, 64));
    return cipher;
}

vstring key_process(string key)
{
    using namespace key;
    key= hex2bin(key);
    // converting 64bit key to 56 bit
    key= permute(key, parityBit, 56);

    string left_key= key.substr(0, 28);
    string right_key= key.substr(28, 28);

    vstring rkb;

    for(int i=0; i<16; i++)
    {
        left_key= shift_left(left_key, shift_table[i]);
        right_key= shift_left(right_key, shift_table[i]);
        string comp= left_key+right_key;
        //compressing key to make it 48bit
        string roundKey= permute(comp, compression_Table, 48);
        rkb.push_back(roundKey);
    }

    return rkb;
}