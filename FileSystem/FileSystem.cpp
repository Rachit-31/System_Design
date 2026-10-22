#include <bits/stdc++.h>
using namespace std;

class File {
public:
    int id;
    string name, description, type, content;

    File(int id, string name, string type,
         string description, string content) {
        this->id = id;
        this->name = name;
        this->type = type;
        this->description = description;
        this->content = content;
    }
};

class Directory {
public:
    int id;
    string name;
    Directory* parent;

    unordered_map<string, unique_ptr<Directory>> directories;
    unordered_map<string, unique_ptr<File>> files;

    Directory(int id, string name, Directory* parent = nullptr) {
        this->id = id;
        this->name = name;
        this->parent = parent;
    }
};

class User {
public:
    int id;
    string name;
    Directory root;

    User(int id, string name) : root(0, "/") {
        this->id = id;
        this->name = name;
    }
};

class FileSystem {
private:
    unordered_map<int, unique_ptr<User>> users;
    int nextFileId = 1;
    int nextDirectoryId = 1;

    vector<string> splitPath(const string& path) {
        vector<string> parts;
        stringstream ss(path);
        string part;

        while (getline(ss, part, '/')) {
            if (!part.empty() && part != ".") {
                if (part == "..") {
                    throw invalid_argument("Parent traversal is not allowed");
                }
                parts.push_back(part);
            }
        }

        return parts;
    }

    Directory* getDirectory(User* user, const string& path) {
        if (!user) return nullptr;

        Directory* curr = &user->root;

        for (const string& part : splitPath(path)) {
            auto it = curr->directories.find(part);

            if (it == curr->directories.end()) {
                return nullptr;
            }

            curr = it->second.get();
        }

        return curr;
    }

public:
    bool addUser(int id, const string& name) {
        if (users.count(id)) return false;

        users[id] = make_unique<User>(id, name);
        return true;
    }

    bool createDirectory(int userId, const string& path) {
        auto it = users.find(userId);
        if (it == users.end()) return false;

        vector<string> parts = splitPath(path);
        Directory* curr = &it->second->root;

        for (const string& part : parts) {
            if (curr->files.count(part)) return false;

            auto dirIt = curr->directories.find(part);

            if (dirIt == curr->directories.end()) {
                auto newDir = make_unique<Directory>(
                    nextDirectoryId++, part, curr
                );

                curr->directories[part] = move(newDir);
            }

            curr = curr->directories[part].get();
        }

        return true;
    }

    bool uploadFile(int userId, const string& directoryPath,
                    const string& name, const string& type,
                    const string& description, const string& content) {
        auto it = users.find(userId);
        if (it == users.end() || name.empty() ||
            name == "." || name == ".." ||
            name.find('/') != string::npos) {
            return false;
        }

        Directory* dir = getDirectory(it->second.get(), directoryPath);
        if (!dir) return false;

        if (dir->files.count(name) || dir->directories.count(name)) {
            return false;
        }

        dir->files[name] = make_unique<File>(
            nextFileId++, name, type, description, content
        );

        return true;
    }

    string downloadFile(int userId, const string& path) {
        auto it = users.find(userId);
        if (it == users.end()) return "";

        vector<string> parts = splitPath(path);
        if (parts.empty()) return "";

        string fileName = parts.back();
        parts.pop_back();

        string directoryPath = "/";
        for (const string& part : parts) {
            directoryPath += part + "/";
        }

        Directory* dir = getDirectory(it->second.get(), directoryPath);
        if (!dir) return "";

        auto fileIt = dir->files.find(fileName);
        if (fileIt == dir->files.end()) return "";

        return fileIt->second->content;
    }

    bool deleteFile(int userId, const string& path) {
        auto it = users.find(userId);
        if (it == users.end()) return false;

        vector<string> parts = splitPath(path);
        if (parts.empty()) return false;

        string fileName = parts.back();
        parts.pop_back();

        string directoryPath = "/";
        for (const string& part : parts) {
            directoryPath += part + "/";
        }

        Directory* dir = getDirectory(it->second.get(), directoryPath);
        if (!dir || !dir->files.count(fileName)) return false;

        dir->files.erase(fileName);
        return true;
    }

    bool deleteDirectory(int userId, const string& path) {
        auto it = users.find(userId);
        if (it == users.end()) return false;

        vector<string> parts = splitPath(path);
        if (parts.empty()) return false;

        string name = parts.back();
        parts.pop_back();

        string parentPath = "/";
        for (const string& part : parts) {
            parentPath += part + "/";
        }

        Directory* parent = getDirectory(it->second.get(), parentPath);
        if (!parent) return false;

        auto dirIt = parent->directories.find(name);
        if (dirIt == parent->directories.end()) return false;

        Directory* target = dirIt->second.get();

        if (!target->directories.empty() || !target->files.empty()) {
            return false;
        }

        parent->directories.erase(dirIt);
        return true;
    }

    bool listDirectory(int userId, const string& path) {
        auto it = users.find(userId);
        if (it == users.end()) return false;

        Directory* dir = getDirectory(it->second.get(), path);
        if (!dir) return false;

        cout << "\nDirectory: " << path << "\n";

        cout << "Subdirectories:\n";
        for (const auto& [name, subdir] : dir->directories) {
            cout << "  [DIR]  " << name << "\n";
        }

        cout << "Files:\n";
        for (const auto& [name, file] : dir->files) {
            cout << "  [FILE] " << name
                 << " | Type: " << file->type
                 << " | Description: " << file->description
                 << "\n";
        }

        return true;
    }
};

int main() {
    FileSystem fs;

    fs.addUser(1, "Rachit");
    fs.addUser(2, "Aman");

    fs.createDirectory(1, "/Documents/Work");
    fs.createDirectory(2, "/Documents/Personal");

    fs.uploadFile(
        1, "/Documents/Work",
        "report.pdf", "application/pdf",
        "Work report", "Report content"
    );

    fs.uploadFile(
        2, "/Documents/Personal",
        "report.pdf", "application/pdf",
        "Personal report", "Personal report content"
    );

    fs.listDirectory(1, "/Documents/Work");
    fs.listDirectory(2, "/Documents/Personal");

    cout << "\nDownloaded content: "
         << fs.downloadFile(1, "/Documents/Work/report.pdf")
         << "\n";

    fs.deleteFile(1, "/Documents/Work/report.pdf");
    fs.listDirectory(1, "/Documents/Work");

    fs.deleteDirectory(1, "/Documents/Work");

    return 0;
}