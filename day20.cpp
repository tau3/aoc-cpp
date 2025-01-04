#include <cassert>
#include <cstddef>
#include <limits>
#include <string>
#include <unordered_map>
#include <vector>

namespace Day20 {

using namespace std;

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

Point extract_min(vector<Point> queue,
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
        if ((point.r >= 0) && (point.c >= 0) && (point.r <= (int)grid.size()) &&
            (point.c <= (int)grid[0].size())) {
            result.push_back(point);
        }

        if (grid[point.r][point.c] == '#') {
            continue;
        }
    }

    return result;
}

int run(const Point &start, const vector<string> &grid) {
    vector<Point> queue;
    unordered_map<Point, int, PointHash> distances;
    for (int r = 0; r <= (int)grid.size(); ++r) {
        for (int c = 0; c <= (int)grid[0].size(); ++c) {
            const Point point{r, c};
            if (grid[r][c] != '#') {
                distances[point] = numeric_limits<int>::max();
                queue.push_back(point);
            }
        }
    }
    distances[start] = 0;
    while (!queue.empty()) {
        const Point u = extract_min(queue, distances);
        for (const Point &v : adjacent(u, grid)) {
            int candidate = distances[u] + 1;
            if (distances[v] > candidate) {
                distances[v] = candidate;
            }
        }
    }

    int result = 0;
    vector<Point> path;
    for (auto [k, v] : distances) {
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
                    ++result;
                }
            }
        }
    }

    return result;
}

int solve_day20_pt1(const vector<string> &input) {
    Point start;
    for (size_t r = 0; r < input.size(); ++r) {
        for (size_t c = 0; c < input[0].size(); ++c) {
            if (input[r][c] == 'S') {
                start = {int(r), int(c)};
            }
        }
    }
    return run(start, input);
};

} // namespace Day20
