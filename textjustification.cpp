// 2017-09-29
#include <cstdio>
#include <iostream> 
#include <vector>
#include <algorithm> 

using namespace std;

vector<string> fullJustify(vector<string>& words, int maxWidth);

int main() {
    vector<string> words = { "This", "is", "an", "example", "of", "text", "justification." };
    vector<string> justifiedWords = fullJustify(words, 8);

    for(auto line = words.begin(); line != words.end(); line++) 
    {
        cout << *line << endl;
    }
}

vector<string> fullJustify(vector<string>& words, int maxWidth) 
{
    return words;
}
