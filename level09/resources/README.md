```markdown
# Snow Crash - Level09 Walkthrough

## 🔐 Level Description

Upon logging into `level09`, we’re presented with the following files:

```bash
level09@SnowCrash:~$ ls
level09  token
```

- `level09`: A binary executable with **setuid** permissions for `flag09`.
- `token`: A file that is **world-readable**, but its content is encrypted.

---

## 📦 Binary Behavior

Running the binary with an argument shows transformed output:

```bash
level09@SnowCrash:~$ ./level09 hello
hfnos
```

Running it with the contents of the `token` file yields unreadable characters:

```bash
level09@SnowCrash:~$ ./level09 `cat token`
f5mpq;v�E��{�{��TS�W�����
```

This indicates that the binary encrypts its input using a **custom algorithm**, and the `token` contains **pre-encrypted** content. Our task is to **reverse this encryption**.

---

## 🧠 Decryption Strategy

After reverse-engineering the binary, we identified that it encrypts each character by **adding its index** to it. To decrypt it, we need to **subtract the index** from each character in the string.

---

## ⚙️ Preparing the Decryption Program

### 1. Create `decrypt.c` on your host machine:

```c
#include <stdio.h>

int main(int argc, char **argv)
{
    char *encrypt;
    int i;

    if (argc != 2)
    {
        printf("Usage: %s <token>\n", argv[0]);
        return (1);
    }

    encrypt = argv[1];
    i = 0;
    while (encrypt[i])
    {
        encrypt[i] = encrypt[i] - i;
        i++;
    }

    printf("Decrypted string: %s\n", encrypt);
    return (0);
}
```

### 2. Copy `decrypt.c` to the Snow Crash virtual machine using `scp`:

```bash
scp -P 4242 decrypt.c level09@[IP_SNOW_CRASH]:/tmp
```

- Replace `[IP_SNOW_CRASH]` with the IP address of your Snow Crash machine.
- `-P 4242` specifies the custom port used by Snow Crash.

### 3. SSH into the Snow Crash machine and navigate to `/tmp`:

```bash
ssh -p 4242 level09@[IP_SNOW_CRASH]
cd /tmp
```

### 4. Compile the decryption program inside `/tmp`:

```bash
gcc decrypt.c -o decrypt
```

Now you have an executable `/tmp/decrypt`.

---

## ✅ Decrypting the Token

Run the decryption program using the contents of the `token`:

```bash
level09@SnowCrash:/tmp$ ./decrypt `cat /home/user/level09/token`
Decrypted string: f3iji1ju5yuevaus41q1afiuq
```

---

## 🏁 Final Step

Use the decrypted token to switch to `flag09` and retrieve the flag:

```bash
level09@SnowCrash:~$ su flag09
Password:
Don't forget to launch getflag !
flag09@SnowCrash:~$ getflag
Check flag.Here is your token : s5cAJpM8ev6XHw998pRWG728z
```

---

## 🧩 Summary

- Read the encrypted token directly.
- Reverse-engineered a custom index-based encryption.
- Wrote a C program to decrypt the token.
- Used `scp` to copy the file into the VM and compiled it inside `/tmp`.
- Used the decrypted token to switch user and retrieve the final flag.

---
