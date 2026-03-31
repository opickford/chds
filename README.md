# chds

A personal C Header-only Data Structures library.

[![build](https://img.shields.io/github/actions/workflow/status/opickford/chds/ci.yml?style=for-the-badge&label=build)](https://github.com/opickford/chds/actions)
[![license](https://img.shields.io/github/license/opickford/chds?style=for-the-badge)](LICENSE)
[![version](https://img.shields.io/github/v/tag/opickford/chds?style=for-the-badge&label=version)](https://github.com/opickford/chds/tags)

---

## Contents

- [Structures](#structures)
- [Requirements](#requirements)
- [Building](#building)
- [Usage](#usage)
- [Running tests](#running-tests)
- [Integration](#integration)
- [Versioning](#versioning)
- [License](#license)

---

## Structures

| Structure | Header | Status |
|-----------|--------|--------|
| Dynamic array (vector) | `chds/vec.h` | stable |

---

## Requirements

- C11 or later
- CMake 3.31 or later

---

## Building

**Configure:**
```bash
cmake -S . -B build
```

**Configure with examples:**
```bash
cmake -S . -B build -DCHDS_BUILD_EXAMPLES=ON
```

**Configure release:**
```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
```

**Build:**
```bash
cmake --build build
```

---

## Usage

Include the header for the structure you need. No linking required.

### Error handling

Functions that allocate memory return a `CHDS_Result`:

```c
if (chds_vec_push(v, 67) != CHDS_OK) {
    /* handle allocation failure */
}
```

### Unprefixed API

Define `CHDS_NO_PREFIX` before including a header to use shorter unprefixed names:

```c
#define CHDS_NO_PREFIX
#include "chds_vec.h"

Vec(int) v = NULL;
vec_push(v, 42);
vec_free(v);
```

Note: unprefixed names may clash with other code. Use with care.

### Version

The current library version is available at runtime:

```c
#include "chds/version.h"

printf("chds version %s\n", CHDS_VERSION_STRING);
```

See the [examples](examples/) directory for more.

---

## Running tests

```bash
cmake -S . -B build -DCHDS_BUILD_TESTS=ON
cmake --build build --config Release
ctest -C Release --test-dir build --output-on-failure
```

---

## Integration

### CMake FetchContent

TODO

### Git submodule

TODO

---

## Versioning

TODO

This project follows [semantic versioning](https://semver.org). See [CHANGELOG.md](CHANGELOG.md) for release history.

---

## Licence

This project is licensed under the [MIT License](LICENSE).