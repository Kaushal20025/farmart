#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> // For system() to create directories

void extract_logs(const std::string& log_file, const std::string& date) {
    std::ifstream infile(log_file);
    if (!infile) {
        std::cerr << "Error: Unable to open log file: " << log_file << "\n";
        return;
    }

    // Ensure the output directory exists
    #ifdef _WIN32
        system("if not exist output mkdir output"); // Windows
    #else
        system("mkdir -p output"); // Linux/macOS
    #endif

    // Create output file
    std::string output_file = "output/output_" + date + ".txt";
    std::ofstream outfile(output_file);
    if (!outfile) {
        std::cerr << "Error: Unable to create output file.\n";
        return;
    }

    std::string line;
    while (std::getline(infile, line)) {
        if (line.rfind(date, 0) == 0) {  // Check if line starts with the given date
            outfile << line << "\n";
        }
    }

    infile.close();
    outfile.close();
    std::cout << "Logs for " << date << " saved to " << output_file << "\n";
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: ./extract_logs YYYY-MM-DD\n";
        return 1;
    }

    std::string log_file = "test_logs.log";  // Name of the log file
    std::string date = argv[1];  // Date from command-line argument

    extract_logs(log_file, date);
    return 0;
}
