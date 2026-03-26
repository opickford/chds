# chds

A personal C Header-only Data Structures library.

[![Windows Release CI](https://github.com/opickford/chds/actions/workflows/ci.yml/badge.svg?branch=main)](https://github.com/opickford/chds/actions/workflows/ci.yml)
# TODO: licence etc.

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
- CMake 4.3 or later

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

TODO

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

## License

TODO

MIT — see [LICENSE](LICENSE) for details.