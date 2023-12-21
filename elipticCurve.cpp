#include <bits/stdc++.h>
using namespace std;

bool isValid(int x, int y, int p) {
    return (y * y - x * x * x - x - 2) % p == 0;
}

vector<pair<int, int>> findPoints(int p) {
    vector<pair<int, int>> points;

    for (int x = 0; x < p; x++) {
        for (int y = 0; y < p; y++) {
            if (isValid(x, y, p)) {
                points.push_back(make_pair(x, y));
            }
        }
    }
    return points;
}

pair<int, int> add(pair<int, int> P, pair<int, int> Q, int p) {

    if (P.first == -1 || Q.first == -1) { 
        return make_pair(-1, -1);
    }

    double l;
    if (P.first == Q.first) {
        if ((P.second + Q.second) % p == 0) {
            return make_pair(-1, -1);
        } else {
            l = (((3 * P.first * P.first + 1)%p) * fmod((pow(2 * P.second, p - 2)), p));
        }
    } else {
        l = (((Q.second - P.second)%p) * fmod(pow(Q.first - P.first, p - 2), p));
    }

    int x = (int(l * l - P.first - Q.first) + p) % p;
    int y = (int(l * (P.first - x) - P.second) + p) % p;

    return make_pair(x, y);
}

pair<int, int> generator(const vector<pair<int, int>>& points, int p) {
    for (const auto& generator : points) {
        auto current_point = generator;
        int count = 0;
        while (current_point.first != -1) {
            current_point = add(current_point, generator, p);
            count++;
            if (count == (points.size() - 1)) {
                return generator;
            }
        }
    }
    return make_pair(-1, -1);
}

int main() {
    int p = 13;
    auto points = findPoints(p);
    auto g = generator(points, p);

    cout<<"Points on the curve:";
    for (const auto& point : points) {
        cout<<"\n("<<point.first<<", "<<point.second<<"),";
    }
    cout<<"\ninfinity\n";
    cout<<"Number of points: "<<points.size() + 1<<endl;
    cout << "Generator: (" << g.first << ", " << g.second << ")" << endl;

    return 0;

}
