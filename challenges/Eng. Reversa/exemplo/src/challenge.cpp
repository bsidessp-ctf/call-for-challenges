#include <iostream>
#include <string>

// codigo morto mais parametros no arquivo para exibir a flag

std::string unXORWithFF(const std::string& hexString) {
    std::string result;

    // Iterate through pairs of characters in the hex string
    for (size_t i = 0; i < hexString.length(); i += 2) {
        // Extract a pair of characters
        std::string pair = hexString.substr(i, 2);

        // Convert the pair from hex to decimal, XOR with FF, and convert back to ASCII
        char decryptedChar = static_cast<char>(std::stoi(pair, nullptr, 16) ^ 0xFF);

        // Append the decrypted character to the result string
        result.push_back(decryptedChar);
    }

    return result;
}

int main(int argc, char* argv[]) {
    std::string i;
    bool i2;
    std::cout << "Digite a senha: ";
    std::cin >> i;

    {
        int x = 0;
        for (char c : i) {
            x += static_cast<int>(c);
        }

        if (x % 2 == 0) {
            i2 = true;
        } else {
            i2 = false;
        }
    }

    // More obfuscation: Random loops
    for (int i = 0; i < 10; ++i) {
        i2 = !i;
    }

    switch (i.length()) {
        case 5:
            i2 = !true;
            break;
        case 7:
            i2 = !i2;
            break;
        case 10:
            i2 = !false;
            break;
        default:
            break;
    }

    int c = 0;
    while (c < 5) {
        i2 = !i2;
        ++c;
    }

    if (strcmp(argv[1], "MZ") == 0 && strcmp(argv[2], "PE") == 0 && strcmp(argv[3], "HIK") == 0) {
        std::cout << unXORWithFF("B7B6B4A0B29E8D989E8D9A8BA0B79E9096938B9091A0C89ACA9BC9C9CFC6C6C6CACDC89CCD9CC699C8C8CAC9CA99CDC8CCCAC899CDC8") << std::endl;
    }

    return 0;
}