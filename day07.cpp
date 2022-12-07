#include <deque>
#include <map>
#include <set>
#include <string>
#include <vector>
#include "common.h"

using namespace std;

string to_path(const deque<string>& dirs)
{
    string result;
    for (const string& dir : dirs) {
        if (!result.empty()) result += "/";
        result += dir;
    }
    return "/" + result;
}

struct DirTree {
    set<string> dirs;
    map<string, vector<string>> dir_to_subdirs;
    map<string, vector<pair<string, int>>> dir_to_files;
};

int calculate_dir_size(const string& dir, const DirTree& dir_tree) {
    int dir_size = 0;
    vector<pair<string, int>> files = dir_tree.dir_to_files.contains(dir) ? dir_tree.dir_to_files.at(dir) : vector<pair<string, int>>{};
    for (const auto& file : files) {
        dir_size += file.second;
    }
    vector<string> subdirs = dir_tree.dir_to_subdirs.contains(dir) ? dir_tree.dir_to_subdirs.at(dir) : vector<string>{};
    for (const auto& subdir : subdirs) {
        dir_size += calculate_dir_size(subdir, dir_tree);
    }
    return dir_size;
}

DirTree parse_dir_tree(const vector<string>& lines) {
    map<string, vector<string>> dir_to_subdirs;
    map<string, vector<pair<string, int>>> dir_to_files;
    set<string> dirs;
    deque<string> current_dir;

    for (const string& line : lines) {
        vector<string> tokens = split(line, " ");
        if (tokens[0] == "$" && tokens[1] == "cd") {
            if (tokens[2] == "/") current_dir = { "" };
            else if (tokens[2] == "..") current_dir.pop_back();
            else current_dir.push_back(tokens[2]);
        } else if (tokens[0] == "dir") {
            string path = to_path(current_dir);
            vector<string> subdirs = dir_to_subdirs.contains(path) ? dir_to_subdirs.at(path) : vector<string>{};
            subdirs.push_back(path + (path.ends_with('/') ? "" : "/") + tokens[1]);
            dir_to_subdirs[path] = subdirs;
            dirs.insert(path);
        } else if (tokens[0] != "$") {
            string path = to_path(current_dir);
            vector<pair<string, int>> files = dir_to_files.contains(path) ? dir_to_files.at(path) : vector<pair<string, int>>{};
            const pair<string, int>& file = make_pair(tokens[1], stoi(tokens[0]));
            files.push_back(file);
            dir_to_files[path] = files;
            dirs.insert(path);
        }
    }
    return { dirs, dir_to_subdirs, dir_to_files };
}

int day07a(const vector<string>& lines) {
    DirTree dir_tree = parse_dir_tree(lines);
    int result = 0;
    for (auto const& dir : dir_tree.dirs) {
        int dir_size = calculate_dir_size(dir, dir_tree);
        if (dir_size < 100000) result += dir_size;
    }
    return result;
}

int day07b(const vector<string>& lines) {
    DirTree dir_tree = parse_dir_tree(lines);
    int unused_size = 70000000 - calculate_dir_size("/", dir_tree);
    int required_extra_size = 30000000 - unused_size;
    int result = 99999999;
    for (auto const& dir : dir_tree.dirs) {
        int dir_size = calculate_dir_size(dir, dir_tree);
        if (dir_size >= required_extra_size && dir_size < result) result = dir_size;
    }
    return result;
}