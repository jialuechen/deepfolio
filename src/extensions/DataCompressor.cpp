#include "DataCompressor.h"
#include <zlib.h>
#include <stdexcept>

// Compresses a string of data using zlib and returns the compressed result as a vector of bytes
std::vector<uint8_t> DataCompressor::compress(const std::string& data) {
    std::vector<uint8_t> compressedData;
    z_stream deflateStream{};
    deflateStream.zalloc = Z_NULL;
    deflateStream.zfree = Z_NULL;
    deflateStream.opaque = Z_NULL;

    // Initialize deflate stream
    if (deflateInit(&deflateStream, Z_BEST_COMPRESSION) != Z_OK) {
        throw std::runtime_error("Failed to initialize zlib for compression");
    }

    deflateStream.avail_in = data.size();
    deflateStream.next_in = reinterpret_cast<Bytef*>(const_cast<char*>(data.data()));

    uint8_t outBuffer[CHUNK_SIZE];
    do {
        deflateStream.avail_out = CHUNK_SIZE;
        deflateStream.next_out = outBuffer;

        deflate(&deflateStream, Z_FINISH);  // Perform compression
        compressedData.insert(compressedData.end(), outBuffer, outBuffer + (CHUNK_SIZE - deflateStream.avail_out));
    } while (deflateStream.avail_out == 0);

    deflateEnd(&deflateStream);
    return compressedData;
}

// Decompresses a vector of bytes using zlib and returns the decompressed result as a string
std::string DataCompressor::decompress(const std::vector<uint8_t>& compressedData) {
    std::string decompressedData;
    z_stream inflateStream{};
    inflateStream.zalloc = Z_NULL;
    inflateStream.zfree = Z_NULL;
    inflateStream.opaque = Z_NULL;

    // Initialize inflate stream
    if (inflateInit(&inflateStream) != Z_OK) {
        throw std::runtime_error("Failed to initialize zlib for decompression");
    }

    inflateStream.avail_in = compressedData.size();
    inflateStream.next_in = const_cast<Bytef*>(compressedData.data());

    uint8_t outBuffer[CHUNK_SIZE];
    do {
        inflateStream.avail_out = CHUNK_SIZE;
        inflateStream.next_out = outBuffer;

        int ret = inflate(&inflateStream, Z_NO_FLUSH);
        if (ret == Z_STREAM_ERROR || ret == Z_DATA_ERROR || ret == Z_MEM_ERROR) {
            inflateEnd(&inflateStream);
            throw std::runtime_error("Failed to decompress data");
        }

        decompressedData.append(reinterpret_cast<char*>(outBuffer), CHUNK_SIZE - inflateStream.avail_out);
    } while (inflateStream.avail_out == 0);

    inflateEnd(&inflateStream);
    return decompressedData;
}
