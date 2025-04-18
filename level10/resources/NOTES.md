
```markdown
# Snow Crash - Level10 Notes

## 🧠 Things I Learned

- **TOCTOU Vulnerability**:  
  A classic security bug where a file is checked for permissions (TOC) but used (TOU) later without rechecking, allowing attackers to change the file in between.

- **Netcat Usage**:
  - Listen on a specific port with `nc -lk [port]`.
  - Useful for setting up servers in simple exploitation tasks.

- **Symlink Switching Technique**:
  - `ln -sf [target] [link]` creates/updates a symlink.
  - Switching between a fake file and the real file very fast can bypass permission checks.

- **Automating Exploits**:
  - Using infinite loops (`while true`) is essential in timing attacks.

## 🛠️ Useful Commands I Used

- `jobs -l`  
  List running background jobs and their process IDs.

- `kill %[job_number]`  
  Kill a background job by its job number.

- `ln -sf`  
  Force update a symbolic link.

- `nc -lk 6969`  
  Listen indefinitely for incoming connections on port 6969.

- `ltrace ./binary`  
  Trace library calls (like `access()` and `connect()`).

- `strings binary`  
  List printable strings in a binary, useful to find hidden information like ports or error messages.
