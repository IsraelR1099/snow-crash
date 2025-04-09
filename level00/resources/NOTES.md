Of course! Here's a clean, well-structured `NOTES.md` you can copy-paste into your `level01/resources/` folder (or wherever you're keeping your notes):

---

```markdown
# 📒 NOTES.md — SUID (Set User ID)

## 🔍 What is SUID?

SUID (Set User ID) is a special file permission in Linux that allows a user to execute a file **with the permissions of the file’s owner**, instead of the user who runs it.

---

## 📄 Example:

```bash
ls -l /usr/bin/sudo
-rwsr-xr-x 2 root root 69708 Mar 12  2015 /usr/bin/sudo
```

### Breakdown:
- `rws` in the **owner** section (instead of `rwx`)
- The `s` means the **SUID bit is set**
- Owner is `root`, so:
  - When **any user** runs this file, it is executed **as root**

---

## ⚠️ Why is this dangerous?

If a binary with SUID:
- Executes commands (especially via `system()`)
- Has insecure path handling (uses `$PATH`)
- Allows user input in unsafe ways

... then a regular user may be able to **escalate to root**.

---

## 🧰 How to find SUID binaries:

```bash
find / -perm -4000 -type f 2>/dev/null
```

This command finds all SUID binaries (4000 = SUID bit) on the system.

---

## 🧹 How to remove SUID (if root):

```bash
chmod u-s /path/to/file
```

---

## 🧪 Real-world attack example:

1. A SUID binary calls `system("cat /some/file")`
2. Attacker creates a fake `cat` in a directory they control
3. Changes `$PATH` to use that directory first
4. Executes the binary
5. The fake `cat` is run **as root**

---

## ✅ Quick Reference

| Symbol | Meaning                                 |
|--------|------------------------------------------|
| `s`    | SUID is set **and** executable (good)    |
| `S`    | SUID is set but **not** executable (broken) |


https://kea.nu/files/textbooks/humblesec/linuxbasicsforhackers.pdf
