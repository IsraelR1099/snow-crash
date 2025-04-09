```markdown
# 🧩 Snow Crash — Level01

## 🧠 Objective

Find the **flag01** password using the information and tools available as the `level01` user.

---

## 🔍 Recon

### 🔸 Checked system user credentials

To check for interesting users or password hints:

```bash
cat /etc/passwd
cat /etc/shadow
```

Found this line in `/etc/shadow`:

```
flag01:42hDRfypTqqnw:3001:3001::/home/flag/flag01:/bin/bash
```

The second field (`42hDRfypTqqnw`) is a **13-character password hash** — a strong clue that this is a classic **DES-crypt** hash.

---

## 🔐 Cracking the password hash

This type of hash (13 characters, no `$` prefix) is a **legacy Unix DES-based hash**, which can be cracked with **John the Ripper**.

### Step-by-step:

#### 1. Save the hash to a file

```bash
echo 'flag01:42hDRfypTqqnw' > flag01.hash
```

#### 2. Run John the Ripper

```bash
john flag01.hash
```

Wait a few seconds... and eventually:

```bash
Loaded 1 password hash (descrypt, traditional crypt(3) [DES 128/128 SSE2-16])
Will run 12 OpenMP threads
Press 'q' or Ctrl-C to abort, almost any other key for status
abcdefg          (flag01)
1g 0:00:00:00 100% 2/3 20.00g/s 995480p/s 995480c/s 995480C/s 123456..lucky0
Use the "--show" option to display all of the cracked passwords reliably
Session completed
```

✅ The password is: `abcdefg`

#### 3. Show cracked passwords (optional)

```bash
john --show flag01.hash
```

---

## 🏁 Conclusion

We found that `flag01`'s password was stored as a DES-crypt hash in `/etc/shadow`.  
By recognizing the format and using **John the Ripper**, we were able to crack it successfully.

---

## 📌 Useful commands recap

```bash
# View users and password hashes
cat /etc/passwd
cat /etc/shadow

# Save the hash to a file
echo 'flag01:42hDRfypTqqnw' > flag01.hash

# Crack with John
john flag01.hash

# Display cracked passwords
john --show flag01.hash
