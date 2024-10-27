#ifndef DATACOMPRESSOR_H
#define DATACOMPRESSOR_H

#include <string>
#include <vector>

class DataCompressor {
public:
    // Compresses a string of data and returns the compressed result as a vector of bytes
    static std::vector<uint8_t> compress(const std::string& data);

    // Decompresses a vector of bytes and returns the decompressed result as a string
    static std::string decompress(const std::vector<uint8_t>& compressedData);

private:
    static const int CHUNK_SIZE = 16384;  // Default buffer size for compression
};

#endif // DATACOMPRESSOR_H
