#include <algorithm>
#include <cmath>
#include <iostream>
#include <climits>
#include <vector>

using std::vector;


struct Segment {
    int start, end;
    
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

vector<int> gen_range(const Segment& s)
{
    vector<int> range;
    for (int i = s.start; i <= s.end; ++i)
    {
        range.emplace_back(i);
    }
    return range;
}

vector<int> diff(const vector<int>& left, const vector<int>& right)
{
    vector<int> intersection;
    std::set_intersection(left.begin(),
                          left.end(),
                          right.begin(),
                          right.end(),
                          std::back_inserter(intersection));
    return intersection;
}

vector<int> optimal_points(const vector<Segment>& segments) {
    vector<int> points;
    vector<int> common_points;
    
    // Prime common points with first element
    common_points = diff(gen_range(segments.front()),
                         gen_range(segments.front()) );
    
    for (auto iter = segments.begin()+1; iter != segments.end(); ++iter)
    {
        auto& segment = *iter;
        
        auto new_segment_range = gen_range(segment);
        auto point_diff = diff(common_points, new_segment_range);
        if (point_diff.empty())
        {
            // Commit points
            points.emplace_back(common_points.back());
            common_points = new_segment_range;
        }
        else
        {
            // Continue to next segment
            common_points = point_diff;
        }
    }
    
    // Commit last point if there is one
    if (!common_points.empty())
    {
        points.emplace_back(common_points.back());
    }
    
    return points;
}

void print_segments(const vector<Segment>& segments)
{
    std::cout << '\n';
    for (auto& s : segments)
    {
        std::cout << s.start << ' ' << s.end << std::endl;
    }
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
