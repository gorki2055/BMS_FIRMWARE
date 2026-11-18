# Complete C Pointers Tutorial — Learned Through the 21S BMS Firmware Codebase

Welcome! This tutorial teaches **C pointers from absolute zero to advanced embedded systems mastery**, using **100% real code examples** directly from this BMS firmware repository.

---

## Table of Contents
1. [What Is a Pointer? (Memory & Addresses Explained)](#1-what-is-a-pointer-memory--addresses-explained)
2. [The Two Core Operators: `&` (Address-Of) and `*` (Dereference)](#2-the-two-core-operators--address-of-and--dereference)
3. [Why Do We Use Pointers? (Pass-by-Value vs. Pass-by-Pointer)](#3-why-do-we-use-pointers-pass-by-value-vs-pass-by-pointer)
4. [Struct Pointers: The Dot (`.`) vs. Arrow (`->`) Operator](#4-struct-pointers-the-dot--vs-arrow---operator)
5. [Output Parameters: Returning Multiple Values via Pointers](#5-output-parameters-returning-multiple-values-via-pointers)
6. [Read-Only Safety: `const` Pointers](#6-read-only-safety-const-pointers)
7. [Arrays, Byte Buffers, Strings & Pointer Arithmetic](#7-arrays-byte-buffers-strings--pointer-arithmetic)
8. [Null Pointers (`NULL`) & Defensive Guard Checks](#8-null-pointers-null--defensive-guard-checks)
9. [Memory Functions (`memset`, `memcpy`) — When to Use `&` and When Not To!](#9-memory-functions-memset-memcpy--when-to-use--and-when-not-to)
10. [Hardware Register Pointers (`volatile` & Memory-Mapped I/O)](#10-hardware-register-pointers-volatile--memory-mapped-io)
11. [How to Read Pointers in Ghidra Decompiled Code](#11-how-to-read-pointers-in-ghidra-decompiled-code)
12. [Master Cheat Sheet & Practice Exercises](#12-master-cheat-sheet--practice-exercises)

---

## 1. What Is a Pointer? (Memory & Addresses Explained)

Think of the microcontroller's memory (RAM and Flash) as a giant street of numbered mailboxes.
* Every mailbox holds **1 byte** (8 bits) of data.
* Every mailbox has a unique **street address** (a 32-bit hexadecimal number on our ARM Cortex-M4 MCU).

In our Nations Tech **N32G45x BMS microcontroller** ([`firmware_source/cmsis/n32g45x.h`](file:///d:/kushal/projects/bms%20firmware%20reverse%20engineering/firmware_source/cmsis/n32g45x.h#L16-L20)):
* **`0x08008000`**: Where our program code lives (Flash memory).
* **`0x20000000`**: Where live variables live (SRAM).
* **`0x40000000`**: Where hardware peripherals (GPIO pins, CAN, UART, ADC) live.

### Normal Variable vs. Pointer Variable

Suppose we declare a normal variable for battery pack temperature:
```c
int16_t temp_c = 25;   /* Normal variable: stores the VALUE 25 */
```
When the program runs, the CPU places `temp_c` inside SRAM—say at memory address **`0x20001000`**.

Now suppose we create a **pointer** to `temp_c`:
```c
int16_t *ptr = &temp_c; /* Pointer variable: stores the ADDRESS 0x20001000 */
```

Look at what is inside memory:

```text
Memory Address       Variable Name       Value Stored Inside        Meaning
------------------------------------------------------------------------------------------------
0x20001000           temp_c (int16_t)    25                         25 °C (2 bytes)
0x20001004           ptr    (int16_t *)  0x20001000                 "Go look at address 0x20001000!"
```

> **Golden Rule #1:**
> * A **normal variable** holds a **value** (like `25` °C or `3650` mV).
> * A **pointer variable** holds a **memory address** (like `0x20001000`) where another variable lives.

---

## 2. The Two Core Operators: `&` (Address-Of) and `*` (Dereference)

Beginners often get confused because C uses the `*` symbol for **two completely different jobs** depending on where it appears. Let's make this crystal clear.

### Operator 1: `&` ("Address-Of")
Putting `&` in front of any variable asks C: ***"What is your memory address?"***
* `temp_c` $\rightarrow$ evaluates to `25` (the value).
* `&temp_c` $\rightarrow$ evaluates to `0x20001000` (the address).

### Operator 2: `*` in a Declaration ("Is a Pointer To...")
When you see `*` **next to a type name** when creating a variable or function parameter, it simply declares that the variable is a pointer:
```c
int32_t      current_ma;   /* Normal 32-bit integer */
int32_t     *p_current;    /* Pointer to a 32-bit integer */
BmsContext_t *ctx;         /* Pointer to a BmsContext_t structure */
```

### Operator 3: `*` in an Expression ("Go to that Address!" / Dereference)
After the pointer is already declared, putting `*` in front of the pointer name means: ***"Follow the arrow to the memory address and read/write the value stored there!"***

```c
int32_t current_ma = 0;          /* 1. Create normal variable (value = 0) */
int32_t *p_curr = &current_ma;   /* 2. Point p_curr at current_ma's address */

*p_curr = -12500;                /* 3. Follow p_curr and write -12500 into that box! */
/* Now current_ma is -12500 (-12.5 A)! */

int32_t reading = *p_curr;       /* 4. Follow p_curr and read the value (-12500) */
```

```text
  [ p_curr ] ──────(*p_curr follows the arrow)──────► [ current_ma ]
 (0x20001008)                                          (0x20001000)
  Holds: 0x20001000                                     Holds: -12500
```

---

## 3. Why Do We Use Pointers? (Pass-by-Value vs. Pass-by-Pointer)

In our BMS firmware, the entire state of the 21-cell battery pack is held in one master struct called `BmsContext_t` (defined in [`firmware_source/include/bms_types.h`](file:///d:/kushal/projects/bms%20firmware%20reverse%20engineering/firmware_source/include/bms_types.h#L118-L143)).

`BmsContext_t` contains:
* 21 cell voltages (`uint16_t cell_mv[21]`)
* 21 calibration gains (`float cell_cal_gain[21]`)
* Temperatures, current, SOC, SOH, MOSFET flags, fault flags, limits, and serial number.
* **Total size of `BmsContext_t`: ~260 bytes.**

### What Happens If You DO NOT Use a Pointer (Pass-by-Value — BAD!)
```c
/* BAD EXAMPLE: Passing the whole struct by value */
void bad_reset_soc(BmsContext_t ctx) {
    ctx.telemetry.soc_pct = 100; /* Modifies a temporary PHOTOCOPY! */
}
```
1. **Wastes CPU & RAM**: Every time you call `bad_reset_soc(ctx)`, the CPU copies all 260 bytes onto the stack.
2. **Changes Are Lost!**: In C, function arguments are passed **by value** (like handing someone a photocopy of a document). Writing on the photocopy does **not** change the original document! When `bad_reset_soc` finishes, the photocopy is thrown away and your original `ctx.telemetry.soc_pct` is unchanged.

### What Happens When You Pass a Pointer (Pass-by-Pointer — GOOD!)
Look at how [`bms_core.c`](file:///d:/kushal/projects/bms%20firmware%20reverse%20engineering/firmware_source/src/bms_core.c#L14) actually does it:
```c
/* REAL CODE from firmware_source/src/bms_core.c (Line 14) */
void bms_core_init(BmsContext_t *ctx) {
    ctx->state = BMS_STATE_INIT;
    ctx->telemetry.total_capacity_mah = BMS_NOMINAL_CAPACITY_MAH;
    ctx->telemetry.soc_pct = 100;
}
```
And look at how [`test_bms_logic.c`](file:///d:/kushal/projects/bms%20firmware%20reverse%20engineering/firmware_source/tests/test_bms_logic.c#L40-L41) calls it:
```c
/* REAL CODE from firmware_source/tests/test_bms_logic.c (Lines 40-41) */
BmsContext_t ctx;      /* Allocate the real 260-byte struct */
bms_core_init(&ctx);   /* Pass ONLY its 4-byte address (&ctx) to the function! */
```

1. **Ultra-Fast**: Instead of copying 260 bytes, the CPU passes a single **4-byte memory address** (`&ctx`).
2. **Modifies the Real Struct**: Because `bms_core_init` has the exact address of `ctx`, every change it makes is written directly into the real `ctx` in memory!

---

## 4. Struct Pointers: The Dot (`.`) vs. Arrow (`->`) Operator

You will see both `.` and `->` used across the BMS codebase. The rule for choosing between them is 100% mechanical:

| Operator | When to Use It | Example from Codebase |
| :---: | :--- | :--- |
| **`.` (Dot)** | When your variable is an **actual struct** (no `*` in its declaration) | `BmsContext_t ctx;`<br>`ctx.state = BMS_STATE_STANDBY;` |
| **`->` (Arrow)** | When your variable is a **pointer to a struct** (has `*` in its declaration) | `BmsContext_t *ctx;`<br>`ctx->state = BMS_STATE_STANDBY;` |

### Why Does `->` Exist?
If `ctx` is a pointer (`BmsContext_t *ctx`), to access a field using `*` and `.`, you would have to write:
```c
(*ctx).state = BMS_STATE_STANDBY;   /* Clunky to type! */
```
(Parentheses are required because `.` has higher precedence than `*`). Because C programmers do this thousands of times, C provides the arrow operator `->` as an exact synonym:
```c
ctx->state = BMS_STATE_STANDBY;     /* Exact same thing as (*ctx).state! */
```

### Real Codebase Pattern: Combining `->` and `.` Together!
Look at line 45 of [`firmware_source/src/bms_parallel.c`](file:///d:/kushal/projects/bms%20firmware%20reverse%20engineering/firmware_source/src/bms_parallel.c#L45):
```c
void bms_parallel_process_tick(BmsContext_t *ctx) {
    uint8_t local_soc = ctx->telemetry.soc_pct;
```
Why did we use **`->` first** and then **`.` second** in `ctx->telemetry.soc_pct`?
1. `ctx` is a **pointer** (`BmsContext_t *ctx`), so to get inside `ctx`, we MUST use `->` (`ctx->telemetry`).
2. Inside `BmsContext_t`, the member `telemetry` is an **embedded struct** (`BmsTelemetry_t telemetry;`, NOT a pointer!), so to get inside `telemetry`, we use `.` (`telemetry.soc_pct`)!

### Real Codebase Pro-Tip: Creating a Short Pointer Alias (`BmsTelemetry_t *t = &ctx->telemetry;`)
Look at lines 48–54 of [`firmware_source/src/bms_core.c`](file:///d:/kushal/projects/bms%20firmware%20reverse%20engineering/firmware_source/src/bms_core.c#L48-L54):
```c
void bms_core_apply_cell_calibration(BmsContext_t *ctx) {
    if (!ctx) return;
    BmsTelemetry_t *t = &ctx->telemetry;  /* <-- Create a shortcut pointer 't'! */
    t->min_cell_mv = 0xFFFFU;
    t->max_cell_mv = 0U;
```
Let's trace `BmsTelemetry_t *t = &ctx->telemetry;` step by step:
1. `ctx->telemetry` accesses the `telemetry` sub-struct inside `*ctx`.
2. `&ctx->telemetry` takes the **memory address** of that `telemetry` sub-struct.
3. `BmsTelemetry_t *t` stores that address in a short pointer named `t`.
4. Now, instead of typing `ctx->telemetry.min_cell_mv` 20 times in the function, we can simply write `t->min_cell_mv`! It compiles to the exact same machine instructions and makes the code much cleaner to read.

---

## 5. Output Parameters: Returning Multiple Values via Pointers

In C, a `return` statement can only return **one** value. What if a function needs to:
* Return `true`/`false` to indicate whether I2C communication succeeded, **AND**
* Give you the newly measured battery pack current?

We solve this using an **Output Pointer Parameter**!

### Example 1: Reading Pack Current (`dvc1124_read_pack_current`)
Look at [`firmware_source/src/dvc1124_afe.c`](file:///d:/kushal/projects/bms%20firmware%20reverse%20engineering/firmware_source/src/dvc1124_afe.c#L168-L185):
```c
bool dvc1124_read_pack_current(int32_t *current_ma) {
    if (!current_ma) return false;
    uint8_t buf[2] = {0};

    if (!dvc1124_read_regs(DVC_REG_CURRENT, buf, 2)) {
        return false; /* I2C read failed! */
    }

    int16_t raw_adc = (int16_t)(((uint16_t)buf[0] << 8) | buf[1]);
    *current_ma = dvc1124_raw_to_current_ma(raw_adc, 0); /* <-- Write answer to caller's box! */
    return true;  /* I2C read succeeded! */
}
```
And look at how [`bms_core.c`](file:///d:/kushal/projects/bms%20firmware%20reverse%20engineering/firmware_source/src/bms_core.c#L354) calls it:
```c
void bms_core_process_10ms_tick(BmsContext_t *ctx) {
    /* Pass the ADDRESS (&) of current_ma so dvc1124_read_pack_current can fill it in! */
    dvc1124_read_pack_current(&ctx->telemetry.current_ma);
}
```

### Example 2: Optional Output Pointer (`blink_out` in `bms_core_get_led_bar_stage`)
Look at [`firmware_source/src/bms_core.c`](file:///d:/kushal/projects/bms%20firmware%20reverse%20engineering/firmware_source/src/bms_core.c#L334-L350):
```c
uint8_t bms_core_get_led_bar_stage(const BmsContext_t *ctx, bool *blink_out) {
    if (blink_out) *blink_out = false; /* Only write if caller passed a valid address! */
    if (!ctx) return 0;

    uint8_t soc = ctx->telemetry.soc_pct;
    bool is_discharging = (ctx->state == BMS_STATE_DISCHARGE || ctx->telemetry.current_ma < -100);

    if (is_discharging && soc < 10U) {
        if (blink_out) *blink_out = true; /* Low-battery <10% blink alert */
        return 1U;
    }
    ...
```
Why does this function check `if (blink_out)` before writing `*blink_out = true`?
* If a caller cares about whether the LED should blink, they pass a variable's address:
  ```c
  bool blink = false;
  uint8_t leds = bms_core_get_led_bar_stage(&ctx, &blink);
  ```
* If a caller **only** wants the number of LEDs (1–5) and doesn't care about blinking, they can pass `NULL`:
  ```c
  uint8_t leds = bms_core_get_led_bar_stage(&ctx, NULL);
  ```
  Because of `if (blink_out)`, passing `NULL` is 100% safe!

---

## 6. Read-Only Safety: `const` Pointers

Wait—if passing a pointer gives a function direct access to our live `BmsContext_t` memory, what if a CAN transmit function accidentally overwrites `ctx->telemetry.soc_pct` because of a typo like `if (ctx->telemetry.soc_pct = 0)` instead of `== 0`?

To prevent accidental modification, we mark the pointer parameter **`const`**:

```c
/* REAL CODE from firmware_source/src/bms_parallel.c (Line 90) */
void bms_parallel_send_heartbeat(const BmsContext_t *ctx) {
    /* ctx->telemetry.soc_pct can be READ here... */
    msg.data[1] = ctx->telemetry.soc_pct;

    /* ...but if you try to write: ctx->telemetry.soc_pct = 50;
     * the C compiler immediately stops with an ERROR! */
}
```

### Rule of Thumb in Our Codebase:
* Functions that **update** BMS state take `BmsContext_t *ctx` (mutable pointer):
  * `bms_core_init(BmsContext_t *ctx)`
  * `bms_core_process_100ms_tick(BmsContext_t *ctx)`
* Functions that **only read/broadcast** BMS state take `const BmsContext_t *ctx` (read-only pointer):
  * `bms_parallel_send_heartbeat(const BmsContext_t *ctx)`
  * `bms_can_send_capacity_soh(const BmsContext_t *ctx)`
  * `bms_can_send_charger_demand(const BmsContext_t *ctx)`

---

## 7. Arrays, Byte Buffers, Strings & Pointer Arithmetic

In C, **arrays and pointers are closely linked**. When you pass an array to a function, the array name automatically converts ("decays") into a **pointer to its first element (`&array[0]`)**!

### 1. Passing an Array to a Function
In `BmsTelemetry_t`, cell voltages are stored in a 21-element array:
```c
uint16_t cell_mv[21];
```
Look at how [`bms_core.c`](file:///d:/kushal/projects/bms%20firmware%20reverse%20engineering/firmware_source/src/bms_core.c#L361) passes `t->cell_mv` into `dvc1124_read_cell_voltages`:
```c
/* In bms_core.c: Notice there is NO '&' in front of t->cell_mv! */
if (dvc1124_read_cell_voltages(t->cell_mv, BMS_SERIES_CELLS)) {
    bms_core_apply_cell_calibration(ctx);
}
```
And look at the function signature in [`dvc1124_afe.c`](file:///d:/kushal/projects/bms%20firmware%20reverse%20engineering/firmware_source/src/dvc1124_afe.c#L129):
```c
bool dvc1124_read_cell_voltages(uint16_t *cell_mv_out, uint8_t num_cells) {
    for (uint8_t i = 0; i < num_cells; i++) {
        cell_mv_out[i] = ...; /* Indexing a pointer with [i] works just like an array! */
    }
}
```
Why does `cell_mv_out[i]` work on a pointer `uint16_t *cell_mv_out`?
Because in C, **square brackets `ptr[i]` are defined as `*(ptr + i)`**!

```text
cell_mv_out (Base Address: 0x20002000)
  │
  ├── cell_mv_out[0]  ==  *(cell_mv_out + 0)  (Address 0x20002000, Cell 1 mV)
  ├── cell_mv_out[1]  ==  *(cell_mv_out + 1)  (Address 0x20002002, Cell 2 mV)
  └── cell_mv_out[2]  ==  *(cell_mv_out + 2)  (Address 0x20002004, Cell 3 mV)
```
*(Note: Adding `+ 1` to a `uint16_t *` automatically advances the byte address by `2` bytes (`sizeof(uint16_t)`). Adding `+ 1` to a `uint32_t *` advances the address by `4` bytes!)*

### 2. Strings Are Just `char *` (Pointers to Characters)
In C, a string like `"6495-SPB24-006-A01"` is stored in memory as an array of ASCII bytes ending with a null terminator byte (`'\0'` = `0x00`).
Look at [`bms_parallel.c`](file:///d:/kushal/projects/bms%20firmware%20reverse%20engineering/firmware_source/src/bms_parallel.c#L19-L27):
```c
void bms_parallel_evaluate_role(BmsContext_t *ctx, const char *local_sn, const char *peer_sn) {
    if (!ctx || !local_sn || !peer_sn) return;
    int cmp = strcmp(local_sn, peer_sn);
```
Here, `const char *local_sn` is a pointer to the first character `'6'` of the serial number string.

---

## 8. Null Pointers (`NULL`) & Defensive Guard Checks

A pointer that points to address `0` (`NULL`) means ***"I point to nothing."***

If your code tries to dereference a `NULL` pointer (`ctx->state` when `ctx == NULL`), the microcontroller attempts to access invalid state or overwrite vector table memory at `0x00000000`, which can crash the firmware or trigger a `HardFault_Handler`.

That is why nearly every function in our BMS firmware begins with a **Null Guard Check**:

```c
/* REAL CODE from firmware_source/src/bms_parallel.c (Line 109-110) */
bool bms_parallel_process_can_rx(BmsContext_t *ctx, uint32_t can_id, const uint8_t *data, uint8_t dlc) {
    if (!ctx || !data || dlc < 4) return false;
```

### Understanding the Syntax `if (!ctx)`:
In C:
* `!ctx` is exact shorthand for `ctx == NULL` (i.e., `ctx == 0`).
* `if (ctx)` is exact shorthand for `ctx != NULL` (i.e., `ctx` points to a valid address).

So `if (!ctx || !data) return false;` reads in plain English as:
> *"If `ctx` is `NULL` OR `data` is `NULL`, abort immediately and return `false`."*

---

## 9. Memory Functions (`memset`, `memcpy`) — When to Use `&` and When Not To!

One of the most common beginner questions when reading C code is:
> *"Why does `memset` sometimes have `&` in front of the first argument, and sometimes NOT have `&`?"*

Look at these two real lines from our codebase side by side:

### Case A: Inside [`bms_core.c`](file:///d:/kushal/projects/bms%20firmware%20reverse%20engineering/firmware_source/src/bms_core.c#L14-L16) (NO `&` used)
```c
void bms_core_init(BmsContext_t *ctx) {
    if (!ctx) return;
    memset(ctx, 0, sizeof(BmsContext_t));   /* <-- NO '&' before ctx! */
```
**Why no `&`?**
Because `memset` expects a **memory address (a pointer)** as its first argument. Here, `ctx` was declared as `BmsContext_t *ctx`—so **`ctx` IS ALREADY a pointer (an address)**!
*(Warning: If you wrote `memset(&ctx, ...)`, you would wipe out the 4-byte pointer variable itself instead of the 260-byte `BmsContext_t` struct!)*

### Case B: Inside [`bms_parallel.c`](file:///d:/kushal/projects/bms%20firmware%20reverse%20engineering/firmware_source/src/bms_parallel.c#L90-L93) (`&` IS used)
```c
void bms_parallel_send_heartbeat(const BmsContext_t *ctx) {
    CanMessage_t msg;                       /* <-- msg is a normal struct (NOT a pointer) */
    memset(&msg, 0, sizeof(msg));           /* <-- MUST use '&msg' to get its address! */
```
**Why use `&` here?**
Because `msg` was declared as `CanMessage_t msg;` (an actual struct on the stack, not a pointer). To pass its address to `memset` or `bms_can_transmit(&msg)`, we must put `&` in front of it!

---

## 10. Hardware Register Pointers (`volatile` & Memory-Mapped I/O)

How does C software physically flip a transistor on the microcontroller silicon to turn on the Pre-Charge MOSFET at Pin `PC4`?

The answer is **Hardware Register Pointers**!

### Step 1: The Hardware Address (`0x40011000`)
In the Nations Tech N32G45x datasheet, GPIO Port C (`GPIOC`) is wired to physical memory address **`0x40011000`**.
Look at [`firmware_source/cmsis/n32g45x.h`](file:///d:/kushal/projects/bms%20firmware%20reverse%20engineering/firmware_source/cmsis/n32g45x.h#L49-L78):

```c
/* 1. Calculate the physical address of GPIOC: 0x40000000 + 0x10000 + 0x1000 = 0x40011000 */
#define GPIOC_BASE            (APB2PERIPH_BASE + 0x1000)

/* 2. Define the layout of the 32-bit hardware registers inside any GPIO port */
typedef struct {
    volatile uint32_t CRL;   /* Offset +0x00: Port configuration register low */
    volatile uint32_t CRH;   /* Offset +0x04: Port configuration register high */
    volatile uint32_t IDR;   /* Offset +0x08: Port input data register */
    volatile uint32_t ODR;   /* Offset +0x0C: Port output data register */
    volatile uint32_t BSRR;  /* Offset +0x10: Port bit set/reset register */
    volatile uint32_t BRR;   /* Offset +0x14: Port bit reset register */
    volatile uint32_t LCKR;  /* Offset +0x18: Port configuration lock register */
} GPIO_TypeDef;

/* 3. Cast raw integer address 0x40011000 into a struct pointer! */
#define GPIOC                 ((GPIO_TypeDef *)GPIOC_BASE)
```

### Step 2: How `GPIOC->BSRR` Works
When [`bms_hal.c`](file:///d:/kushal/projects/bms%20firmware%20reverse%20engineering/firmware_source/src/bms_hal.c#L129) executes:
```c
GPIOC->BSRR = (1 << 4);  /* Drive Pin PC4 High (3.3V) */
```
1. `GPIOC` expands to `((GPIO_TypeDef *)0x40011000)` — a pointer pointing directly at hardware address `0x40011000`.
2. `->BSRR` adds the struct offset of `BSRR` (`+0x10`), targeting hardware address **`0x40011010`**.
3. The CPU executes a single `STR` (Store Register) instruction to address `0x40011010`, and the silicon immediately drives Pin `PC4` to 3.3V!

### Why Is `volatile` Required on Hardware Pointers?
Notice every register in `GPIO_TypeDef` has the keyword **`volatile`**.
* Without `volatile`, the C compiler assumes memory only changes when C code writes to it. If you check a status register in a loop (`while ((USART1->STS & TXE) == 0)`), an optimizing compiler without `volatile` would read `STS` once and loop forever!
* **`volatile`** tells the compiler: *"This pointer points to live hardware that changes on its own! Never cache it in a register and never optimize away any read or write!"*

### Another Real Example: Reading the 96-Bit Chip UID (`0x1FFFF7F0`)
Look at [`firmware_source/src/bms_hal.c`](file:///d:/kushal/projects/bms%20firmware%20reverse%20engineering/firmware_source/src/bms_hal.c#L261-L270):
```c
void bms_hal_read_mcu_uid(uint32_t uid_out[3]) {
    if (!uid_out) return;
#ifdef __arm__
    const volatile uint32_t *uid_reg = (const volatile uint32_t *)0x1FFFF7F0UL;
    uid_out[0] = uid_reg[0]; /* Reads 32-bit word at 0x1FFFF7F0 */
    uid_out[1] = uid_reg[1]; /* Reads 32-bit word at 0x1FFFF7F4 */
    uid_out[2] = uid_reg[2]; /* Reads 32-bit word at 0x1FFFF7F8 */
#endif
}
```
Here, `(const volatile uint32_t *)0x1FFFF7F0UL` turns the factory silicon serial number address `0x1FFFF7F0` into a read-only hardware pointer, and `uid_reg[0..2]` reads the three consecutive 32-bit words!

---

## 11. How to Read Pointers in Ghidra Decompiled Code

When you open [`decompiled/bms_firmware_decompiled.c`](file:///d:/kushal/projects/bms%20firmware%20reverse%20engineering/decompiled/bms_firmware_decompiled.c), Ghidra doesn't initially know the names of our C structs (`BmsContext_t` or `BmsTelemetry_t`). Instead, Ghidra knows **base addresses** and **byte offsets**, so it generates raw pointer arithmetic and casts!

Once you understand how to read one Ghidra pointer expression, you can reverse-engineer any firmware in the world.

### Decoding a Real Ghidra Line (`FUN_08010654`, Line 10545)
In [`decompiled/bms_firmware_decompiled.c`](file:///d:/kushal/projects/bms%20firmware%20reverse%20engineering/decompiled/bms_firmware_decompiled.c#L10545), Ghidra outputs:
```c
sVar1 = *(short *)(DAT_0801090c + 0x22);
```
It looks scary at first, but let's peel it from the inside out:

```text
        *(short *)(DAT_0801090c + 0x22)
                   \__________/
                    1. Base address of Telemetry struct in SRAM (e.g. 0x20020800)
                                \____/
                                 2. Add byte offset +0x22 (34 bytes inside the struct)
         \_______/
          3. Cast that address to a (short *) — a pointer to a 16-bit signed integer (int16_t *)
        *
        4. Dereference (*) the pointer: Read the 16-bit signed integer at that address!
```

And what lives at offset `+0x22` inside the telemetry struct? **`min_temp_c` (`int16_t`)**!
So in our clean reconstructed code ([`bms_core.c`](file:///d:/kushal/projects/bms%20firmware%20reverse%20engineering/firmware_source/src/bms_core.c)), that entire scary expression is simply:
```c
int16_t min_temp = ctx->telemetry.min_temp_c;
```

### Side-by-Side Translation Table: Ghidra vs. Clean C

| Ghidra Decompiled Expression | What It Means in Memory | Clean Reconstructed C Equivalent |
| :--- | :--- | :--- |
| `*(byte *)(base + 5)` | Read 1 unsigned byte (`uint8_t`) at offset `+5` | `ctx->telemetry.soc_pct` |
| `*(short *)(base + 0x22)` | Read 2-byte signed int (`int16_t`) at offset `+0x22` | `ctx->telemetry.min_temp_c` |
| `*(ushort *)(base + 0x06)` | Read 2-byte unsigned int (`uint16_t`) at offset `+0x06` | `ctx->telemetry.max_cell_mv` |
| `*(float *)(base + 0x10)` | Read 4-byte `float` at offset `+0x10` | `ctx->telemetry.current_ma` |
| `pcVar1[8] = (char)uVar4;` | Write 1 byte at `*(pcVar1 + 8)` | `ctx->throttled_dsg_a = (uint8_t)throttled;` |

---

## 12. Master Cheat Sheet & Practice Exercises

### Pointer Syntax Cheat Sheet

| Syntax | Name | Meaning |
| :--- | :--- | :--- |
| `int32_t x = 10;` | Value declaration | Creates an integer variable `x` holding `10`. |
| `int32_t *p;` | Pointer declaration | Creates a pointer `p` that can hold the address of an `int32_t`. |
| `p = &x;` | Address-of (`&`) | Stores the memory address of `x` inside `p`. |
| `*p = 20;` | Dereference (`*`) | Follows `p` to `x`'s memory box and writes `20` into `x`. |
| `ctx->soc_pct` | Arrow operator (`->`) | Accesses member `soc_pct` through struct **pointer** `ctx`. |
| `ctx.soc_pct` | Dot operator (`.`) | Accesses member `soc_pct` on an actual struct **variable** `ctx`. |
| `const int32_t *p` | Read-only pointer | You can read `*p`, but the compiler forbids writing `*p = ...`. |
| `volatile uint32_t *r` | Hardware register pointer | Tells compiler `*r` is hardware and must never be cached/optimized out. |
| `p[3]` | Subscript operator | Identical to `*(p + 3)` — accesses the 4th element starting at `p`. |
| `if (!p)` | Null guard | Checks if `p == NULL` (`0x00000000`) before dereferencing it. |

---

### Self-Test Exercises (With Answers Below)

Test your understanding on these 4 snippets from our BMS firmware:

1. **Question 1**: In `void bms_core_calculate_soc(BmsContext_t *ctx)`, why do we call `bms_soc_estimator_update(ctx, 1000);` **without** an `&` in front of `ctx`?
2. **Question 2**: In `bms_core_process_100ms_tick(BmsContext_t *ctx)`, look at:
   ```c
   dvc1124_read_temperatures(t->temp_c, BMS_NTC_TEMP_SENSORS, &t->mos_temp_c);
   ```
   Why does `t->temp_c` have **no `&`**, while `&t->mos_temp_c` **does have an `&`**?
3. **Question 3**: What bug happens if someone writes:
   ```c
   BmsContext_t *ctx = NULL;
   ctx->state = BMS_STATE_STANDBY;
   ```
4. **Question 4**: In Ghidra, you see `*(uint32_t *)0x40021024`. What is this code doing?

---

<details>
<summary><b>Click to View Answers</b></summary>

1. **Answer 1**: Because `ctx` is already declared as `BmsContext_t *ctx` (a pointer!), and `bms_soc_estimator_update` expects a `BmsContext_t *`. Passing `ctx` passes the 4-byte memory address directly.
2. **Answer 2**:
   * `t->temp_c` is an **array** (`int16_t temp_c[4]`), and in C an array name automatically decays into a pointer to its first element (`&t->temp_c[0]`).
   * `t->mos_temp_c` is a **single `int16_t` variable** (`int16_t mos_temp_c`), so we must use `&` (`&t->mos_temp_c`) to pass its address as an output parameter!
3. **Answer 3**: Dereferencing a `NULL` pointer! `ctx` points to address `0x00000000`, so `ctx->state` tries to write to address `0x00000000`, causing an immediate hardware fault (`HardFault_Handler`) or crash.
4. **Answer 4**: It casts the raw hardware register address `0x40021024` (which is the N32G45x `RCC->CSR` Reset/Clock Control Status Register) into a 32-bit unsigned integer pointer `(uint32_t *)`, and dereferences it with `*` to read the 32-bit hardware register value!
</details>
