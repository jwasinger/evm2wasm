#include <string>
#include <iostream>
#include <fstream>
#include <streambuf>

#include <evm2wasm.h>

using namespace std;

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

    if(wast) {
        cout << evm2wasm::evm2wast(input_str) << endl;
    } else {
        cout << evm2wasm::evm2wasm(input_str) << endl;
    }

    return 0;
}
