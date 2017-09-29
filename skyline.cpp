// 2017-09-21
#include <cstdio>
#include <iostream> 
#include <vector>
#include <algorithm> 

using namespace std;

struct Building {
    int startPos;
    int height;
    int width; 
};

struct SkylineSegment {
    int x;
    int y; 
};

vector<SkylineSegment>* ComputeSkyline(vector<SkylineSegment>* skyline1, vector<SkylineSegment>* skyline2);
vector<SkylineSegment>* ComputeSkyline(Building& building1);
vector<SkylineSegment>* ComputeSkyline(Building& building1, Building& building2);
vector<SkylineSegment>* ComputeSkyline(Building* buildings, int start, int end);

int main() {
    int N; scanf("%d", &N);
    Building buildings[N];
    for(int i = 0; i < N; i++) {    
        int s = 0, h = 0, w = 0;        
        scanf("%d %d %d", &s, &h, &w);
        buildings[i].startPos = s;
        buildings[i].height = h;
        buildings[i].width = w;
    }

    vector<SkylineSegment> skyline = *ComputeSkyline(buildings, 0, N-1);
    for(int i = 0; i < skyline.size(); i++)
    {
        cout << skyline[i].x << " " << skyline[i].y << " ";
    }
    cout << endl;
}

vector<SkylineSegment>* ComputeSkyline(Building* buildings, int start, int end) 
{    
    if (end - start == 0)
    {
        return ComputeSkyline(buildings[start]);
    }
    else if (end - start == 1)
    {
        return ComputeSkyline(buildings[start], buildings[end]);
    }
    else
    {
        int midpoint = start + ((end - start) / 2);
        vector<SkylineSegment>* skyline1 = ComputeSkyline(buildings, start, midpoint);
        vector<SkylineSegment>* skyline2 = ComputeSkyline(buildings, midpoint + 1, end);
        vector<SkylineSegment>* combinedSkyline = ComputeSkyline(ComputeSkyline(buildings, start, midpoint), ComputeSkyline(buildings, midpoint + 1, end));

        // deallocate intermediate skylines after merging
        delete skyline1;
        delete skyline2;

        return combinedSkyline;
    }
}

vector<SkylineSegment>* ComputeSkyline(vector<SkylineSegment>* skyline1, vector<SkylineSegment>* skyline2)
{
    vector<SkylineSegment>* combinedSkyline = new vector<SkylineSegment>();
    
    int skyline1Index = 0;
    int skyline2Index = 0;
    int currentYPosition1 = 0;
    int currentYPosition2 = 0;
    int lastCombinedYPosition = 0;

    // assumption: skyline segments are sorted
    while(skyline1Index < skyline1->size() || skyline2Index < skyline2->size())
    {
        SkylineSegment currentSegment;

        if(skyline2Index >= skyline2->size())
        {
            currentSegment = skyline1->at(skyline1Index);
            currentYPosition2 = currentSegment.y;     
            currentYPosition1 = 0;
            skyline1Index++;
        }
        else if(skyline1Index >= skyline1->size())
        {
            currentSegment = skyline2->at(skyline2Index);
            currentYPosition1 = currentSegment.y;    
            currentYPosition2 = 0;        
            skyline2Index++;
        }
        else
        {
            SkylineSegment skyline1Segment = skyline1->at(skyline1Index);
            SkylineSegment skyline2Segment = skyline2->at(skyline2Index);

            if(skyline1Segment.x < skyline2Segment.x) 
            {
                currentSegment = skyline1Segment;
                currentYPosition1 = skyline1Segment.y;
                skyline1Index++;
            }
            else if(skyline1Segment.x > skyline2Segment.x)
            {
                currentSegment = skyline2Segment;
                currentYPosition2 = skyline2Segment.y;
                skyline2Index++;
            }
            else
            {
                if(skyline1Segment.y >= skyline2Segment.y)
                {
                    currentSegment = skyline1Segment;
                }
                else
                {
                    currentSegment = skyline2Segment;
                }

                currentYPosition1 = skyline1Segment.y;
                currentYPosition2 = skyline2Segment.y;                                        

                skyline1Index++;
                skyline2Index++;
            }
        }

        if(max(currentYPosition1, currentYPosition2) != lastCombinedYPosition)
        {
            // update Y position of segment to insert -> max Y position. 
            lastCombinedYPosition = max(currentYPosition1, currentYPosition2);
            currentSegment.y = lastCombinedYPosition;
            combinedSkyline->push_back(currentSegment);
        }
    }

    return combinedSkyline;
}

