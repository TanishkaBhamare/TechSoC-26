//
// Created by TANISHKA on 23-10-2026.
//
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

const std::string SAFE_CHARS =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

long long modPow(long long m, long long e, long long n) {
    long long result = 1;
    m %= n;
    for (long long i = 0; i < e; i++) {
        result = (result * m) % n;
    }
    return result;
}

int gcd(int a, int b) {
    while (b != 0) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}


std::string toBinary(unsigned char c, int bits = 8) {
    std::string bin = "";
    for (int i = bits - 1; i >= 0; i--) {
        if ((c >> i) & 1) {
            bin += '1';
        } else {
            bin += '0';
        }
    }
    return bin;
}

long long binaryToDecimal(const std::string& bin) {
    long long decimal = 0;
    for (char bit : bin) {
        decimal = decimal * 2 + (bit - '0');
    }
    return decimal;
}

std::string RSA_ENC(const std::string& msg, long long n, long long e) {
    std::string result = "";
    for (size_t i = 0; i < msg.length(); i++) {
        long long m = static_cast<unsigned char>(msg[i]);
        long long c = modPow(m, e, n);
        if (i > 0) {
            result += "-";
        }
        result += std::to_string(c);
    }
    return result;
}

std::string RSA_DEC(const std::string& cipher, long long n, long long d) {
    std::string result = "";
    std::string numStr = "";

    for (char ch : cipher) {
        if (ch == '-') {
            // We hit a dash, so process the number we just built
            long long c = std::stoll(numStr);
            long long m = modPow(c, d, n);
            result += static_cast<char>(m);
            numStr = ""; // Reset for the next number
        } else {
            numStr += ch;
        }
    }

    // Process the final number after the last dash
    if (!numStr.empty()) {
        long long c = std::stoll(numStr);
        long long m = modPow(c, d, n);
        result += static_cast<char>(m);
    }

    return result;
}

std::string B64_ENC(const std::string& input) {
    std::string joined = "";
    for (size_t i = 0; i < input.length(); i++) {
        joined += toBinary(static_cast<unsigned char>(input[i]), 8);
    }

    // Padding with '0' bits so the bit string length is a multiple of 6
    while (joined.length() % 6 != 0) {
        joined += '0';
    }

    std::string encoded = "";
    for (size_t i = 0; i < joined.length(); i += 6) {
        long long idx = binaryToDecimal(joined.substr(i, 6));
        encoded += SAFE_CHARS[idx];
    }

    // Add '=' padding based on input byte length modulo 3
    if (input.length() % 3 == 1) {
        encoded += "==";
    } else if (input.length() % 3 == 2) {
        encoded += "=";
    }

    return encoded;
}

std::string B64_DEC(const std::string& input) {
    std::string joined = "";
    for (size_t i = 0; i < input.length(); i++) {
        if (input[i] == '=') {
            break;
        }
        size_t idx = SAFE_CHARS.find(input[i]);
        if (idx != std::string::npos) {
            joined += toBinary(static_cast<unsigned char>(idx), 6);
        }
    }

    std::string decoded = "";
    for (size_t i = 0; i + 8 <= joined.length(); i += 8) {
        long long asciiVal = binaryToDecimal(joined.substr(i, 8));
        decoded += static_cast<char>(asciiVal);
    }

    return decoded;
}


long long findPrivateKey(long long p, long long q, long long e) {
    long long phi = (p - 1) * (q - 1);
    for (long long d = 1; d <= phi; d++) {
        if ((e * d) % phi == 1) {
            return d;
        }
    }
    return -1;
}


long long breakToyRSA(long long n, long long e) {
    for (long long p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            long long q = n / p;
            return findPrivateKey(p, q, e);
        }
    }
    return -1;
}

std::vector<std::string> parseOperations(const std::string& arrStr) {
    std::vector<std::string> ops;
    if (arrStr.length() < 2) return ops;

    // Strip outer '[' and ']'
    std::string inner = arrStr.substr(1, arrStr.length() - 2);
    std::string current = "";
    int parenDepth = 0;

    for (char ch : inner) {
        if (ch == '(') {
            parenDepth++;
            current += ch;
        } else if (ch == ')') {
            parenDepth--;
            current += ch;
        } else if (ch == ',' && parenDepth == 0) {
            if (!current.empty()) {
                ops.push_back(current);
                current = "";
            }
        } else {
            current += ch;
        }
    }
    if (!current.empty()) {
        ops.push_back(current);
    }
    return ops;
}

int main() {
    std::string currentMsg;
    std::string opsArrayStr;

    if (!(std::cin >> currentMsg >> opsArrayStr)) {
        return 0;
    }

    std::vector<std::string> operations = parseOperations(opsArrayStr);

    for (const std::string& op : operations) {
        if (op == "B64_ENC") {
            currentMsg = B64_ENC(currentMsg);
        } else if (op == "B64_DEC") {
            currentMsg = B64_DEC(currentMsg);
        } else if (op.rfind("RSA_ENC(", 0) == 0) {
            size_t openParen = op.find('(');
            size_t comma = op.find(',', openParen + 1);
            size_t closeParen = op.find(')', comma + 1);
            long long n = std::stoll(op.substr(openParen + 1, comma - openParen - 1));
            long long e = std::stoll(op.substr(comma + 1, closeParen - comma - 1));
            currentMsg = RSA_ENC(currentMsg, n, e);
        } else if (op.rfind("RSA_DEC(", 0) == 0) {
            size_t openParen = op.find('(');
            size_t comma = op.find(',', openParen + 1);
            size_t closeParen = op.find(')', comma + 1);
            long long n = std::stoll(op.substr(openParen + 1, comma - openParen - 1));
            long long d = std::stoll(op.substr(comma + 1, closeParen - comma - 1));
            currentMsg = RSA_DEC(currentMsg, n, d);
        }

        std::cout << "After " << op << ": " << currentMsg << "\n";
    }

    return 0;
}
