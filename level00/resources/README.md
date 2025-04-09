```markdown
# 🧩 Snow Crash — Level00

## 🧠 Objective

Find the **flag00** password using the information and tools available as the `level00` user.

---

## 🔍 Recon

### 🔸 Checked existing users and groups

To understand the system's structure:

```bash
cat /etc/passwd
cat /etc/shadow
cat /etc/group
```

Noticed the user `flag00` exists — this is likely the target.

---

## 🕵️ Search for SUID binaries owned by `flag00`

The `find` command is useful for discovering files that may run with elevated privileges.

### Initial attempts:

```bash
find / -user flag00 -perm 4000
```

This looks for files **owned by flag00** with the **SUID bit set** (`4000`).  
Didn't show useful output due to permission errors.

### Final working command:

```bash
find / -user flag00 2>/dev/null
```

This command ignores permission errors and shows:

```bash
/usr/sbin/john
/rofs/usr/sbin/john
```

---

## 📂 Investigated the binary

```bash
cat /usr/sbin/john
```

Output:

```
cdiiddwpgswtgt
```

Suspicious — possibly a **password encoded** in some way.

---

## 🧪 Decryption hypothesis

Looks like a Caesar cipher (simple character shift).

After testing different shifts manually or using tools, it turns out the text is encoded with a **Caesar cipher with a shift of 11**.

To decode:

```bash
cat /usr/sbin/john | tr 'a-zA-Z' 'l-za-kL-ZA-K'
```

Result:

```
nottohardhere
```

✅ This is the password (the flag).

---

## 🏁 Conclusion

The file `/usr/sbin/john` was a SUID binary owned by `flag00`.
Instead of being an executable, it directly stored the encoded password using a Caesar cipher with a **shift of 11**.

---

## 📌 Useful commands recap

```bash
# Find files owned by a user (suppress permission errors)
find / -user flag00 2>/dev/null

# Decode Caesar cipher with shift 11
echo cdiiddwpgswtgt | tr 'a-zA-Z' 'l-za-kL-ZA-K'
