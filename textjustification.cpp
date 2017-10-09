// 2017-09-29
#include <cstdio>
#include <iostream> 
#include <vector>
#include <algorithm> 

using namespace std;

string constructJustifiedLine(vector<string>& words, int start, int end, int maxWidth, int currentWidth) ;
vector<string> fullJustify(vector<string>& words, int maxWidth);

int main() {
    vector<string> words = {"Listen","to","many,","speak","to","a","few."};
    vector<string> lines = fullJustify(words, 6);

    for(auto line = lines.begin(); line != lines.end(); line++) 
    {
        cout << *line << "|" << endl;
    }
}

vector<string> fullJustify(vector<string>& words, int maxWidth) 
{
    vector<string> result;
    int currentWidth = 0;
    int startIndexForCurrentLine = 0;

    for(int i = 0; i < words.size(); i++) 
    {
        string word = words[i];
        if(currentWidth + word.length() > maxWidth)
        {
            // Subtract 1 from currentWidth, since last word did not fit... but we accounted an extra final space
            result.push_back(constructJustifiedLine(words, startIndexForCurrentLine, i - 1, maxWidth, currentWidth - 1));
            currentWidth = word.length() + 1;
            startIndexForCurrentLine = i;
        }
        else if(currentWidth + word.length() == maxWidth) 
        {
            result.push_back(constructJustifiedLine(words, startIndexForCurrentLine, i, maxWidth, currentWidth + word.length()));
            currentWidth = 0;
            startIndexForCurrentLine = i + 1;
        }
        else 
        {
            currentWidth = currentWidth + word.length() + 1;
        }
    }

    if(startIndexForCurrentLine < words.size())
    {
        string lastLine = "";
        // Last line of text should "be left justified and no extra space is inserted between words" 
        for(int i = startIndexForCurrentLine; i < words.size(); i++)
        {
            lastLine = lastLine + words[i];
            if(i != words.size() - 1)
            {
                lastLine = lastLine + ' ';
            }
        }
        int extraSpacesNeedForLastLine = maxWidth - lastLine.length();
        for(int j = 0; j < extraSpacesNeedForLastLine; j++)
        {
            lastLine = lastLine + ' ';
        }
        
        result.push_back(lastLine);
    }
    
    return result;
}

string constructJustifiedLine(vector<string>& words, int start, int end, int maxWidth, int currentWidth) 
{
    string joinedWord = "";
    int extraWidth = maxWidth - currentWidth;
    int spaceSize = (end - start > 0) ? extraWidth / (end - start) : 0;
    int indivisibleSpaces = (end - start > 0) ? extraWidth % (end - start) : 0;

    for(int i = start; i < end; i++)
    {
        joinedWord += words[i];

        // add single space
        joinedWord = joinedWord + ' ';
        
        // extra space for all but last word
        for(int j = 0; j < spaceSize; j++)
        {
            joinedWord = joinedWord + ' ';
        }

        if(indivisibleSpaces > 0)
        {
            joinedWord = joinedWord + ' ';
            indivisibleSpaces -= 1;
        }
    }

    // add last word without extra spaces
    joinedWord = joinedWord + words[end];

    int extraSpacesNeedForSingleWord = maxWidth - joinedWord.length();
    for(int j = 0; j < extraSpacesNeedForSingleWord; j++)
    {
        joinedWord = joinedWord + ' ';
    }

    return joinedWord;
} 
