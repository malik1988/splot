# nanogui 

[source](https://github.com/mitsuba-renderer/nanogui)

```bash
git clone --cursive https://github.com/mitsuba-renderer/nanogui
```

## Note!

if `Clang` is used ,nanogui will try to set "libc++" for cmake, but splot did not .
This will cause c++ ABI incompatible. So comment lines under:
`Prefer libc++ in conjunction with Clang`.