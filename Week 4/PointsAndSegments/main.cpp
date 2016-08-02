#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;


enum Type
{
    START = 0,
    POINT = 1,
    END = 2
};

struct Point
{
    Point(int point, size_t index, Type type) : point(point), index(index), type(type) {}
    
    int point;
    size_t index;
    Type type;
    
    bool operator==(const Point& p) const
    {
        if (point == p.point)
        {
            if (type == p.type)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    
    bool operator!=(const Point& p) const
    {
        return !operator==(p);
    }
    
    bool operator<(const Point& p) const
    {
        if (point < p.point)
        {
            return true;
        }
        else if (point == p.point)
        {
            return type < p.type;
        }
        else
        {
            return false;
        }
    }
    
    bool operator>(const Point& p) const
    {
        return !operator<(p);
    }
    
    bool operator<=(const Point& p) const
    {
        return !operator>(p);
    }
    
    bool operator>=(const Point& p) const
    {
        return !operator<(p);
    }
};

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

vector<int> fast_count_segments(vector<int>& starts, vector<int>& ends, vector<int>& points) {
    vector<int> cnt(points.size());
    
    vector<Point> line;
    
    for (size_t s = 0; s < starts.size(); ++s)
    {
        line.emplace_back( Point(starts[s], s, Type::START) );
    }
    
    for (size_t e = 0; e < ends.size(); ++e)
    {
        line.emplace_back( Point(ends[e], e, Type::END) );
    }
    
    for (size_t p = 0; p < points.size(); ++p)
    {
        line.emplace_back( Point(points[p], p, Type::POINT) );
    }
    
    std::sort(line.begin(), line.end());
    
    long long open_segments { 0 };
    for (auto& point : line)
    {
        if (point.type == START)
        {
            ++open_segments;
        }
        else if (point.type == POINT)
        {
            cnt[point.index] += open_segments;
        }
        else
        {
            --open_segments;
        }
    }
    
    return cnt;
}

vector<int> naive_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
    vector<int> cnt(points.size());
    for (size_t i = 0; i < points.size(); i++) {
        for (size_t j = 0; j < starts.size(); j++) {
            cnt[i] += starts[j] <= points[i] && points[i] <= ends[j];
        }
    }
    return cnt;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    vector<int> starts(n), ends(n);
    for (size_t i = 0; i < starts.size(); i++) {
        std::cin >> starts[i] >> ends[i];
    }
    vector<int> points(m);
    for (size_t i = 0; i < points.size(); i++) {
        std::cin >> points[i];
    }
    
    //use fast_count_segments
    //vector<int> cnt = naive_count_segments(starts, ends, points);
    //for (size_t i = 0; i < cnt.size(); i++) {
    //    std::cout << cnt[i] << ' ';
    //}
    
    //std::cout << std::endl;
    
    vector<int> cnt2 = fast_count_segments(starts, ends, points);
    for (size_t i = 0; i < cnt2.size(); i++) {
        std::cout << cnt2[i] << ' ';
    }
}
