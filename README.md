# uv-k5-firmware

this firmware is an early work in progress!!!

my goals with this are to just go back and do it from scratch, hopefully more "properly" this time around,
removing all of those useless to "us hams" features like PTT-ID

i also want to improve the UI/UX uh we'll see how that goes

shoutouts to all the people involved in the quansheng scene!!!

# building

if you use Nix then `nix develop`, if you don't then uh uhm

then:
```
meson setup --cross-file meson_cross.ini build/
meson compile -C build/
# flashing:
k5prog -v -YYY -F -b build/main.bin
```
