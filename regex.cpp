// 2017-09-17
#include <stdio.h>
#include <iostream> 
#include <algorithm> 

using namespace std;

bool isMatch(string s, string p);
bool isMatch(string s, string p, int sIndex, int pIndex);

int main() {
    cout << isMatch("ab", ".*") << endl;
}

bool isMatch(string s, string p) {
    return isMatch(s, p, 0, 0);
}

bool isMatch(string s, string p, int sIndex, int pIndex) {
    char currentPChar;
    bool isKleeneStar = false;
    int pSize = p.size();
    int sSize = s.size();

    for(; pIndex < pSize; pIndex++)
    {
        currentPChar = p[pIndex];
        if(pIndex < pSize - 1 && p[pIndex + 1] == '*')
        {
            isKleeneStar = true;
            pIndex++;
        }
        else
        {
            isKleeneStar = false;
        }

        if(sIndex >= sSize)
        {
            return false;
        }
        else if(!isKleeneStar) 
        {
            if(currentPChar == '.' || currentPChar == s[sIndex])
            {
                sIndex++;
            }
            else
            {
                return false;
            }
        }
        else 
        {
            while(sIndex < sSize)
            {
                if(currentPChar == '.' || currentPChar == s[sIndex])
                {
                    if(isMatch(s, p, sIndex, pIndex + 1))
                    {
                        return true;
                    }

                    sIndex++;
                }
                else
                {
                    break;
                }
            }
        }
    }

    return sIndex == sSize;
}