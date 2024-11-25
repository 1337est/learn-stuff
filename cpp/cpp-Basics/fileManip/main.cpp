#include <cstdio>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>

class Crud {
private:
    std::string m_path;

public:
    Crud(const std::string& path)
        : m_path{ path }
    {
        // create output directory if it doesn't exist
        std::filesystem::path dir = std::filesystem::path(m_path).parent_path();
        if (!std::filesystem::exists(dir)) {
            std::cout << "Creating output directory " << dir << '\n';
            std::filesystem::create_directory(dir);
        }
    }

    // CREATING A FILE
    void createFile(const std::string& inputText) {
        std::ofstream file(m_path);
        if (file.is_open()) {
            file << inputText;
            file.close();
        } else {
            std::cerr << "Unable to create file\n";
        }
    }

    // READING A FILE
    void readFile() const {
        std::ifstream file(m_path);
        std::string text{};

        if (file.is_open()) {
            while (getline(file, text)) {
                std::cout << text << '\n';
            }
            file.close();
        } else {
            std::cerr << "Unable to read file\n";
        }
    }

    // UPDATE A FILE
    void updateFile(const std::string& oldText, const std::string& newText) {
        std::ifstream readFile(m_path);
        std::ofstream writeFile("./output/tempfile.txt");
        std::string text{};

        if (readFile.is_open() && writeFile.is_open()) {
            while (getline(readFile, text)) {
                std::size_t pos = text.find(oldText);
                while (pos != std::string::npos) {
                    text.replace(pos, oldText.size(), newText);
                    pos = text.find(oldText, pos + newText.size());
                }
                writeFile << text << '\n';
            }
            readFile.close();
            writeFile.close();

            std::remove(m_path.c_str());
            std::rename("./output/tempfile.txt", m_path.c_str());
        } else {
            std::cerr << "Unable to update file\n";
        }
    }


    // DELETE A FILE
    void deleteFile() const {
        if (std::remove(m_path.c_str()) == 0) {
            std::cout << "File deleted successfully\n";
        } else {
            std::cerr << "Unable to delete file\n";
        }
    }
};

int main() {
    Crud cruddyFile("./output/file.txt");

    // CREATE
    cruddyFile.createFile("STOP LOOKING AT ME!");

    // READ
    cruddyFile.readFile();

    // UPDATE
    cruddyFile.updateFile("STOP", "KEEP");

    // READ updated file
    cruddyFile.readFile();

    // DELETE
    cruddyFile.deleteFile();

    return 0;
}
