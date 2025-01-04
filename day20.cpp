#include "day20.hpp"
#include <cassert>
#include <cstddef>
#include <iostream>
#include <limits>
#include <unordered_map>
#include <stack>

namespace Day20 {

struct Point {
    int r;
    int c;
};

bool operator==(const Point &lhs, const Point &rhs) {
    return (lhs.r == rhs.r) && (lhs.c == rhs.c);
}

struct PointHash {
    size_t operator()(const Point &point) const {
        const auto [r, c] = point;
        return 31 * r + 17 * c;
    }
};

Point extract_min(vector<Point> &queue,
                  const unordered_map<Point, int, PointHash> distances) {
    assert(!queue.empty());

    Point result = queue[0];
    int min_distance = distances.at(result);
    size_t index = 0;
    for (size_t i = 1; i < queue.size(); ++i) {
        const Point current = queue[i];
        const int distance = distances.at(current);
        if (distance < min_distance) {
            result = current;
            min_distance = distance;
            index = i;
        }
    }
    queue.erase(queue.begin() + index);
    return result;
}

vector<Point> adjacent(const Point &point, const vector<string> &grid) {
    const auto [x, y] = point;
    vector<Point> all = {{x - 1, y}, {x + 1, y}, {x, y + 1}, {x, y - 1}};

    vector<Point> result;
    for (const Point &point : all) {
        if (grid[point.r][point.c] == '#') {
            continue;
        }

        if ((point.r >= 0) && (point.c >= 0) && (point.r < (int)grid.size()) &&
            (point.c < (int)grid[0].size())) {
            result.push_back(point);
        }
    }

    return result;
}

int run(const Point &start, const vector<string> &grid) {
    vector<Point> queue;
    unordered_map<Point, int, PointHash> distances;
    for (int r = 0; r < (int)grid.size(); ++r) {
        for (int c = 0; c < (int)grid[0].size(); ++c) {
            if (grid[r][c] != '#') {
                const Point point{r, c};
                distances[point] = numeric_limits<int>::max();
                // queue.push_back(point);
            }
        }
    }
    distances[start] = 0;

    cout << "before queue" << endl;
    while (!queue.empty()) {
        const Point u = extract_min(queue, distances);
        // cout << "pop(" << u.r << "," << u.c << ")" << endl;
        if (distances.find(u) != distances.end()) {
            continue;
        }
        for (const Point &v : adjacent(u, grid)) {
            const int candidate = distances[u] + 1;
            if (distances[v] > candidate) {
                distances[v] = candidate;
            }
        }
    }
    cout << "after queue" << endl;

    int result = 0;
    vector<Point> path;
    for (const auto &[k, _] : distances) {
        path.push_back(k);
    }

    for (size_t i = 0; i < path.size(); ++i) {
        for (size_t j = i + 1; j < path.size(); ++j) {
            const Point &lhs = path[i];
            const Point &rhs = path[j];
            const int dist = abs(lhs.r - rhs.r) + abs(lhs.c - rhs.c);
            if (dist == 2) {
                const int saved = abs(distances[lhs] - distances[rhs]);
                if (saved >= 100) {
                    cout << "from(" << lhs.r << "," << lhs.c << ")" << endl;
                    cout << "to(" << rhs.r << "," << rhs.c << ")" << endl;
                    cout << "saved " << saved << endl;
                    ++result;
                }
            }
        }
    }

    return result;
}

int solve_day20_pt1(const vector<string> &input) {
    cout << "go" << endl;
    Point start;
    for (size_t r = 0; r < input.size(); ++r) {
        for (size_t c = 0; c < input[0].size(); ++c) {
            if (input[r][c] == 'S') {
                start = {int(r), int(c)};
            }
        }
    }
    cout << "start " << start.r << " " << start.c << endl;
    return run(start, input);
};

} // namespace Day20
