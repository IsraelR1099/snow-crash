```markdown
# Snow Crash - Level 02 Solution

## 📄 Description

In this level, we are provided with a `level02.pcap` file located in the home directory. The goal is to retrieve the password for the next level by analyzing this network capture.

---

## 🔍 Approach

### 1. Initial Recon

To get a quick sense of the contents inside the `.pcap` file, I used the `strings` command:

```bash
strings level02.pcap | grep -iE 'login|password|flag'
```

This revealed some interesting plaintext strings such as:

```
wwwbugs login:
Password:
Login incorrect
```

Which hinted that the pcap contains a session capturing someone logging into a system.

---

### 2. Deep Dive with tcpdump

I used `tcpdump` to inspect the raw packet contents:

```bash
tcpdump -nn -X -r level02.pcap | less
```

I manually scanned for the packets around the keyword `Password:` and noticed that **each typed character was being sent in a separate TCP packet** — likely from a telnet session or similar.

Each relevant packet ends with a single ASCII character (hex-encoded). These characters together form the password.

---

### 3. Extracting the Password

While scanning manually worked, some characters appeared wrong at first. For example, I initially got:

```
ft_wandrNDRelLOL
```

But this did not work. After inspecting the hex dump more carefully (especially converting hex to ASCII using `xxd` or `tshark`), I found the correct password:

```
ft_waNDReL0L
```

**The difference was in case sensitivity and a `0` instead of `O`.**

## 🔑 Final Password

```
ft_waNDReL0L
```

You can now use this password to move to the next level in Snow Crash.
