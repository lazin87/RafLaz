//
// Created by rafal on 5/23/25.
//

#ifndef RAFLAZ_H
#define RAFLAZ_H

#include <cstdint>

#if defined(_WIN32)

#ifdef LIBRARY_EXPORTS
        #define RAFLAZ_API __declspec(dllexport)
#else
        #define RAFLAZ_API __declspec(dllimport)
#endif // #ifdef LIBRARY_EXPORTS

#else // #if defined(_WIN32)
#define RAFLAZ_API __attribute__((visibility("default")))
#endif // #if defined(_WIN32)

#ifdef __cplusplus
extern "C" {
#endif  // #ifdef __cplusplus

RAFLAZ_API int32_t Foo();

#ifdef __cplusplus
}
#endif // #ifdef __cplusplus

#endif //RAFLAZ_H
