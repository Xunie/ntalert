#ifndef BLOBS_H
#define BLOBS_H
#include <string>
#include <map>

struct blob {
    const void *ptr;
    const size_t size;
    
    blob( const void *p, const size_t s ) : ptr(p), size(s) {};
};

// (should) contain all the binary blobs linked into the binary
extern const std::map<std::string, blob> blobs;

#endif /* BLOBS_H */
