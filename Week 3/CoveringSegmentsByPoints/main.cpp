#include <algorithm>
#include <cmath>
#include <iostream>
#include <climits>
#include <vector>

using std::vector;


struct Segment {
    int start, end;
    
    Segment() : start(0), end(0) {};
    Segment(int start, int end) : start(start), end(end) {}
    
    int length() const
    {
        return end - start;
    }
    
    bool operator==(const Segment& s) const
    {
        if (start == s.start && end == s.end)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
    bool operator!=(const Segment& s) const
    {
        return !operator==(s);
    }
    
    bool operator<(const Segment& s) const
    {
        if (start < s.start)
        {
            return true;
        }
        else if (start == s.start && length() < s.length())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
    bool operator>(const Segment& s) const
    {
        if (start > s.start)
        {
            return true;
        }
        else if (start == s.start && length() > s.length())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
    bool operator<=(const Segment& s) const
    {
        return !operator>(s);
    }
    
    bool operator>=(const Segment& s) const
    {
        return !operator<(s);
    }
};

Segment overlap(const Segment& left_most, const Segment& right_most)
{
    Segment overlapping_points;
    
    if (right_most.start <= left_most.end)
    {
        // Lines intersect
        overlapping_points.start = std::max( left_most.start, right_most.start );
        overlapping_points.end = std::min( left_most.end, right_most.end );
    }
    
    return overlapping_points;
}

vector<int> optimal_points(const vector<Segment>& segments) {
    vector<int> points;
    
    // Prime the segment
    Segment common_segment = segments.front();
    
    for (auto iter = segments.begin()+1; iter != segments.end(); ++iter)
    {
        auto& segment = *iter;
        
        auto overlapping_points = overlap( common_segment, segment );
        
        if (overlapping_points == Segment(0,0))
        {
            // Doesn't overlap, commit points
            points.emplace_back(common_segment.end);
            common_segment = segment;
        }
        else
        {
            common_segment = overlapping_points;
        }
    }
    
    if (common_segment != Segment(0, 0) )
    {
        points.emplace_back(common_segment.end);
    }
    
    return points;
}

int main() {
    int n;
    std::cin >> n;
    vector<Segment> segments;
    for (size_t i = 0; i < n; ++i) {
        int start, end;
        std::cin >> start >> end;
        segments.emplace_back( Segment(start, end) );
    }

    std::sort(segments.begin(), segments.end(), std::less<Segment>());

    vector<int> points = optimal_points(segments);
    std::cout << points.size() << "\n";
    for (size_t i = 0; i < points.size(); ++i) {
        std::cout << points[i] << " ";
    }
}