vector<SkylineSegment>* ComputeSkyline(Building& building1)
{
    vector<SkylineSegment>* skylineSegments = new vector<SkylineSegment>();
    
    SkylineSegment segment1;
    segment1.x = building1.startPos;
    segment1.y = building1.height;
    skylineSegments->push_back(segment1);    

    SkylineSegment segment2;
    segment2.x = building1.startPos + building1.width;
    segment2.y = 0;
    skylineSegments->push_back(segment2);
    
    return skylineSegments;
}

vector<SkylineSegment>* ComputeSkyline(Building& building1, Building& building2)
{
    // Safety: simplify our code by simplifying assumptions
    if(building1.startPos > building2.startPos ||
        (building1.startPos == building2.startPos && building1.height < building2.height))
    {
        return ComputeSkyline(building2, building1);
    }

    vector<SkylineSegment>* skylineSegments = new vector<SkylineSegment>();
    
    SkylineSegment segment1;
    segment1.x = building1.startPos;
    segment1.y = building1.height;
    skylineSegments->push_back(segment1);

    SkylineSegment segment2;    
    if(building2.startPos > building1.startPos + building1.width)
    {
        segment2.x = building1.startPos + building1.width;
        segment2.y = 0;
        skylineSegments->push_back(segment2); 
    }
    
    SkylineSegment segment3;    
    if(building2.height > building1.height ||
          (building2.startPos > building1.startPos + building1.width)) 
    {
        segment3.x = building2.startPos;
        segment3.y = building2.height;
        skylineSegments->push_back(segment3);
    }

    SkylineSegment segment4;    
    SkylineSegment segment5;    
    if(building2.startPos + building2.width > building1.startPos + building1.width)
    {
        if(building1.height > building2.height)
        {
            segment4.x = building1.startPos + building1.width;
            segment4.y = building2.height;
            skylineSegments->push_back(segment4);
            
            segment5.x = building2.startPos + building2.width;
            segment5.y = 0;
            skylineSegments->push_back(segment5);       
        }
        else if(building1.height < building2.height) 
        {
            segment4.x = building2.startPos + building2.width;
            segment4.y = 0;
            skylineSegments->push_back(segment4);  
        } 
        else 
        {
            segment4.x = building2.startPos + building2.width;
            segment4.y = 0;
            skylineSegments->push_back(segment4);
        }
    }
    else if(building2.startPos + building2.width < building1.startPos + building1.width)
    {
        if(building1.height > building2.height) 
        {
            segment4.x = building1.startPos + building1.width;
            segment4.y = 0;
            skylineSegments->push_back(segment4);            
        }
        else if(building1.height < building2.height) 
        {
            segment4.x = building2.startPos + building2.width;
            segment4.y = building1.height;
            skylineSegments->push_back(segment4);
            
            segment5.x = building1.startPos + building1.width;
            segment5.y = 0;
            skylineSegments->push_back(segment5);            
        }
        else
        {
            segment4.x = building1.startPos + building1.width;
            segment4.y = 0;
            skylineSegments->push_back(segment4);     
        }
    }
    else
    {
        segment4.x = building1.startPos + building1.width;
        segment4.y = max(building1.height, building2.height);
        skylineSegments->push_back(segment4);
    }

    return skylineSegments;
}
