#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include <arpa/inet.h>
#include <unistd.h>

// ---------------- RESP ENCODER ----------------
std::string encodeResp(const std::vector<std::string>& args) {
    std::ostringstream out;

    out << "*" << args.size() << "\r\n";

    for (const auto& arg : args) {
        out << "$" << arg.size() << "\r\n";
        out << arg << "\r\n";
    }

    return out.str();
}

// ---------------- SEND COMMAND ----------------
void sendCommand(int sock, const std::vector<std::string>& cmd) {
    std::string data = encodeResp(cmd);
    send(sock, data.c_str(), data.size(), 0);
}

// ---------------- MAIN ----------------
int main(int argc, char* argv[]) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "Socket creation failed\n";
        return 1;
    }

    sockaddr_in server{};
    server.sin_family = AF_INET;
    server.sin_port = htons(6379);

    if (inet_pton(AF_INET, "127.0.0.1", &server.sin_addr) <= 0) {
        std::cerr << "Invalid address\n";
        return 1;
    }

    if (connect(sock, (sockaddr*)&server, sizeof(server)) < 0) {
        std::cerr << "Connection failed\n";
        return 1;
    }

    // -------- TEST COMMANDS --------
    // 1. Ensure the user actually passed a command
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <command> [args...]\n";
        std::cerr << "Example: " << argv[0] << " SET key hello\n";
        return 1;
    }

    // ... your socket connection initialization (e.g., creating 'sock') ...

    // 2. Build the command vector directly from argv
    std::vector<std::string> command;
    for (int i = 1; i < argc; ++i) {
        command.push_back(argv[i]);
    }

    // 3. Send the single dynamic command
    sendCommand(sock, command);
    //sendCommand(sock, {"SET", "key", "hello"});

    // -------- READ RESPONSE --------
    char buffer[1024] = {0};
    int bytes = recv(sock, buffer, sizeof(buffer), 0);

    if (bytes > 0) {
        std::cout << "Response:\n";
        std::cout << std::string(buffer, bytes) << std::endl;
    } else {
        std::cout << "No response\n";
    }

    close(sock);
    return 0;
}