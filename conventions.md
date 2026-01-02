# Project Conventions

## Naming Conventions

- Type names (`struct`, `union`, `enum`) shall be in `snake_case`.
- `typedef` aliases shall be in `snake_case` with a `_t` suffix.

- Global constants (typically `enum` values) shall be in `UPPER_CASE`.
- Macro names shall be in `UPPER_CASE`.
- Function-like macro arguments shall be in `snake_case`.

- Function names shall be in `snake_case`.
- Auxiliary (internal) function names shall be in `snake_case` with a leading `_`.
- Local variable names shall be in `snake_case`.
- Global variable names shall be in `snake_case` (discouraged).



---

## Ownership Conventions

### Primitive Types

- Ownership of primitive types is trivial, as they are trivially copyable.

### User-Defined Types

- A complete type value stored directly in a `struct` implies ownership.

- Complete types that define destruction semantics shall not be copied,
  except via designated clone or move functions.

- Complete types may define designated lifecycle functions:
  - construction functions produce owned values,
  - destruction functions consume owned values,
  - move functions transfer ownership from source to destination.

- A pointer to any type, complete or incomplete, is assumed to be borrowed
  unless explicitly documented otherwise.

---

## Function Safety Conventions

- Destruction and cleanup functions shall be safe to call on zero-initialized
  objects.

- Functions may assert internal invariants, as well as runtime failures

- Functions shall not allocate memory unless explicitly indicated by their
  name or documentation.

- Functions may return success or failure via their return value; output
  parameters shall be never read by function.

---

## Lifecycle Function Naming

- `<type>_create` functions return an owned value.

- `<type>_destroy` functions consume an owned value and bring it to a
  zero-initialized state, releasing all owned resources.

- `<type>_move` functions transfer ownership and zero the source value.

---

## Module Conventions

- Resources acquired by a module shall be released by the same module.

- Data structures owning resources shall expose access via handles or indices;
  they shall not expose borrowed pointers to internal storage that may be
  invalidated (e.g., by reallocation).

---

Deviations from these conventions shall be explicit and documented.
