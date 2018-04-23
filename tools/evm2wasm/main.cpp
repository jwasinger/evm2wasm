#include <string>
#include <iostream>
#include <fstream>
#include <streambuf>

#include <evm2wasm.h>

using namespace std;

std::vector<char> HexToBytes(const std::string& hex) {
    std::vector<char> bytes;

    for (unsigned int i = 0; i < hex.length()-1; i += 2) {
        std::string byteString = hex.substr(i, 2);
        char byte = (char) strtol(byteString.c_str(), NULL, 16);
        bytes.push_back(byte);
    }

    return bytes;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <EVM file> [--wast]" << endl;
        return 1;
    }

    bool wast = false;
    if (argc == 3) {
        wast = (string(argv[2]) == "--wast");
        if(!wast) {
            cerr << "Usage: " << argv[0] << " <EVM file> [--wast]" << endl;
            return 1;
        }
    }

    ifstream input(argv[1]);
    if (!input.is_open()) {
        cerr << "File not found: " << argv[1] << endl;
        return 1;
    }

    string input_str(
        (std::istreambuf_iterator<char>(input)),
        std::istreambuf_iterator<char>()
    );

    std::vector<char> evmCode = HexToBytes(input_str);

    if(wast) {
        cout << evm2wasm::evm2wast(evmCode) << endl;
    } else {
        cout << evm2wasm::evm2wasm(evmCode) << endl;
    }

    return 0;
}
